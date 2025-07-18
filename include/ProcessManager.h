#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include "PCB.h"
#include <memory>
#include <queue>
#include <vector>
#include <functional>

class ProcessManager {
public:
    ProcessManager();

    /// @brief Create a new process and add it to the job queue
    std::shared_ptr<PCB> createProcess(int arrivalTime, int burstTime, const std::vector<int>& maxResources);

    /// @brief Check if job queue is empty
    bool isJobQueueEmpty() const;

    /// @brief Peek at the next job in the job queue (does not remove)
    std::shared_ptr<PCB> peekNextJob() const;

    /// @brief Remove and return next job from job queue
    std::shared_ptr<PCB> popNextJob();

    /// @brief Move all jobs whose arrival time <= current time to ready queue
    void updateJobQueueToReadyQueue(int currentTime);

    /// @brief Move process to waiting queue
    void moveToWaitingQueue(std::shared_ptr<PCB> process);

    /// @brief Move process to ready queue
    void moveToReadyQueue(std::shared_ptr<PCB> process);

    /// @brief Wake process (from I/O) to ready queue
    void wakeProcess(std::shared_ptr<PCB> process);

    /// @brief Return and remove next ready process
    std::shared_ptr<PCB> getNextReadyProcess();

    /// @brief Check if ready queue is empty
    bool isReadyQueueEmpty() const;

    /// @brief Debug: List contents of job queue
    void listJobs() const;

    /// @brief Return a copy of ready queue
    std::queue<std::shared_ptr<PCB>> getReadyQueueCopy() const;

    /// @brief Return a copy of waiting queue
    std::queue<std::shared_ptr<PCB>> getWaitingQueueCopy() const;

private:
    struct CompareArrival {
        bool operator()(const std::shared_ptr<PCB>& a, const std::shared_ptr<PCB>& b) const {
            return a->getArrivalTime() > b->getArrivalTime(); // Min-heap based on arrivalTime
        }
    };

    int nextPID = 1;
    std::priority_queue<std::shared_ptr<PCB>, std::vector<std::shared_ptr<PCB>>, CompareArrival> jobQueue;
    std::queue<std::shared_ptr<PCB>> readyQueue;
    std::queue<std::shared_ptr<PCB>> waitingQueue;
};

#endif // PROCESS_MANAGER_H
