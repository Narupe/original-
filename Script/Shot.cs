using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class Shot : MonoBehaviour
{
	public float forceMultiplier = 7f;  // ボールに加える力の倍率
	private Vector3 dragStartPos;        // ドラッグの開始位置
	private Vector3 dragEndPos;          // ドラッグの終了位置
	private Rigidbody rb;
	private bool isDragging = false;
	private GameObject draggedObject = null;  // 現在ドラッグしているオブジェクト

	public AudioClip sound1;
	AudioSource audioSource;

	private bool canDrag = true;  // ドラッグ可能かどうかのフラグ
	private float dragCooldownTime = 10f;  // ドラッグ可能になるまでのクールダウン時間
	private float dragCooldownTimer = 0f;  // クールダウン用タイマー

	private int jumpCount = 0;      // ジャンプ回数
	private int maxJumps = 5;       // 最大ジャンプ回数

	private LineRenderer lineRenderer;  // LineRendererの参照

	//インターバルゲージ
	public Image UIobj;
	public bool roop;
	public float countTime = 10.0f;

	//敵のHP
	public Slider slider;

	public Image fadePanel;             // フェード用のUIパネル（Image）
	public float fadeDuration = 3.0f;   // フェードの完了にかかる時間
	public string nextSceneName = "AllClear";  // 次に遷移するシーン名

	void Start()
	{
		fadePanel.enabled = false;  // 初めはフェードパネルを非表示にしておく

		slider.value = 100;

		rb = GetComponent<Rigidbody>();
		audioSource = GetComponent<AudioSource>();

		// LineRendererでドラッグしたときの線を描画
		lineRenderer = GetComponent<LineRenderer>();
		lineRenderer.positionCount = 0;  // 最初は線を表示しない
		lineRenderer.startColor = Color.red;  // 線の開始色を赤に設定
		lineRenderer.endColor = Color.red;    // 線の終了色を赤に設定
		lineRenderer.startWidth = 0.05f; // 線の太さ
		lineRenderer.endWidth = 0.05f;   // 線の太さ
	}

	void Update()
	{
		// ドラッグ可能な時間かどうかを確認
		if (!canDrag)
		{
			dragCooldownTimer += Time.deltaTime;
			if (dragCooldownTimer >= dragCooldownTime)
			{
				canDrag = true;  // 10秒経過したらドラッグ可能にする
				dragCooldownTimer = 0f;  // タイマーリセット
			}
		}

		if (canDrag)
		{
			Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
			RaycastHit hit;

			// Raycastでオブジェクトにヒットした場合
			if (Physics.Raycast(ray, out hit, 10.0f))
			{
				// ヒットしたオブジェクトがボールの場合
				if (hit.collider.gameObject.CompareTag("Player"))
				{
					// 左クリックでドラッグ開始
					if (Input.GetMouseButtonDown(0))
					{
						StartDrag(hit.collider.gameObject);  // ヒットしたボールをドラッグ対象にする
					}
				}

				// ドラッグ中
				if (isDragging)
				{
					Dragging();
				}

				// 左クリックを離してドラッグ終了
				if (Input.GetMouseButtonUp(0))
				{
					EndDrag();

					// もし roop が true ならば
					if (roop)
					{
						// 最初の処理 (UIobj.fillAmount を 0 に設定)
						UIobj.fillAmount = 0.0f;

						// fillAmount が 0 のときに加算を開始する
						if (UIobj.fillAmount == 0.0f)
						{
							StartCoroutine(IncrementFillAmount());
						}
					}
				}

				// Coroutine で fillAmount を加算
				IEnumerator IncrementFillAmount()
				{
					while (UIobj.fillAmount < 1.0f)  // 1.0f に達するまで繰り返し加算
					{
						UIobj.fillAmount += 1.0f / countTime * Time.deltaTime;
						yield return null;  // 次のフレームまで待機
					}
				}

			}
			else
			{
				// ボール以外のオブジェクトに当たっていれば、ドラッグを解除
				if (Input.GetMouseButtonUp(0))
				{
					EndDrag();
				}
			}
		}

		// スペースキーまたはJumpボタンでジャンプ処理
		if (Input.GetKeyDown(KeyCode.Space) && jumpCount < maxJumps)
		{
			Jump();
		}
	}

	void StartDrag(GameObject hitObject)
	{
		// ドラッグ開始時、ボールを認識してそのオブジェクトをドラッグ対象にする
		draggedObject = hitObject;
		dragStartPos = GetMouseWorldPosition();
		isDragging = true;  // ドラッグ開始

		// LineRendererの設定
		lineRenderer.positionCount = 2;  // 線の頂点を2つ設定（開始点と現在位置）
		lineRenderer.SetPosition(0, dragStartPos);  // 開始位置を設定
	}

	void Dragging()
	{
		// ドラッグ中の位置を取得
		Vector3 currentPos = GetMouseWorldPosition();

		// LineRendererの現在位置を更新
		lineRenderer.SetPosition(1, currentPos);
	}

	void EndDrag()
	{
		// ドラッグ終了位置を取得
		dragEndPos = GetMouseWorldPosition();
		isDragging = false;  // ドラッグ終了

		// LineRendererを消去
		lineRenderer.positionCount = 0;

		if (draggedObject != null)
		{
			// ドラッグした距離と方向を計算してボールに力を加える
			Vector3 dragVector = dragStartPos - dragEndPos;
			Rigidbody rb = draggedObject.GetComponent<Rigidbody>();
			if (rb != null)
			{
				rb.AddForce(dragVector * forceMultiplier, ForceMode.Impulse);
			}

			draggedObject = null;  // ドラッグ対象のオブジェクトをリセット

			// ドラッグが終了したらクールダウンを開始
			canDrag = false;  // 再ドラッグ不可にする
		}

		// 音(sound1)を鳴らす
		audioSource.PlayOneShot(sound1);
	}

	void Jump()
	{
		if (rb != null && jumpCount < maxJumps)
		{
			// 上方向に力を加えてジャンプ
			rb.AddForce(Vector3.up * 10f, ForceMode.Impulse);
			jumpCount++;  // ジャンプ回数を増加

			// 音(sound1)を鳴らす
			audioSource.PlayOneShot(sound1);
		}
	}

	Vector3 GetMouseWorldPosition()
	{
		// マウス位置をワールド座標に変換
		Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
		RaycastHit hit;

		// 地面に当たった場所を取得
		if (Physics.Raycast(ray, out hit))
		{
			return hit.point;
		}

		return Vector3.zero;  // 何も当たらなかった場合
	}

	//当たるコライダーによって減る量が変わる
	void OnCollisionEnter(Collision other)
	{
		if (other.gameObject.name == "Props_Roof Helipad")
		{
			slider.value -= 10;
		}

		if (other.gameObject.name == "Props_Roof Helipad2")
		{
			slider.value -= 20;
		}

		if (slider.value == 0)
		{
			StartCoroutine(FadeOutAndLoadScene());
		}
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
