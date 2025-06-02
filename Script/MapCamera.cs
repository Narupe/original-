using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MapCamera : MonoBehaviour
{
	[SerializeField]
	
	private GameObject target;
	private Vector3 offset;

	void Start()
	{
		// ゲーム開始時点のカメラとターゲットの距離（オフセット）を取得
		offset = gameObject.transform.position - target.transform.position;
	}
	/// <summary>
	/// プレイヤーが移動した後にカメラが移動するようにするためにLateUpdateにする。
	/// </summary>
	void LateUpdate()
	{
		// カメラの位置をターゲットの位置にオフセットを足した場所にする。
		gameObject.transform.position = target.transform.position + offset;
	}
}
