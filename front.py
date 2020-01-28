from subprocess import Popen, PIPE
import os
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation


p = Popen(['a.exe'], stdin=PIPE, stdout=PIPE)
plt.ion()

try:
    while True:
        infected = p.stdout.readline().decode('ascii')
        infected = infected[:-3].split('_')
        infected_x = [int(x) for x in infected[0::2]]
        infected_y = [int(y) for y in infected[1::2]]
        healthy = p.stdout.readline().decode('ascii')
        healthy = healthy[:-3].split('_')
        healthy_x = [int(x) for x in healthy[0::2]]
        healthy_y = [int(y) for y in healthy[1::2]]
        p.stdin.write(b'\x00')
        p.stdin.flush()
        plt.scatter(infected_x, infected_y, c='red', s=0.8)
        plt.scatter(healthy_x, healthy_y, c='green', s=0.8)
        plt.draw()
        plt.waitforbuttonpress()
        plt.clf()
except KeyboardInterrupt:
    pass

