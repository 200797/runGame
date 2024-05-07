#pragma once
#include <chrono>

namespace Time
{
	using namespace std::chrono;
	using steady_clock = std::chrono::steady_clock;
	using time_point = std::chrono::time_point<steady_clock>;
		
	void Init();
	void Refresh();
	void Start();
	void Pause();
	void Resume();
	void Reset();

	float ElapsedTime();
	float DeltaTime();
	float End();
}
