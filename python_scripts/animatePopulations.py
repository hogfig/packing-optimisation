import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import csv
import sys 

def read_circle_data(file_path):
    batches = []
    current_batch = []

    with open(file_path, 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            if not row:  # Empty line indicates a new batch
                if current_batch:
                    batches.append(current_batch)
                    current_batch = []
            else:
                x, y, radius, color = row
                current_batch.append((float(x), float(y), float(radius), color))

        if current_batch:  # Add the last batch if the file doesn't end with an empty line
            batches.append(current_batch)

    return batches

def update(frame, batches, ax):
    batch = batches[frame]
    ax.clear()
    ax.set_xlim(-10, 10)
    ax.set_ylim(-10, 10)
    
    for circle in batch:
        x, y, radius, color = circle
        circle_patch = plt.Circle((x, y), radius, color=color, alpha=0.5)
        ax.add_patch(circle_patch)
    ax.set_title(f"Batch {frame + 1}")

def main():
    # File path to the CSV file
    file_path = sys.argv[1]

    # Read the circle data from the CSV file
    batches = read_circle_data(file_path)

    # Set up the figure and axis for the animation
    fig, ax = plt.subplots()
    ax.set_xlim(-10, 10)
    ax.set_ylim(-10, 10)

    # Create the animation
    num_batches = len(batches)
    ani = FuncAnimation(fig, update, frames=num_batches, fargs=(batches, ax), interval=1000, repeat=True)

    # Display the animation
    plt.show()

if __name__ == "__main__":
    main()
