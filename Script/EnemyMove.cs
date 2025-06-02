using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyMove : MonoBehaviour
{
	private Vector3 startPosition;

	[Header("Y Axis (�㉺�ړ�)")]
	public bool isMoveY = true;             // Y���̓�����L���ɂ��邩
	public float moveSpeedY = 0.5f;
	public float moveRangeY = 5f;
	public bool startMovingUp = true;

	[Header("X Axis (���E�ړ�)")]
	public bool isMoveX = false;            // X���̓�����L���ɂ��邩
	public float moveSpeedX = 0.5f;
	public float moveRangeX = 3f;
	public bool startMovingRight = true;

	[Header("Z Axis (�O��ړ�)")]
	public bool isMoveZ = false;            // Z���̓�����L���ɂ��邩
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
		// �f�t�H���g�͈ړ��Ȃ��i0�j
		float newY = 0f;
		float newX = 0f;
		float newZ = 0f;

		// �e�����L���ȂƂ������ASin�g�œ�����
		if (isMoveY)
			newY = Mathf.Sin(Time.time * moveSpeedY + phaseOffsetY) * moveRangeY;

		if (isMoveX)
			newX = Mathf.Sin(Time.time * moveSpeedX + phaseOffsetX) * moveRangeX;

		if (isMoveZ)
			newZ = Mathf.Sin(Time.time * moveSpeedZ + phaseOffsetZ) * moveRangeZ;

		// �������Ĉʒu���X�V
		transform.position = startPosition + new Vector3(newX, newY, newZ);
	}
}
