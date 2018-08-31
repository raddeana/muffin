# -*- coding: utf-8 -*-
import numpy as np
from matplotlib import pyplot as plt

plt.rcParams['savefig.dpi'] = 300
plt.rcParams['figure.dpi'] = 300

colours = ["#348ABD", "#A60628"]

prior = [1/20., 20/21.]             # 图书管理员和农民的先验概率分别是 1/20 和 20/21
posterior = [0.087, 1-0.087]        # 后验概率
plt.bar([0, .7], prior, alpha=0.70, width=0.25,
        color=colours[0], label="prior distribution",
        lw="3", edgecolor=colours[0])

plt.bar([0 + 0.25, .7 + 0.25], posterior, alpha=0.7,
        width=0.25, color=colours[1],
        label="posterior distribution",
        lw="3", edgecolor=colours[1])


plt.ylim(0, 1)
plt.xticks([0.20, 0.95], ['Librarian', 'Farmer'])
plt.title("Prior and Posterior probability of Steve's occupation")
plt.ylabel("Probability")
plt.legend(loc="upper left")

plt.show()
