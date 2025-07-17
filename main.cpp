#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

#include "Scheduler/SchedulerFactory.h"
#include "ProcessManager.h"
#include "TimeManager.h"

// #include "PCB.h"

using namespace std;

void printHelp() {
    std::cout << "Commands:\n"
              << "  add        - Add a new process\n"
              << "  list       - Show job queue\n"
              << "  help       - Show this help message\n"
              << "  exit       - Quit the simulator\n";
}

int main() {
    cout << "\n=====  OS Simulator =====\n";
    printHelp();

    ProcessManager process;
    string input;

    Scheduler *scheduler = nullptr;
    while (!scheduler) {
        scheduler = SchedulerFactory::createScheduler();
        if (!scheduler)
        {
            cout << "Invalid scheduler choice. Please try again.\n";
        }
    }

    while (true) {
        cout << "Enter command (type 'help for options): ";
        getline(cin, input);

        if (input == "exit") {
            break;
        }
        else if (input == "help") {
            printHelp();
        }
        else if (input == "add") {
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
            while (ss >> val)
            {
                maxResources.push_back(val);
            }

            auto pcb = process.createProcess(arrivalTime, burstTime, maxResources);
            scheduler->addProcess(pcb);
        }
        else if (input == "list") {
            process.listJobs();
        }
        else if (input == "simulate") {
            int ticks;
            cout << "Enter number of time units to simulate: ";
            cin >> ticks;
            cin.ignore();

            for (int i = 0; i < ticks; ++i) {
                TimeManager::tick();
                scheduler->simulateTimeStep(TimeManager::getTime());
                this_thread::sleep_for(chrono::milliseconds(500));
            }
        }
        else {
            cout << "Unknown command. Type 'help' to see available commands.\n";
        }
    }

    cout << "Exiting OS Simulator...\n";
    delete scheduler;     // Clean up the scheduler instance
    TimeManager::reset(); // Reset the time manager
    cout << "Goodbye!\n";
    return 0;
}
