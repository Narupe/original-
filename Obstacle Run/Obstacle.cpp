#include "Obstacle.h"

// static �����o�ϐ��i�N���X�O�ň�x�ǂݍ��ނ����j
int Obstacle::type_ball = -1;
int Obstacle::type_fall = -1;

void Obstacle::loadModels()
{
	if (type_ball == -1) {
		type_ball = MV1LoadModel(_T("../resource/Obstacle/Ball.mv1"));
	}
	if (type_fall == -1) {
		type_fall = MV1LoadModel(_T("../resource/Obstacle/Fall.mv1"));
	}
}

Obstacle::Obstacle(int type, VECTOR pos, float v)
{
	loadModels();  // ���f�������ǂݍ��݂Ȃ炱���œǂݍ���

	obstacle_type = type;
	switch (type)
	{
	case TYPE_BALL:
		initialize(TYPE_BALL, 900.0f, pos, v);
		break;

	case TYPE_FALL:
		initialize(TYPE_FALL, 9.0f, pos, v);
		break;

	default:
		// �����ȃ^�C�v
		flag = false;
		break;
	}
}


void Obstacle::initialize(int type, float extendf, VECTOR pos, float v)
{
	switch (type) 
	{
	case TYPE_BALL:
		model_handle = MV1DuplicateModel(type_ball);
		move_vector = VGet(v, 0.0f, 0.0f);  // X�����Ɉړ�
		model_extend = VGet(OBSTACLE_SCALE, OBSTACLE_SCALE, OBSTACLE_SCALE);
		break;

	case TYPE_FALL:
		model_handle = MV1DuplicateModel(type_fall);
		move_vector = VGet(0.0f, 0.0f, -v); // Z���������Av��0�Ȃ�Î~
		model_extend = VGet(OBSTACLE_SCALE * 0.2f, OBSTACLE_SCALE * 0.5f, OBSTACLE_SCALE * 0.2f); // �T�C�Y����
		break;

	}

	collision_radius = 200.0f;
	flag = true;

	model_position = pos;
	model_rotation = VGet(0.0f, 0.0f, 0.0f);

	MV1SetScale(model_handle, model_extend);
	MV1SetPosition(model_handle, model_position);
}

void Obstacle::update()
{
	model_position = VAdd(model_position, move_vector);

	switch (obstacle_type)
	{
	case TYPE_BALL:
		// X�������ŉ�ʊO�ɏo���疳��
		if (model_position.x > WORLD_LIMIT_LEFT || model_position.x < WORLD_LIMIT_RIGHT)
			flag = false;

		model_rotation.z -= move_vector.x / 1000.0f;
		break;

	case TYPE_FALL:
		// Z�������Ńv���C���[����O�ɗ����疳��
		if (model_position.z > -200.0f)
			flag = false;
		break;
	}

	MV1SetPosition(model_handle, model_position);
	MV1SetRotationXYZ(model_handle, model_rotation);
}

float Obstacle::get_radius()
{
	return collision_radius;
}

void Obstacle::draw()
{
	// �R�c���f����`��
	MV1DrawModel(model_handle);
}

void Obstacle::finalize()
{
	// ���f���n���h���̍폜
	MV1DeleteModel(model_handle);
}

VECTOR Obstacle::get_position()
{
	return model_position;
}

// ��Q���̈ړ��ʂ� VECTOR �^�Ŏ擾����
VECTOR Obstacle::get_move_vector() 
{
	return VGet(speed, 0.0f, 0.0f);
}