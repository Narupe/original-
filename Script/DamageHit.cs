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
		//Component���擾
		audioSource = GetComponent<AudioSource>();
	}

	private void OnCollisionEnter(Collision collision)
	{
		//��(sound1)��炷
		audioSource.PlayOneShot(sound1);
	}
}
