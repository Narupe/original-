using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ColisionSound : MonoBehaviour
{
	// �Ԃ��������̉�
	public AudioClip se;
	// AudioClip�Đ��p
	AudioSource audiosource1;

	// Start is called before the first frame update
	void Start()
	{
		// AudioSource�R���|�[�l���g�擾
		audiosource1 = GetComponent<AudioSource>();
	}

	// Update is called once per frame
	void Update()
	{

	}

	// �Ԃ��������ɉ���炷
	void OnCollisionEnter(Collision col)
	{
		// �Փ˂����I�u�W�F�N�g�̃^�O�� "Block" �̏ꍇ�͉���炳�Ȃ�
		if (col.gameObject.CompareTag("Block"))
		{
			return;  // ����炳�Ȃ��ŏ������I��
		}

		// ����ȊO�̃I�u�W�F�N�g�ɂԂ������ꍇ�͉���炷
		audiosource1.PlayOneShot(se);
	}
}
