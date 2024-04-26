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
	// ‘‚«•û–Y‚ê‚½‚©‚çˆê’UAŒã‚Å\‘¢‘Ì‚É’¼‚µ‚Ä
		float duration_;	//—h‚ç‚µ‚½‚¢ŠÔ
		float strength_;			//—h‚ê‚Ì‹­‚³
		float vibrato_;			//—h‚ê‚Ì”ÍˆÍ

		struct ShakeInfo
		{
			// \‘¢‘Ì‚ÌƒAƒNƒZƒXü‚è–Y‚ê‚¿‚Á‚½
			float duration;
			float strength;
			float vibrato;
		};

	XMFLOAT3 initPos_;	 // —h‚ç‚·‘O‚ÌƒJƒƒ‰ˆÊ’u
	bool IsShaking_;		//—h‚ê‚Ä‚¢‚é‚©ƒtƒ‰ƒO
	float totalTime_;	//—h‚ê‚ÌŒo‰ßŠÔ

	std::mt19937 gen;

};

