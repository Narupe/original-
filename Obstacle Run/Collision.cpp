#include "Collision.h"
#include <cmath>

bool collision_player_obstacle(Player* t_player, Obstacle* t_obstacle)
{
    float player_radius = CHARA_RADIUS;
    float obstacle_radius = t_obstacle->get_radius();

    VECTOR player_pos = t_player->get_position();
    VECTOR obstacle_pos = t_obstacle->get_position();

    float dx = player_pos.x - obstacle_pos.x;
    float dy = player_pos.y - obstacle_pos.y;
    float dz = player_pos.z - obstacle_pos.z;

    float dist_sq = dx * dx + dy * dy + dz * dz;
    float total_radius = player_radius + obstacle_radius;
    float radius_sq = total_radius * total_radius;

    if (dist_sq <= radius_sq)
    {
        // 方向ベクトル計算 → 単位ベクトルにする
        VECTOR dir = VSub(player_pos, obstacle_pos);
        dir = VNorm(dir);

        // 押し返しの強さ
        float knockback_strength = 60.0f;  // 調整可
        VECTOR knockback = VScale(dir, knockback_strength);

        // プレイヤーに加える
        t_player->add_vector(knockback);

        return true;
    }

    return false;
}

//プレイヤーとゴールの当たり判定
bool collision_player_gall(Player* t_Player)
{
	//ゴールの座標範囲
	float goal_right = -3000.0f;
	float goal_down = -180000.0f;   //ゴールの位置

	// プレイヤーの
	VECTOR pos = t_Player->get_position();

	// 範囲内なら true を返す
	if (pos.x >= goal_right && pos.z <= goal_down) {
		return true;
	}

	// 範囲外なら false を返す
	return false;
}