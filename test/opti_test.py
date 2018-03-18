import pandas
from matplotlib import pyplot as plt
pandas.set_option('display.width', 5000)


data = pandas.read_csv('test/data.csv', header=None)
columns = {}
for i in range(0, len(data.columns), 3):
	columns[i] = 'w_{0}'.format(i)
for i in range(1, len(data.columns), 3):
	columns[i] = 'O_{0}'.format(i)
for i in range(2, len(data.columns), 3):
	columns[i] = 's_{0}'.format(i)
data = data.rename(columns=columns)
# data = data[list(data.columns)[:len(data.columns)-6]]

for i in range(0, len(data.columns), 3):
	data[[columns[i], columns[i+1], columns[i+2]]].plot(x=columns[i], y=[columns[i+1], columns[i+2]])
	plt.draw()
plt.show()

print(data[:10])

