using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ColisionSound : MonoBehaviour
{
	// ぶつかった時の音
	public AudioClip se;
	// AudioClip再生用
	AudioSource audiosource1;

	// Start is called before the first frame update
	void Start()
	{
		// AudioSourceコンポーネント取得
		audiosource1 = GetComponent<AudioSource>();
	}

	// Update is called once per frame
	void Update()
	{

	}

	// ぶつかった時に音を鳴らす
	void OnCollisionEnter(Collision col)
	{
		// 衝突したオブジェクトのタグが "Block" の場合は音を鳴らさない
		if (col.gameObject.CompareTag("Block"))
		{
			return;  // 音を鳴らさないで処理を終了
		}

		// それ以外のオブジェクトにぶつかった場合は音を鳴らす
		audiosource1.PlayOneShot(se);
	}
}
