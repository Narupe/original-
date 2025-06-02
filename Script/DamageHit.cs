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
		//Component‚ðŽæ“¾
		audioSource = GetComponent<AudioSource>();
	}

	private void OnCollisionEnter(Collision collision)
	{
		//‰¹(sound1)‚ð–Â‚ç‚·
		audioSource.PlayOneShot(sound1);
	}
}
