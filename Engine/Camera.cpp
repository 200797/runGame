#include "camera.h"
#include "Direct3D.h"

using namespace Direct3D;

XMFLOAT3 _position;
XMFLOAT3 _target;
XMMATRIX _view;
XMMATRIX _proj;
XMMATRIX _billBoard;

// 揺れ情報
struct ShakeInfo
{
    float Duration; // 時間
    float Strength; // 揺れの強さ
    float Vibrato;  // どのくらい振動するか
    float StartTime; // 揺れ開始時間
};

ShakeInfo _shakeInfo;

// 初期化（プロジェクション行列作成）
void Camera::Initialize()
{
    _position = XMFLOAT3(0, 3, -10); // カメラの位置
    _target = XMFLOAT3(0, 0, 0);     // カメラの焦点

    // プロジェクション行列
    _proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)screenWidth_ / (FLOAT)screenHeight_, 0.1f, 1000.0f);

    // 揺れ情報初期化
    _shakeInfo.Duration = 0.0f;
    _shakeInfo.Strength = 0.0f;
    _shakeInfo.Vibrato = 0.0f;
    _shakeInfo.StartTime = 0.0f;
}

// 更新（ビュー行列作成）
void Camera::Update()
{
    // ビュー行列
    _view = XMMatrixLookAtLH(XMVectorSet(_position.x, _position.y, _position.z, 0),
        XMVectorSet(_target.x, _target.y, _target.z, 0), XMVectorSet(0, 1, 0, 0));

    // 揺れ処理
    UpdateShake();
}

// 揺れ更新
void Camera::UpdateShake()
{
    if (_shakeInfo.Duration > 0.0f && _shakeInfo.StartTime > 0.0f)
    {
        float currentTime = GetCurrentTime();
        float elapsedTime = currentTime - _shakeInfo.StartTime;

        if (elapsedTime <= _shakeInfo.Duration)
        {
            float strength = _shakeInfo.Strength * (1.0f - (elapsedTime / _shakeInfo.Duration));
            float randomX = RandomFloat(-strength, strength);
            float randomY = RandomFloat(-strength, strength);

            _position.x += randomX;
            _position.y += randomY;
        }
        else
        {
            // 揺れ終了

            _position = XMFLOAT3(0, 3, -10);

            _shakeInfo.Duration = 0.0f;
            _shakeInfo.Strength = 0.0f;
            _shakeInfo.Vibrato = 0.0f;
            _shakeInfo.StartTime = 0.0f;
        }
    }
}

// 焦点を設定
void Camera::SetTarget(XMFLOAT3 target) { _target = target; }

// 位置を設定
void Camera::SetPosition(XMFLOAT3 position) { _position = position; }

// 焦点を取得
XMFLOAT3 Camera::GetTarget() { return _target; }

// 位置を取得
XMFLOAT3 Camera::GetPosition() { return _position; }

// ビュー行列を取得
XMMATRIX Camera::GetViewMatrix() { return _view; }

// プロジェクション行列を取得
XMMATRIX Camera::GetProjectionMatrix() { return _proj; }

// ビルボード用回転行列を取得
XMMATRIX Camera::GetBillboardMatrix() { return _billBoard; }

// カメラを揺らす
void Camera::Shake(float duration, float strength, float vibrato)
{
    _shakeInfo.Duration = duration;
    _shakeInfo.Strength = strength;
    _shakeInfo.Vibrato = vibrato;
    _shakeInfo.StartTime = GetCurrentTime();
}

// 指定範囲内のランダムな浮動小数点数を取得するヘルパー関数
float Camera::RandomFloat(float min, float max)
{
    float scale = rand() / (float)RAND_MAX;
    return min + scale * (max - min);
}
