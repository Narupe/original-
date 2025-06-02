#include "GameManager.h"
#include "Collision.h"

int bgm_title; // タイトルのBGM
int bgm_play;  // プレイ中のBGM
int bgm_over;  // ゲームオーバーのBGM

// 障害物効果音
int se_hit;

// タイトルの画像
int titleImage;

// ゲームオーバーの画像
int overImage;

// ゲームクリアの画像
int clearImage;

//ゲームプレイ中の画像
int playImage;

Game_manager::Game_manager()
{
    // 初期設定
    game_state = GAME_STATE_TITLE;
    game_character = GAME_CHARA_MAN;  // ゲームキャラクターの初期化

    // フォントデータの作成
    font_count_down = CreateFontToHandle(NULL, 100, 10, -1);

    //タイトルBGM
    bgm_title = LoadSoundMem(_T("../resource/Sound/Drive_and_Cruise_2.mp3"));
    ChangeVolumeSoundMem(200, bgm_title);  // 音量調整（0～255）

    //プレイ中BGM
    bgm_play = LoadSoundMem(_T("../resource/Sound/ドードドド・スタンピード.mp3"));
    ChangeVolumeSoundMem(150, bgm_play);   // 音量調整（0～255）

    //プレイ中BGM
    bgm_over = LoadSoundMem(_T("../resource/Sound/ダイヤモンドより美しく.mp3"));
    ChangeVolumeSoundMem(200, bgm_over);   // 音量調整（0～255）

    // 効果音
    se_hit = LoadSoundMem(_T("../resource/Sound/Big_Hits_2.mp3")); // 任意の効果音ファイル
    ChangeVolumeSoundMem(200, se_hit);     // 音量（0～255）

    // タイトル時に画像を読み込む
    titleImage = LoadGraph(_T("../resource/gazou/dot-picture-game-style2-1024x576.JPG"));

    // ゲームオーバー時に画像を読み込む
    overImage = LoadGraph(_T("../resource/gazou/spaceship2.JPG"));

    // ゲームクリア時に画像を読み込む
    clearImage = LoadGraph(_T("../resource/gazou/night-sky2-1024x576.JPG"));

    // ゲームプレイ中に画像を読み込む
    playImage = LoadGraph(_T("../resource/gazou/moonnight3-1024x576.JPG"));

    obstacle_span = 0;
    obstacle_interval = 60;
    key_span = 0;

    // 各オブジェクトの初期化
    obj_player = Player(GAME_CHARA_MAN, VGet(0.0f, 0.0f, 0.0f));  // プレイヤーの初期化
    obj_timer = Timer();    // タイマーオブジェクトの初期化
    obj_camera = Camera();  // カメラオブジェクトの初期化
    obj_stage = Stage();    // ステージオブジェクトの初期化
}

//タイトルの処理
void Game_manager::GameState_Title()
{
    // スペースキーが押されたら、キャラクターセレクトへ移行
    if (game_span++ >= 30 && CheckHitKey(KEY_INPUT_SPACE) == 1) 
    {
        // 移行処理
        clsDx();
        key_span = 0;
        game_span = 0;
        game_state = GAME_STATE_SELECT;
    }
}

//ゲームのメイン
void Game_manager::update()
{
    switch (game_state)
    {
    case GAME_STATE_TITLE:
        if (is_bgm_over_playing)
        {
            StopSoundMem(bgm_over);
            is_bgm_over_playing = false;               // ゲームオーバーBGM停止
        }
        // タイトルBGM
        if (!is_bgm_title_playing)
        {
            PlaySoundMem(bgm_title, DX_PLAYTYPE_LOOP); // ループ再生
            is_bgm_title_playing = true;
        }
        GameState_Title();
        break;
    case GAME_STATE_SELECT:
        // 難易度の選択
        if (key_span++ > 10)
        {
            if (CheckHitKey(KEY_INPUT_UP) == 1)
            {
                key_span = 0;
                if (--game_mode < 0) { game_mode = GAME_MODE_HARD; }
            }
            if (CheckHitKey(KEY_INPUT_DOWN) == 1)
            {
                key_span = 0;
                if (++game_mode > GAME_MODE_HARD) { game_mode = GAME_MODE_EASY; }
            }
        }
        // スペースキーが押されたら、ゲームへ移行
        if (game_span++ >= 30 && CheckHitKey(KEY_INPUT_SPACE) == 1)
        {
            // 難易度による、障害物の数の設定
            switch (game_mode)
            {
            case GAME_MODE_EASY: obstacle_interval = 30; break;
            case GAME_MODE_NORMAL: obstacle_interval = 10; break;
            case GAME_MODE_HARD: obstacle_interval = 5; break;
            }

            // キャラクターの読み込み
            switch (game_character)
            {
            case GAME_CHARA_MAN: obj_player = Player(GAME_CHARA_MAN, VGet(0.0f, 0.0f, 0.0f)); break;

            }

            // 移行処理
            key_span = 0;
            game_span = 0;
            game_state = GAME_STATE_PLAY;
        }

        break;
    case GAME_STATE_PLAY:
        if (is_bgm_title_playing)
        {
            StopSoundMem(bgm_title);
            is_bgm_title_playing = false;                   // タイトルBGM停止
        }
        // プレイ中BGM
        if (!is_bgm_play_playing)
        {
            PlaySoundMem(bgm_play, DX_PLAYTYPE_LOOP);       // ループ再生
            is_bgm_play_playing = true;
        }
        if (key_span++ > 180)
        {                                                   // 3秒以上経過したら
            obj_player.update();							// プレイヤーの操作
            obj_timer.update();								// タイマーの更新
        }
        else
        {
            obj_timer.initialize();							// タイマーの初期化
        }
        if (key_span++ > 180)
        {
            for (unsigned int i = 0; i < obj_obstacle.size(); ++i)
            {
                obj_obstacle.at(i).update();				// 障害物の移動
            }
        }
        obj_camera.update(obj_player.get_position());		// カメラの更新

        // クリアしている場合
        if (game_clear)
        {
            // 当たったらリザルトへ移行
            game_state = GAME_STATE_RESULT;
        }
        // 失敗している場合
        else if (game_miss)
        {
            // しばらく待ってからリザルトへ移行
            if (game_span++ >= 120)
            {
                game_state = GAME_STATE_RESULT;
            }
        }
        // プレイ中の場合
        else
        {
            // プレイヤーとゴールのあたり判定
            if (collision_player_gall(&obj_player))
            {
                game_clear = true;
            }
            // プレイヤーと障害物のあたり判定
            for (unsigned int i = 0; i < obj_obstacle.size(); ++i)
            {
                if (collision_player_obstacle(&obj_player, &obj_obstacle.at(i)))
                {
                    // 効果音の再生
                    PlaySoundMem(se_hit, DX_PLAYTYPE_BACK); // 同時再生可能タイプ

                    game_miss = true;
                    obj_player.control_off();
                    obj_camera.track_off();
                }
            }
        }

        // 障害物の追加
        obstacle_make();

        break;
    case GAME_STATE_RESULT:
        if (is_bgm_play_playing)
        {
            StopSoundMem(bgm_play);
            is_bgm_play_playing = false;              // プレイ中BGM停止
        }
        // ゲームオーバーBGM
        if (!is_bgm_over_playing)
        {
            PlaySoundMem(bgm_over, DX_PLAYTYPE_LOOP); // ループ再生
            is_bgm_over_playing = true;
        }
        // スペースキーが押されたら、各種初期化してタイトルへ移行
        if (CheckHitKey(KEY_INPUT_SPACE) == 1)
        {
            // 各インスタンス
            obj_player = Player(GAME_CHARA_MAN, VGet(0.0f, 0.0f, 0.0f));
            obj_obstacle.clear();
            obj_camera = Camera();

            // ゲームクリアの判定変数
            game_span = 0;
            game_clear = false;
            game_miss = false;

            game_state = GAME_STATE_TITLE;
        }
        break;
    }
}

// 描画関数
void Game_manager::draw()
{
    switch (game_state)
    {
    case GAME_STATE_TITLE:
        SetFontSize(64);
        ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
        // 画像を表示
        DrawGraph(0.5, 1, titleImage, TRUE);
        DrawFormatString(100, 50, GetColor(255, 0, 0), _T("Obstacle Run\nスペースキー：\nスタート"));
        SetFontSize(32);
        DrawFormatString(250, 350, GetColor(0, 200, 200), _T("ESCキー：\n終了"));
        break;
    case GAME_STATE_SELECT:
        SetFontSize(20);
        ChangeFontType(DX_FONTTYPE_ANTIALIASING);
        DrawGraph(0.5, 1, titleImage, TRUE);
        DrawFormatString(250, 200, GetColor(255, 0, 0), _T("EASY"));
        DrawFormatString(250, 220, GetColor(255, 0, 0), _T("NORMAL"));
        DrawFormatString(250, 240, GetColor(255, 0, 0), _T("HARD"));
        DrawFormatString(160, 200 + game_mode * 20, GetColor(255, 255, 0), _T("->"));
        break;
    case GAME_STATE_PLAY:
        SetFontSize(30);
        // カウントダウン
        if (key_span <= 60) { ++key_span; }
        else if (key_span <= 120) { DrawStringToHandle(200, 100, _T("3"), GetColor(255, 0, 0), font_count_down); ++key_span; }
        else if (key_span <= 180) { DrawStringToHandle(200, 100, _T("2"), GetColor(255, 0, 0), font_count_down); }
        else if (key_span <= 240) { DrawStringToHandle(200, 100, _T("1"), GetColor(255, 0, 0), font_count_down); }

        // ゲームモード表示
        switch (game_mode) {
        case GAME_MODE_EASY: DrawFormatString(10, 10, GetColor(255, 100, 255), _T("MODE[ EASY ]")); break;
        case GAME_MODE_NORMAL: DrawFormatString(10, 10, GetColor(255, 100, 255), _T("MODE[ NORMAL ]")); break;
        case GAME_MODE_HARD: DrawFormatString(10, 10, GetColor(255, 100, 255), _T("MODE[ HARD ]")); break;
        }

        // タイマー表示
        obj_timer.draw();

        break;
    case GAME_STATE_RESULT:
        if (game_clear)
        {
            switch (game_mode)
            {
            case GAME_MODE_EASY:
                SetFontSize(30); 
                // 画像を表示
                DrawGraph(0.5, 1, clearImage, TRUE);
                DrawFormatString(250, 100, GetColor(255, 255, 100), _T("ゴーール！！"));
                DrawFormatString(250, 150, GetColor(255, 100, 100), _T("すごいね\nスペースキー：タイトル"));
                break;
            case GAME_MODE_NORMAL:
                SetFontSize(30);  
                // 画像を表示
                DrawGraph(0.5, 1, clearImage, TRUE);
                DrawFormatString(250, 100, GetColor(255, 100, 100), _T("ゴーール！！"));
                DrawFormatString(250, 150, GetColor(255, 100, 100), _T("素晴らしい\nスペースキー：タイトル"));
                break;
            case GAME_MODE_HARD:
                SetFontSize(30); 
                // 画像を表示
                DrawGraph(0.5, 1, clearImage, TRUE);
                DrawFormatString(250, 100, GetColor(255, 100, 100), _T("ゴーール！！"));
                DrawFormatString(250, 150, GetColor(255, 100, 100), _T("コングラチュレーション\nスペースキー：タイトル"));
                break;
            }
        }
        else if (game_miss)
        {
            switch (game_mode)
            {
            case GAME_MODE_EASY:
                SetFontSize(30);
                // 画像を表示
                DrawGraph(0.5, 1, overImage, TRUE);
                DrawFormatString(250, 100, GetColor(255, 100, 100), _T("当たりました"));
                DrawFormatString(250, 150, GetColor(255, 100, 100), _T("ゲームオーバー\nスペースキー：タイトル"));
                break;
            case GAME_MODE_NORMAL:
                SetFontSize(30);  
                // 画像を表示
                DrawGraph(0.5, 1, overImage, TRUE);
                DrawFormatString(250, 100, GetColor(255, 100, 100), _T("当たりました"));
                DrawFormatString(250, 150, GetColor(255, 100, 100), _T("ゲームオーバー\nスペースキー：タイトル"));
                break;
            case GAME_MODE_HARD:
                SetFontSize(30);  
                // 画像を表示
                DrawGraph(0.5, 1, overImage, TRUE);
                DrawFormatString(250, 100, GetColor(255, 100, 100), _T("当たりました"));
                DrawFormatString(250, 150, GetColor(255, 100, 100), _T("ゲームオーバー\nスペースキー：タイトル"));
                break;
            }
        }
        break;
    }

    obj_player.draw();				        // プレイヤークラス
    for (unsigned int i = 0; i < obj_obstacle.size(); ++i)
    {
        obj_obstacle.at(i).draw();          // 障害物クラス
    }
    obj_stage.draw();				        // ステージクラス
}

void Game_manager::finalize()
{
    // ゲーム終了時に必要な後始末
    obj_player.finalize();                  // プレイヤーの後始末
    obj_stage.finalize();                   // ステージの後始末
    for (unsigned int i = 0; i < obj_obstacle.size(); ++i) 
    {
        obj_obstacle.at(i).finalize();		// 障害物クラス
    }

    DeleteGraph(titleImage);

    // フォントデータの削除
    DeleteFontToHandle(font_count_down);
}

// 障害物の生成
void Game_manager::obstacle_make()
{
    // ランダム分岐数の初期値（EASYでは最大5分岐、NORMAL/HARDで7）
    int rand_num = 6;

    // プレイヤーの現在位置（Z座標）の取得
    float player_pos_z = obj_player.get_position().z;

    // ゲームモードに応じてランダム分岐数を調整
    switch (game_mode)
    {
    case GAME_MODE_EASY:
        rand_num = 5;
        break;
    case GAME_MODE_NORMAL:
    case GAME_MODE_HARD:
        rand_num = 7;
        break;
    }

    // 障害物をプレイヤーの進行方向にオフセットした位置に出現させるための基準
    float obstacle_offset = player_pos_z + 1500.0f;

    // 障害物生成間隔が一定以上経過したら、新しい障害物を生成
    if (obstacle_span++ >= obstacle_interval)
    {
        // BALLタイプの障害物をランダムなパターンで生成
        switch (xorshift_rand(rand_num))
        {
        case 0:
            // プレイヤーより奥の左側
            obj_obstacle.push_back(Obstacle(TYPE_BALL, VGet(WORLD_LIMIT_LEFT, 100.0f, player_pos_z + 2000.0f), -50.0f));
            break;
        case 1:
            // プレイヤーより奥の左側（さらに遠く）
            obj_obstacle.push_back(Obstacle(TYPE_BALL, VGet(WORLD_LIMIT_LEFT, 100.0f, player_pos_z + 2400.0f), -50.0f));
            break;
        case 2:
            // プレイヤーより前方の右側（近距離）
            obj_obstacle.push_back(Obstacle(TYPE_BALL, VGet(WORLD_LIMIT_RIGHT, 100.0f, player_pos_z - 2000.0f), 50.0f));
            break;
        case 3:
            // プレイヤーより前方の右側（さらに近距離）
            obj_obstacle.push_back(Obstacle(TYPE_BALL, VGet(WORLD_LIMIT_RIGHT, 100.0f, player_pos_z - 2400.0f), 50.0f));
            break;
        case 4:
            // プレイヤーより奥の中央位置
            obj_obstacle.push_back(Obstacle(TYPE_BALL, VGet((WORLD_LIMIT_LEFT + WORLD_LIMIT_RIGHT) / 2.0f, 100.0f, player_pos_z + 3000.0f), -50.0f));
            break;
        case 5:
            // プレイヤーより前方の中央位置（遠くに配置）
            obj_obstacle.push_back(Obstacle(TYPE_BALL, VGet((WORLD_LIMIT_LEFT + WORLD_LIMIT_RIGHT) / 2.0f, 100.0f, player_pos_z - 4000.0f), 50.0f));
            break;
        }

        // FALLタイプの障害物もランダムな場所に生成（静止）
        switch (xorshift_rand(4))
        {
        case 0:
            // 左側・後方
            obj_obstacle.push_back(Obstacle(TYPE_FALL, VGet(WORLD_LIMIT_LEFT, 100.0f, player_pos_z - 5000.0f), 0.0f));
            break;
        case 1:
            // 右側・後方
            obj_obstacle.push_back(Obstacle(TYPE_FALL, VGet(WORLD_LIMIT_RIGHT, 100.0f, player_pos_z - 5000.0f), 0.0f));
            break;
        case 2:
            // 中央・さらに後方
            obj_obstacle.push_back(Obstacle(TYPE_FALL, VGet((WORLD_LIMIT_LEFT + WORLD_LIMIT_RIGHT) / 2.0f, 100.0f, player_pos_z - 8000.0f), 0.0f));
            break;
        case 3:
            // 中央・やや後方
            obj_obstacle.push_back(Obstacle(TYPE_FALL, VGet((WORLD_LIMIT_LEFT + WORLD_LIMIT_RIGHT) / 2.0f, 100.0f, player_pos_z - 4000.0f), 0.0f));
            break;
        }

        // 生成間隔カウンターをリセット
        obstacle_span = 0;
    }

    // 無効（flag=false）になった障害物を削除・解放
    for (auto itr = obj_obstacle.begin(); itr != obj_obstacle.end();)
    {
        if (itr->flag)
        {
            itr++;
        }
        else
        {
            itr->finalize();               // モデル削除などの後処理
            itr = obj_obstacle.erase(itr); // リストから削除
        }
    }
}
