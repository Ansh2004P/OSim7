#include <iostream>
#include "Scheduler/SJF_preemptive.h"
#include "TimeManager.h"

void SJFPreemptive::addProcess(std::shared_ptr<PCB> process) {
    process->setState(ProcessState::NEW);
    jobQueue.push_back(process);
}

void SJFPreemptive::runNextProcess() {
    if (!readyQueue.empty()) {
        auto next = readyQueue.top();
        readyQueue.pop();

        contextSwitch(next);
        next->setState(ProcessState::RUNNING);
        runningProcess = next;

        std::cout << "Running PID: " << next->getPID()
                  << " [Remaining: " << next->getRemainingTime() << "]\n";
    }
}

void SJFPreemptive::updateProcessState() {
    if (runningProcess) {
        int rem = runningProcess->getRemainingTime();
        runningProcess->setRemainingTime(rem - 1);

        if (rem - 1 <= 0) {
            std::cout << "Process PID: " << runningProcess->getPID() << " completed.\n";
            runningProcess->setState(ProcessState::TERMINATED);
            runningProcess->setCompletionTime(TimeManager::getTime());
            runningProcess = nullptr;
        }
    }
}

void SJFPreemptive::simulateTimeStep(int currentTime) {
    std::cout << "[Time " << currentTime << "] ";

    // 1. Move arrived jobs to readyQueue
    for (auto it = jobQueue.begin(); it != jobQueue.end();) {
        if ((*it)->getArrivalTime() <= currentTime) {
            (*it)->setState(ProcessState::READY);
            std::cout << "Process PID: " << (*it)->getPID() << " arrived.\n";
            readyQueue.push(*it);

            // Preempt if newly arrived process is better
            if (runningProcess && (*it)->getRemainingTime() < runningProcess->getRemainingTime()) {
                std::cout << "Preempting PID: " << runningProcess->getPID()
                          << " for PID: " << (*it)->getPID() << "\n";

                runningProcess->setState(ProcessState::READY);
                readyQueue.push(runningProcess);
                runningProcess = nullptr;
            }

            it = jobQueue.erase(it);
        } else {
            ++it;
        }
    }

    // 2. If no running process, pick the next
    if (!runningProcess) {
        runNextProcess();
    }

    // 3. Decrement time of currently running process
    if (runningProcess) {
        std::cout << "Process PID: " << runningProcess->getPID()
                  << " running [Remaining: " << runningProcess->getRemainingTime() << "]\n";
    }

    updateProcessState();  // Now handles decrement and checks for termination
}

void SJFPreemptive::printQueue() const {
    std::cout << "Ready Queue (Shortest Remaining Time First):\n";
    auto copy = readyQueue;
    while (!copy.empty()) {
        auto p = copy.top(); copy.pop();
        std::cout << "  PID: " << p->getPID()
                  << ", Remaining: " << p->getRemainingTime()
                  << ", Arrival: " << p->getArrivalTime() << "\n";
    }
}
