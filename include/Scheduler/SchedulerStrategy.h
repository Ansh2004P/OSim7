#ifndef SCHEDULER_H
#define SCHEDULER_H

#pragma once

#include "PCB.h"
#include <queue>
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

    /// @brief Adds a process to the scheduler’s internal queue (usually transitions from NEW to READY).
    virtual void addProcess(std::shared_ptr<PCB> process) = 0;

    /// @brief Runs the next process according to the scheduling algorithm.
    virtual void runNextProcess() = 0;

    /// @brief Handles events like process completion, IO wait, etc.
    virtual void updateProcessState() = 0;

    /// @brief Simulates one time step (used to decrement burst time, check completions, etc.)
    virtual void simulateTimeStep(int currentTime) = 0;

    /// @brief Prints internal state of scheduler queues (for debugging)
    virtual void printQueue() const = 0;

    /// @brief Returns true if the CPU is currently idle
    virtual bool isIdle() const = 0;

    /// @brief Performs a context switch (can be overridden for algorithm-specific logic)
    virtual void contextSwitch(std::shared_ptr<PCB> nextProcess) {
        runningProcess = nextProcess;
    }

    /// @brief Get the currently running process (optional utility)
    std::shared_ptr<PCB> getRunningProcess() const {
        return runningProcess;
    }

  /// @brief Returns true if a process is currently running
    bool hasRunningProcess() const {
        return runningProcess != nullptr;
    }
};

#endif // SCHEDULER_H
