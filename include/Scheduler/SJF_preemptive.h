#pragma once
#include "Scheduler.h"
#include <queue>
#include <vector>
#include <memory>

class SJFPreemptive : public Scheduler {
private:
    struct CompareRemainingTime {
        bool operator()(const std::shared_ptr<PCB>& a, const std::shared_ptr<PCB>& b) const {
            return a->getRemainingTime() > b->getRemainingTime(); // min-heap
        }
    };

    std::priority_queue<std::shared_ptr<PCB>, std::vector<std::shared_ptr<PCB>>, CompareRemainingTime> readyQueue;
    std::vector<std::shared_ptr<PCB>> jobQueue;  // Holds all jobs until they arrive

public:
    void addProcess(std::shared_ptr<PCB> process) override;
    void runNextProcess() override;
    void updateProcessState() override;
    void simulateTimeStep(int currentTime) override;
    void printQueue() const override;
    std::string name() const { return "SJF Preemptive"; }
    bool isIdle() const override {
        return readyQueue.empty() && runningProcess == nullptr && jobQueue.empty();
    }
};
