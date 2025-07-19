#ifndef SJF_PREEMPTIVE_H
#define SJF_PREEMPTIVE_H

#include "SchedulerStrategy.h"
#include <queue>
#include <vector>
#include <memory>

class SJFPreemptive : public Scheduler {
public:
    void addProcess(std::shared_ptr<PCB> process) override;
    void runNextProcess() override;
    void updateProcessState() override;
    void simulateTimeStep(int currentTime) override;
    void printQueue() const override;
    bool isIdle() const override;
    std::string getName() const override { return "SJF Preemptive"; }

private:
    struct CompareRemainingTime {
        bool operator()(const std::shared_ptr<PCB>& a, const std::shared_ptr<PCB>& b) const {
            return a->getRemainingTime() > b->getRemainingTime(); // min-heap
        }
    };

    std::priority_queue<std::shared_ptr<PCB>, 
                       std::vector<std::shared_ptr<PCB>>, 
                       CompareRemainingTime> readyQueue;
};

#endif // SJF_PREEMPTIVE_H
