#include "Player.h"

#pragma once

class Timer 
{
private:
	int time_start;		// �J�n����
	float time;			// �o�ߎ���

public:
	// �V���O���g��
	static Timer* GetInstance()
	{
		static Timer instance;
		return &instance;
	}

	Timer();			// �R���X�g���N�^
	void initialize();	// ������
	void update();		// �X�V
	void draw();		// �`��
	float GetDeltaTime() { return time; }
};