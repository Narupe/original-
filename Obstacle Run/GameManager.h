#pragma once

#include "Player.h"
#include "Obstacle.h"
#include "Stage.h"
#include "Camera.h"
#include "Timer.h"
#include "Collision.h"
#include <vector>

// �Q�[���̏��
#define GAME_STATE_TITLE    (0)
#define GAME_STATE_SELECT   (1)
#define GAME_STATE_PLAY     (2)
#define GAME_STATE_RESULT   (3)

enum class GAME_STATE : int   //enum�̕����悢(enum = �܂Ƃ߁j
{
    TITLE,
    SELECT,
    PLAY,
    RESULT,

    MAX,             //enum�̒��ɔ[�߂�
    UNKNOWN = -1,    //enum�̒��ɔ[�߂�
};

enum class SAMPLE_FLAG : unsigned int
{
    INVICIBLE = 1 << 0,   //0x00000001
    CAN_SHOT = 1 << 1,    //0x00000002
    CAN_JUMP = 1 << 2,    //0x00000004
    CAN_MOVE = 1 << 3,    //0x00000008
    CAN_ATTACK = 1 << 4,  //0x00000010
    CAN_DEFENCE = 1 << 5, //0x00000020

    UNKNOWN = 0,
};

//�Q�[���̓�Փx
#define GAME_MODE_EASY     0
#define GAME_MODE_NORMAL   1
#define GAME_MODE_HARD     2

enum class GAME_MODE : int   //enum�̕����悢
{
    EASY,
    NORMAL,
    HARD,

    MAX,
    UNKNOWN = -1,
};

class Game_manager
{
private:
    int game_state;                     // �Q�[���̏��
    int game_mode;		                // �Q�[���̓�Փx
    int game_character;                 // �Q�[���Ŏg�p����L�����N�^�[

    int game_span;		                // �Q�[���I����̑ҋ@����
    bool game_clear;	                // �Q�[���N���A�t���O
    bool game_miss;		                // �Q�[�����s�t���O�@�@bool�Œ�`

    Player obj_player;                  // �v���C���[�C���X�^���X
    std::vector<Obstacle> obj_obstacle;	// ��Q���C���X�^���X
    Stage obj_stage;                    // �X�e�[�W�C���X�^���X
    Camera obj_camera;                  // �J�����C���X�^���X
    Timer obj_timer;                    // �^�C�}�[

    int obstacle_span;                  // ��Q���쐬�̌��Ԋu
    int obstacle_interval;              // ��Q���쐬�̐����Ԋu
    int key_span;                       // �L�[���͂̐����Ԋu

    int font_count_down;                // �J�E���g�_�E���p�̃t�H���g
    bool is_bgm_title_playing = false;  // �^�C�g��BGM�t���O
    bool is_bgm_play_playing = false;   // �v���C��BGM�t���O
    bool is_bgm_over_playing = false;   // �Q�[���I�[�o�[BGM�t���O

    // XorShift���������p�̏�ԕϐ��i�K�v�ɉ�����Game_manager�̃����o�ϐ��ɂ��Ă�OK�j
    unsigned int x = 123456789;
    unsigned int y = 362436069;
    unsigned int z = 521288629;
    unsigned int w = 88675123;

    unsigned int xorshift()
    {
        unsigned int t = x ^ (x << 11);
        x = y; y = z; z = w;
        w = w ^ (w >> 19) ^ (t ^ (t >> 8));
        return w;
    }

    // �͈͕t�������i0�`max-1�j
    int xorshift_rand(int max)
    {
        return xorshift() % max;
    }

public:
    Game_manager();             // �R���X�g���N�^
    void update();              // �X�V����
    void draw();                // �`�揈��
    void finalize();            // ���f���f�[�^�̊J������
    void obstacle_make();       // ��Q���쐬�E�폜

    void GameState_Title();     // �^�C�g����ʂ̏������s���܂�
};

