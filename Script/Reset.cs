using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Reset : MonoBehaviour
{
	public GameObject HitPrefab;

	private Vector3 _initialPosition;
	private Quaternion _initialRotation;
	private Rigidbody _rigidbody;

	private bool _resetting = false;  // ���Z�b�g�����ǂ����̃t���O

	void Start()
	{
		// �����ʒu�Ɖ�]�̎擾
		_initialPosition = gameObject.transform.position;
		_initialRotation = gameObject.transform.rotation;
		// Rigidbody�̎擾
		_rigidbody = GetComponent<Rigidbody>();
	}

	void OnCollisionEnter(Collision collision)
	{
		if (collision.gameObject.tag == "stage" && !_resetting)
		{
			Invoke("ResetMove", 3f); // 3�b��Ƀ��Z�b�g����(5�b��ɍĂуh���b�O�\�j
		}
	}

	private void ResetMove()
	{
		_resetting = true;

		// Rigidbody�����݂���ꍇ�A�������Z���~
		if (_rigidbody != null)
		{
			_rigidbody.isKinematic = true; // �������Z�𖳌���
		}

		// �ʒu�̏������Ɖ�]�̃��Z�b�g
		gameObject.transform.position = _initialPosition;
		gameObject.transform.rotation = _initialRotation;

		// �����̔������i����Y���j
		Vector3 correctedPosition = gameObject.transform.position;
		correctedPosition.y = _initialPosition.y; // �����������ʒu��Y�ɍ��킹��
		gameObject.transform.position = correctedPosition;

		// �����ҋ@���Ă��畨�����Z���ėL����
		Invoke("EnablePhysics", 0.1f); // �����Z�����ԂōėL����
	}

	private void EnablePhysics()
	{
		// Rigidbody�����݂���ꍇ�A�������Z���ėL����
		if (_rigidbody != null)
		{
			_rigidbody.isKinematic = false; // �������Z���ėL����
		}

		_resetting = false;  // ���Z�b�g�I��
	}
}
