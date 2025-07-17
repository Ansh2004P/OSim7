#pragma once
#include "Scheduler/Scheduler.h"
#include <queue>
#include <memory>

using namespace std;

class SJF : public Scheduler
{
public:
    void addProcess(std::shared_ptr<PCB> process) override;
    void runNextProcess() override;
    void updateProcessState() override;
    void simulateTimeStep(int currentTime) override;
    void printQueue() const override;
    bool isIdle() const override;
    string name() const { return "SJF"; }

private:
    struct CompareBurstTime {
        bool operator()(const shared_ptr<PCB>& a, const shared_ptr<PCB>& b) {
            return a->getBurstTime() >b->getBurstTime();
        }
    };

    priority_queue<shared_ptr<PCB>, vector<shared_ptr<PCB>>, CompareBurstTime> readyQueue;
};