#include<iostream>
#include<sstream>
#include "ProcessManager.h"
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
    // vector<int> maxResources ={3, 2, 1};
    // PCB p1(1, 0, 5, maxResources);

    // cout<<"Process Id: "<< p1.pid<<" created with state: "<< p1.getStateString()<<endl;

    // p1.setState(ProcessState::READY);
    // cout<<"Process Id: "<< p1.pid<<" state changed to: "<< p1.getStateString()<<endl;

    // p1.setState(ProcessState::RUNNING);
    // cout<<"Process Id: "<< p1.pid<<" state changed to: "<< p1.getStateString()<<endl;

    // p1.setState(ProcessState::TERMINATED);
    // cout<<"Process Id: "<< p1.pid<<" state changed to: "<< p1.getStateString()<<endl;

    cout<<"\n=====  OS Simulator =====\n";
    printHelp();

    ProcessManager process;
    string input;
    
    while(true) {

        cout<<"Enter command (type 'help for options): ";
        getline(cin, input);

        if(input=="exit") {
            break;
        } else if(input=="help") {
            printHelp();
        } else if(input =="add") {
            int burstTime, arrivalTime;
            vector<int> maxResources;

            cout<<"Enter burst time: ";
            cin>>burstTime;

            cout<<"Enter arrival time: ";
            cin>>arrivalTime;

            cin.ignore();

            string resources;
            cout<<"Enter max resources (space-separated, e.g., 3 2 1): ";
            getline(cin, resources);

            stringstream ss(resources);
            int val;
            while(ss >> val) {
                maxResources.push_back(val);
            }

            process.createProcess(arrivalTime, burstTime, maxResources);
        } else if(input=="list") {
            process.listJobs();
        } else {
            cout<<"Unknown command. Type 'help' to see available commands.\n";
        }
    }
    cout<<"Exiting OS Simulator...\n";
    return 0;
}