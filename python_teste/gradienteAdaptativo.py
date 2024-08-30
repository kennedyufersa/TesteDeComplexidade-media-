import numpy as np
import matplotlib.pyplot as plt

def fun(a,b,c,x):
    return a*x + b
def dFunA(a,b,c,x):
    return -x
def dFunB(a,b,c,x):
    return -1
def dFunC(a,b,c,x):
    return -1

x = np.loadtxt('tamanhos.txt')
y = np.loadtxt('tempos.txt')  

# Ajuste de escala
escalaX = 0.001;
escalaY = 100;
# escalaX =1;
# escalaY =1;
lX = len(x);

x = x * escalaX
y = y * escalaY
a = 1
b = 1
c = 1
d = 0.000001
histE = []
E = 10^5;
Ea = 0;
cont = 0;
theta = 10^-8;
epsilon = 0.00001
while abs(E-Ea)/E > 0.01:
    Ea = E;
    E = np.sum((y - fun(a,b,c,x)) ** 2) / lX
    r = np.sqrt(E);
    dA = epsilon*np.sum((y - fun(a,b,c,x)) * (dFunA(a,b,c,x)))/(theta + r);
    dB = epsilon*np.sum((y - fun(a,b,c,x)) * (dFunB(a,b,c,x)))/(theta + r);
    a = a - dA
    b = b - dB
    # b = b - d * np.sum((y - fun(a,b,c,x)) * (dFunC(a,b,c,x)))
    histE.append(E)
    cont = cont + 1
    # if cont%10 == 0:
    #     print('Cont: ', cont);
    #     print('Erro: ', E);
plt.figure(figsize=(10, 5))
plt.subplot(1, 2, 1)
plt.plot(x, y/escalaY, 'o', label='Dados originais')
plt.plot(x, fun(a,b,c,x)/escalaY, 'r', label='Linha Ajustada')
plt.xlabel('Tamanhos (em mil unidades)')
plt.ylabel('Tempos (s)')
plt.title('Gráfico de Tamanhos vs Tempos')
plt.legend()

plt.subplot(1, 2, 2)
plt.plot(histE, label='Erro')
plt.xlabel('Iterações')
plt.ylabel('Erro')
plt.title('Histórico de Erros (Variação de Erro < 10e-3)')
plt.legend()

plt.tight_layout()
plt.show()
print(a,b)

# AdaGrad - Ref.: https://medium.com/@ieeecisunb/algoritmos-de-otimiza%C3%A7%C3%A3o-com-taxa-de-aprendizado-adaptativa-31fe2874e066