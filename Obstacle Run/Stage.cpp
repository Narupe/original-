#include "Stage.h"
#include "Player.h"

// 地面モデルのハンドル配列
int ground_model_handle;

// ステージクラス
Stage::Stage()
{
    // ステージモデルの読み込みと設定
    model_extend = VGet(0.3f, 0.25f, 0.2f);
    model_handle_stage = MV1LoadModel(_T("../resource/Stage/原点.mv1"));
    MV1SetScale(model_handle_stage, model_extend);
    model_position = VGet(-500.0f, -250.0f, 600.0f);
    MV1SetPosition(model_handle_stage, model_position);

    // 地面モデルの読み込み
    ground_model_handle = MV1LoadModel(_T("../resource/Stage/床02.mv1"));

    // 地面スケーリング
    updateGroundShape();

    /* ゴール */
    model_handle_gall = MV1LoadModel(_T("../resource/Stage/Gall.mv1"));		// 3Dモデルの読み込み
    MV1SetScale(model_handle_gall, VGet(6.3f, 1.0f, 3.0f));			        // 3Dモデルの拡大縮小
    MV1SetPosition(model_handle_gall, VGet(-410.0f, -50.0f, -180000.0f));	    // 3Dモデルの3D空間への配置
}

void Stage::update()
{
    // 地面の位置を更新する処理
    VECTOR ground_pos = VGet(ground_position.x, ground_position.y, ground_position.z);
    MV1SetPosition(ground_model_handle, ground_pos);
}

void Stage::draw()
{
    // ステージモデルを描画
    MV1DrawModel(model_handle_stage);

    // ゴールモデルを描画
    MV1DrawModel(model_handle_gall);

    // 地面モデルを描画
    MV1DrawModel(ground_model_handle);
}

// 地面の形状のスケーリングを設定する関数
void Stage::updateGroundShape()
{
    // Z軸のスケーリングを時間経過で増加させる
    static float scale_z = 100.0f;  // 初期Z軸スケール
    scale_z += 100.0f;  // Z軸のスケールを少しずつ大きくする（0.1fを任意に調整）

    // 地面のスケーリングを更新
    ground_extend = VGet(1.0f, 1.0f, scale_z);  // Z軸のスケールを変更
    MV1SetScale(ground_model_handle, ground_extend);

    // 地面の位置を設定（固定値）
    ground_position = VGet(320.0f, 0.0f, 600.0f);
}

void Stage::finalize()
{
    // モデルハンドルが有効なら解放
    if (model_handle_stage != -1)
    {
        MV1DeleteModel(model_handle_stage);
        model_handle_stage = -1;  // ハンドルを無効にする
    }

    if (model_handle_gall != -1)
    {
        MV1DeleteModel(model_handle_gall);
        model_handle_gall = -1;  // ハンドルを無効にする
    }

    if (ground_model_handle != -1)
    {
        MV1DeleteModel(ground_model_handle);
        ground_model_handle = -1;  // ハンドルを無効にする
    }
}