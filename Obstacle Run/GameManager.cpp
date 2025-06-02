#include "GameManager.h"
#include "Collision.h"

int bgm_title; // �^�C�g����BGM
int bgm_play;  // �v���C����BGM
int bgm_over;  // �Q�[���I�[�o�[��BGM

// ��Q�����ʉ�
int se_hit;

// �^�C�g���̉摜
int titleImage;

// �Q�[���I�[�o�[�̉摜
int overImage;

// �Q�[���N���A�̉摜
int clearImage;

//�Q�[���v���C���̉摜
int playImage;

Game_manager::Game_manager()
{
    // �����ݒ�
    game_state = GAME_STATE_TITLE;
    game_character = GAME_CHARA_MAN;  // �Q�[���L�����N�^�[�̏�����

    // �t�H���g�f�[�^�̍쐬
    font_count_down = CreateFontToHandle(NULL, 100, 10, -1);

    //�^�C�g��BGM
    bgm_title = LoadSoundMem(_T("../resource/Sound/Drive_and_Cruise_2.mp3"));
    ChangeVolumeSoundMem(200, bgm_title);  // ���ʒ����i0�`255�j

    //�v���C��BGM
    bgm_play = LoadSoundMem(_T("../resource/Sound/�h�[�h�h�h�E�X�^���s�[�h.mp3"));
    ChangeVolumeSoundMem(150, bgm_play);   // ���ʒ����i0�`255�j

    //�v���C��BGM
    bgm_over = LoadSoundMem(_T("../resource/Sound/�_�C�������h��������.mp3"));
    ChangeVolumeSoundMem(200, bgm_over);   // ���ʒ����i0�`255�j

    // ���ʉ�
    se_hit = LoadSoundMem(_T("../resource/Sound/Big_Hits_2.mp3")); // �C�ӂ̌��ʉ��t�@�C��
    ChangeVolumeSoundMem(200, se_hit);     // ���ʁi0�`255�j

    // �^�C�g�����ɉ摜��ǂݍ���
    titleImage = LoadGraph(_T("../resource/gazou/dot-picture-game-style2-1024x576.JPG"));

    // �Q�[���I�[�o�[���ɉ摜��ǂݍ���
    overImage = LoadGraph(_T("../resource/gazou/spaceship2.JPG"));

    // �Q�[���N���A���ɉ摜��ǂݍ���
    clearImage = LoadGraph(_T("../resource/gazou/night-sky2-1024x576.JPG"));

    // �Q�[���v���C���ɉ摜��ǂݍ���
    playImage = LoadGraph(_T("../resource/gazou/moonnight3-1024x576.JPG"));

    obstacle_span = 0;
    obstacle_interval = 60;
    key_span = 0;

    // �e�I�u�W�F�N�g�̏�����
    obj_player = Player(GAME_CHARA_MAN, VGet(0.0f, 0.0f, 0.0f));  // �v���C���[�̏�����
    obj_timer = Timer();    // �^�C�}�[�I�u�W�F�N�g�̏�����
    obj_camera = Camera();  // �J�����I�u�W�F�N�g�̏�����
    obj_stage = Stage();    // �X�e�[�W�I�u�W�F�N�g�̏�����
}

//�^�C�g���̏���
void Game_manager::GameState_Title()
{
    // �X�y�[�X�L�[�������ꂽ��A�L�����N�^�[�Z���N�g�ֈڍs
    if (game_span++ >= 30 && CheckHitKey(KEY_INPUT_SPACE) == 1) 
    {
        // �ڍs����
        clsDx();
        key_span = 0;
        game_span = 0;
        game_state = GAME_STATE_SELECT;
    }
}

//�Q�[���̃��C��
void Game_manager::update()
{
    switch (game_state)
    {
    case GAME_STATE_TITLE:
        if (is_bgm_over_playing)
        {
            StopSoundMem(bgm_over);
            is_bgm_over_playing = false;               // �Q�[���I�[�o�[BGM��~
        }
        // �^�C�g��BGM
        if (!is_bgm_title_playing)
        {
            PlaySoundMem(bgm_title, DX_PLAYTYPE_LOOP); // ���[�v�Đ�
            is_bgm_title_playing = true;
        }
        GameState_Title();
        break;
    case GAME_STATE_SELECT:
        // ��Փx�̑I��
        if (key_span++ > 10)
        {
            if (CheckHitKey(KEY_INPUT_UP) == 1)
            {
                key_span = 0;
                if (--game_mode < 0) { game_mode = GAME_MODE_HARD; }
            }
            if (CheckHitKey(KEY_INPUT_DOWN) == 1)
            {
                key_span = 0;
                if (++game_mode > GAME_MODE_HARD) { game_mode = GAME_MODE_EASY; }
            }
        }
        // �X�y�[�X�L�[�������ꂽ��A�Q�[���ֈڍs
        if (game_span++ >= 30 && CheckHitKey(KEY_INPUT_SPACE) == 1)
        {
            // ��Փx�ɂ��A��Q���̐��̐ݒ�
            switch (game_mode)
            {
            case GAME_MODE_EASY: obstacle_interval = 30; break;
            case GAME_MODE_NORMAL: obstacle_interval = 10; break;
            case GAME_MODE_HARD: obstacle_interval = 5; break;
            }

            // �L�����N�^�[�̓ǂݍ���
            switch (game_character)
            {
            case GAME_CHARA_MAN: obj_player = Player(GAME_CHARA_MAN, VGet(0.0f, 0.0f, 0.0f)); break;

            }

            // �ڍs����
            key_span = 0;
            game_span = 0;
            game_state = GAME_STATE_PLAY;
        }

        break;
    case GAME_STATE_PLAY:
        if (is_bgm_title_playing)
        {
            StopSoundMem(bgm_title);
            is_bgm_title_playing = false;                   // �^�C�g��BGM��~
        }
        // �v���C��BGM
        if (!is_bgm_play_playing)
        {
            PlaySoundMem(bgm_play, DX_PLAYTYPE_LOOP);       // ���[�v�Đ�
            is_bgm_play_playing = true;
        }
        if (key_span++ > 180)
        {                                                   // 3�b�ȏ�o�߂�����
            obj_player.update();							// �v���C���[�̑���
            obj_timer.update();								// �^�C�}�[�̍X�V
        }
        else
        {
            obj_timer.initialize();							// �^�C�}�[�̏�����
        }
        if (key_span++ > 180)
        {
            for (unsigned int i = 0; i < obj_obstacle.size(); ++i)
            {
                obj_obstacle.at(i).update();				// ��Q���̈ړ�
            }
        }
        obj_camera.update(obj_player.get_position());		// �J�����̍X�V

        // �N���A���Ă���ꍇ
        if (game_clear)
        {
            // ���������烊�U���g�ֈڍs
            game_state = GAME_STATE_RESULT;
        }
        // ���s���Ă���ꍇ
        else if (game_miss)
        {
            // ���΂炭�҂��Ă��烊�U���g�ֈڍs
            if (game_span++ >= 120)
            {
                game_state = GAME_STATE_RESULT;
            }
        }
        // �v���C���̏ꍇ
        else
        {
            // �v���C���[�ƃS�[���̂����蔻��
            if (collision_player_gall(&obj_player))
            {
                game_clear = true;
            }
            // �v���C���[�Ə�Q���̂����蔻��
            for (unsigned int i = 0; i < obj_obstacle.size(); ++i)
            {
                if (collision_player_obstacle(&obj_player, &obj_obstacle.at(i)))
                {
                    // ���ʉ��̍Đ�
                    PlaySoundMem(se_hit, DX_PLAYTYPE_BACK); // �����Đ��\�^�C�v

                    game_miss = true;
                    obj_player.control_off();
                    obj_camera.track_off();
                }
            }
        }

        // ��Q���̒ǉ�
        obstacle_make();

        break;
    case GAME_STATE_RESULT:
        if (is_bgm_play_playing)
        {
            StopSoundMem(bgm_play);
            is_bgm_play_playing = false;              // �v���C��BGM��~
        }
        // �Q�[���I�[�o�[BGM
        if (!is_bgm_over_playing)
        {
            PlaySoundMem(bgm_over, DX_PLAYTYPE_LOOP); // ���[�v�Đ�
            is_bgm_over_playing = true;
        }
        // �X�y�[�X�L�[�������ꂽ��A�e�평�������ă^�C�g���ֈڍs
        if (CheckHitKey(KEY_INPUT_SPACE) == 1)
        {
            // �e�C���X�^���X
            obj_player = Player(GAME_CHARA_MAN, VGet(0.0f, 0.0f, 0.0f));
            obj_obstacle.clear();
            obj_camera = Camera();

            // �Q�[���N���A�̔���ϐ�
            game_span = 0;
            game_clear = false;
            game_miss = false;

            game_state = GAME_STATE_TITLE;
        }
        break;
    }
}

// �`��֐�
void Game_manager::draw()
{
    switch (game_state)
    {
    case GAME_STATE_TITLE:
        SetFontSize(64);
        ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
        // �摜��\��
        DrawGraph(0.5, 1, titleImage, TRUE);
        DrawFormatString(100, 50, GetColor(255, 0, 0), _T("Obstacle Run\n�X�y�[�X�L�[�F\n�X�^�[�g"));
        SetFontSize(32);
        DrawFormatString(250, 350, GetColor(0, 200, 200), _T("ESC�L�[�F\n�I��"));
        break;
    case GAME_STATE_SELECT:
        SetFontSize(20);
        ChangeFontType(DX_FONTTYPE_ANTIALIASING);
        DrawGraph(0.5, 1, titleImage, TRUE);
        DrawFormatString(250, 200, GetColor(255, 0, 0), _T("EASY"));
        DrawFormatString(250, 220, GetColor(255, 0, 0), _T("NORMAL"));
        DrawFormatString(250, 240, GetColor(255, 0, 0), _T("HARD"));
        DrawFormatString(160, 200 + game_mode * 20, GetColor(255, 255, 0), _T("->"));
        break;
    case GAME_STATE_PLAY:
        SetFontSize(30);
        // �J�E���g�_�E��
        if (key_span <= 60) { ++key_span; }
        else if (key_span <= 120) { DrawStringToHandle(200, 100, _T("3"), GetColor(255, 0, 0), font_count_down); ++key_span; }
        else if (key_span <= 180) { DrawStringToHandle(200, 100, _T("2"), GetColor(255, 0, 0), font_count_down); }
        else if (key_span <= 240) { DrawStringToHandle(200, 100, _T("1"), GetColor(255, 0, 0), font_count_down); }

        // �Q�[�����[�h�\��
        switch (game_mode) {
        case GAME_MODE_EASY: DrawFormatString(10, 10, GetColor(255, 100, 255), _T("MODE[ EASY ]")); break;
        case GAME_MODE_NORMAL: DrawFormatString(10, 10, GetColor(255, 100, 255), _T("MODE[ NORMAL ]")); break;
        case GAME_MODE_HARD: DrawFormatString(10, 10, GetColor(255, 100, 255), _T("MODE[ HARD ]")); break;
        }

        // �^�C�}�[�\��
        obj_timer.draw();

        break;
    case GAME_STATE_RESULT:
        if (game_clear)
        {
            switch (game_mode)
            {
            case GAME_MODE_EASY:
                SetFontSize(30); 
                // �摜��\��
                DrawGraph(0.5, 1, clearImage, TRUE);
                DrawFormatString(250, 100, GetColor(255, 255, 100), _T("�S�[�[���I�I"));
                DrawFormatString(250, 150, GetColor(255, 100, 100), _T("��������\n�X�y�[�X�L�[�F�^�C�g��"));
                break;
            case GAME_MODE_NORMAL:
                SetFontSize(30);  
                // �摜��\��
                DrawGraph(0.5, 1, clearImage, TRUE);
                DrawFormatString(250, 100, GetColor(255, 100, 100), _T("�S�[�[���I�I"));
                DrawFormatString(250, 150, GetColor(255, 100, 100), _T("�f���炵��\n�X�y�[�X�L�[�F�^�C�g��"));
                break;
            case GAME_MODE_HARD:
                SetFontSize(30); 
                // �摜��\��
                DrawGraph(0.5, 1, clearImage, TRUE);
                DrawFormatString(250, 100, GetColor(255, 100, 100), _T("�S�[�[���I�I"));
                DrawFormatString(250, 150, GetColor(255, 100, 100), _T("�R���O���`�����[�V����\n�X�y�[�X�L�[�F�^�C�g��"));
                break;
            }
        }
        else if (game_miss)
        {
            switch (game_mode)
            {
            case GAME_MODE_EASY:
                SetFontSize(30);
                // �摜��\��
                DrawGraph(0.5, 1, overImage, TRUE);
                DrawFormatString(250, 100, GetColor(255, 100, 100), _T("������܂���"));
                DrawFormatString(250, 150, GetColor(255, 100, 100), _T("�Q�[���I�[�o�[\n�X�y�[�X�L�[�F�^�C�g��"));
                break;
            case GAME_MODE_NORMAL:
                SetFontSize(30);  
                // �摜��\��
                DrawGraph(0.5, 1, overImage, TRUE);
                DrawFormatString(250, 100, GetColor(255, 100, 100), _T("������܂���"));
                DrawFormatString(250, 150, GetColor(255, 100, 100), _T("�Q�[���I�[�o�[\n�X�y�[�X�L�[�F�^�C�g��"));
                break;
            case GAME_MODE_HARD:
                SetFontSize(30);  
                // �摜��\��
                DrawGraph(0.5, 1, overImage, TRUE);
                DrawFormatString(250, 100, GetColor(255, 100, 100), _T("������܂���"));
                DrawFormatString(250, 150, GetColor(255, 100, 100), _T("�Q�[���I�[�o�[\n�X�y�[�X�L�[�F�^�C�g��"));
                break;
            }
        }
        break;
    }

    obj_player.draw();				        // �v���C���[�N���X
    for (unsigned int i = 0; i < obj_obstacle.size(); ++i)
    {
        obj_obstacle.at(i).draw();          // ��Q���N���X
    }
    obj_stage.draw();				        // �X�e�[�W�N���X
}

void Game_manager::finalize()
{
    // �Q�[���I�����ɕK�v�Ȍ�n��
    obj_player.finalize();                  // �v���C���[�̌�n��
    obj_stage.finalize();                   // �X�e�[�W�̌�n��
    for (unsigned int i = 0; i < obj_obstacle.size(); ++i) 
    {
        obj_obstacle.at(i).finalize();		// ��Q���N���X
    }

    DeleteGraph(titleImage);

    // �t�H���g�f�[�^�̍폜
    DeleteFontToHandle(font_count_down);
}

// ��Q���̐���
void Game_manager::obstacle_make()
{
    // �����_�����򐔂̏����l�iEASY�ł͍ő�5����ANORMAL/HARD��7�j
    int rand_num = 6;

    // �v���C���[�̌��݈ʒu�iZ���W�j�̎擾
    float player_pos_z = obj_player.get_position().z;

    // �Q�[�����[�h�ɉ����ă����_�����򐔂𒲐�
    switch (game_mode)
    {
    case GAME_MODE_EASY:
        rand_num = 5;
        break;
    case GAME_MODE_NORMAL:
    case GAME_MODE_HARD:
        rand_num = 7;
        break;
    }

    // ��Q�����v���C���[�̐i�s�����ɃI�t�Z�b�g�����ʒu�ɏo�������邽�߂̊
    float obstacle_offset = player_pos_z + 1500.0f;

    // ��Q�������Ԋu�����ȏ�o�߂�����A�V������Q���𐶐�
    if (obstacle_span++ >= obstacle_interval)
    {
        // BALL�^�C�v�̏�Q���������_���ȃp�^�[���Ő���
        switch (xorshift_rand(rand_num))
        {
        case 0:
            // �v���C���[��艜�̍���
            obj_obstacle.push_back(Obstacle(TYPE_BALL, VGet(WORLD_LIMIT_LEFT, 100.0f, player_pos_z + 2000.0f), -50.0f));
            break;
        case 1:
            // �v���C���[��艜�̍����i����ɉ����j
            obj_obstacle.push_back(Obstacle(TYPE_BALL, VGet(WORLD_LIMIT_LEFT, 100.0f, player_pos_z + 2400.0f), -50.0f));
            break;
        case 2:
            // �v���C���[���O���̉E���i�ߋ����j
            obj_obstacle.push_back(Obstacle(TYPE_BALL, VGet(WORLD_LIMIT_RIGHT, 100.0f, player_pos_z - 2000.0f), 50.0f));
            break;
        case 3:
            // �v���C���[���O���̉E���i����ɋߋ����j
            obj_obstacle.push_back(Obstacle(TYPE_BALL, VGet(WORLD_LIMIT_RIGHT, 100.0f, player_pos_z - 2400.0f), 50.0f));
            break;
        case 4:
            // �v���C���[��艜�̒����ʒu
            obj_obstacle.push_back(Obstacle(TYPE_BALL, VGet((WORLD_LIMIT_LEFT + WORLD_LIMIT_RIGHT) / 2.0f, 100.0f, player_pos_z + 3000.0f), -50.0f));
            break;
        case 5:
            // �v���C���[���O���̒����ʒu�i�����ɔz�u�j
            obj_obstacle.push_back(Obstacle(TYPE_BALL, VGet((WORLD_LIMIT_LEFT + WORLD_LIMIT_RIGHT) / 2.0f, 100.0f, player_pos_z - 4000.0f), 50.0f));
            break;
        }

        // FALL�^�C�v�̏�Q���������_���ȏꏊ�ɐ����i�Î~�j
        switch (xorshift_rand(4))
        {
        case 0:
            // �����E���
            obj_obstacle.push_back(Obstacle(TYPE_FALL, VGet(WORLD_LIMIT_LEFT, 100.0f, player_pos_z - 5000.0f), 0.0f));
            break;
        case 1:
            // �E���E���
            obj_obstacle.push_back(Obstacle(TYPE_FALL, VGet(WORLD_LIMIT_RIGHT, 100.0f, player_pos_z - 5000.0f), 0.0f));
            break;
        case 2:
            // �����E����Ɍ��
            obj_obstacle.push_back(Obstacle(TYPE_FALL, VGet((WORLD_LIMIT_LEFT + WORLD_LIMIT_RIGHT) / 2.0f, 100.0f, player_pos_z - 8000.0f), 0.0f));
            break;
        case 3:
            // �����E�����
            obj_obstacle.push_back(Obstacle(TYPE_FALL, VGet((WORLD_LIMIT_LEFT + WORLD_LIMIT_RIGHT) / 2.0f, 100.0f, player_pos_z - 4000.0f), 0.0f));
            break;
        }

        // �����Ԋu�J�E���^�[�����Z�b�g
        obstacle_span = 0;
    }

    // �����iflag=false�j�ɂȂ�����Q�����폜�E���
    for (auto itr = obj_obstacle.begin(); itr != obj_obstacle.end();)
    {
        if (itr->flag)
        {
            itr++;
        }
        else
        {
            itr->finalize();               // ���f���폜�Ȃǂ̌㏈��
            itr = obj_obstacle.erase(itr); // ���X�g����폜
        }
    }
}
