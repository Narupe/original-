using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;  // SceneManagerを使うために追加

public class Pause : MonoBehaviour
{
	// ポーズした時に表示するUI
	[SerializeField]
	private GameObject pauseUI;

	// Update is called once per frame
	void Update()
	{
		//Qキーでポーズ画面
		if (Input.GetKeyDown("q"))
		{
			// ポーズUIのアクティブ、非アクティブを切り替え
			pauseUI.SetActive(!pauseUI.activeSelf);

			// ポーズUIが表示されてる時は停止
			if (pauseUI.activeSelf)
			{
				Time.timeScale = 0f;  // ゲームを一時停止
			}
			else  //もう一度Qキーを押すと再開
			{
				Time.timeScale = 1f;  // ゲームを再開
			}
		}
	}

	// シーンが読み込まれる直前に呼び出される
	private void OnEnable()
	{
		// シーンが読み込まれるたびに呼ばれるイベントを登録
		SceneManager.sceneLoaded += OnSceneLoaded;
	}

	private void OnDisable()
	{
		// イベントの解除
		SceneManager.sceneLoaded -= OnSceneLoaded;
	}

	private void OnSceneLoaded(Scene scene, LoadSceneMode mode)
	{
		// Titleシーンに遷移したかをチェック
		if (SceneManager.GetActiveScene().name == "Title")
		{
			// すでにポーズUIが非表示なら再度非表示にする
			if (pauseUI.activeSelf)
			{
				pauseUI.SetActive(false);
			}

			// 時間スケールが1になっていない場合、1にリセット
			if (Time.timeScale != 1f)
			{
				Time.timeScale = 1f;
			}
		}
	}

}
