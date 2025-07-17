#include "Scheduler/FCFS.h"
#include "Logger.h"
#include "TimeManager.h"

using namespace std;

FCFS::FCFS() {}

void FCFS::addProcess(shared_ptr<PCB> process)
{
    process->setState(ProcessState::READY);
    readyQueue.push(process);

    Logger::info("Time " + std::to_string(TimeManager::getTime()) + ": Process " + std::to_string(process->getPID()) + " → READY");
}

void FCFS::runNextProcess()
{
    if(!runningProcess && !readyQueue.empty()) {
        runningProcess =readyQueue.front();
        readyQueue.pop();

        runningProcess->setState(ProcessState::RUNNING);

        Logger::success("Time " + std::to_string(TimeManager::getTime()) + ": Process " + std::to_string(runningProcess->getPID()) + " → RUNNING");
    }
}

void FCFS::updateProcessState() {
    if(runningProcess) {
        int remaining = runningProcess->getRemainingTime()-1;
        runningProcess->setRemainingTime(remaining);

        if(remaining<=0) {
            runningProcess->setState(ProcessState::TERMINATED);
            Logger::error("Time " + std::to_string(TimeManager::getTime()) + ": Process " + std::to_string(runningProcess->getPID()) + " → TERMINATED");
            runningProcess = nullptr;
        }
    }
    runNextProcess();
}

void FCFS::printQueue() const {
    std::queue<std::shared_ptr<PCB>> temp = readyQueue;
    Logger::info("Current FCFS Ready Queue:");

    if (temp.empty()) {
        Logger::warn("Ready Queue is empty.");
        return;
    }

    while (!temp.empty()) {
        auto process = temp.front(); 
        temp.pop();
        
        Logger::log(LogLevel::INFO, "  PID " + std::to_string(process->getPID()) + " | Remaining Time: " + std::to_string(process->getRemainingTime()));
    }
}

void FCFS::simulateTimeStep(int currentTime) {
    Logger::log(LogLevel::INFO, "=== Tick " + std::to_string(currentTime) + " ===");
    updateProcessState();
    printQueue();
}