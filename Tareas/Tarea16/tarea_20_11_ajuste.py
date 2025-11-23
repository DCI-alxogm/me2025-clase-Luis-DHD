# -*- coding: utf-8 -*-
"""
Created on Thu Nov 20 23:06:09 2025

@author: luisd
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import minimize

#Definir los modelos
#Peleg
def modelo1(aw, b):
    b0, b1, b2, b3 = b
    return b0 * (aw ** b1) + b2 * (aw ** b3)
#DLP
def modelo2(aw, b):
    b0, b1, b2, b3 = b
    aw = np.clip(aw, 1e-6, 1-1e-6)  
    x = np.log(-np.log(aw))
    return b0 + b1*x + b2*(x**2) + b3*(x**3)

#Chi cuadrada
def chi2_modelo1(b, aw, Xe):
    Xe_pred = modelo1(aw, b)
    return np.sum((Xe - Xe_pred) ** 2)

def chi2_modelo2(b, aw, Xe):
    Xe_pred = modelo2(aw, b)
    return np.sum((Xe - Xe_pred) ** 2)

#Encontrar los parámetros
def ajustar_con_minimize(aw, Xe, nombre):
    resultados = {}
    
    #  Para el modelo 1 
    b0_init = [1.0, 1.0, 1.0, 1.0] # valores iniciales
    res1 = minimize(chi2_modelo1, b0_init,args=(aw, Xe), method='Nelder-Mead', options={'maxiter': 10000, 'disp': False}
    )
    resultados['modelo1'] = {
        'b': res1.x,
        'chi2': res1.fun,
        'success': res1.success
    }
    
    # Para el modelo 2 
    b0_init = [1.0, 0.1, 0.01, 0.001]  # valores iniciales más suaves para polinomio
    res2 = minimize(chi2_modelo2, b0_init, args=(aw, Xe), method='Nelder-Mead',options={'maxiter': 10000, 'disp': False}
    )
    resultados['modelo2'] = {
        'b': res2.x,
        'chi2': res2.fun,
        'success': res2.success
    }
    
    # Imprimir resultados
    b1 = resultados['modelo1']['b']
    b2 = resultados['modelo2']['b']
    print(f"{nombre:<35} | (b0={b1[0]:.4f}, b1={b1[1]:.4f}, b2={b1[2]:.4f}, b3={b1[3]:.4f})")
    print(f"{'':<35} | (b0={b2[0]:.4f}, b1={b2[1]:.4f}, b2={b2[2]:.4f}, b3={b2[3]:.4f})")
    print("-" * 100)
    
    return resultados

#Graficar y ajustar
print("="*100)
print("AJUSTE POR CHI CUADRADA")
print("="*100)

# Lista de archivos
archivos = [
    ("roasted_25.dat", "Roasted beans (25°C)"),
    ("roasted_35.dat", "Roasted beans (35°C)"),
    ("roasted_45.dat", "Roasted beans (45°C)"),
    ("medium_25.dat", "Medium grind (25°C)"),
    ("medium_35.dat", "Medium grind (35°C)"),
    ("medium_45.dat", "Medium grind (45°C)"),
    ("fine_25.dat", "Fine grind (25°C)"),
    ("fine_35.dat", "Fine grind (35°C)"),
    ("fine_45.dat", "Fine grind (45°C)")
]

# Guardar todos los resultados 
todos_resultados = {}

# Figura para graficar
fig, axes = plt.subplots(3, 3, figsize=(18, 12))
fig.suptitle('Ajuste de modelos: Experimental vs Predicción', fontsize=16)

# Procesar cada archivo
for i, (archivo, nombre) in enumerate(archivos):
    # Cargar datos
    data = np.loadtxt(archivo, skiprows=1).T
    aw = data[1]   # columna 1: aw
    Xe = data[3]   # columna 3: Xe (% d.b.)
    
    # Ajustar modelos
    res = ajustar_con_minimize(aw, Xe, nombre)
    todos_resultados[nombre] = res
    
    # Graficar
    row, col = divmod(i, 3)
    ax = axes[row, col]
    
    # Datos experimentales
    ax.scatter(aw, Xe, color='black', s=40, marker='s', label='Experimental', zorder=5)
    
    # Modelo 1
    b1 = res['modelo1']['b']
    aw_fit = np.linspace(aw.min(), aw.max(), 300)
    Xe_fit1 = modelo1(aw_fit, b1)
    ax.plot(aw_fit, Xe_fit1, '--', color='blue', 
            label=f'Modelo 1\nChi2={res["modelo1"]["chi2"]:.4f}')
    
    # Modelo 2
    b2 = res['modelo2']['b']
    Xe_fit2 = modelo2(aw_fit, b2)
    ax.plot(aw_fit, Xe_fit2, '-', color='red', 
            label=f'Modelo 2\nChi2={res["modelo2"]["chi2"]:.4f}')
    
    ax.set_xlabel('$a_w$')
    ax.set_ylabel('$X_e$ (% d.b.)')
    ax.set_title(nombre, fontsize=12)
    ax.grid(True, linestyle=':', alpha=0.6)
    ax.legend(fontsize=9)

plt.tight_layout(rect=[0, 0, 1, 0.96])
plt.savefig('ajustes_minimize.png', dpi=150, bbox_inches='tight')
plt.show()

#Determinar el mejor modelo para cada caso
print("\n" + "="*60)
print("El mejor modelo es:")
print("="*60)
for nombre, res in todos_resultados.items():
    chi1 = res['modelo1']['chi2']
    chi2 = res['modelo2']['chi2']
    mejor = "Modelo 1" if chi1 < chi2 else "Modelo 2"
    print(f"{nombre:<30} -> Mejor: {mejor} (Chi2_M1={chi1:.6f}, Chi2_M2={chi2:.6f})")