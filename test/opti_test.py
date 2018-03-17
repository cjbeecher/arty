import pandas
from matplotlib import pyplot as plt
pandas.set_option('display.width', 5000)


data = pandas.read_csv('test/data.csv', header=None)
columns = {i: 'dw_{0}'.format(i) if i % 2 == 1 else 'slope_{0}'.format(i) for i in range(1, len(data.columns)+1)}
columns[0] = 'w'
data = data.rename(columns=columns)

data = data.sort_values(by='w').set_index('w')

for i in range(1, len(data.columns), 2):
	data[[columns[i], columns[i+1]]].plot()
	plt.draw()
plt.show()

print(data[:10])

