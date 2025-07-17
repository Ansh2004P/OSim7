#pragma once
#include "PCB.h"
#include <vector>
#include <queue>
#include <memory>

class ProcessManager {
    int nextPID = 1;
    std::priority_queue<
        std::shared_ptr<PCB>,
        std::vector<std::shared_ptr<PCB>>,
        bool(*)(const std::shared_ptr<PCB>&, const std::shared_ptr<PCB>&)
    > jobQueue;

public:
    ProcessManager();

    std::shared_ptr<PCB> createProcess(int arrival, int burst, const std::vector<int>& maxRes);
    bool jobQueueEmpty() const;
    std::shared_ptr<PCB> peekJob();
    std::shared_ptr<PCB> popJob();
    void listJobs() const;
};
