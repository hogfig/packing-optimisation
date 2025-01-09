import csv
import matplotlib.pyplot as plt
from matplotlib import style
import pandas as pd
import sys

style.use('fivethirtyeight')
fig = plt.figure()
ax = fig.add_subplot(1,1,1)

def animate():
    filePath = sys.argv[1]

    with open(filePath) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        count = 0;
        for row in csv_reader:
            if(row):
                circle_patch = plt.Circle((float(row[0]), float(row[1])), float(row[2]), color=row[-1])
                circle_patch.fill = False
                ax.add_patch(circle_patch)
                ax.plot()

animate()
plt.show()