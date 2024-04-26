#include "Shaker.h"
#include "Engine/Camera.h"
#include <algorithm>


Shaker::Shaker(float ShakeDuration):
	gen(std::random_device()()), IsShaking_(true), totalTime_(0)
{
	initPos_ = Camera::GetPosition();
	duration_ = ShakeDuration;
}

Shaker::~Shaker()
{
	Camera::SetPosition(initPos_);
}

void Shaker::Update()
{
	// ��U,�\���̉��Ŏ኱�������������邩��o���̈�����

	// �h��ʒu���X�V
	RandShake(duration_, strength_, vibrato_, totalTime_);
	totalTime_++;
	if (totalTime_ >= duration_)
	{
		IsShaking_ = false;
		totalTime_ = 0.0f;
		// ���X�̈ʒu�ɖ߂�
		Camera::SetPosition(initPos_);
	}

}

void Shaker::RandShake(float duration, float strength, float vibrato, float totalTime)
{
	// ���̃��\�b�h�������񂭂�������Ƃł�������f�o�b�O���������ǂ�����
	// ���������W�b�N���̂��l����������������

	// �h��̋���������
	strength_ = strength;
	std::uniform_real_distribution<float> dist(-strength, strength);
	float randX = dist(gen);
	float randY = dist(gen);
	
	// ���ۂɓ�����
	Camera::SetPosition(XMFLOAT3(initPos_.x+randX, initPos_.y+randY, initPos_.z));

	// �����ʒu-vibrato�`�����ʒu+vibrato�̊ԂɎ��߂�
	vibrato_ = vibrato;
	float ratio = 1.0f - totalTime/ duration_;
	vibrato_ *= ratio; // �t�F�[�h�A�E�g�̂��߁A�o�ߎ��Ԃŗh�ꂪ�キ�Ȃ�悤��

	float clampX;
	float clampY;
	std::clamp(clampX, initPos_.x - vibrato_, initPos_.x + vibrato_);
	std::clamp(clampX, initPos_.y - vibrato_, initPos_.y + vibrato_);

	// Clamp�������܂�������
	Camera::SetPosition(XMFLOAT3(clampX, clampY, initPos_.z));
}

void Shaker::PerlinNoiseShake(float _duration, float _strength, float _vibrato, float _totalTime, XMFLOAT3 _initPos)
{
	// �p�[�����m�C�Y�̒l���Z�b�g
	float strength = strength;
	float randOffset;
	float randX;
	float randY;

	// -strength �` strength �̒l�ɕϊ�
	randX *= strength;
	randY *= strength;

	// -vibrato �` vibrato �̒l�ɕϊ�
	float vibrato = _vibrato;
	float ratio = 1.0f - _totalTime / _duration;
	vibrato *= ratio;
	randX = std::clamp(randX, -vibrato, vibrato);
	randY = std::clamp(randY, -vibrato, vibrato);

	// �����ʒu�ɉ�����`�ŃZ�b�g
	Camera::SetPosition(XMFLOAT3(randX, randY, _initPos.z));
}

float Shaker::GetPerlinNoiseValue(float _offSet, float _speed, float _time)
{
	
}
