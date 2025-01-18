import csv
import matplotlib.pyplot as plt
import sys
from scipy.signal import lfilter

def main():
    filePath = sys.argv[1]
    
    with open(filePath) as csv_file:
        plotArray = []
        x = []
        csv_reader = csv.reader(csv_file, delimiter=',')
        x_count = 1
        for row in csv_reader:
            if(row):
                plotArray.append(float(row[0]))
                x.append(x_count)
                x_count += 1
        n = 100  # the larger n is, the smoother curve will be
        b = [1.0 / n] * n
        a = 1
        yy = lfilter(b, a, plotArray)
        plt.plot(x, plotArray)
        plt.plot(x, yy, linewidth=2, linestyle="-", c="r")
        plt.show()


main()