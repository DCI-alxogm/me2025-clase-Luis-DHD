# -*- coding: utf-8 -*-
"""
Created on Sat Nov 22 11:30:53 2025

@author: luisd
"""
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
# %%
#cargar datos
roasted_25=np.loadtxt("roasted_25.dat",skiprows=1).T
roasted_35=np.loadtxt("roasted_35.dat").T
roasted_45=np.loadtxt("roasted_45.dat").T
medium_25=np.loadtxt("medium_25.dat").T
medium_35=np.loadtxt("medium_35.dat").T
medium_45=np.loadtxt("medium_45.dat").T
fine_25=np.loadtxt("fine_25.dat").T
fine_35=np.loadtxt("fine_35.dat").T
fine_45=np.loadtxt("fine_45.dat").T
# %%


# Graficar a)#
plt.figure(figsize=(12, 7))
#plt.plot(datos[0],datos[1], label="f(x)", color='blue', linewidth=2)
plt.plot(roasted_25[1], roasted_25[3], 's', label='Experimental (25°C)', color='orange')
plt.plot(roasted_35[1], roasted_35[3], 's', label='Experimental (35°C)', color='magenta')
plt.plot(roasted_45[1], roasted_45[3], 's', label='Experimental (45°C)', color='darkred')
plt.xlabel('a_w')
plt.ylabel('X_e(%d.b.)')
plt.title('Roasted beans')
plt.legend()
# %%
# Graficar b)#
plt.figure(figsize=(12, 7))
#plt.plot(datos[0],datos[1], label="f(x)", color='blue', linewidth=2)
plt.plot(medium_25[1], medium_25[3], 's', label='Experimental (25°C)', color='yellow')
plt.plot(medium_35[1], medium_35[3], 's', label='Experimental (35°C)', color='orange')
plt.plot(medium_45[1], medium_45[3], 's', label='Experimental (45°C)', color='magenta')
plt.xlabel('a_w')
plt.ylabel('X_e(%d.b.)')
plt.title('Ground roasted medium size')
plt.legend()
# %%
# Graficar c)#
plt.figure(figsize=(12, 7))
#plt.plot(datos[0],datos[1], label="f(x)", color='blue', linewidth=2)
plt.plot(fine_25[1], fine_25[3], 's', label='Experimental (25°C)', color='palegreen')
plt.plot(fine_35[1], fine_35[3], 's', label='Experimental (35°C)', color='turquoise')
plt.plot(fine_45[1], fine_45[3], 's', label='Experimental (45°C)', color='darkslategray')
plt.xlabel('a_w')
plt.ylabel('X_e(%d.b.)')
plt.title('Ground roasted fine size')
plt.legend()