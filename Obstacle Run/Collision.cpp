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
        // �����x�N�g���v�Z �� �P�ʃx�N�g���ɂ���
        VECTOR dir = VSub(player_pos, obstacle_pos);
        dir = VNorm(dir);

        // �����Ԃ��̋���
        float knockback_strength = 60.0f;  // ������
        VECTOR knockback = VScale(dir, knockback_strength);

        // �v���C���[�ɉ�����
        t_player->add_vector(knockback);

        return true;
    }

    return false;
}

//�v���C���[�ƃS�[���̓����蔻��
bool collision_player_gall(Player* t_Player)
{
	//�S�[���̍��W�͈�
	float goal_right = -3000.0f;
	float goal_down = -180000.0f;   //�S�[���̈ʒu

	// �v���C���[��
	VECTOR pos = t_Player->get_position();

	// �͈͓��Ȃ� true ��Ԃ�
	if (pos.x >= goal_right && pos.z <= goal_down) {
		return true;
	}

	// �͈͊O�Ȃ� false ��Ԃ�
	return false;
}