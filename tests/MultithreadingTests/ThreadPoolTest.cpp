#include "../../src/Multithreading/ThreadPool.hpp"
#include <gtest/gtest.h>

void exampleTask(int id) {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate work
    std::cout << "Task " << id << " finished on thread " << std::this_thread::get_id() << std::endl;
}

TEST(ThreadPoolTest, BasicTest)
{
    ThreadPool pool(2); // Create a thread pool with 2 threads

    auto futureTask1 = pool.enqueue(exampleTask, 1);
    auto futureTask2 = pool.enqueue(exampleTask, 2);

    // Check if the task is done without blocking
    while (futureTask1.wait_for(std::chrono::milliseconds(500)) != std::future_status::ready) {
        std::cout << "Task is still running...\n";
    }

    // Task finished, retrieve result (if any)
    futureTask1.get(); // Blocks if not yet finished, but we already checked
    futureTask2.get();

    std::cout << "Task has completed!\n";

}
