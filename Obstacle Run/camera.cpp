#include "Camera.h"

Camera::Camera()
{
	//カメラの空間座標の初期化
	position = VGet(800.0f, 240.0f, 1500.0f);
	//カメラの位置と注視点をセット、注視点は原点
	SetCameraPositionAndTarget_UpVecY(position, VGet(0.0f, 0.0f, 0.0f));

	track = true;
}

void Camera::update(VECTOR pos)
{
	if (track)
	{
		// プレイヤーの真後ろかつ斜め上にカメラを配置
		float offsetX = 80.0f;    // X軸方向に80単位
		float offsetZ = 1840.0f;  // Z軸方向に1840単位
		float offsetY = 900.0f;   // Y軸方向に900単位（斜め上にするため）

		// 常にカメラはプレイヤーの後ろかつ斜め上に配置
		position = VGet(pos.x - offsetX,offsetY, pos.z + offsetZ);
	}

    // カメラの位置と注視点をセット、注視点はプレイヤー
    SetCameraPositionAndTarget_UpVecY(position, pos);
}

void Camera::draw()
{
	//座標の表示　GetColor(255, 255, 255)
	//DrawLine3D(VGet(-1000.0f, 0.0f, 0.0f), VGet(1000.0f, 0.0f, 0.0f), GetColor(255, 0, 0));			// x 赤
	//DrawLine3D(VGet(0.0f, -1000.0f, 0.0f), VGet(0.0f, 1000.0f, 0.0f), GetColor(0, 255, 0));			// y 青
	//DrawLine3D(VGet(0.0f, 0.0f, -1000.0f), VGet(0.0f, 0.0f, 1000.0f), GetColor(0, 0, 255));		// z 緑

	// DrawFormatString(10, 10, GetColor(255, 255, 255), "CAMERA(%f, %f, %f)", position.x, position.y, position.z);
}

void Camera::track_off()
{
	track = false;
}