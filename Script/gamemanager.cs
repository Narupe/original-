using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;

public class gamemanager : MonoBehaviour
{
    //HP�J�E���^�[
    [SerializeField]
    TextMeshProUGUI _hpText;

    [SerializeField]
    LifeCounter _hp;

	[SerializeField]
	TextMeshProUGUI _superBallText;

	[SerializeField]
	Inventory _superBall;

	private void Start()
	{
		
	}

	//�t���[����
	void Update()
	{
		_hpText.text = "x " + _hp.HpCount;

		_superBallText.text = "x " + _superBall.SuperBallCount;
		
	}
}
