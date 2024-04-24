#include "Shaker.h"
#include "Engine/Camera.h"


Shaker::Shaker(float ShakeDuration):
	gen(std::random_device()()), IsSheking_(true), totalShakeTime_(0)
{
	backUpPos_ = Camera::GetPosition();
	shakeDuration_ = ShakeDuration;
}

Shaker::~Shaker()
{
	Camera::SetPosition(backUpPos_);
}

void Shaker::Update()
{
	if (!IsSheking_) return;

	// ShekePos(); // ÀÛ‚É—h‚ç‚·
	totalShakeTime_++;
	if (totalShakeTime_ >= shakeDuration_)
	{
		IsSheking_ = false;
		Camera::SetPosition(backUpPos_);
	}
}

void Shaker::ShekePos(float duration, float strength, float vibrato, float totalTime)
{
	// ‚µ‚É‘Ê
	// —h‚ê‚Ì‹­‚³‚ğŒˆ’è
	strength_ = strength;
	std::uniform_real_distribution<float> dist(-strength, strength);
	// Œ»İ‚ÌˆÊ’u‚É‰Á‚¦‚é
	float randX = dist(gen);
	float randY = dist(gen);
	
	transform_.position_.x += randX;
	transform_.position_.y += randY;

	vibrato_ = vibrato;
	float ratio = 1.0f - totalTime/ shakeDuration_;
	vibrato_ *= ratio;
	transform_.position_.x;

	// ‚±‚Á‚©‚ç‰ö‚µ‚¢‚©‚çˆê’U•Û—¯
	// Camera::SetPosition();
}


