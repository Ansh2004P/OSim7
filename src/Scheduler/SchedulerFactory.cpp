// Scheduler/SchedulerFactory.cpp

#include <iostream>
#include "Scheduler/SchedulerFactory.h"
#include "Scheduler/FCFS.h"
#include "Scheduler/RoundRobin.h"
#include "Scheduler/SJF.h"

using namespace std;

Scheduler *SchedulerFactory::createScheduler() {
    int choice;
    cout << "\nChoose scheduling algorithm:\n";
    cout << "1. FCFS\n";
    cout << "2. Round Robin\n";
    cout << "3. Shortest Job First\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        return new FCFS();
    } else if (choice == 2) {
        int tq;
        cout << "Enter time quantum for Round Robin: ";
        cin >> tq;
        return new RoundRobin(tq);
    } else if(choice == 3) {
        return new SJF();
    } else {
        cout << "Invalid choice! Defaulting to FCFS.\n";
        return new FCFS();
    }
}