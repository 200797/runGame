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
	// 一旦,構造体回りで若干怪しい部分あるからバラの引数で

	// 揺れ位置情報更新
	RandShake(duration_, strength_, vibrato_, totalTime_);
	totalTime_++;
	if (totalTime_ >= duration_)
	{
		IsShaking_ = false;
		totalTime_ = 0.0f;
		// 元々の位置に戻す
		Camera::SetPosition(initPos_);
	}

}

void Shaker::RandShake(float duration, float strength, float vibrato, float totalTime)
{
	// このメソッドうっさんくさいから家でじっくりデバッグした方が良さそう
	// 多分がロジック自体を考え直した方がいい

	// 揺れの強さを決定
	strength_ = strength;
	std::uniform_real_distribution<float> dist(-strength, strength);
	float randX = dist(gen);
	float randY = dist(gen);
	
	// 実際に動かす
	Camera::SetPosition(XMFLOAT3(initPos_.x+randX, initPos_.y+randY, initPos_.z));

	// 初期位置-vibrato～初期位置+vibratoの間に収める
	vibrato_ = vibrato;
	float ratio = 1.0f - totalTime/ duration_;
	vibrato_ *= ratio; // フェードアウトのため、経過時間で揺れが弱くなるように

	float clampX;
	float clampY;
	std::clamp(clampX, initPos_.x - vibrato_, initPos_.x + vibrato_);
	std::clamp(clampX, initPos_.y - vibrato_, initPos_.y + vibrato_);

	// Clampした分また動かす
	Camera::SetPosition(XMFLOAT3(clampX, clampY, initPos_.z));
}

void Shaker::PerlinNoiseShake(float _duration, float _strength, float _vibrato, float _totalTime, XMFLOAT3 _initPos)
{
	// パーリンノイズの値をセット
	float strength = strength;
	float randOffset;
	float randX;
	float randY;

	// -strength ～ strength の値に変換
	randX *= strength;
	randY *= strength;

	// -vibrato ～ vibrato の値に変換
	float vibrato = _vibrato;
	float ratio = 1.0f - _totalTime / _duration;
	vibrato *= ratio;
	randX = std::clamp(randX, -vibrato, vibrato);
	randY = std::clamp(randY, -vibrato, vibrato);

	// 初期位置に加える形でセット
	Camera::SetPosition(XMFLOAT3(randX, randY, _initPos.z));
}

float Shaker::GetPerlinNoiseValue(float _offSet, float _speed, float _time)
{
	
}
