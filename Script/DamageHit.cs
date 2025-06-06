using System.Collections;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using UnityEngine;

public class DamageHit : MonoBehaviour
{
	public AudioClip sound1;
	AudioSource audioSource;

	void Start()
	{
		//Componentを取得
		audioSource = GetComponent<AudioSource>();
	}

	private void OnCollisionEnter(Collision collision)
	{
		//音(sound1)を鳴らす
		audioSource.PlayOneShot(sound1);
	}
}
