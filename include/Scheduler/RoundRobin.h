#pragma once
#include "SchedulerStrategy.h"
#include <queue>
#include <memory>

using namespace std;

class RoundRobin : public Scheduler {
public: 
    RoundRobin(int timeQuantum);
    void addProcess(shared_ptr<PCB> process) override;
    void runNextProcess() override;
    void updateProcessState() override;
    void simulateTimeStep(int currentTime) override;
    void printQueue() const override;
    bool isIdle() const override;

private:
    int timeQuantum;
    int timeSliceRemaining =0;
    queue<shared_ptr<PCB>> readyQueue;

    void contextSwitch(shared_ptr<PCB> nextProcess) override;
};
