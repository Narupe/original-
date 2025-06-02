#pragma once

#include "Player.h"
#include "Obstacle.h"

//プレイヤーと障害物の簡易当たり判定　当たるとtrueを返す
bool collision_player_obstacle(Player* t_player, Obstacle* t_obstacle);

//プレイヤーとゴールの当たり判定
bool collision_player_gall(Player* t_Player);