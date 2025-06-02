#include "Timer.h"
#include "DxLib.h"

Timer::Timer()
{
    initialize();
}

void Timer::initialize()
{
    time_start = GetNowCount();        // ���݌o�ߎ��Ԃ𓾂�
    time = 0.0f;                       // ���ݎ��Ԃ̏�����
}

void Timer::update()
{
    // �[�����N�����Ă���̌o�ߎ��ԁi�P�� �~���b�j���擾
    int nowTime = GetNowCount();

    // �O��Ƃ̍�����P�� �b�œ���
    time += (nowTime - time_start) / 100.0f;

    // �J�n�����ƌ��ݎ����̍����i�[����
    time_start = nowTime;
}

void Timer::draw()
{
    // �o�ߎ��Ԃ�`��
    DrawFormatString(250, 10, GetColor(255, 100, 100), _T("%.1f"), time); // 1���̏������x�ŕ\��
}

