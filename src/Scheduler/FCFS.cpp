#include "Scheduler/FCFS.h"
#include "Logger.h"
#include "TimeManager.h"

using namespace std;

FCFS::FCFS() {}

void FCFS::addProcess(shared_ptr<PCB> process) {
    process->setState(ProcessState::READY);
    readyQueue.push(process);

    Logger::info("Time " + to_string(TimeManager::getTime()) + 
                 ": Process " + to_string(process->getPID()) + " → READY");
}

void FCFS::runNextProcess() {
    if (!runningProcess && !readyQueue.empty()) {
        runningProcess = readyQueue.front();
        readyQueue.pop();

        runningProcess->setState(ProcessState::RUNNING);

        Logger::success("Time " + to_string(TimeManager::getTime()) + 
                        ": Process " + to_string(runningProcess->getPID()) + " → RUNNING");
    }
}

void FCFS::updateProcessState() {
    if (runningProcess) {
        int remaining = runningProcess->getRemainingTime() - 1;
        runningProcess->setRemainingTime(remaining);

        if (remaining <= 0) {
            runningProcess->setState(ProcessState::TERMINATED);
            Logger::error("Time " + to_string(TimeManager::getTime()) + 
                          ": Process " + to_string(runningProcess->getPID()) + " → TERMINATED");

            runningProcess = nullptr;
        }
    }

    runNextProcess();
}

void FCFS::printQueue() const {
    queue<shared_ptr<PCB>> tempQueue = readyQueue;

    Logger::info("Current FCFS Ready Queue:");

    if (tempQueue.empty()) {
        Logger::warn("  Ready Queue is empty.");
        return;
    }

    while (!tempQueue.empty()) {
        auto process = tempQueue.front();
        tempQueue.pop();

        Logger::info("  PID " + to_string(process->getPID()) +
                     " | Remaining Time: " + to_string(process->getRemainingTime()));
    }
}

void FCFS::simulateTimeStep(int currentTime) {
    Logger::info("=== Tick " + to_string(currentTime) + " ===");
    updateProcessState();
    printQueue();
}

bool FCFS::isIdle() const {
    return readyQueue.empty() && runningProcess == nullptr;
}
