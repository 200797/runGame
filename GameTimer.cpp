#include "GameTimer.h"

GameTimer::GameTimer()
{
}

void GameTimer::Start() 
{
    startTime_ = std::chrono::steady_clock::now();
}

void GameTimer::Stop() 
{
    stopTime_ = std::chrono::steady_clock::now();
}


double GameTimer::GetElapsedTime() 
{
    std::chrono::duration<double> elapsed = stopTime_ - startTime_;
    return elapsed.count();
}

double GameTimer::GetCurrentElapsedTime() 
{
    // 計測開始から現在までの経過時間(秒)を計算
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = now - startTime_;
    return elapsed.count();
}