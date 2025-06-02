using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BrokenBlock : MonoBehaviour
{
	// �v���C���[�̃^�O
	private string playerTag = "Player";

	// �Փ˔���
	private void OnCollisionEnter(Collision collision)
	{
		// �Փ˂����I�u�W�F�N�g�̃^�O�� "Player" �������ꍇ
		if (collision.gameObject.CompareTag(playerTag))
		{
			// �������g���\���ɂ���
			gameObject.SetActive(false);
		}
	}

	// �g���K�[���� (�����g���K�[���g�p���Ă���ꍇ)
	private void OnTriggerEnter(Collider other)
	{
		// �Փ˂����I�u�W�F�N�g�̃^�O�� "Player" �������ꍇ
		if (other.CompareTag(playerTag))
		{
			// �������g���\���ɂ���
			gameObject.SetActive(false);
		}
	}
}
