import matplotlib.pyplot as plt
import math
with open('data.txt', 'r') as f:
    data = f.readlines()
delays = [float(value) for value in data]
plt.plot(delays)
plt.show()
ipdv99 = delays[math.ceil((len(delays) - 1)*0.99)] - delays[0]  # from swus
print("IPDV99: {}".format(ipdv99))
ipdv95 = delays[math.ceil((len(delays) - 1) * 0.95)] - delays[0]
print("IPDV95: {}".format(ipdv95))

fig, ax = plt.subplots()
data = ax.hist(delays)

ax.plot([ipdv95 + delays[0], ipdv95 + delays[0]], [0.95*max(data[0]), 0], color='red')
ax.text((ipdv95 + delays[0])*0.9, max(data[0]), "centyl 95")
ax.plot([ipdv99 + delays[0], ipdv99 + delays[0]], [0.9*max(data[0]), 0], color='green')
ax.text((ipdv99 + delays[0])*0.9, max(data[0])*0.95, "centyl 99")
ax.set_xlabel('Delay.')
ax.set_ylabel('Number of occurrences.')
plt.show()
