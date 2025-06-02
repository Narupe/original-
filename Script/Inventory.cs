using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Inventory : MonoBehaviour
{
	// スーパーボールの数
	private int _superBallCount;

	// 鍵の数を読めるようにする
	public int SuperBallCount { get { return _superBallCount; } }

	public AudioClip sound1;
	AudioSource audioSource;

	void Start()
	{
		// ゲーム開始時に保存された数を読み込む
		_superBallCount = PlayerPrefs.GetInt("SuperBallCount", 0);

		// シーン遷移時に呼び出されるイベントを登録
		SceneManager.sceneLoaded += OnSceneLoaded;

		// ゲーム終了時に呼ばれる処理を登録
		Application.quitting += OnApplicationQuit;

		//Componentを取得
		audioSource = GetComponent<AudioSource>();
	}

	private void OnTriggerEnter(Collider other)
	{
		// アイテムかどうかを確認
		Item item = other.GetComponent<Item>();
		if (item == null)
			return;

		// 虹玉を確認する
		if (item.Type == ItemType.superball)
		{
			//音(sound1)を鳴らす
			audioSource.PlayOneShot(sound1);

			// 虹玉を拾ったので、数える
			_superBallCount++;

			// PlayerPrefsに保存
			PlayerPrefs.SetInt("SuperBallCount", _superBallCount);

			// _superBallCountが増えた場合、全てのシーンからsuperballを削除
			DeleteAllSuperballs();
		}

		// アイテムを削除
		Destroy(other.gameObject);
	}

	private void OnSceneLoaded(Scene scene, LoadSceneMode mode)
	{
		// Stage01シーンが読み込まれた場合
		if (scene.name == "Stage01")
		{
			// _superBallCountを初期化
			_superBallCount = 0;

			// PlayerPrefsにも初期化の情報を保存
			PlayerPrefs.SetInt("SuperBallCount", _superBallCount);
			PlayerPrefs.Save();
		}
	}

	private void OnApplicationQuit()
	{
		// ゲーム終了時に初期化
		_superBallCount = 0;

		// PlayerPrefsに初期化された値を保存
		PlayerPrefs.SetInt("SuperBallCount", _superBallCount);
		PlayerPrefs.Save();

		// ゲーム終了時にsuperballを削除
		DeleteAllSuperballs();
	}

	private void DeleteAllSuperballs()
	{
		// シーン内のすべてのsuperballオブジェクトを探して削除
		Item[] superballs = FindObjectsOfType<Item>();  // 全てのItemオブジェクトを取得

		foreach (var superball in superballs)
		{
			if (superball.Type == ItemType.superball)
			{
				Destroy(superball.gameObject);  // superballオブジェクトを削除
			}
		}
	}

}
