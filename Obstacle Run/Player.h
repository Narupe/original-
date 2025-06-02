#pragma once

#include "DxLib.h"
#include <string>

// キャラクターの設定
#define CHARA_MOVE_SPEED      (40.0f)     // キャラクターの移動速度
#define CHARA_JUMP_POWER      (5.0f)      // ジャンプ力
#define CHARA_SCALE           (4.0f)      // キャラクターのモデルスケール

#define CHARA_RADIUS          (200.0f)       // プレイヤーの当たり判定の半径

// 位置の初期設定
#define CHARA_START_X         (-320.0f)      // 初期X座標
#define CHARA_START_Y         (0.0f)         // 初期Y座標
#define CHARA_START_Z         (600.0f)       // 初期Z座標

// キャラクター
#define GAME_CHARA_MAN		  (0)

// 重力の設定
#define GRAVITY               (-0.3f)       // 重力加速度 (下方向)

// プレイヤーの入力情報を格納する構造体
struct PADINPUT
{
    int NowInput;    // 現在の入力（フレーム単位）
    int EdgeInput;   // 現在のフレームで押されたボタンのみビットが立っている入力値
};

class Player 
{
private:
    static int model_handle_man;        // 男のハンドル
    static const int AnimeNum = 3;      // アニメーションの数
    static int currentAnim;             // 現在のアニメーション番号
    static int animeId[AnimeNum];       // アニメーションID

    bool isPlayingOnceAnim = false;     // アニメーション再生フラグ
    bool jumpAnimPlaying = false;       // ジャンプアニメーション再生フラグ

    int model_handle;                   // モデルハンドル
    VECTOR model_position;              // モデルの位置
    VECTOR model_rotation;              // モデルの回転
    VECTOR model_extend;                // モデルのスケール
    float chara_radius;                 // モデルの半径
    float velocity_y;                   // Y軸方向の速度
    bool isOnGround = true;
    float JumpPower = 0.0f;
    float speed;
    VECTOR model_move_external;	        // 3Dモデルへの外力

public:
    Player();
    Player(int name, VECTOR pos);
    void initialize(int name, float extendf, VECTOR pos, bool anim_load);
    void update();
    void apply_gravity();
    void update_control();
    void update_anim();
    void draw();
    void finalize();
    bool is_move();
    void add_vector(VECTOR vec);	  // 外からの力をぶつける
    void control_off();				  // 操作できなくする

    VECTOR get_position();

private:
    VECTOR handle_movement_input(VECTOR moveVec, float speed);
};