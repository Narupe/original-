#include "Camera.h"

Camera::Camera()
{
	//�J�����̋�ԍ��W�̏�����
	position = VGet(800.0f, 240.0f, 1500.0f);
	//�J�����̈ʒu�ƒ����_���Z�b�g�A�����_�͌��_
	SetCameraPositionAndTarget_UpVecY(position, VGet(0.0f, 0.0f, 0.0f));

	track = true;
}

void Camera::update(VECTOR pos)
{
	if (track)
	{
		// �v���C���[�̐^��납�΂ߏ�ɃJ������z�u
		float offsetX = 80.0f;    // X��������80�P��
		float offsetZ = 1840.0f;  // Z��������1840�P��
		float offsetY = 900.0f;   // Y��������900�P�ʁi�΂ߏ�ɂ��邽�߁j

		// ��ɃJ�����̓v���C���[�̌�납�΂ߏ�ɔz�u
		position = VGet(pos.x - offsetX,offsetY, pos.z + offsetZ);
	}

    // �J�����̈ʒu�ƒ����_���Z�b�g�A�����_�̓v���C���[
    SetCameraPositionAndTarget_UpVecY(position, pos);
}

void Camera::draw()
{
	//���W�̕\���@GetColor(255, 255, 255)
	//DrawLine3D(VGet(-1000.0f, 0.0f, 0.0f), VGet(1000.0f, 0.0f, 0.0f), GetColor(255, 0, 0));			// x ��
	//DrawLine3D(VGet(0.0f, -1000.0f, 0.0f), VGet(0.0f, 1000.0f, 0.0f), GetColor(0, 255, 0));			// y ��
	//DrawLine3D(VGet(0.0f, 0.0f, -1000.0f), VGet(0.0f, 0.0f, 1000.0f), GetColor(0, 0, 255));		// z ��

	// DrawFormatString(10, 10, GetColor(255, 255, 255), "CAMERA(%f, %f, %f)", position.x, position.y, position.z);
}

void Camera::track_off()
{
	track = false;
}