#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include "PCB.h"
#include <queue> 
#include <memory> 

using namespace std;

class ProcessManager {
    private:
        int nextPID =1;
        queue<shared_ptr<PCB>> jobQueue;

    public: 
        ProcessManager();


        shared_ptr<PCB> createProcess(int arrivalTime, int burstTime, const vector<int>& maxResources);

        void listJobs() const;

};

#endif