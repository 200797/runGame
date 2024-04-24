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

	void ShekePos(float duration, float strength, float vibrato, float totalTime);

private:
	// �������Y�ꂽ�����U�A��ō\���̂ɒ�����
		float shakeDuration_;	//�h�炵��������
		float strength_;			//�h��̋���
		float vibrato_;			//�h��͈̔�

		struct ShakeInfo
		{
			// �\���̂̃A�N�Z�X����Y�ꂿ����
			float duration;
			float strength;
			float vibrato;
		};

	XMFLOAT3 backUpPos_;	 // �h�炷�O�̃J�����ʒu
	bool IsSheking_;		//�h��Ă��邩�t���O
	float totalShakeTime_;	//�h��̌o�ߎ���

	std::mt19937 gen;

};

