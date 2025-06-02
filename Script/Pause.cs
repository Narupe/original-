using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;  // SceneManager���g�����߂ɒǉ�

public class Pause : MonoBehaviour
{
	// �|�[�Y�������ɕ\������UI
	[SerializeField]
	private GameObject pauseUI;

	// Update is called once per frame
	void Update()
	{
		//Q�L�[�Ń|�[�Y���
		if (Input.GetKeyDown("q"))
		{
			// �|�[�YUI�̃A�N�e�B�u�A��A�N�e�B�u��؂�ւ�
			pauseUI.SetActive(!pauseUI.activeSelf);

			// �|�[�YUI���\������Ă鎞�͒�~
			if (pauseUI.activeSelf)
			{
				Time.timeScale = 0f;  // �Q�[�����ꎞ��~
			}
			else  //������xQ�L�[�������ƍĊJ
			{
				Time.timeScale = 1f;  // �Q�[�����ĊJ
			}
		}
	}

	// �V�[�����ǂݍ��܂�钼�O�ɌĂяo�����
	private void OnEnable()
	{
		// �V�[�����ǂݍ��܂�邽�тɌĂ΂��C�x���g��o�^
		SceneManager.sceneLoaded += OnSceneLoaded;
	}

	private void OnDisable()
	{
		// �C�x���g�̉���
		SceneManager.sceneLoaded -= OnSceneLoaded;
	}

	private void OnSceneLoaded(Scene scene, LoadSceneMode mode)
	{
		// Title�V�[���ɑJ�ڂ��������`�F�b�N
		if (SceneManager.GetActiveScene().name == "Title")
		{
			// ���łɃ|�[�YUI����\���Ȃ�ēx��\���ɂ���
			if (pauseUI.activeSelf)
			{
				pauseUI.SetActive(false);
			}

			// ���ԃX�P�[����1�ɂȂ��Ă��Ȃ��ꍇ�A1�Ƀ��Z�b�g
			if (Time.timeScale != 1f)
			{
				Time.timeScale = 1f;
			}
		}
	}

}
