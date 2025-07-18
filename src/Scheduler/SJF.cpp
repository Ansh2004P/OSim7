#include "Scheduler/SJF.h"
#include "ProcessManager.h"
#include <iostream>

using namespace std;

/// @brief Pointer to global process manager passed externally
extern ProcessManager processManager;

/// @brief Custom comparator for priority_queue (already in SJF.h)
/// struct CompareBurst { bool operator()(...) }

void SJF::addProcess(shared_ptr<PCB> process)
{
    process->setState(ProcessState::READY);
    readyQueue.push(process);
    cout << "Process PID: " << process->getPID() << " added to Ready Queue (Burst: " 
         << process->getBurstTime() << ")\n";
}

void SJF::runNextProcess()
{
    if (!readyQueue.empty())
    {
        auto next = readyQueue.top();
        readyQueue.pop();

        contextSwitch(next);
        next->setState(ProcessState::RUNNING);
        runningProcess = next;

        cout << "Started Process PID: " << next->getPID()
             << " [Burst: " << next->getBurstTime() << "]\n";
    }
}

void SJF::updateProcessState()
{
    if (runningProcess)
    {
        int remaining = runningProcess->getRemainingTime() - 1;
        runningProcess->setRemainingTime(remaining);

        if (remaining <= 0)
        {
            cout << "Process PID: " << runningProcess->getPID() << " completed.\n";
            runningProcess->setState(ProcessState::TERMINATED);
            runningProcess = nullptr;
        }
    }
}

void SJF::simulateTimeStep(int currentTime)
{
    cout << "[Time " << currentTime << "] ";

    // Add all newly arrived processes to readyQueue
    while (!processManager.isJobQueueEmpty() &&
           processManager.peekNextJob()->getArrivalTime() <= currentTime)
    {
        auto arrivingProcess = processManager.popNextJob();
        addProcess(arrivingProcess);
    }

    if (!runningProcess)
    {
        runNextProcess();
    }
    else
    {
        cout << "Process PID: " << runningProcess->getPID() << " running (Remaining: "
             << runningProcess->getRemainingTime() << ")\n";
    }

    updateProcessState();
}

void SJF::printQueue() const
{
    cout << "SJF Ready Queue (Shortest Burst First):\n";
    auto copy = readyQueue;
    while (!copy.empty())
    {
        auto p = copy.top();
        copy.pop();
        cout << "  PID: " << p->getPID() << ", Burst: " << p->getBurstTime() << "\n";
    }
}

bool SJF::isIdle() const
{
    return runningProcess == nullptr && readyQueue.empty();
}
