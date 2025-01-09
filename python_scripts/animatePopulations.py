import csv
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
import pandas as pd

style.use('fivethirtyeight')
fig = plt.figure()
ax = fig.add_subplot(1,1,1)

def animate(i):
    with open('/Users/robertjelic/Documents/C++/Ellipses/tests/EATests/CSV_Files/highest_fitness_geometry.txt') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        count = 0;
        for row in csv_reader:
            if(row):
                circle_patch = plt.Circle((float(row[0]), float(row[1])), float(row[2]), color=row[-1])
                circle_patch.fill = False
                ax.add_patch(circle_patch)
            else:
                plt.title(count)
                ax.plot()
                plt.pause(2)
                ax.clear()
                count+=1
        ax.plot()
        plt.pause(2)
        ax.clear()

ani = animation.FuncAnimation(fig, animate, interval=2000, cache_frame_data=False)
plt.show()