#include "Player.h"
#include "Stage.h"
#include "camera.h"
#include "Timer.h"

// �v���C���[�̃��f���n���h��
int Player::model_handle_man = -1;
const int AnimeFrame = 30;           // �A�j���[�V�����̃t���[����/�b
const int AnimeNum = 3;              // �A�j���[�V�����̐�

int animeIndex = 0;                  // ���݂̃A�j���[�V�����C���f�b�N�X
float animeTime = 0;                 // �A�j���[�V�����̐i�s����
int previousAnimeIndex = 0;          // �O��̃A�j���[�V�����C���f�b�N�X

// �A�j���[�V�����̃A�^�b�`
int attachIndex[AnimeNum];
float animeTotalTime[AnimeNum];

// �v���C���[�̏�ԃt���O
bool isMoving = false;               // �����Ă��邩�ǂ���

// �R���X�g���N�^�FPlayer �I�u�W�F�N�g��������
Player::Player()
{
    // ���f�������[�h
    model_handle_man = MV1LoadModel(_T("../resource/3Dmodel/passive_marker_man.mv1"));
    if (model_handle_man == -1)
    {
        printf("Model load failed: passive_marker_man.mv1\n"); // ���f���̓ǂݍ��ݎ��s��
        return;
    }
    // �������֐����Ăяo���i�v���C���[�̖��O�A�g���X�P�[���A�ʒu�A�A�j���[�V�����̃��[�h�L���j
    initialize(GAME_CHARA_MAN, 20.0f, VGet(0.0f, 0.0f, 0.0f), false);
}

// �����t���R���X�g���N�^�F���O�ƈʒu���w�肵�ăv���C���[��������
Player::Player(int name, VECTOR pos)
{
    if (name == GAME_CHARA_MAN)
    {
        // �v���C���[��������
        initialize(name, 20.0f, pos, true);
    }
}

// �v���C���[�̏������֐�
void Player::initialize(int name, float extendf, VECTOR pos, bool anim_load)
{
    if (name == GAME_CHARA_MAN)
    {
        // ���f���𕡐�
        model_handle = MV1DuplicateModel(model_handle_man);
        if (model_handle == -1)
        {
            printf("Model duplicate failed for character\n"); // ���f���������s��
            return;
        }
    }

    // ���f���̃X�P�[����ݒ�
    model_extend = VGet(CHARA_SCALE, CHARA_SCALE, CHARA_SCALE);
    MV1SetScale(model_handle, model_extend);

    // ���f���̏����ʒu��ݒ�
    model_position = VGet(CHARA_START_X + pos.x, CHARA_START_Y + pos.y, CHARA_START_Z + pos.z);
    model_rotation = VGet(90.0f, 0.0f, 0.0f);                // ������]
    MV1SetPosition(model_handle, model_position);

    // �W�����v��
    JumpPower = 0.0f;

    // �A�j���[�V�����̓ǂݍ���
    int animeId[AnimeNum] = {
        MV1LoadModel(_T("../resource/Action/Arm Stretching (1).mv1")),
        MV1LoadModel(_T("../resource/Action/Running.mv1")),
        MV1LoadModel(_T("../resource/Action/Jump.mv1")),
    };

    // �A�j���[�V�����̊m�F�ƃA�^�b�`
    for (int i = 0; i < AnimeNum; ++i)
    {
        if (animeId[i] == -1)
        {
            printf("Failed to load animation: %d\n", i);   // �A�j���[�V�����̓ǂݍ��ݎ��s��
            return;
        }

        // �A�j���[�V���������f���ɃA�^�b�`
        attachIndex[i] = MV1AttachAnim(model_handle, 0, animeId[i]);
        if (attachIndex[i] == -1)
        {
            printf("Failed to attach animation: %d\n", i); // �A�j���[�V�����̃A�^�b�`���s��
            return;
        }

        // �A�j���[�V�����̃u�����h���ݒ�
        MV1SetAttachAnimBlendRate(model_handle, attachIndex[i], (i == animeIndex ? 1.0f : 0.0f));
        animeTotalTime[i] = MV1GetAttachAnimTotalTime(model_handle, attachIndex[i]);
    }

    //  �O��̃A�j���[�V�����C���f�b�N�X
    previousAnimeIndex = 0;
}

// �v���C���[�̍X�V����
void Player::update()
{
    update_control();  // ���͂̎擾�ƈړ�����
    update_anim();     // �A�j���[�V�����̍X�V
    apply_gravity();   // �d�͂̓K�p
}

// �d�͂̓K�p����
void Player::apply_gravity()
{
    bool isJumping = (model_position.y > 0.0f);

    // �v���C���[���n�ʂɂ��邩�m�F
    if (model_position.y <= 0.0f)
    {
        velocity_y = 0.0f;
        model_position.y = 0.0f;

        if (isJumping)
        {
            isJumping = false;
        }
    }
    else
    {
        velocity_y += GRAVITY * 0.019f;            // �d�͂̓K�p
    }

    // �ʒu�̍X�V
    model_position.y += velocity_y;
    MV1SetPosition(model_handle, model_position);  // ���f���̈ʒu���X�V
}

// ���͂Ɋ�Â����ړ�����
void Player::update_control()
{
    VECTOR moveVec = VGet(0.0f, 0.0f, 0.0f);
    float speed = CHARA_MOVE_SPEED;

    // �W�����v�����i�������u�Ԃɂ̂ݔ����j
    if (CheckHitKey(KEY_INPUT_SPACE) && isOnGround && !jumpAnimPlaying)
    {
        JumpPower = CHARA_JUMP_POWER;
        isOnGround = false;
        isMoving = true;

        // �A�j���Đ��J�n
        animeIndex = 2;               // �W�����v�A�j��
        jumpAnimPlaying = true;       // 1�񂵂��Đ�����Ȃ��悤��
        isPlayingOnceAnim = true;
    }

    // �W�����v���̕�������
    if (!isOnGround)
    {
        JumpPower += GRAVITY;        // �d�͂Ō���
        model_position.y += JumpPower;

        // �n�ʂɓ��B�iy = 0�j�����璅�n
        if (model_position.y <= 0.0f)
        {
            model_position.y = 0.0f;
            isOnGround = true;
            JumpPower = 0.0f;
        }
    }

    // �������̈ړ��iXZ���ʁj
    moveVec = handle_movement_input(moveVec, speed);
    moveVec = VAdd(moveVec, model_move_external);
    model_move_external = VGet(0.0f, 0.0f, 0.0f);

    model_position = VAdd(model_position, moveVec);     // XZ�ʒu�̍X�V

    // �v���C���[�������Ă���ꍇ�A���[���h�̐������Ɉʒu�𒲐�
    if (isMoving)
    {
        if (WORLD_LIMIT_DOWN < model_position.z) model_position.z = WORLD_LIMIT_DOWN;
        if (WORLD_LIMIT_LEFT < model_position.x) model_position.x = WORLD_LIMIT_LEFT;
        if (model_position.x < WORLD_LIMIT_RIGHT) model_position.x = WORLD_LIMIT_RIGHT;
    }

    // ���f���ʒu�̍X�V
    MV1SetPosition(model_handle, model_position);

    // update_control �̃A�j���I�����W�b�N�̍Ō�
    if (!isPlayingOnceAnim) 
    {
        if (!isOnGround) animeIndex = 2;
        else if (isMoving)    animeIndex = 1;
        else                  animeIndex = 0;
    }
}

// �ړ����͂̏���
VECTOR Player::handle_movement_input(VECTOR moveVec, float speed)
{
    moveVec = VAdd(moveVec, VGet(0.0f, 0.0f, -speed));  // ��{�I�ɑO�i
    isMoving = true;

    // W�L�[�Œ�~
    if (CheckHitKey(KEY_INPUT_W))
    {
        moveVec = VGet(0.0f, 0.0f, 0.0f);
        isMoving = false;
    }
    // D�L�[�ŉE�ړ�
    if (CheckHitKey(KEY_INPUT_D))
    {
        moveVec = VAdd(moveVec, VGet(-speed, 0.0f, 0.0f));
    }
    // A�L�[�ō��ړ�
    if (CheckHitKey(KEY_INPUT_A))
    {
        moveVec = VAdd(moveVec, VGet(speed, 0.0f, 0.0f));
    }

    return moveVec;
}

//�A�j���[�V�����̏���
void Player::update_anim()
{
    if (animeIndex != previousAnimeIndex)
    {
        if (previousAnimeIndex != -1)
        {
            MV1SetAttachAnimBlendRate(model_handle, attachIndex[previousAnimeIndex], 0.0f);
        }

        MV1SetAttachAnimBlendRate(model_handle, attachIndex[animeIndex], 1.0f);
        animeTime = 0.0f;
        previousAnimeIndex = animeIndex;
    }

    // �A�j���[�V�����̍Đ����x
    animeTime += 0.5f;

    // ���Đ��A�j���̏I������
    if (isPlayingOnceAnim)
    {
        MV1SetAttachAnimTime(model_handle, attachIndex[animeIndex], animeTime);

        if (animeTime >= animeTotalTime[animeIndex])
        {
            animeTime = 0.0f;
            isPlayingOnceAnim = false;

            // �g���K�[�����i�Ăщ�����悤�Ɂj
            if (animeIndex == 2) jumpAnimPlaying = false;
            

            animeIndex = 0;         // �ҋ@�A�j���֖߂�
        }
    }
    else
    {
        // �ʏ�̃��[�v�A�j��
        if (animeTime >= animeTotalTime[animeIndex])
        {
            animeTime = 0.0f;
        }
        MV1SetAttachAnimTime(model_handle, attachIndex[animeIndex], animeTime);
    }
}

// ���f���̕`��
void Player::draw()
{
    MV1DrawModel(model_handle);
}

// �폜����
void Player::finalize()
{
    MV1DeleteModel(model_handle);  // ���f���̍폜
}

// �ړ������ǂ����̔���
bool Player::is_move()
{
    return (CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_D));
}

// �O������x�N�g�������Z
void Player::add_vector(VECTOR vec)
{
    model_move_external = VAdd(model_move_external, vec);
}

// �ړ����~
void Player::control_off()
{
    isMoving = false;
}

// �v���C���[�̈ʒu���擾
VECTOR Player::get_position()
{
    return model_position;
}
