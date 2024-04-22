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
    // �v���J�n���猻�݂܂ł̌o�ߎ���(�b)���v�Z
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = now - startTime_;
    return elapsed.count();
}