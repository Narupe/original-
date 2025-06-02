#pragma once
#include "DxLib.h"
#include <string>

//���݉\�Ȕ͈�
#define WORLD_LIMIT_LEFT   (4000.0f)
#define WORLD_LIMIT_RIGHT  (-6000.0f)

#define OBSTACLE_SCALE     (4.0f)         // ��Q���̃��f���X�P�[��

//��Q���̃^�C�v
#define TYPE_BALL          (0)
#define TYPE_FALL          (1)

class Obstacle
{
private:
	std::string model_name;     // 3D���f���̃t�@�C���� (model_name�̓t�@�C�������Ăԁj
	VECTOR model_extend;        // 3D���f���̏k�ڗ�
	VECTOR model_position;      // 3D���f���̍��W
	VECTOR model_rotation;      // 3D���f���̉�]�l
	VECTOR move_vector;         // ��Q���̓����̕����Ƒ��x
	float collision_radius;     // �{�[���̔��a

	int obstacle_type;		    // ��Q���̎��
	int model_handle;			// 3D���f���n���h��
	static int type_ball;	
	static int type_fall;		

	float speed;				// ��Q���̃X�s�[�h

public:
	float model_size;			// ��Q���̑傫��
	bool flag;					// �L���t���O

	void loadModels();
	Obstacle(int type, VECTOR pos, float v);									// ���W���w�肵�č쐬�@�R���X�g���N�^�[(�������K�v�j
	void initialize(int type, float extendf, VECTOR pos, float v);		        // �����ݒ�
	void update();		        // �X�V
	void draw();		        // �`��
	void finalize();	        // ���f���f�[�^�̊J��

	VECTOR get_position();		// ���W��Ԃ�
	float get_radius();         // ���a��Ԃ��֐���ǉ�
	VECTOR get_move_vector();	// �ړ��ʂ�Ԃ� �v���C���[�ɂԂ���Ƃ��̂��
};