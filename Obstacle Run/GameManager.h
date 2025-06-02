#pragma once

#include "Player.h"
#include "Obstacle.h"
#include "Stage.h"
#include "Camera.h"
#include "Timer.h"
#include "Collision.h"
#include <vector>

// ゲームの状態
#define GAME_STATE_TITLE    (0)
#define GAME_STATE_SELECT   (1)
#define GAME_STATE_PLAY     (2)
#define GAME_STATE_RESULT   (3)

enum class GAME_STATE : int   //enumの方がよい(enum = まとめ）
{
    TITLE,
    SELECT,
    PLAY,
    RESULT,

    MAX,             //enumの中に納める
    UNKNOWN = -1,    //enumの中に納める
};

enum class SAMPLE_FLAG : unsigned int
{
    INVICIBLE = 1 << 0,   //0x00000001
    CAN_SHOT = 1 << 1,    //0x00000002
    CAN_JUMP = 1 << 2,    //0x00000004
    CAN_MOVE = 1 << 3,    //0x00000008
    CAN_ATTACK = 1 << 4,  //0x00000010
    CAN_DEFENCE = 1 << 5, //0x00000020

    UNKNOWN = 0,
};

//ゲームの難易度
#define GAME_MODE_EASY     0
#define GAME_MODE_NORMAL   1
#define GAME_MODE_HARD     2

enum class GAME_MODE : int   //enumの方がよい
{
    EASY,
    NORMAL,
    HARD,

    MAX,
    UNKNOWN = -1,
};

class Game_manager
{
private:
    int game_state;                     // ゲームの状態
    int game_mode;		                // ゲームの難易度
    int game_character;                 // ゲームで使用するキャラクター

    int game_span;		                // ゲーム終了後の待機時間
    bool game_clear;	                // ゲームクリアフラグ
    bool game_miss;		                // ゲーム失敗フラグ　　boolで定義

    Player obj_player;                  // プレイヤーインスタンス
    std::vector<Obstacle> obj_obstacle;	// 障害物インスタンス
    Stage obj_stage;                    // ステージインスタンス
    Camera obj_camera;                  // カメラインスタンス
    Timer obj_timer;                    // タイマー

    int obstacle_span;                  // 障害物作成の現間隔
    int obstacle_interval;              // 障害物作成の制限間隔
    int key_span;                       // キー入力の制限間隔

    int font_count_down;                // カウントダウン用のフォント
    bool is_bgm_title_playing = false;  // タイトルBGMフラグ
    bool is_bgm_play_playing = false;   // プレイ中BGMフラグ
    bool is_bgm_over_playing = false;   // ゲームオーバーBGMフラグ

    // XorShift乱数生成用の状態変数（必要に応じてGame_managerのメンバ変数にしてもOK）
    unsigned int x = 123456789;
    unsigned int y = 362436069;
    unsigned int z = 521288629;
    unsigned int w = 88675123;

    unsigned int xorshift()
    {
        unsigned int t = x ^ (x << 11);
        x = y; y = z; z = w;
        w = w ^ (w >> 19) ^ (t ^ (t >> 8));
        return w;
    }

    // 範囲付き乱数（0～max-1）
    int xorshift_rand(int max)
    {
        return xorshift() % max;
    }

public:
    Game_manager();             // コンストラクタ
    void update();              // 更新処理
    void draw();                // 描画処理
    void finalize();            // モデルデータの開放処理
    void obstacle_make();       // 障害物作成・削除

    void GameState_Title();     // タイトル画面の処理を行います
};

