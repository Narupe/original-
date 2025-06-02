using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class BGMManager : MonoBehaviour
{
    //流すBGMを統括しているスクリプト

    //シングルトン設定ここから
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
    //シングルトン設定ここまで




    public AudioSource A_BGM;//AudioSource型の変数A_BGMを宣言　対応するAudioSourceコンポーネントをアタッチ
    public AudioSource B_BGM;//AudioSource型の変数B_BGMを宣言　対応するAudioSourceコンポーネントをアタッチ
    public AudioSource C_BGM;//AudioSource型の変数C_BGMを宣言　対応するAudioSourceコンポーネントをアタッチ
    public AudioSource D_BGM;//AudioSource型の変数D_BGMを宣言　対応するAudioSourceコンポーネントをアタッチ
    public AudioSource E_BGM;//AudioSource型の変数E_BGMを宣言　対応するAudioSourceコンポーネントをアタッチ
    public AudioSource F_BGM;//AudioSource型の変数F_BGMを宣言　対応するAudioSourceコンポーネントをアタッチ
    public AudioSource G_BGM;//AudioSource型の変数G_BGMを宣言　対応するAudioSourceコンポーネントをアタッチ
    public AudioSource H_BGM;//AudioSource型の変数G_BGMを宣言　対応するAudioSourceコンポーネントをアタッチ

    private string beforeScene;//string型の変数beforeSceneを宣言 

    void Start()
    {
        beforeScene = "Title";//起動時のシーン名 を代入しておく
        A_BGM.Play();//A_BGMのAudioSourceコンポーネントに割り当てたAudioClipを再生

        //シーンが切り替わった時に呼ばれるメソッドを登録
        SceneManager.activeSceneChanged += OnActiveSceneChanged;
    }




    //シーンが切り替わった時に呼ばれるメソッド　
    void OnActiveSceneChanged(Scene prevScene, Scene nextScene)
    {
        //シーンがどう変わったかで判定
        //TitleからStage01へ
        if (beforeScene == "Title" && nextScene.name == "Stage01")
        {
            A_BGM.Stop();
            B_BGM.Play();
        }

        // Stage01からNext Stageへ
        if (beforeScene == "Stage01" && nextScene.name == "Next Stage")
        {
            B_BGM.Stop();
            D_BGM.Play();
        }

		// Next StageからStage02へ
		if (beforeScene == "Next Stage" && nextScene.name == "Stage02")
		{
			D_BGM.Stop();
			C_BGM.Play();
		}

		// Stage02からStage03へ
		if (beforeScene == "Stage02" && nextScene.name == "Stage03")
        {
            if (DontDestroyEnabled)
            {
                // Sceneを遷移してもオブジェクトが消えないようにする
                DontDestroyOnLoad(this);
            }
        }

        // Stage03からNextStageへ
        if (beforeScene == "Stage03" && nextScene.name == "NextStage")
        {
            C_BGM.Stop();
            D_BGM.Play();
        }

        // NextStageからStage05へ
        if (beforeScene == "NextStage" && nextScene.name == "Stage05")
        {
            D_BGM.Stop();
            E_BGM.Play();
        }

        // NextStageからTitleへ
        if (beforeScene == "NextStage" && nextScene.name == "Title")
        {
            D_BGM.Stop();
            A_BGM.Play();
        }

        // GameClearになったとき
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

		// Stage12になったとき
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

		// GameClearになったとき
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

		// GameOverになったとき
		if (nextScene.name == "GameOver")
        {
            A_BGM.Stop();
            B_BGM.Stop();
            C_BGM.Stop();
            D_BGM.Stop();
            E_BGM.Stop();
            F_BGM.Play();
        }

		// Titleになったとき
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

		//遷移後のシーン名を「１つ前のシーン名」として保持
		beforeScene = nextScene.name;
    }
}
