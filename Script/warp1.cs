using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class warp1 : MonoBehaviour
{
    //���[�v������I�u�W�F�N�g�̈ʒu���擾

	public GameObject Capsule;
	private Vector3 trans;
	private Vector3 startPosition;

	public float moveSpeed = 0.5f;  // ���E�̈ړ����x
	public float moveRange = 3f;  // �ړ��͈�

	public AudioClip sound1;
    AudioSource audioSource;

    void Start()
	{
		trans = Capsule.transform.position;

		startPosition = transform.position;

		//Component���擾
		audioSource = GetComponent<AudioSource>();
    }

	void OnTriggerEnter(Collider other)
	{
        //��(sound1)��炷
        audioSource.PlayOneShot(sound1);

        other.gameObject.transform.position = trans;
    }

	void Update()
	{
		// ���ԂɊ�Â��č��E�Ɉړ�
		float newX = Mathf.Sin(Time.time * moveSpeed) * moveRange;
		transform.position = startPosition + new Vector3(newX, 0, 0);
	}
}
