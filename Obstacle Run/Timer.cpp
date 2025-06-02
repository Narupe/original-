#include "Timer.h"
#include "DxLib.h"

Timer::Timer()
{
    initialize();
}

void Timer::initialize()
{
    time_start = GetNowCount();        // 現在経過時間を得る
    time = 0.0f;                       // 現在時間の初期化
}

void Timer::update()
{
    // 端末が起動してからの経過時間（単位 ミリ秒）を取得
    int nowTime = GetNowCount();

    // 前回との差分を単位 秒で得る
    time += (nowTime - time_start) / 100.0f;

    // 開始時刻と現在時刻の差を格納する
    time_start = nowTime;
}

void Timer::draw()
{
    // 経過時間を描画
    DrawFormatString(250, 10, GetColor(255, 100, 100), _T("%.1f"), time); // 1桁の小数精度で表示
}

