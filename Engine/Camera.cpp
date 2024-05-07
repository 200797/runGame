#include "camera.h"
#include "Direct3D.h"

using namespace Direct3D;

XMFLOAT3 _position;
XMFLOAT3 _target;
XMMATRIX _view;
XMMATRIX _proj;
XMMATRIX _billBoard;

// �h����
struct ShakeInfo
{
    float Duration; // ����
    float Strength; // �h��̋���
    float Vibrato;  // �ǂ̂��炢�U�����邩
    float StartTime; // �h��J�n����
};

ShakeInfo _shakeInfo;

// �������i�v���W�F�N�V�����s��쐬�j
void Camera::Initialize()
{
    _position = XMFLOAT3(0, 3, -10); // �J�����̈ʒu
    _target = XMFLOAT3(0, 0, 0);     // �J�����̏œ_

    // �v���W�F�N�V�����s��
    _proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)screenWidth_ / (FLOAT)screenHeight_, 0.1f, 1000.0f);

    // �h���񏉊���
    _shakeInfo.Duration = 0.0f;
    _shakeInfo.Strength = 0.0f;
    _shakeInfo.Vibrato = 0.0f;
    _shakeInfo.StartTime = 0.0f;
}

// �X�V�i�r���[�s��쐬�j
void Camera::Update()
{
    // �r���[�s��
    _view = XMMatrixLookAtLH(XMVectorSet(_position.x, _position.y, _position.z, 0),
        XMVectorSet(_target.x, _target.y, _target.z, 0), XMVectorSet(0, 1, 0, 0));

    // �h�ꏈ��
    UpdateShake();
}

// �h��X�V
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
            // �h��I��

            _position = XMFLOAT3(0, 3, -10);

            _shakeInfo.Duration = 0.0f;
            _shakeInfo.Strength = 0.0f;
            _shakeInfo.Vibrato = 0.0f;
            _shakeInfo.StartTime = 0.0f;
        }
    }
}

// �œ_��ݒ�
void Camera::SetTarget(XMFLOAT3 target) { _target = target; }

// �ʒu��ݒ�
void Camera::SetPosition(XMFLOAT3 position) { _position = position; }

// �œ_���擾
XMFLOAT3 Camera::GetTarget() { return _target; }

// �ʒu���擾
XMFLOAT3 Camera::GetPosition() { return _position; }

// �r���[�s����擾
XMMATRIX Camera::GetViewMatrix() { return _view; }

// �v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix() { return _proj; }

// �r���{�[�h�p��]�s����擾
XMMATRIX Camera::GetBillboardMatrix() { return _billBoard; }

// �J������h�炷
void Camera::Shake(float duration, float strength, float vibrato)
{
    _shakeInfo.Duration = duration;
    _shakeInfo.Strength = strength;
    _shakeInfo.Vibrato = vibrato;
    _shakeInfo.StartTime = GetCurrentTime();
}

// �w��͈͓��̃����_���ȕ��������_�����擾����w���p�[�֐�
float Camera::RandomFloat(float min, float max)
{
    float scale = rand() / (float)RAND_MAX;
    return min + scale * (max - min);
}
