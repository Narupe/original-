#pragma once
#include "DxLib.h"

class Camera
{
private:
	VECTOR position;          //カメラの座標
	bool track;               //追尾するかどうか

public:
	Camera();                 //コンストラクタ
	void update(VECTOR pos);  //カメラの座標の更新
	void draw();              //座標軸などの描画
	void track_off();
};