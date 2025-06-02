using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class ScoreManager : MonoBehaviour
{
	[SerializeField]
	TextMeshProUGUI _scoreText;

	[SerializeField]
	LifeCounter _hp;

	private void Start()
	{

	}

	public static string GetRank(int HpCount)
	{
		if (HpCount >= 20)
			return "A";
		else if (HpCount >= 15)
			return "B";
		else
			return "C";
	}

	//ƒtƒŒ[ƒ€–ˆ
	void Update()
	{
		GetRank(0);
		_scoreText.text = "SCORE  " + _hp.HpCount;
	}
}
