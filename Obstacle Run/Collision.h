#pragma once

#include "Player.h"
#include "Obstacle.h"

//�v���C���[�Ə�Q���̊ȈՓ����蔻��@�������true��Ԃ�
bool collision_player_obstacle(Player* t_player, Obstacle* t_obstacle);

//�v���C���[�ƃS�[���̓����蔻��
bool collision_player_gall(Player* t_Player);