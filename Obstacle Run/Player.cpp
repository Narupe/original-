#include "Player.h"
#include "Stage.h"
#include "camera.h"
#include "Timer.h"

// プレイヤーのモデルハンドル
int Player::model_handle_man = -1;
const int AnimeFrame = 30;           // アニメーションのフレーム数/秒
const int AnimeNum = 3;              // アニメーションの数

int animeIndex = 0;                  // 現在のアニメーションインデックス
float animeTime = 0;                 // アニメーションの進行時間
int previousAnimeIndex = 0;          // 前回のアニメーションインデックス

// アニメーションのアタッチ
int attachIndex[AnimeNum];
float animeTotalTime[AnimeNum];

// プレイヤーの状態フラグ
bool isMoving = false;               // 動いているかどうか

// コンストラクタ：Player オブジェクトを初期化
Player::Player()
{
    // モデルをロード
    model_handle_man = MV1LoadModel(_T("../resource/3Dmodel/passive_marker_man.mv1"));
    if (model_handle_man == -1)
    {
        printf("Model load failed: passive_marker_man.mv1\n"); // モデルの読み込み失敗時
        return;
    }
    // 初期化関数を呼び出す（プレイヤーの名前、拡張スケール、位置、アニメーションのロード有無）
    initialize(GAME_CHARA_MAN, 20.0f, VGet(0.0f, 0.0f, 0.0f), false);
}

// 引数付きコンストラクタ：名前と位置を指定してプレイヤーを初期化
Player::Player(int name, VECTOR pos)
{
    if (name == GAME_CHARA_MAN)
    {
        // プレイヤーを初期化
        initialize(name, 20.0f, pos, true);
    }
}

// プレイヤーの初期化関数
void Player::initialize(int name, float extendf, VECTOR pos, bool anim_load)
{
    if (name == GAME_CHARA_MAN)
    {
        // モデルを複製
        model_handle = MV1DuplicateModel(model_handle_man);
        if (model_handle == -1)
        {
            printf("Model duplicate failed for character\n"); // モデル複製失敗時
            return;
        }
    }

    // モデルのスケールを設定
    model_extend = VGet(CHARA_SCALE, CHARA_SCALE, CHARA_SCALE);
    MV1SetScale(model_handle, model_extend);

    // モデルの初期位置を設定
    model_position = VGet(CHARA_START_X + pos.x, CHARA_START_Y + pos.y, CHARA_START_Z + pos.z);
    model_rotation = VGet(90.0f, 0.0f, 0.0f);                // 初期回転
    MV1SetPosition(model_handle, model_position);

    // ジャンプ力
    JumpPower = 0.0f;

    // アニメーションの読み込み
    int animeId[AnimeNum] = {
        MV1LoadModel(_T("../resource/Action/Arm Stretching (1).mv1")),
        MV1LoadModel(_T("../resource/Action/Running.mv1")),
        MV1LoadModel(_T("../resource/Action/Jump.mv1")),
    };

    // アニメーションの確認とアタッチ
    for (int i = 0; i < AnimeNum; ++i)
    {
        if (animeId[i] == -1)
        {
            printf("Failed to load animation: %d\n", i);   // アニメーションの読み込み失敗時
            return;
        }

        // アニメーションをモデルにアタッチ
        attachIndex[i] = MV1AttachAnim(model_handle, 0, animeId[i]);
        if (attachIndex[i] == -1)
        {
            printf("Failed to attach animation: %d\n", i); // アニメーションのアタッチ失敗時
            return;
        }

        // アニメーションのブレンド率設定
        MV1SetAttachAnimBlendRate(model_handle, attachIndex[i], (i == animeIndex ? 1.0f : 0.0f));
        animeTotalTime[i] = MV1GetAttachAnimTotalTime(model_handle, attachIndex[i]);
    }

    //  前回のアニメーションインデックス
    previousAnimeIndex = 0;
}

// プレイヤーの更新処理
void Player::update()
{
    update_control();  // 入力の取得と移動処理
    update_anim();     // アニメーションの更新
    apply_gravity();   // 重力の適用
}

// 重力の適用処理
void Player::apply_gravity()
{
    bool isJumping = (model_position.y > 0.0f);

    // プレイヤーが地面にいるか確認
    if (model_position.y <= 0.0f)
    {
        velocity_y = 0.0f;
        model_position.y = 0.0f;

        if (isJumping)
        {
            isJumping = false;
        }
    }
    else
    {
        velocity_y += GRAVITY * 0.019f;            // 重力の適用
    }

    // 位置の更新
    model_position.y += velocity_y;
    MV1SetPosition(model_handle, model_position);  // モデルの位置を更新
}

// 入力に基づいた移動処理
void Player::update_control()
{
    VECTOR moveVec = VGet(0.0f, 0.0f, 0.0f);
    float speed = CHARA_MOVE_SPEED;

    // ジャンプ処理（押した瞬間にのみ反応）
    if (CheckHitKey(KEY_INPUT_SPACE) && isOnGround && !jumpAnimPlaying)
    {
        JumpPower = CHARA_JUMP_POWER;
        isOnGround = false;
        isMoving = true;

        // アニメ再生開始
        animeIndex = 2;               // ジャンプアニメ
        jumpAnimPlaying = true;       // 1回しか再生されないように
        isPlayingOnceAnim = true;
    }

    // ジャンプ中の物理挙動
    if (!isOnGround)
    {
        JumpPower += GRAVITY;        // 重力で減速
        model_position.y += JumpPower;

        // 地面に到達（y = 0）したら着地
        if (model_position.y <= 0.0f)
        {
            model_position.y = 0.0f;
            isOnGround = true;
            JumpPower = 0.0f;
        }
    }

    // 横方向の移動（XZ平面）
    moveVec = handle_movement_input(moveVec, speed);
    moveVec = VAdd(moveVec, model_move_external);
    model_move_external = VGet(0.0f, 0.0f, 0.0f);

    model_position = VAdd(model_position, moveVec);     // XZ位置の更新

    // プレイヤーが動いている場合、ワールドの制限内に位置を調整
    if (isMoving)
    {
        if (WORLD_LIMIT_DOWN < model_position.z) model_position.z = WORLD_LIMIT_DOWN;
        if (WORLD_LIMIT_LEFT < model_position.x) model_position.x = WORLD_LIMIT_LEFT;
        if (model_position.x < WORLD_LIMIT_RIGHT) model_position.x = WORLD_LIMIT_RIGHT;
    }

    // モデル位置の更新
    MV1SetPosition(model_handle, model_position);

    // update_control のアニメ選択ロジックの最後
    if (!isPlayingOnceAnim) 
    {
        if (!isOnGround) animeIndex = 2;
        else if (isMoving)    animeIndex = 1;
        else                  animeIndex = 0;
    }
}

// 移動入力の処理
VECTOR Player::handle_movement_input(VECTOR moveVec, float speed)
{
    moveVec = VAdd(moveVec, VGet(0.0f, 0.0f, -speed));  // 基本的に前進
    isMoving = true;

    // Wキーで停止
    if (CheckHitKey(KEY_INPUT_W))
    {
        moveVec = VGet(0.0f, 0.0f, 0.0f);
        isMoving = false;
    }
    // Dキーで右移動
    if (CheckHitKey(KEY_INPUT_D))
    {
        moveVec = VAdd(moveVec, VGet(-speed, 0.0f, 0.0f));
    }
    // Aキーで左移動
    if (CheckHitKey(KEY_INPUT_A))
    {
        moveVec = VAdd(moveVec, VGet(speed, 0.0f, 0.0f));
    }

    return moveVec;
}

//アニメーションの処理
void Player::update_anim()
{
    if (animeIndex != previousAnimeIndex)
    {
        if (previousAnimeIndex != -1)
        {
            MV1SetAttachAnimBlendRate(model_handle, attachIndex[previousAnimeIndex], 0.0f);
        }

        MV1SetAttachAnimBlendRate(model_handle, attachIndex[animeIndex], 1.0f);
        animeTime = 0.0f;
        previousAnimeIndex = animeIndex;
    }

    // アニメーションの再生速度
    animeTime += 0.5f;

    // 一回再生アニメの終了判定
    if (isPlayingOnceAnim)
    {
        MV1SetAttachAnimTime(model_handle, attachIndex[animeIndex], animeTime);

        if (animeTime >= animeTotalTime[animeIndex])
        {
            animeTime = 0.0f;
            isPlayingOnceAnim = false;

            // トリガー解除（再び押せるように）
            if (animeIndex == 2) jumpAnimPlaying = false;
            

            animeIndex = 0;         // 待機アニメへ戻す
        }
    }
    else
    {
        // 通常のループアニメ
        if (animeTime >= animeTotalTime[animeIndex])
        {
            animeTime = 0.0f;
        }
        MV1SetAttachAnimTime(model_handle, attachIndex[animeIndex], animeTime);
    }
}

// モデルの描画
void Player::draw()
{
    MV1DrawModel(model_handle);
}

// 削除処理
void Player::finalize()
{
    MV1DeleteModel(model_handle);  // モデルの削除
}

// 移動中かどうかの判定
bool Player::is_move()
{
    return (CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_D));
}

// 外部からベクトルを加算
void Player::add_vector(VECTOR vec)
{
    model_move_external = VAdd(model_move_external, vec);
}

// 移動を停止
void Player::control_off()
{
    isMoving = false;
}

// プレイヤーの位置を取得
VECTOR Player::get_position()
{
    return model_position;
}
