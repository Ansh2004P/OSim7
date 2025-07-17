#include "Scheduler/RoundRobin.h"
#include "Logger.h"

RoundRobin::RoundRobin(int tq) : timeQuantum(tq), timeSliceRemaining(0) {}

void RoundRobin::addProcess(shared_ptr<PCB> process)
{
    process->setState(ProcessState::READY);
    readyQueue.push(process);

    Logger::info("Time " + to_string(process->getArrivalTime()) + ": PID " + to_string(process->getPID()) + " added to READY queue.");
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

        Logger::error(" PID " + to_string(runningProcess->getPID()) + " -> TERMINATED");
        runningProcess = nullptr;
    }
    else if (timeSliceRemaining <= 0)
    {
        runningProcess->setState(ProcessState::READY);
        readyQueue.push(runningProcess);

        Logger::warn("PID " + to_string(runningProcess->getPID()) + " time slice expired -> back to READY");

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
        runningProcess->setRemainingTime(runningProcess->getRemainingTime() - 1);
        timeSliceRemaining--;

        Logger::success("Time " + to_string(currentTime) + ": PID " + to_string(runningProcess->getPID()) + " running, remaining time = " + to_string(runningProcess->getRemainingTime()));
    }

    updateProcessState();
}

void RoundRobin::printQueue() const
{
    queue<shared_ptr<PCB>> temp = readyQueue;
    Logger::info("Round Robin Ready Queue:");

    while (!temp.empty())
    {
        auto process = temp.front();
        temp.pop();

        Logger::info("  PID: " + to_string(process->getPID()) + ", Remaining: " + to_string(process->getRemainingTime()));
    }
}

void RoundRobin::contextSwitch(shared_ptr<PCB> nxtProcess)
{
    runningProcess = nxtProcess;
    timeSliceRemaining = timeQuantum;

    Logger::info("Context switch to PID " + to_string(runningProcess->getPID()) + ", time slice = " + to_string(timeSliceRemaining));
}