using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LastStage : MonoBehaviour
{
	public void NextBtn()
	{
		SceneManager.LoadScene("Stage12");
	}

	public void OverBtn()
	{
		SceneManager.LoadScene("Title");
	}
}
