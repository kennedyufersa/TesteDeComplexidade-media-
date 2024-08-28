import numpy as np
import matplotlib.pyplot as plt

x = np.loadtxt('tamanhos.txt')
y = np.loadtxt('tempos.txt')  

# Ajuste de escala
escalaX = 0.001;
escalaY = 100;
lX = len(x);

x = x * escalaX
y = y * escalaY
a = 1
b = 1
d = 0.000001
histE = []
E = 10^5;
Ea = 0;
cont = 0;
while abs(E-Ea)/E > 0.01:
    Ea = E;
    E = np.sum((y - b - a * x) ** 2) / lX
    a = a - d * np.sum((y - b - a * x) * (-x))
    b = b - d * np.sum((y - b - a * x) * (-1))
    histE.append(E)
    cont = cont + 1
    if cont%10 == 0:
        print('Cont: ', cont);
        print('Erro: ', E);


plt.figure(figsize=(10, 5))
plt.subplot(1, 2, 1)
plt.plot(x, y/escalaY, 'o', label='Dados originais')
plt.plot(x, (a * x + b)/escalaY, 'r', label='Linha Ajustada')
plt.xlabel('Tamanhos (em mil unidades)')
plt.ylabel('Tempos (s)')
plt.title('Gráfico de Tamanhos vs Tempos')
plt.legend()

plt.subplot(1, 2, 2)
plt.plot(histE, label='Erro')
plt.xlabel('Iterações')
plt.ylabel('Erro')
plt.title('Histórico de Erros (Erro Final < 10e-8)')
plt.legend()

plt.tight_layout()
plt.show()