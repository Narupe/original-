using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FALL : MonoBehaviour
{
	private const string playerTag = "Player";
	private bool isHidden = false;

	private Renderer objRenderer;
	private Collider objCollider;

	private void Start()
	{
		objRenderer = GetComponent<Renderer>();
		objCollider = GetComponent<Collider>();
	}

	private void OnCollisionEnter(Collision collision)
	{
		if (collision.gameObject.CompareTag(playerTag))
		{
			HideAndRespawn();
		}
	}

	private void OnTriggerEnter(Collider other)
	{
		if (other.CompareTag(playerTag))
		{
			HideAndRespawn();
		}
	}

	private void HideAndRespawn()
	{
		if (!isHidden)
		{
			StartCoroutine(HideAndReappear());
		}
	}

	private IEnumerator HideAndReappear()
	{
		isHidden = true;

		if (objRenderer != null) objRenderer.enabled = false;
		if (objCollider != null) objCollider.enabled = false;

		yield return new WaitForSeconds(30f);

		if (objRenderer != null) objRenderer.enabled = true;
		if (objCollider != null) objCollider.enabled = true;

		isHidden = false;
	}
}
