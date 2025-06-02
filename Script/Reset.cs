using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Reset : MonoBehaviour
{
	public GameObject HitPrefab;

	private Vector3 _initialPosition;
	private Quaternion _initialRotation;
	private Rigidbody _rigidbody;

	private bool _resetting = false;  // リセット中かどうかのフラグ

	void Start()
	{
		// 初期位置と回転の取得
		_initialPosition = gameObject.transform.position;
		_initialRotation = gameObject.transform.rotation;
		// Rigidbodyの取得
		_rigidbody = GetComponent<Rigidbody>();
	}

	void OnCollisionEnter(Collision collision)
	{
		if (collision.gameObject.tag == "stage" && !_resetting)
		{
			Invoke("ResetMove", 3f); // 3秒後にリセット処理(5秒後に再びドラッグ可能）
		}
	}

	private void ResetMove()
	{
		_resetting = true;

		// Rigidbodyが存在する場合、物理演算を停止
		if (_rigidbody != null)
		{
			_rigidbody.isKinematic = true; // 物理演算を無効化
		}

		// 位置の初期化と回転のリセット
		gameObject.transform.position = _initialPosition;
		gameObject.transform.rotation = _initialRotation;

		// 高さの微調整（特にY軸）
		Vector3 correctedPosition = gameObject.transform.position;
		correctedPosition.y = _initialPosition.y; // 高さを初期位置のYに合わせる
		gameObject.transform.position = correctedPosition;

		// 少し待機してから物理演算を再有効化
		Invoke("EnablePhysics", 0.1f); // 少し短い時間で再有効化
	}

	private void EnablePhysics()
	{
		// Rigidbodyが存在する場合、物理演算を再有効化
		if (_rigidbody != null)
		{
			_rigidbody.isKinematic = false; // 物理演算を再有効化
		}

		_resetting = false;  // リセット終了
	}
}
