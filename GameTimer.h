#pragma once

#include <chrono>

class GameTimer {
public:
    GameTimer();
    void Start();
    void Stop();
    double GetElapsedTime();
    double GetCurrentElapsedTime();

private:
    std::chrono::steady_clock::time_point startTime_;
    std::chrono::steady_clock::time_point stopTime_;
};
