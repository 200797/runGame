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
	// 書き方忘れたから一旦、後で構造体に直して
		float shakeDuration_;	//揺らしたい時間
		float strength_;			//揺れの強さ
		float vibrato_;			//揺れの範囲

		struct ShakeInfo
		{
			// 構造体のアクセス周り忘れちった
			float duration;
			float strength;
			float vibrato;
		};

	XMFLOAT3 backUpPos_;	 // 揺らす前のカメラ位置
	bool IsSheking_;		//揺れているかフラグ
	float totalShakeTime_;	//揺れの経過時間

	std::mt19937 gen;

};

