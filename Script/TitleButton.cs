using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class TitleButton : MonoBehaviour
{
	//�X�^�[�g�{�^����Stage01�ֈڍs
	public void StartBtn()
	{
		SceneManager.LoadScene("Stage01");
	}

	//�ݒ�{�^����Config�ֈڍs
	public void ConfBtn()
	{
		SceneManager.LoadScene("Config");
	}
}