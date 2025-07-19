// src/ProcessManager.cpp

#include "ProcessManager.h"
#include <iostream>

using namespace std;

/// @brief Initialize jobQueue with comparator
ProcessManager::ProcessManager() : jobQueue(CompareArrival()) {}

/// @brief Create a new process and add to job queue
std::shared_ptr<PCB> ProcessManager::createProcess(int arrival, int burst, const vector<int>& maxRes) {
    auto pcb = make_shared<PCB>(nextPID++, arrival, burst, maxRes);
    jobQueue.push(pcb);
    return pcb;
}

/// @brief Check if job queue is empty
bool ProcessManager::isJobQueueEmpty() const {
    return jobQueue.empty();
}

/// @brief Peek at the next job in job queue
std::shared_ptr<PCB> ProcessManager::peekNextJob() const {
    if (jobQueue.empty()) return nullptr;
    return jobQueue.top();
}

/// @brief Pop the top process from job queue
std::shared_ptr<PCB> ProcessManager::popNextJob() {
    if (jobQueue.empty()) return nullptr;
    auto p = jobQueue.top();
    jobQueue.pop();
    return p;
}

/// @brief Move all processes with arrival time <= currentTime to readyQueue
void ProcessManager::updateJobQueueToReadyQueue(int currentTime) {
    while (!jobQueue.empty() && jobQueue.top()->getArrivalTime() <= currentTime) {
        auto process = jobQueue.top(); jobQueue.pop();
        process->setState(ProcessState::READY);
        readyQueue.push(process);
    }
}

/// @brief Move process to waiting queue
void ProcessManager::moveToWaitingQueue(std::shared_ptr<PCB> process) {
    process->setState(ProcessState::WAITING);
    waitingQueue.push(process);
}

/// @brief Move process to ready queue
void ProcessManager::moveToReadyQueue(std::shared_ptr<PCB> process) {
    process->setState(ProcessState::READY);
    readyQueue.push(process);
}

/// @brief Wake process from waiting to ready (e.g., I/O done)
void ProcessManager::wakeProcess(std::shared_ptr<PCB> process) {
    moveToReadyQueue(process);
}

/// @brief Get and remove next ready process
std::shared_ptr<PCB> ProcessManager::getNextReadyProcess() {
    if (readyQueue.empty()) return nullptr;
    auto p = readyQueue.front();
    readyQueue.pop();
    return p;
}

/// @brief Check if ready queue is empty
bool ProcessManager::isReadyQueueEmpty() const {
    return readyQueue.empty();
}

/// @brief Print all jobs in job queue (for debugging)
void ProcessManager::listJobs() const {
    cout << "Current Job Queue:\n";
    cout << "PID\tArrival\tBurst\tRemaining\tState\n";
    auto temp = jobQueue;
    while (!temp.empty()) {
        auto p = temp.top(); temp.pop();
        cout << p->getPID() << "\t" << p->getArrivalTime() << "\t"
             << p->getBurstTime() << "\t" << p->getRemainingTime()
             << "\t\t" << p->getStateString() << "\n";
    }
}

/// @brief Return a copy of ready queue
queue<shared_ptr<PCB>> ProcessManager::getReadyQueueCopy() const {
    return readyQueue;
}

/// @brief Return a copy of waiting queue
queue<shared_ptr<PCB>> ProcessManager::getWaitingQueueCopy() const {
    return waitingQueue;
}
