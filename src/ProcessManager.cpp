#include "ProcessManager.h"
#include <iostream>

bool compareArrival(const std::shared_ptr<PCB>& a, const std::shared_ptr<PCB>& b) {
    return a->getArrivalTime() > b->getArrivalTime();  // Min-heap
}

ProcessManager::ProcessManager() : jobQueue(compareArrival) {}

std::shared_ptr<PCB> ProcessManager::createProcess(int arrival, int burst, const std::vector<int>& maxRes) {
    auto pcb = std::make_shared<PCB>(nextPID++, arrival, burst, maxRes);
    jobQueue.push(pcb);
    return pcb;
}

bool ProcessManager::jobQueueEmpty() const {
    return jobQueue.empty();
}

std::shared_ptr<PCB> ProcessManager::peekJob() {
    return jobQueue.top();
}

std::shared_ptr<PCB> ProcessManager::popJob() {
    auto p = jobQueue.top();
    jobQueue.pop();
    return p;
}

void ProcessManager::listJobs() const {
    std::cout << "Current Jobs:\n";
    std::cout << "PID\tArrival\tBurst\tRemaining\tState\n";

    auto temp = jobQueue;
    while (!temp.empty()) {
        auto p = temp.top(); temp.pop();
        std::cout << p->getPID() << "\t" << p->getArrivalTime() << "\t" << p->getBurstTime()
                  << "\t" << p->getRemainingTime() << "\t" << p->getStateString() << "\n";
    }
}
