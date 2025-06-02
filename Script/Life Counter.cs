using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class LifeCounter : MonoBehaviour
{
	// イベントを定義
	public System.Action<int> HpChanged;

	public static int _hpCount;

	// HPの数を読めるようにする
	public int HpCount { get { return _hpCount; } }

	private static LifeCounter _instance;

	public Image fadePanel;             // フェード用のUIパネル（Image）
	public float fadeDuration = 3.0f;   // フェードの完了にかかる時間
	public string nextSceneName = "GameOver";  // 次に遷移するシーン名

	void Awake()
	{
		// シングルトンを実現するために
		if (_instance != null)
		{
			// すでにインスタンスが存在していた場合はこのオブジェクトを削除する
			Destroy(gameObject);
		}
		else
		{
			// 新しいインスタンスを保持
			_instance = this;

			// シーンが切り替わる前に前のシーンのLifeCounterを削除
			SceneManager.sceneUnloaded += OnSceneUnloaded;
		}
	}

	void Start()
	{
		// HPは30で始まる
		if(_hpCount == 0)_hpCount = 30;
		fadePanel.enabled = false;  // 初めはフェードパネルを非表示にしておく
	}

	// シーンが切り替わる直前に呼ばれる
	private void OnSceneUnloaded(Scene scene)
	{
		// HPの値を次のシーンに渡すため、シーンが切り替わる前に値を保存
		PlayerPrefs.SetInt("HPCount", _hpCount);
	}

	// シーンがロードされたときに呼ばれる
	void OnEnable()
	{
		SceneManager.sceneLoaded += OnSceneLoaded;
	}

	void OnDisable()
	{
		SceneManager.sceneLoaded -= OnSceneLoaded;
	}

	// シーンがロードされた後に呼ばれる
	void OnSceneLoaded(Scene scene, LoadSceneMode mode)
	{
		// シーンがStage01ならHPを初期化
		if (scene.name == "Stage01")
		{
			_hpCount = 30;  // 初期化
			PlayerPrefs.SetInt("HPCount", _hpCount);  // PlayerPrefsの値も初期化
		}
		else
		{
			// プレイヤーのHPを保存から復元
			_hpCount = PlayerPrefs.GetInt("HPCount", 30);

			// HP変更イベントを呼び出す
			HpChanged?.Invoke(_hpCount);
		}

		// シーンがStage12ならHPを初期化
		if (scene.name == "Stage12")
		{
			_hpCount = 30;  // 初期化
			PlayerPrefs.SetInt("HPCount", _hpCount);  // PlayerPrefsの値も初期化
		}
		else
		{
			// プレイヤーのHPを保存から復元
			_hpCount = PlayerPrefs.GetInt("HPCount", 30);

			// HP変更イベントを呼び出す
			HpChanged?.Invoke(_hpCount);
		}
	}

	// トリガーに入ったとき
	private void OnTriggerEnter(Collider other)
	{
		// "Box" タグを持っている場合は何もしない
		if (other.CompareTag("Box"))
			return;

		// HPが0なら何もしない
		if (_hpCount == 0)
			return;

		_hpCount -= 1;
		PlayerPrefs.SetInt("HPCount", _hpCount);  // PlayerPrefsにHPを保存
		HpChanged?.Invoke(_hpCount);

		// もし、HPが0になったら
		if (_hpCount == 0)
		{
			StartCoroutine(FadeOutAndLoadScene());
		}
	}

	private void OnCollisionEnter(Collision collision)
	{
		// "Enemy" タグ以外は無視
		if (!collision.gameObject.CompareTag("Enemy"))
			return;

		// HPが0なら何もしない
		if (_hpCount == 0)
			return;

		_hpCount -= 1;
		PlayerPrefs.SetInt("HPCount", _hpCount);
		HpChanged?.Invoke(_hpCount);

		if (_hpCount == 0)
		{
			StartCoroutine(FadeOutAndLoadScene());
		}
	}

	// ゲーム終了時にHPをリセットする処理
	public void ResetHpCountOnGameExit()
	{
		_hpCount = 30;  // 初期値にリセット
		PlayerPrefs.SetInt("HPCount", _hpCount);  // PlayerPrefsでもリセット
	}

	public IEnumerator FadeOutAndLoadScene()
	{
		fadePanel.enabled = true;                 // パネルを有効化
		float elapsedTime = 0.0f;                 // 経過時間を初期化
		Color startColor = fadePanel.color;       // フェードパネルの開始色を取得
		Color endColor = new Color(startColor.r, startColor.g, startColor.b, 1.0f); // フェードパネルの最終色を設定

		// フェードアウトアニメーションを実行
		while (elapsedTime < fadeDuration)
		{
			elapsedTime += Time.deltaTime;                        // 経過時間を増やす
			float t = Mathf.Clamp01(elapsedTime / fadeDuration);  // フェードの進行度を計算
			fadePanel.color = Color.Lerp(startColor, endColor, t); // パネルの色を変更してフェードアウト
			yield return null;                                     // 1フレーム待機
		}

		fadePanel.color = endColor;  // フェードが完了したら最終色に設定
		SceneManager.LoadScene(nextSceneName); // シーンをロードしてメニューシーンに遷移
	}
}