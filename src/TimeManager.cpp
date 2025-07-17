// TimeManager.cpp
#include "TimeManager.h"

int TimeManager::systemTime = 0;

int TimeManager::getTime() {
    return systemTime;
}

void TimeManager::tick() {
    systemTime++;
}

void TimeManager::reset() {
    systemTime = 0;
}
