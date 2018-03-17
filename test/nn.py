import numpy as np


def sig(x):
	return 1.0 / (1.0 + np.exp(-1.0 * x))

weights = [np.matrix([
	[0.901082, 0.768242],
	[-0.333797, 0.851613]
]),
np.matrix([
	[-0.916815],
	[0.609679]
])
]

inp = np.matrix([
	[10.123456, 4.123456],
	[2.16, 5.123456],
	[3.13456, 6.123456],
	[4.0, 5.0]
])

sig = np.vectorize(sig)

output = inp * weights[0]
output = sig(output)
output = output * weights[1]

print(output)

