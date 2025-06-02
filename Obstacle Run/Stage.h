#pragma once
#include "DxLib.h"
#include <string>

//���݉\�Ȕ͈�
#define WORLD_LIMIT_LEFT   (2000.0f)     //����
#define WORLD_LIMIT_RIGHT  (-3000.0f)    //�E��
#define WORLD_LIMIT_UP     (-8000.0f)    //�O
#define WORLD_LIMIT_DOWN   (1000.0f)     //���


// �X�e�[�W�N���X
class Stage 
{
private:
    // �o�ߎ��Ԃ��Ǘ�����ϐ��i�~���b�P�ʁj
    unsigned int previousTime;
    float elapsedTime;

public:
    Stage();
    void update();
    void draw();
    void updateGroundShape();
    void finalize();

    // �����̃����o�ϐ�
    VECTOR model_extend;
    int model_handle_stage;
    // �n�ʃ��f���̃n���h���z��
    int ground_model_handle;
    int model_handle_gall;
    VECTOR model_position;
    VECTOR ground_position;
    VECTOR ground_extend;
};
