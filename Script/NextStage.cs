using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class NextStage : MonoBehaviour
{
	public void NextBtn()
	{
		SceneManager.LoadScene("Stage05");
	}

	public void OverBtn()
	{
		SceneManager.LoadScene("Title");
	}
}
