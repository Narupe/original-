#include "Player.h"

#pragma once

class Timer 
{
private:
	int time_start;		// 開始時間
	float time;			// 経過時間

public:
	// シングルトン
	static Timer* GetInstance()
	{
		static Timer instance;
		return &instance;
	}

	Timer();			// コンストラクタ
	void initialize();	// 初期化
	void update();		// 更新
	void draw();		// 描画
	float GetDeltaTime() { return time; }
};