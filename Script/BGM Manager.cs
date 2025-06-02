using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class BGMManager : MonoBehaviour
{
    //����BGM�𓝊����Ă���X�N���v�g

    //�V���O���g���ݒ肱������
    static public BGMManager instance;

    public bool DontDestroyEnabled = true;

    private void Awake()
    {
        if (instance == null)
        {
            instance = this;
            DontDestroyOnLoad(this.gameObject);
        }
        else
        {
            Destroy(this.gameObject);
        }

    }
    //�V���O���g���ݒ肱���܂�




    public AudioSource A_BGM;//AudioSource�^�̕ϐ�A_BGM��錾�@�Ή�����AudioSource�R���|�[�l���g���A�^�b�`
    public AudioSource B_BGM;//AudioSource�^�̕ϐ�B_BGM��錾�@�Ή�����AudioSource�R���|�[�l���g���A�^�b�`
    public AudioSource C_BGM;//AudioSource�^�̕ϐ�C_BGM��錾�@�Ή�����AudioSource�R���|�[�l���g���A�^�b�`
    public AudioSource D_BGM;//AudioSource�^�̕ϐ�D_BGM��錾�@�Ή�����AudioSource�R���|�[�l���g���A�^�b�`
    public AudioSource E_BGM;//AudioSource�^�̕ϐ�E_BGM��錾�@�Ή�����AudioSource�R���|�[�l���g���A�^�b�`
    public AudioSource F_BGM;//AudioSource�^�̕ϐ�F_BGM��錾�@�Ή�����AudioSource�R���|�[�l���g���A�^�b�`
    public AudioSource G_BGM;//AudioSource�^�̕ϐ�G_BGM��錾�@�Ή�����AudioSource�R���|�[�l���g���A�^�b�`
    public AudioSource H_BGM;//AudioSource�^�̕ϐ�G_BGM��錾�@�Ή�����AudioSource�R���|�[�l���g���A�^�b�`

    private string beforeScene;//string�^�̕ϐ�beforeScene��錾 

    void Start()
    {
        beforeScene = "Title";//�N�����̃V�[���� �������Ă���
        A_BGM.Play();//A_BGM��AudioSource�R���|�[�l���g�Ɋ��蓖�Ă�AudioClip���Đ�

        //�V�[�����؂�ւ�������ɌĂ΂�郁�\�b�h��o�^
        SceneManager.activeSceneChanged += OnActiveSceneChanged;
    }




    //�V�[�����؂�ւ�������ɌĂ΂�郁�\�b�h�@
    void OnActiveSceneChanged(Scene prevScene, Scene nextScene)
    {
        //�V�[�����ǂ��ς�������Ŕ���
        //Title����Stage01��
        if (beforeScene == "Title" && nextScene.name == "Stage01")
        {
            A_BGM.Stop();
            B_BGM.Play();
        }

        // Stage01����Next Stage��
        if (beforeScene == "Stage01" && nextScene.name == "Next Stage")
        {
            B_BGM.Stop();
            D_BGM.Play();
        }

		// Next Stage����Stage02��
		if (beforeScene == "Next Stage" && nextScene.name == "Stage02")
		{
			D_BGM.Stop();
			C_BGM.Play();
		}

		// Stage02����Stage03��
		if (beforeScene == "Stage02" && nextScene.name == "Stage03")
        {
            if (DontDestroyEnabled)
            {
                // Scene��J�ڂ��Ă��I�u�W�F�N�g�������Ȃ��悤�ɂ���
                DontDestroyOnLoad(this);
            }
        }

        // Stage03����NextStage��
        if (beforeScene == "Stage03" && nextScene.name == "NextStage")
        {
            C_BGM.Stop();
            D_BGM.Play();
        }

        // NextStage����Stage05��
        if (beforeScene == "NextStage" && nextScene.name == "Stage05")
        {
            D_BGM.Stop();
            E_BGM.Play();
        }

        // NextStage����Title��
        if (beforeScene == "NextStage" && nextScene.name == "Title")
        {
            D_BGM.Stop();
            A_BGM.Play();
        }

        // GameClear�ɂȂ����Ƃ�
        if (nextScene.name == "GameClear")
        {
            A_BGM.Stop();
            B_BGM.Stop();
            C_BGM.Stop();
            D_BGM.Stop();
            E_BGM.Stop();
            F_BGM.Stop();
            H_BGM.Stop();
            G_BGM.Play();
        }

		// Stage12�ɂȂ����Ƃ�
		if (nextScene.name == "Stage12")
		{
			A_BGM.Stop();
			B_BGM.Stop();
			C_BGM.Stop();
			D_BGM.Stop();
			E_BGM.Stop();
			F_BGM.Stop();
			G_BGM.Stop();
			H_BGM.Play();
		}

		// GameClear�ɂȂ����Ƃ�
		if (nextScene.name == "AllClear")
		{
			A_BGM.Stop();
			B_BGM.Stop();
			C_BGM.Stop();
			D_BGM.Stop();
			E_BGM.Stop();
			F_BGM.Stop();
			H_BGM.Stop();
			G_BGM.Play();
		}

		// GameOver�ɂȂ����Ƃ�
		if (nextScene.name == "GameOver")
        {
            A_BGM.Stop();
            B_BGM.Stop();
            C_BGM.Stop();
            D_BGM.Stop();
            E_BGM.Stop();
            F_BGM.Play();
        }

		// Title�ɂȂ����Ƃ�
		if (nextScene.name == "Title")
		{
			A_BGM.Play();
			B_BGM.Stop();
			C_BGM.Stop();
			D_BGM.Stop();
			E_BGM.Stop();
			F_BGM.Stop();
			G_BGM.Stop();
			H_BGM.Stop();
		}

		//�J�ڌ�̃V�[�������u�P�O�̃V�[�����v�Ƃ��ĕێ�
		beforeScene = nextScene.name;
    }
}
