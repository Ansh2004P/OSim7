#include "PCB.h"

using namespace std;

/// @brief Constructs a new PCB
/// @param _pid The process ID
/// @param _arrival The arrival time
/// @param _burst The burst time
/// @param maxRes The maximum resources
PCB::PCB(int _pid, int _arrival, int _burst, const vector<int> &maxRes)
    : pid(_pid), arrivalTime(_arrival), burstTime(_burst), remainingTime(_burst),
      state(NEW), maxResources(maxRes), allocatedResources(maxRes.size(), 0) {}

/// @brief Gets the process ID
int PCB::getPID() const {
    return pid;
}

/// @brief Gets the arrival time of the process
int PCB::getArrivalTime() const {
    return arrivalTime;
}

/// @brief Gets the burst time of the process
int PCB::getBurstTime() const {
    return burstTime;
}

/// @brief Gets the remaining time of the process
int PCB::getRemainingTime() const {
    return remainingTime;
}

/// @brief Gets the current state of the process
ProcessState PCB::getState() const {
    return state;
}

/// @brief Gets the completion time of the process
int PCB::getCompletionTime() const { 
    return completionTime; 
}

/// @brief Gets the maximum resources of the process
vector<int> PCB::getMaxResources() const {
    return maxResources;
}

/// @brief Gets the allocated resources of the process
vector<int> PCB::getAllocatedResources() const {
    return allocatedResources;
}

/// @brief Sets the arrival time of the process
/// @param time The new arrival time
void PCB::setArrivalTime(int time) {
    arrivalTime = time;
}

/// @brief Sets the burst time of the process
/// @param time The new burst time 
void PCB::setBurstTime(int time) {
    burstTime = time;
}

/// @brief Sets the remaining time of the process
/// @param time The new remaining time
void PCB::setRemainingTime(int time) {
    remainingTime = time;
}

/// @brief Sets the completion time of the process
/// @param time The new completion time
void PCB::setCompletionTime(int time) { 
    completionTime = time; 
}

/// @brief Sets the state of the process
/// @param newState The new state of the process
void PCB::setState(ProcessState newState) {
    state = newState;
}

/// @brief Sets the maximum resources of the process
/// @param res The new maximum resources
void PCB::setMaxResources(const vector<int> &res) {
    maxResources = res;
}

/// @brief Sets the allocated resources of the process
/// @param res The new allocated resources
void PCB::setAllocatedResources(const vector<int> &res) {
    allocatedResources = res;
}

/// @brief Gets the string representation of the current state
/// @return The string representation of the state
string PCB::getStateString() const {
    switch (state) {
        case NEW: 
            return "NEW";
        case READY:
            return "READY";
        case RUNNING:
            return "RUNNING";
        case WAITING:
            return "WAITING";
        case TERMINATED:
            return "TERMINATED";
        case SUSPENDED_READY: 
            return "SUSPENDED_READY";
        case SUSPENDED_WAITING: 
            return "SUSPENDED_WAITING";
        default:
            return "UNKNOWN";
    }
}