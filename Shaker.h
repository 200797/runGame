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
	// 書き方忘れたから一旦、後で構造体に直して
		float duration_;	//揺らしたい時間
		float strength_;			//揺れの強さ
		float vibrato_;			//揺れの範囲

		struct ShakeInfo
		{
			// 構造体のアクセス周り忘れちった
			float duration;
			float strength;
			float vibrato;
		};

	XMFLOAT3 initPos_;	 // 揺らす前のカメラ位置
	bool IsShaking_;		//揺れているかフラグ
	float totalTime_;	//揺れの経過時間

	std::mt19937 gen;

};

