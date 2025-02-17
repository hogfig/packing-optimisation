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

        if current_batch:
            batches.append(current_batch)

    return batches

def update(frame):
    batch = batches[frame]
    ax.clear()
    ax.set_xlim(-10, 10)
    ax.set_ylim(-10, 10)

    for circle in batch:
        x, y, radius, color = circle
        circle_patch = plt.Circle((x, y), radius, color=color, alpha=0.5)
        ax.add_patch(circle_patch)
    
    ax.set_title(f"Batch {frame + 1}")

def toggle_animation(event):
    """Pause or resume animation on key press."""
    global anim_running
    if event.key == " ":
        if anim_running:
            ani.pause()  # Pause the animation
        else:
            ani.resume()  # Resume the animation
        anim_running = not anim_running

def main():
    global ani, anim_running, batches, ax

    file_path = sys.argv[1]
    batches = read_circle_data(file_path)

    fig, ax = plt.subplots()
    ax.set_xlim(-10, 10)
    ax.set_ylim(-10, 10)

    num_batches = len(batches)
    ani = FuncAnimation(fig, update, frames=num_batches, interval=1000, repeat=True)

    # Initialize animation state
    anim_running = True

    # Connect key press event (Spacebar to pause/resume)
    fig.canvas.mpl_connect("key_press_event", toggle_animation)

    plt.show()

if __name__ == "__main__":
    main()