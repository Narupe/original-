using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class Select : MonoBehaviour
{
	public Image fadePanel;             // �t�F�[�h�p��UI�p�l���iImage�j
	public float fadeDuration = 3.0f;   // �t�F�[�h�̊����ɂ����鎞��
	public string nextSceneName = "NextStage";  // ���ɑJ�ڂ���V�[����

	private void Start()
	{
		fadePanel.enabled = false;  // ���߂̓t�F�[�h�p�l�����\���ɂ��Ă���
	}
	
	private void OnCollisionEnter(Collision collision)
	{
		// ����̃I�u�W�F�N�g�ƏՓ˂����ꍇ�Ƀt�F�[�h�A�E�g���J�n
		if (collision.gameObject.CompareTag("Box")) // Player�^�O�̃I�u�W�F�N�g�Ɠ��������ꍇ
		{
			StartCoroutine(FadeOutAndLoadScene());
		}
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
