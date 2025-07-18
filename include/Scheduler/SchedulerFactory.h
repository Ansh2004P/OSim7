// Scheduler/SchedulerFactory.h
#pragma once

#include "SchedulerStrategy.h"

class SchedulerFactory {
public:
    static Scheduler* createScheduler();
};
