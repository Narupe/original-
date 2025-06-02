#pragma once

#include "DxLib.h"
#include <string>

// �L�����N�^�[�̐ݒ�
#define CHARA_MOVE_SPEED      (40.0f)     // �L�����N�^�[�̈ړ����x
#define CHARA_JUMP_POWER      (5.0f)      // �W�����v��
#define CHARA_SCALE           (4.0f)      // �L�����N�^�[�̃��f���X�P�[��

#define CHARA_RADIUS          (200.0f)       // �v���C���[�̓����蔻��̔��a

// �ʒu�̏����ݒ�
#define CHARA_START_X         (-320.0f)      // ����X���W
#define CHARA_START_Y         (0.0f)         // ����Y���W
#define CHARA_START_Z         (600.0f)       // ����Z���W

// �L�����N�^�[
#define GAME_CHARA_MAN		  (0)

// �d�͂̐ݒ�
#define GRAVITY               (-0.3f)       // �d�͉����x (������)

// �v���C���[�̓��͏����i�[����\����
struct PADINPUT
{
    int NowInput;    // ���݂̓��́i�t���[���P�ʁj
    int EdgeInput;   // ���݂̃t���[���ŉ����ꂽ�{�^���̂݃r�b�g�������Ă�����͒l
};

class Player 
{
private:
    static int model_handle_man;        // �j�̃n���h��
    static const int AnimeNum = 3;      // �A�j���[�V�����̐�
    static int currentAnim;             // ���݂̃A�j���[�V�����ԍ�
    static int animeId[AnimeNum];       // �A�j���[�V����ID

    bool isPlayingOnceAnim = false;     // �A�j���[�V�����Đ��t���O
    bool jumpAnimPlaying = false;       // �W�����v�A�j���[�V�����Đ��t���O

    int model_handle;                   // ���f���n���h��
    VECTOR model_position;              // ���f���̈ʒu
    VECTOR model_rotation;              // ���f���̉�]
    VECTOR model_extend;                // ���f���̃X�P�[��
    float chara_radius;                 // ���f���̔��a
    float velocity_y;                   // Y�������̑��x
    bool isOnGround = true;
    float JumpPower = 0.0f;
    float speed;
    VECTOR model_move_external;	        // 3D���f���ւ̊O��

public:
    Player();
    Player(int name, VECTOR pos);
    void initialize(int name, float extendf, VECTOR pos, bool anim_load);
    void update();
    void apply_gravity();
    void update_control();
    void update_anim();
    void draw();
    void finalize();
    bool is_move();
    void add_vector(VECTOR vec);	  // �O����̗͂��Ԃ���
    void control_off();				  // ����ł��Ȃ�����

    VECTOR get_position();

private:
    VECTOR handle_movement_input(VECTOR moveVec, float speed);
};