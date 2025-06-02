using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BrokenBlock : MonoBehaviour
{
	// プレイヤーのタグ
	private string playerTag = "Player";

	// 衝突判定
	private void OnCollisionEnter(Collision collision)
	{
		// 衝突したオブジェクトのタグが "Player" だった場合
		if (collision.gameObject.CompareTag(playerTag))
		{
			// 自分自身を非表示にする
			gameObject.SetActive(false);
		}
	}

	// トリガー判定 (もしトリガーを使用している場合)
	private void OnTriggerEnter(Collider other)
	{
		// 衝突したオブジェクトのタグが "Player" だった場合
		if (other.CompareTag(playerTag))
		{
			// 自分自身を非表示にする
			gameObject.SetActive(false);
		}
	}
}
