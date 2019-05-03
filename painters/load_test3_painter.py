import pandas as pd
import matplotlib.pyplot as plt

file = open('test_results/load_test3_result.txt', 'r')
file.readline()

values = file.readline()[0:-2].split(' ')

avg_values = dict()

for heap in 'Binomial', 'Fibonacci':
	for i in range(4):
		file.readline()
	avg_values[heap] = (file.readline()[5:-2].split(' '))

df = pd.DataFrame(index=values, data=avg_values)
df = df.astype(float)

df.plot(grid=True)
plt.xlabel('Operations count')
plt.ylabel('Time (second)')
plt.title('merge(other_heap) operation test')

plt.savefig('graphics/load_test3_result.png')
