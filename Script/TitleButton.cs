using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class TitleButton : MonoBehaviour
{
	//スタートボタンでStage01へ移行
	public void StartBtn()
	{
		SceneManager.LoadScene("Stage01");
	}

	//設定ボタンでConfigへ移行
	public void ConfBtn()
	{
		SceneManager.LoadScene("Config");
	}
}