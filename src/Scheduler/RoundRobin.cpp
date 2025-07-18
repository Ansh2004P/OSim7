#include "Scheduler/RoundRobin.h"
#include "Logger.h"

RoundRobin::RoundRobin(int tq) : timeQuantum(tq), timeSliceRemaining(0) {}

void RoundRobin::addProcess(std::shared_ptr<PCB> process)
{
    process->setState(ProcessState::READY);
    readyQueue.push(process);

    Logger::info("Time " + std::to_string(process->getArrivalTime()) +
                 ": PID " + std::to_string(process->getPID()) +
                 " added to READY queue.");
}

void RoundRobin::runNextProcess()
{
    if (!runningProcess && !readyQueue.empty())
    {
        auto nxt = readyQueue.front();
        readyQueue.pop();
        contextSwitch(nxt);
    }
}

void RoundRobin::updateProcessState()
{
    if (!runningProcess)
        return;

    if (runningProcess->getRemainingTime() <= 0)
    {
        runningProcess->setState(ProcessState::TERMINATED);
        Logger::error("PID " + std::to_string(runningProcess->getPID()) + " -> TERMINATED");
        runningProcess = nullptr;
    }
    else if (timeSliceRemaining <= 0)
    {
        runningProcess->setState(ProcessState::READY);
        readyQueue.push(runningProcess);
        Logger::warn("PID " + std::to_string(runningProcess->getPID()) +
                     " time slice expired -> back to READY");

        runningProcess = nullptr;
    }
}

void RoundRobin::simulateTimeStep(int currentTime)
{
    if (!runningProcess)
    {
        runNextProcess();
    }

    if (runningProcess)
    {
        runningProcess->setState(ProcessState::RUNNING);

        // Guard to ensure remainingTime never goes negative
        if (runningProcess->getRemainingTime() > 0)
            runningProcess->setRemainingTime(runningProcess->getRemainingTime() - 1);

        timeSliceRemaining--;

        Logger::success("Time " + std::to_string(currentTime) +
                        ": PID " + std::to_string(runningProcess->getPID()) +
                        " running, remaining time = " +
                        std::to_string(runningProcess->getRemainingTime()));
    }
    else
    {
        Logger::warn("Time " + std::to_string(currentTime) + ": CPU is idle.");
    }

    updateProcessState();
}

void RoundRobin::printQueue() const
{
    std::queue<std::shared_ptr<PCB>> temp = readyQueue;
    Logger::info("Round Robin Ready Queue:");

    while (!temp.empty())
    {
        auto process = temp.front();
        temp.pop();

        Logger::info("  PID: " + std::to_string(process->getPID()) +
                     ", Remaining: " + std::to_string(process->getRemainingTime()));
    }
}

void RoundRobin::contextSwitch(std::shared_ptr<PCB> nxtProcess)
{
    runningProcess = nxtProcess;
    timeSliceRemaining = timeQuantum;

    Logger::info("Context switch to PID " +
                 std::to_string(runningProcess->getPID()) +
                 ", time slice = " + std::to_string(timeSliceRemaining));
}

bool RoundRobin::isIdle() const
{
    return readyQueue.empty() && runningProcess == nullptr;
}
