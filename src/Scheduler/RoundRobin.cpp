#include "Scheduler/RoundRobin.h"
#include "Logger.h"
#include "TimeManager.h"

RoundRobin::RoundRobin(int tq) : timeQuantum(tq), timeSliceRemaining(0) {}

void RoundRobin::addProcess(std::shared_ptr<PCB> process) {
    process->setState(ProcessState::READY);
    readyQueue.push(process);
    Logger::info("Time " + std::to_string(TimeManager::getTime()) +
                 ": PID " + std::to_string(process->getPID()) +
                 " added to READY queue.");
}

void RoundRobin::runNextProcess() {
    if (!runningProcess && !readyQueue.empty()) {
        auto next = readyQueue.front();
        readyQueue.pop();
        contextSwitch(next);
    }
}

void RoundRobin::contextSwitch(std::shared_ptr<PCB> nextProcess) {
    runningProcess = nextProcess;
    timeSliceRemaining = timeQuantum; // Reset time slice
    
    Logger::info("Context switch to PID " +
                 std::to_string(runningProcess->getPID()) +
                 ", time slice = " + std::to_string(timeSliceRemaining));
}

void RoundRobin::updateProcessState() {
    if (!runningProcess) return;

    // CRITICAL FIX: Only decrement remaining time once per tick
    int remaining = runningProcess->getRemainingTime() - 1;
    runningProcess->setRemainingTime(remaining);
    timeSliceRemaining--; // Also decrement time slice
    
    Logger::success("Time " + std::to_string(TimeManager::getTime()) +
                    ": PID " + std::to_string(runningProcess->getPID()) +
                    " running, remaining time = " + std::to_string(remaining) +
                    ", time slice left = " + std::to_string(timeSliceRemaining));

    // Check for process completion
    if (remaining <= 0) {
        runningProcess->setState(ProcessState::TERMINATED);
        runningProcess->setCompletionTime(TimeManager::getTime());
        Logger::error("PID " + std::to_string(runningProcess->getPID()) + " → TERMINATED");
        runningProcess = nullptr;
        timeSliceRemaining = 0;
        return;
    }
    
    // Check for time slice expiration
    if (timeSliceRemaining <= 0) {
        runningProcess->setState(ProcessState::READY);
        readyQueue.push(runningProcess);
        Logger::warn("PID " + std::to_string(runningProcess->getPID()) +
                     " time slice expired → back to READY");
        runningProcess = nullptr;
    }
}

void RoundRobin::simulateTimeStep(int currentTime) {
    // Start next process if CPU is idle
    if (!runningProcess) {
        runNextProcess();
        if (runningProcess) {
            runningProcess->setState(ProcessState::RUNNING);
        }
    }

    // Execute current process for one time unit
    if (runningProcess) {
        updateProcessState(); // This handles all time decrements
    } else {
        Logger::warn("Time " + std::to_string(currentTime) + ": CPU is idle.");
    }
}

void RoundRobin::printQueue() const {
    std::queue<std::shared_ptr<PCB>> temp = readyQueue;
    Logger::info("Round Robin Ready Queue:");

    while (!temp.empty()) {
        auto process = temp.front();
        temp.pop();
        Logger::info("  PID: " + std::to_string(process->getPID()) +
                     ", Remaining: " + std::to_string(process->getRemainingTime()));
    }
}

bool RoundRobin::isIdle() const {
    return readyQueue.empty() && runningProcess == nullptr;
}
