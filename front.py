from subprocess import Popen, PIPE
import matplotlib.pyplot as plt


p = Popen(['backend.exe'], stdin=PIPE, stdout=PIPE)
plt.ion()
plt.rcParams['figure.figsize'] = (10, 8)
i = 0

while True:
    plt.clf()
    plt.xlim(-100, 1100)
    plt.ylim(-100, 900)
    artists = []
    labels = []

    infected = p.stdout.readline().decode('ascii')
    infected = infected[:-3].split('_')
    infected_x = [int(x) for x in infected[0::2]]
    infected_y = [int(y) for y in infected[1::2]]
    artists.append(plt.scatter(infected_x, infected_y, c='red', s=1.2))
    labels.append('Infected: ' + str(len(infected_x)))

    death = p.stdout.readline().decode('ascii')
    if len(death) > 3:
        death = death[:-3].split('_')
        death_x = [int(x) for x in death[0::2]]
        death_y = [int(y) for y in death[1::2]]
        artists.append(plt.scatter(death_x, death_y, c='purple', s=1.2))
        labels.append('Death: ' + str(len(death_x)))

    healthy = p.stdout.readline().decode('ascii')
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
    
p.terminate()
