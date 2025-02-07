import csv
import matplotlib.pyplot as plt
import sys

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

        fig, ax = plt.subplots()
        ax.set_xlabel("Number of iteration")
        ax.set_ylabel("Fitness score of population")
        plt.plot(x, plotArray)
        plt.show()


main()