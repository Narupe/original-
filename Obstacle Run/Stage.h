#pragma once
#include "DxLib.h"
#include <string>

//存在可能な範囲
#define WORLD_LIMIT_LEFT   (2000.0f)     //左側
#define WORLD_LIMIT_RIGHT  (-3000.0f)    //右側
#define WORLD_LIMIT_UP     (-8000.0f)    //前
#define WORLD_LIMIT_DOWN   (1000.0f)     //後ろ


// ステージクラス
class Stage 
{
private:
    // 経過時間を管理する変数（ミリ秒単位）
    unsigned int previousTime;
    float elapsedTime;

public:
    Stage();
    void update();
    void draw();
    void updateGroundShape();
    void finalize();

    // 既存のメンバ変数
    VECTOR model_extend;
    int model_handle_stage;
    // 地面モデルのハンドル配列
    int ground_model_handle;
    int model_handle_gall;
    VECTOR model_position;
    VECTOR ground_position;
    VECTOR ground_extend;
};
