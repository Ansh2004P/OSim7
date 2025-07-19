#ifndef SCHEDULER_STRATEGY_H
#define SCHEDULER_STRATEGY_H

#include "PCB.h"
#include <queue>
#include <vector>
#include <memory>

/// @brief Abstract Base Class for pluggable Schedulers (FCFS, SJF, RR, etc.)
class Scheduler {
protected:
    /// @brief Queue for waiting processes (e.g., for I/O)
    std::queue<std::shared_ptr<PCB>> waitingQueue;

    /// @brief Currently running process (can be nullptr)
    std::shared_ptr<PCB> runningProcess = nullptr;

public:
    virtual ~Scheduler() = default;

    /// @brief Adds a process to the scheduler's internal queue
    virtual void addProcess(std::shared_ptr<PCB> process) = 0;

    /// @brief Runs the next process according to the scheduling algorithm
    virtual void runNextProcess() = 0;

    /// @brief Handles events like process completion, IO wait, etc.
    virtual void updateProcessState() = 0;

    /// @brief Simulates one time step
    virtual void simulateTimeStep(int currentTime) = 0;

    /// @brief Prints internal state of scheduler queues
    virtual void printQueue() const = 0;

    /// @brief Returns true if the CPU is currently idle
    virtual bool isIdle() const = 0;

    /// @brief Returns true if a process is currently running
    virtual bool hasRunningProcess() const {
        return runningProcess != nullptr;
    }

    /// @brief Returns true when all processes are TERMINATED
    virtual bool allProcessesTerminated() const {
        return isIdle(); // Simplified - relies on isIdle implementation
    }

    /// @brief Get the currently running process
    std::shared_ptr<PCB> getRunningProcess() const {
        return runningProcess;
    }

    /// @brief Get scheduler name (for debugging)
    virtual std::string getName() const { return "Generic Scheduler"; }

protected:
    /// @brief Performs a context switch
    virtual void contextSwitch(std::shared_ptr<PCB> nextProcess) {
        runningProcess = nextProcess;
    }
};

#endif // SCHEDULER_STRATEGY_H
