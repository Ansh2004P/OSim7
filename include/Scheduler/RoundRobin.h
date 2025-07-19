#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include "SchedulerStrategy.h"
#include <queue>
#include <memory>

class RoundRobin : public Scheduler {
public: 
    RoundRobin(int timeQuantum);
    
    void addProcess(std::shared_ptr<PCB> process) override;
    void runNextProcess() override;
    void updateProcessState() override;
    void simulateTimeStep(int currentTime) override;
    void printQueue() const override;
    bool isIdle() const override;
    std::string getName() const override { return "Round Robin"; }

private:
    int timeQuantum;
    int timeSliceRemaining;
    std::queue<std::shared_ptr<PCB>> readyQueue;

protected:
    void contextSwitch(std::shared_ptr<PCB> nextProcess) override;
};

#endif // ROUND_ROBIN_H
