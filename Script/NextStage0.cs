using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class NextStage0 : MonoBehaviour
{
	public void NextBtn()
	{
		SceneManager.LoadScene("Stage02");
	}

	public void OverBtn()
	{
		SceneManager.LoadScene("Title");
	}
}
