#pragma once

#include "PCB.h"
#include "SchedulerStrategy.h"
#include <queue>

using namespace std;

/// @brief First-Come, First-Served (FCFS) scheduling strategy implementation.
/// Implements the basic queue-based scheduling algorithm where the first process to arrive is executed first.
class FCFS: public Scheduler {
public:
    FCFS();
    
    /// @brief Adds a process to the FCFS ready queue (transitions from NEW to READY).
    /// @param process A shared pointer to the PCB of the process being added.
    void addProcess(shared_ptr<PCB> process) override;

    /// @brief Runs the next process from the FCFS ready queue (transitions READY to RUNNING).
    void runNextProcess() override;

    /// @brief Handles events and updates state of the currently running process.
    /// Could trigger transitions: RUNNING → WAITING, READY, or TERMINATED.
    void updateProcessState() override;

    /// @brief Prints all processes currently in the FCFS ready queue.
    void printQueue() const override;

    void simulateTimeStep(int currentTime) override;

    bool isIdle() const override;
private:
    queue<shared_ptr<PCB>> readyQueue;
};