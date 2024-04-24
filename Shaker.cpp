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

	// ShekePos(); // 実際に揺らす
	totalShakeTime_++;
	if (totalShakeTime_ >= shakeDuration_)
	{
		IsSheking_ = false;
		Camera::SetPosition(backUpPos_);
	}
}

void Shaker::ShekePos(float duration, float strength, float vibrato, float totalTime)
{
	// 試しに書写
	// 揺れの強さを決定
	strength_ = strength;
	std::uniform_real_distribution<float> dist(-strength, strength);
	// 現在の位置に加える
	float randX = dist(gen);
	float randY = dist(gen);
	
	transform_.position_.x += randX;
	transform_.position_.y += randY;

	vibrato_ = vibrato;
	float ratio = 1.0f - totalTime/ shakeDuration_;
	vibrato_ *= ratio;
	transform_.position_.x;

	// こっから怪しいから一旦保留
	// Camera::SetPosition();
}


