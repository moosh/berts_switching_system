/*******************************************************************************

    stopwatch.h

    Copyright (c) 2025 Mooshwerks
    All Rights Reserved
    
*******************************************************************************/

#pragma once

#include <ctime>
#include <chrono>

class Stopwatch
{
    double mStartTime;
    double mStopTime;

public:
    Stopwatch()
    {
    }

    ~Stopwatch()
    {

    }

    void start()
    {
        mStartTime = now();
    }

    void stop()
    {
        mStopTime = now();
    }

    double elapsedMilliseconds()
    {
        return this->elapsedSeconds() / 1000.0f;
    }

    double elapsedSeconds()
    {
        return mStopTime - mStartTime;
    }

    static double now()
    {
        using namespace std::chrono;
        return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count() / double(1e6);
    }
};
