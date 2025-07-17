// Scheduler/SJF.cpp

#include "Scheduler/SJF.h"
#include <iostream>

void SJF::addProcess(std::shared_ptr<PCB> process)
{
    process->setState(ProcessState::READY);
    readyQueue.push(process);
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

        std::cout << "Running Process PID: " << next->getPID() << " [Burst: " << next->getBurstTime() << "]\n";
    }
    else
    {
        runningProcess = nullptr;
    }
}

void SJF::updateProcessState()
{
    if (runningProcess)
    {
        runningProcess->setRemainingTime(runningProcess->getRemainingTime() - 1);

        if (runningProcess->getRemainingTime() <= 0)
        {
            std::cout << "Process PID: " << runningProcess->getPID() << " completed.\n";
            runningProcess->setState(ProcessState::TERMINATED);
            runningProcess = nullptr;
        }
    }
}

void SJF::simulateTimeStep(int currentTime)
{
    std::cout << "[Time " << currentTime << "] ";

    if (!runningProcess)
    {
        runNextProcess();
    }
    else
    {
        std::cout << "Process PID: " << runningProcess->getPID() << " running.\n";
    }

    updateProcessState();
}

void SJF::printQueue() const
{
    std::cout << "SJF Ready Queue (shortest burst first):\n";
    auto copy = readyQueue;
    while (!copy.empty())
    {
        auto p = copy.top();
        copy.pop();
        std::cout << "  PID: " << p->getPID() << ", Burst: " << p->getBurstTime() << "\n";
    }
}

bool SJF::isIdle() const
{
    return runningProcess == nullptr && readyQueue.empty();
}