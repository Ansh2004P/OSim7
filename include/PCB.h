#ifndef PCB_H
#define PCB_H

#include <vector>
#include <string>

enum ProcessState {
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED,
    SUSPENDED_READY,
    SUSPENDED_WAITING
};

class PCB {
public:
    int pid;

    PCB(int _pid, int _arrival, int _burst, const std::vector<int>& maxRes);

    // Getters
    int getPID() const;
    int getArrivalTime() const;
    int getBurstTime() const;
    int getRemainingTime() const;
    ProcessState getState() const;
    std::vector<int> getMaxResources() const;
    std::vector<int> getAllocatedResources() const;
    std::string getStateString() const;

    // Setters
    void setArrivalTime(int time);
    void setBurstTime(int time);
    void setRemainingTime(int time);
    void setState(ProcessState newState);
    void setMaxResources(const std::vector<int>& res);
    void setAllocatedResources(const std::vector<int>& res);

private:
    int arrivalTime;
    int burstTime;
    int remainingTime;
    ProcessState state;

    std::vector<int> maxResources;
    std::vector<int> allocatedResources;
};

#endif // PCB_H
