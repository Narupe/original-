using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class FinalStage : MonoBehaviour
{
	public void NextBtn()
	{
		SceneManager.LoadScene("Stage13");
	}

	public void OverBtn()
	{
		SceneManager.LoadScene("Title");
	}
}
