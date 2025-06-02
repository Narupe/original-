using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameClear : MonoBehaviour
{
	public Image fadePanel;             // �t�F�[�h�p��UI�p�l���iImage�j
	public float fadeDuration = 3.0f;   // �t�F�[�h�̊����ɂ����鎞��
	public string nextSceneName = "GameClear";  // ���ɑJ�ڂ���V�[����

	private void Start()
	{
		fadePanel.enabled = false;  // ���߂̓t�F�[�h�p�l�����\���ɂ��Ă���
	}

	//�����A�g���K�[�ɓ�������E�E�E
	private void OnTriggerEnter(Collider other)
	{
		//�����Ă������̂��A�uInvenory�v�R���|�[�l���g������̂����m�F
		Inventory inventory = other.GetComponent<Inventory>();

		//�����uInventory�v���Ȃ���΁A�Ȃɂ����Ȃ�
		if (inventory == null)
		{
			return;
		}

		//�����X�[�p�[�{�[���̐��̓[����������A�Ȃɂ����Ȃ�
		if (inventory.SuperBallCount == 0)
		{
			return;
		}

		StartCoroutine(FadeOutAndLoadScene());
	}

	public IEnumerator FadeOutAndLoadScene()
	{
		fadePanel.enabled = true;                 // �p�l����L����
		float elapsedTime = 0.0f;                 // �o�ߎ��Ԃ�������
		Color startColor = fadePanel.color;       // �t�F�[�h�p�l���̊J�n�F���擾
		Color endColor = new Color(startColor.r, startColor.g, startColor.b, 1.0f); // �t�F�[�h�p�l���̍ŏI�F��ݒ�

		// �t�F�[�h�A�E�g�A�j���[�V���������s
		while (elapsedTime < fadeDuration)
		{
			elapsedTime += Time.deltaTime;                        // �o�ߎ��Ԃ𑝂₷
			float t = Mathf.Clamp01(elapsedTime / fadeDuration);  // �t�F�[�h�̐i�s�x���v�Z
			fadePanel.color = Color.Lerp(startColor, endColor, t); // �p�l���̐F��ύX���ăt�F�[�h�A�E�g
			yield return null;                                     // 1�t���[���ҋ@
		}

		fadePanel.color = endColor;  // �t�F�[�h������������ŏI�F�ɐݒ�
		SceneManager.LoadScene(nextSceneName); // �V�[�������[�h���ă��j���[�V�[���ɑJ��
	}
}
