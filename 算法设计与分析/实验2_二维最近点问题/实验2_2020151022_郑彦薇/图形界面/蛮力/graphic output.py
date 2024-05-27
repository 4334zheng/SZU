import matplotlib.pyplot as plt
import numpy as np
import random

a = range(0, 20, 1)
x = random.sample(a, 10)
y = random.sample(a, 10)

for i in range(len(x)-1):
    for j in range(i+1, len(x)):
        plt.plot([x[i], x[j]], [y[i], y[j]], color='red')
        plt.scatter(x, y, color='blue')
        plt.show()