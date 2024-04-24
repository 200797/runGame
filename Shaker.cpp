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

	// ShekePos(); // ���ۂɗh�炷
	totalShakeTime_++;
	if (totalShakeTime_ >= shakeDuration_)
	{
		IsSheking_ = false;
		Camera::SetPosition(backUpPos_);
	}
}

void Shaker::ShekePos(float duration, float strength, float vibrato, float totalTime)
{
	// �����ɏ���
	// �h��̋���������
	strength_ = strength;
	std::uniform_real_distribution<float> dist(-strength, strength);
	// ���݂̈ʒu�ɉ�����
	float randX = dist(gen);
	float randY = dist(gen);
	
	transform_.position_.x += randX;
	transform_.position_.y += randY;

	vibrato_ = vibrato;
	float ratio = 1.0f - totalTime/ shakeDuration_;
	vibrato_ *= ratio;
	transform_.position_.x;

	// ������������������U�ۗ�
	// Camera::SetPosition();
}


