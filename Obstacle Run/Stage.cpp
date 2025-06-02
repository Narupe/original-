#include "Stage.h"
#include "Player.h"

// �n�ʃ��f���̃n���h���z��
int ground_model_handle;

// �X�e�[�W�N���X
Stage::Stage()
{
    // �X�e�[�W���f���̓ǂݍ��݂Ɛݒ�
    model_extend = VGet(0.3f, 0.25f, 0.2f);
    model_handle_stage = MV1LoadModel(_T("../resource/Stage/���_.mv1"));
    MV1SetScale(model_handle_stage, model_extend);
    model_position = VGet(-500.0f, -250.0f, 600.0f);
    MV1SetPosition(model_handle_stage, model_position);

    // �n�ʃ��f���̓ǂݍ���
    ground_model_handle = MV1LoadModel(_T("../resource/Stage/��02.mv1"));

    // �n�ʃX�P�[�����O
    updateGroundShape();

    /* �S�[�� */
    model_handle_gall = MV1LoadModel(_T("../resource/Stage/Gall.mv1"));		// 3D���f���̓ǂݍ���
    MV1SetScale(model_handle_gall, VGet(6.3f, 1.0f, 3.0f));			        // 3D���f���̊g��k��
    MV1SetPosition(model_handle_gall, VGet(-410.0f, -50.0f, -180000.0f));	    // 3D���f����3D��Ԃւ̔z�u
}

void Stage::update()
{
    // �n�ʂ̈ʒu���X�V���鏈��
    VECTOR ground_pos = VGet(ground_position.x, ground_position.y, ground_position.z);
    MV1SetPosition(ground_model_handle, ground_pos);
}

void Stage::draw()
{
    // �X�e�[�W���f����`��
    MV1DrawModel(model_handle_stage);

    // �S�[�����f����`��
    MV1DrawModel(model_handle_gall);

    // �n�ʃ��f����`��
    MV1DrawModel(ground_model_handle);
}

// �n�ʂ̌`��̃X�P�[�����O��ݒ肷��֐�
void Stage::updateGroundShape()
{
    // Z���̃X�P�[�����O�����Ԍo�߂ő���������
    static float scale_z = 100.0f;  // ����Z���X�P�[��
    scale_z += 100.0f;  // Z���̃X�P�[�����������傫������i0.1f��C�ӂɒ����j

    // �n�ʂ̃X�P�[�����O���X�V
    ground_extend = VGet(1.0f, 1.0f, scale_z);  // Z���̃X�P�[����ύX
    MV1SetScale(ground_model_handle, ground_extend);

    // �n�ʂ̈ʒu��ݒ�i�Œ�l�j
    ground_position = VGet(320.0f, 0.0f, 600.0f);
}

void Stage::finalize()
{
    // ���f���n���h�����L���Ȃ���
    if (model_handle_stage != -1)
    {
        MV1DeleteModel(model_handle_stage);
        model_handle_stage = -1;  // �n���h���𖳌��ɂ���
    }

    if (model_handle_gall != -1)
    {
        MV1DeleteModel(model_handle_gall);
        model_handle_gall = -1;  // �n���h���𖳌��ɂ���
    }

    if (ground_model_handle != -1)
    {
        MV1DeleteModel(ground_model_handle);
        ground_model_handle = -1;  // �n���h���𖳌��ɂ���
    }
}