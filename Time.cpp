#include "Time.h"
#include <Windows.h>

namespace
{
    LARGE_INTEGER freq;
    LARGE_INTEGER current;
    LARGE_INTEGER pausedTime;
    float deltaTime;
    bool paused = false;
    LARGE_INTEGER startTime;
    LARGE_INTEGER endTime;
}

void Time::Init()
{
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&current);
    startTime = current;
}

void Time::Refresh()
{
    if (!paused)
    {
        LARGE_INTEGER last = current;
        QueryPerformanceCounter(&current);
        deltaTime = static_cast<float>(current.QuadPart - last.QuadPart) / freq.QuadPart;
    }
}

void Time::Start()
{
    paused = false;
    QueryPerformanceCounter(&current);
    startTime = current;
}

void Time::Pause()
{
    if (!paused)
    {
        paused = true;
        QueryPerformanceCounter(&pausedTime);
    }
}

void Time::Resume()
{
    if (paused)
    {
        paused = false;
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        LARGE_INTEGER pauseDuration;
        pauseDuration.QuadPart = now.QuadPart - pausedTime.QuadPart;
        current.QuadPart += pauseDuration.QuadPart;
        startTime.QuadPart += pauseDuration.QuadPart;
    }
}

void Time::Reset()
{
    QueryPerformanceCounter(&current);
    startTime = current;
}

float Time::DeltaTime()
{
    return deltaTime;
}

float Time::End()
{
    QueryPerformanceCounter(&endTime);
    return static_cast<float>(endTime.QuadPart - startTime.QuadPart) / freq.QuadPart;
}

float Time::ElapsedTime()
{
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return static_cast<float>(now.QuadPart - startTime.QuadPart) / freq.QuadPart;
}