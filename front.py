from subprocess import Popen, PIPE
import matplotlib.pyplot as plt

COUGHT_MARGIN = 0.1
PROGRESS_RATE = 0.02
TRANSFER_PROB = 0.1
MASKED_RATIO = 0.4
JUMP_PROB = 0.002

MAP_SIZE = 800
POPULATION_SIZE = 5000
RANGE = 4

CORPSE_HANDLE = 1
AIRBRONE = 1
RANDOM_PROGRESS = 1

params = [COUGHT_MARGIN, PROGRESS_RATE, TRANSFER_PROB, MASKED_RATIO, JUMP_PROB, MAP_SIZE, 
          POPULATION_SIZE, RANGE, CORPSE_HANDLE, AIRBRONE, RANDOM_PROGRESS]
command = ['backend.exe'] + [str(p) for p in params]

p = Popen(command, stdin=PIPE, stdout=PIPE)
plt.ion()
plt.rcParams['figure.figsize'] = (10, 8)
i = 0

infected_num = []
death_num = []
while True:
    plt.clf()
    plt.xlim(-100, 1100)
    plt.ylim(-100, 900)
    artists = []
    labels = []

    infected = p.stdout.readline().decode('ascii')
    if len(infected) > 3:
        infected = infected[:-3].split('_')
        infected_x = [int(x) for x in infected[0::2]]
        infected_y = [int(y) for y in infected[1::2]]
        artists.append(plt.scatter(infected_x, infected_y, c='red', s=1.2))
        labels.append('Infected: ' + str(len(infected_x)))
        infected_num.append(len(infected_x))
    else:
        infected_num.append(0)

    death = p.stdout.readline().decode('ascii')
    if len(death) > 3:
        death = death[:-3].split('_')
        death_x = [int(x) for x in death[0::2]]
        death_y = [int(y) for y in death[1::2]]
        artists.append(plt.scatter(death_x, death_y, c='purple', s=1.2))
        labels.append('Death: ' + str(len(death_x)))
        death_num.append(len(death_x))
    else:
        death_num.append(0)

    healthy = p.stdout.readline().decode('ascii')
    if len(healthy) > 3:
        healthy = healthy[:-3].split('_')
        healthy_x = [int(x) for x in healthy[0::2]]
        healthy_y = [int(y) for y in healthy[1::2]]
        artists.append(plt.scatter(healthy_x, healthy_y, c='green', s=1.2))
        labels.append('Healthy: ' + str(len(healthy_x)))

    i += 1
    p.stdin.write(b'\x00')
    p.stdin.flush()
    plt.legend(artists, labels, loc='right', fontsize='medium')
    plt.title('Iteration ' + str(i))
    plt.draw()
    stay = plt.waitforbuttonpress()
    if not stay:
        break


plt.clf()
line1, = plt.plot(infected_num, c='red')
line2, = plt.plot(death_num, c='purple')
plt.legend([line1, line2], ['Infected', 'Death'], loc='upper left', fontsize='medium')
plt.title('Plague Statistics')
plt.draw()
p.terminate()
plt.waitforbuttonpress()
print('Program Ended')
