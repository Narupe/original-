#pragma once
#include "DxLib.h"
#include <string>

//存在可能な範囲
#define WORLD_LIMIT_LEFT   (4000.0f)
#define WORLD_LIMIT_RIGHT  (-6000.0f)

#define OBSTACLE_SCALE     (4.0f)         // 障害物のモデルスケール

//障害物のタイプ
#define TYPE_BALL          (0)
#define TYPE_FALL          (1)

class Obstacle
{
private:
	std::string model_name;     // 3Dモデルのファイル名 (model_nameはファイル名を呼ぶ）
	VECTOR model_extend;        // 3Dモデルの縮尺率
	VECTOR model_position;      // 3Dモデルの座標
	VECTOR model_rotation;      // 3Dモデルの回転値
	VECTOR move_vector;         // 障害物の動きの方向と速度
	float collision_radius;     // ボールの半径

	int obstacle_type;		    // 障害物の種類
	int model_handle;			// 3Dモデルハンドル
	static int type_ball;	
	static int type_fall;		

	float speed;				// 障害物のスピード

public:
	float model_size;			// 障害物の大きさ
	bool flag;					// 有効フラグ

	void loadModels();
	Obstacle(int type, VECTOR pos, float v);									// 座標を指定して作成　コンストラクター(引数が必要）
	void initialize(int type, float extendf, VECTOR pos, float v);		        // 初期設定
	void update();		        // 更新
	void draw();		        // 描画
	void finalize();	        // モデルデータの開放

	VECTOR get_position();		// 座標を返す
	float get_radius();         // 半径を返す関数を追加
	VECTOR get_move_vector();	// 移動量を返す プレイヤーにぶつけるときのやつ
};