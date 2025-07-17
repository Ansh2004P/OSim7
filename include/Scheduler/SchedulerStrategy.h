// Scheduler.h

#pragma once
#include "PCB.h"
#include <queue>
#include <memory>
#include <vector>

using namespace std;


/// @brief Abstract Base Class for pluggable Schedulers (FCFS, Round Robin, etc.).
class Scheduler {
public:
    virtual ~Scheduler() =default;

    /// @brief Adds a process to the scheduler’s internal queue (usually transitions from NEW to READY).
    /// @param process Shared pointer to a PCB to be scheduled.
    virtual void addProcess(std::shared_ptr<PCB> process) = 0;

    /// @brief Runs the next process according to the scheduling algorithm.
    /// Typically results in a READY → RUNNING state transition.
    virtual void runNextProcess() = 0;

    /// @brief Handles events like process completion, IO wait, etc.
    /// Could lead to RUNNING → WAITING / READY / TERMINATED.
    virtual void updateProcessState() = 0;

    /// @brief Simulates a time step (unit time passage).
    /// Concrete schedulers use this to perform automatic transitions (e.g., decrement burst time).
    /// @param currentTime The current simulation time.
    virtual void simulateTimeStep(int currentTime) = 0;

    /// @brief Prints internal scheduling queue(s), useful for debugging or visualizing algorithm behavior.
    virtual void printQueue() const = 0;

protected:
    /// @brief Currently running process (if any).
    std::shared_ptr<PCB> runningProcess = nullptr;

    /// @brief Performs a context switch from current process to next.
    virtual void contextSwitch(std::shared_ptr<PCB> nextProcess) {
        // default implementation, can be overridden
    };
};
