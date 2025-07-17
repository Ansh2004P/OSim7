#include "ProcessManager.h"
#include "Logger.h"
#include <iostream>

using namespace std;

ProcessManager::ProcessManager() {}

shared_ptr<PCB> ProcessManager::createProcess(int arrivalTime, int burstTime, const vector<int>& maxResources) {
    auto process = make_shared<PCB>(nextPID++, arrivalTime, burstTime, maxResources);
    jobQueue.push(process);

    Logger::info("Process " + to_string(process->getPID()) + 
                 " added to job queue (Burst: " + to_string(burstTime) +
                 ", Arrival: " + to_string(arrivalTime) + ")");
    return process;
}

void ProcessManager::listJobs() const {
    queue<shared_ptr<PCB>> tmp = jobQueue;

    if (tmp.empty()) {
        Logger::warn("Job queue is empty.");
        return;
    }

    Logger::info("Listing jobs in the job queue:");
    cout << "--------------------------------------------------\n";
    cout << "PID\tBurst\tArrival\tState\n";
    cout << "--------------------------------------------------\n";

    while (!tmp.empty()) {
        auto process = tmp.front();
        tmp.pop();

        cout << process->getPID() << "\t"
             << process->getBurstTime() << "\t"
             << process->getArrivalTime() << "\t"
             << process->getStateString() << "\n";
    }
    cout << "--------------------------------------------------\n";
}
