using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class warp1 : MonoBehaviour
{
    //ワープさせるオブジェクトの位置を取得

	public GameObject Capsule;
	private Vector3 trans;
	private Vector3 startPosition;

	public float moveSpeed = 0.5f;  // 左右の移動速度
	public float moveRange = 3f;  // 移動範囲

	public AudioClip sound1;
    AudioSource audioSource;

    void Start()
	{
		trans = Capsule.transform.position;

		startPosition = transform.position;

		//Componentを取得
		audioSource = GetComponent<AudioSource>();
    }

	void OnTriggerEnter(Collider other)
	{
        //音(sound1)を鳴らす
        audioSource.PlayOneShot(sound1);

        other.gameObject.transform.position = trans;
    }

	void Update()
	{
		// 時間に基づいて左右に移動
		float newX = Mathf.Sin(Time.time * moveSpeed) * moveRange;
		transform.position = startPosition + new Vector3(newX, 0, 0);
	}
}
