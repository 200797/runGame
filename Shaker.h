#pragma once

#include <random>
#include "Engine/GameObject.h"

class Shaker : public GameObject
{
public:
	Shaker();
	Shaker(float ShakeDuration);
	~Shaker();
	void Update() override;

	void RandShake(float duration, float strength, float vibrato, float totalTime);
	void PerlinNoiseShake(float duration, float strength, float vibrato, float totalTime, XMFLOAT3 _initPos);
private:
	float GetPerlinNoiseValue(float _offSet, float _speed, float _time);

private:
	// �������Y�ꂽ�����U�A��ō\���̂ɒ�����
		float duration_;	//�h�炵��������
		float strength_;			//�h��̋���
		float vibrato_;			//�h��͈̔�

		struct ShakeInfo
		{
			// �\���̂̃A�N�Z�X����Y�ꂿ����
			float duration;
			float strength;
			float vibrato;
		};

	XMFLOAT3 initPos_;	 // �h�炷�O�̃J�����ʒu
	bool IsShaking_;		//�h��Ă��邩�t���O
	float totalTime_;	//�h��̌o�ߎ���

	std::mt19937 gen;

};

