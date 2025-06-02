using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyMove : MonoBehaviour
{
	private Vector3 startPosition;

	[Header("Y Axis (上下移動)")]
	public bool isMoveY = true;             // Y軸の動きを有効にするか
	public float moveSpeedY = 0.5f;
	public float moveRangeY = 5f;
	public bool startMovingUp = true;

	[Header("X Axis (左右移動)")]
	public bool isMoveX = false;            // X軸の動きを有効にするか
	public float moveSpeedX = 0.5f;
	public float moveRangeX = 3f;
	public bool startMovingRight = true;

	[Header("Z Axis (前後移動)")]
	public bool isMoveZ = false;            // Z軸の動きを有効にするか
	public float moveSpeedZ = 0.5f;
	public float moveRangeZ = 2f;
	public bool startMovingForward = true;

	private float phaseOffsetY;
	private float phaseOffsetX;
	private float phaseOffsetZ;

	void Start()
	{
		startPosition = transform.position;

		phaseOffsetY = startMovingUp ? 0f : Mathf.PI;
		phaseOffsetX = startMovingRight ? 0f : Mathf.PI;
		phaseOffsetZ = startMovingForward ? 0f : Mathf.PI;
	}

	void Update()
	{
		// デフォルトは移動なし（0）
		float newY = 0f;
		float newX = 0f;
		float newZ = 0f;

		// 各軸が有効なときだけ、Sin波で動かす
		if (isMoveY)
			newY = Mathf.Sin(Time.time * moveSpeedY + phaseOffsetY) * moveRangeY;

		if (isMoveX)
			newX = Mathf.Sin(Time.time * moveSpeedX + phaseOffsetX) * moveRangeX;

		if (isMoveZ)
			newZ = Mathf.Sin(Time.time * moveSpeedZ + phaseOffsetZ) * moveRangeZ;

		// 合成して位置を更新
		transform.position = startPosition + new Vector3(newX, newY, newZ);
	}
}
