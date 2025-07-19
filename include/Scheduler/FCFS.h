#ifndef FCFS_H
#define FCFS_H

#include "SchedulerStrategy.h"
#include <queue>
#include <memory>

/// @brief First-Come, First-Served scheduling strategy implementation
class FCFS : public Scheduler {
public:
    FCFS();

    void addProcess(std::shared_ptr<PCB> process) override;
    void runNextProcess() override;
    void updateProcessState() override;
    void printQueue() const override;
    void simulateTimeStep(int currentTime) override;
    bool isIdle() const override;
    std::string getName() const override { return "FCFS"; }

private:
    std::queue<std::shared_ptr<PCB>> readyQueue;
};

#endif // FCFS_H
