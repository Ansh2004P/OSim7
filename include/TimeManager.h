// TimeManager.h
#pragma once

/// @brief Manages global system time across the simulation.
class TimeManager {
public:
    /// @brief Gets the current system time.
    static int getTime();

    /// @brief Advances the system time by 1 tick.
    static void tick();

    /// @brief Resets the system time to 0.
    static void reset();

private:
    static int systemTime;
};
