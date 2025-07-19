#ifndef SJF_H
#define SJF_H

#include "SchedulerStrategy.h"
#include <queue>
#include <vector>
#include <memory>

class SJF : public Scheduler {
public:
    void addProcess(std::shared_ptr<PCB> process) override;
    void runNextProcess() override;
    void updateProcessState() override;
    void simulateTimeStep(int currentTime) override;
    void printQueue() const override;
    bool isIdle() const override;
    std::string getName() const override { return "SJF"; }

private:
    struct CompareBurstTime {
        bool operator()(const std::shared_ptr<PCB>& a, const std::shared_ptr<PCB>& b) const {
            return a->getBurstTime() > b->getBurstTime(); // min-heap
        }
    };

    std::priority_queue<std::shared_ptr<PCB>, 
                       std::vector<std::shared_ptr<PCB>>, 
                       CompareBurstTime> readyQueue;
};

#endif // SJF_H
