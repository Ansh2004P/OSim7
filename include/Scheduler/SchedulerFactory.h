// Scheduler/SchedulerFactory.h
#pragma once

#include "Scheduler/Scheduler.h"

class SchedulerFactory {
public:
    static Scheduler* createScheduler();
};
