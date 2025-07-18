#pragma once

#include "Scheduler/SchedulerStrategy.h"
#include <queue>
#include <memory>
using namespace std;

/// @brief First-Come, First-Served (FCFS) scheduling strategy implementation.
///        This scheduler picks the first process that arrives and runs it to completion.
class FCFS : public Scheduler {
public:
    FCFS();

    /// @brief Adds a process to the FCFS ready queue (transitions from NEW to READY).
    /// @param process A shared pointer to the PCB of the process being added.
    void addProcess(std::shared_ptr<PCB> process) override;

    /// @brief Runs the next process from the FCFS ready queue (transitions READY → RUNNING).
    void runNextProcess() override;

    /// @brief Handles updates to the running process, e.g., reducing remaining time or terminating.
    /// Transitions: RUNNING → TERMINATED or back to READY (if preempted — not in FCFS though).
    void updateProcessState() override;

    /// @brief Prints all processes currently in the FCFS ready queue.
    void printQueue() const override;

    /// @brief Simulates one unit of time in the scheduler.
    /// Called every clock tick by the main loop.
    void simulateTimeStep(int currentTime) override;

    /// @brief Checks whether the CPU is idle (no running or ready processes).
    bool isIdle() const override;

private:
    queue<shared_ptr<PCB>> readyQueue;
};
