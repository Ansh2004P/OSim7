// main.cpp

#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include "ProcessManager.h"
#include "Scheduler/SchedulerFactory.h"
#include "Scheduler/FCFS.h"
#include "Scheduler/RoundRobin.h"
// #include "Scheduler/SJF_Preemptive.h"

#include "TimeManager.h"

using namespace std;

ProcessManager processManager;

void printHelp() {
    std::cout << "Commands:\n"
              << "  add        - Add a new process\n"
              << "  list       - Show job queue\n"
              << "  simulate   - Simulate until all processes are done\n"
              << "  help       - Show this help message\n"
              << "  exit       - Quit the simulator\n";
}

int main() {
    cout << "\n=====  OS Simulator =====\n";
    printHelp();

    Scheduler* scheduler = SchedulerFactory::createScheduler();
    string input;

    while (true) {
        cout << "\nEnter command (type 'help' for options): ";
        getline(cin, input);

        if (input == "exit") {
            break;

        } else if (input == "help") {
            printHelp();

        } else if (input == "add") {
            int burstTime, arrivalTime;
            vector<int> maxResources;

            cout << "Enter arrival time: ";
            cin >> arrivalTime;

            cout << "Enter burst time: ";
            cin >> burstTime;
            cin.ignore();

            string resources;
            cout << "Enter max resources (space-separated, e.g., 3 2 1): ";
            getline(cin, resources);

            stringstream ss(resources);
            int val;
            while (ss >> val) {
                maxResources.push_back(val);
            }

            processManager.createProcess(arrivalTime, burstTime, maxResources);

        } else if (input == "list") {
            processManager.listJobs();

        } else if (input == "simulate") {
            cout << "\nSimulating until all processes complete...\n";

            while (!processManager.isJobQueueEmpty() ||
                   !processManager.isReadyQueueEmpty() ||
                   scheduler->hasRunningProcess() ||
                   !scheduler->allProcessesTerminated()) {

                TimeManager::tick();
                int currentTime = TimeManager::getTime();

                cout << "\n[Time " << currentTime << "] Tick\n";

                // Move jobs that have arrived to ready queue
                processManager.updateJobQueueToReadyQueue(currentTime);

                // Send ready processes to scheduler
                while (!processManager.isReadyQueueEmpty()) {
                    scheduler->addProcess(processManager.getNextReadyProcess());
                }

                scheduler->simulateTimeStep(currentTime);
                this_thread::sleep_for(chrono::milliseconds(500));
            }

            cout << "\n✅ Simulation complete. All processes terminated.\n";

        } else {
            cout << "Unknown command. Type 'help' to see available commands.\n";
        }
    }

    cout << "Exiting OS Simulator...\n";
    return 0;
}
