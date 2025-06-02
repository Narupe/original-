using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Inventory : MonoBehaviour
{
	// �X�[�p�[�{�[���̐�
	private int _superBallCount;

	// ���̐���ǂ߂�悤�ɂ���
	public int SuperBallCount { get { return _superBallCount; } }

	public AudioClip sound1;
	AudioSource audioSource;

	void Start()
	{
		// �Q�[���J�n���ɕۑ����ꂽ����ǂݍ���
		_superBallCount = PlayerPrefs.GetInt("SuperBallCount", 0);

		// �V�[���J�ڎ��ɌĂяo�����C�x���g��o�^
		SceneManager.sceneLoaded += OnSceneLoaded;

		// �Q�[���I�����ɌĂ΂�鏈����o�^
		Application.quitting += OnApplicationQuit;

		//Component���擾
		audioSource = GetComponent<AudioSource>();
	}

	private void OnTriggerEnter(Collider other)
	{
		// �A�C�e�����ǂ������m�F
		Item item = other.GetComponent<Item>();
		if (item == null)
			return;

		// ���ʂ��m�F����
		if (item.Type == ItemType.superball)
		{
			//��(sound1)��炷
			audioSource.PlayOneShot(sound1);

			// ���ʂ��E�����̂ŁA������
			_superBallCount++;

			// PlayerPrefs�ɕۑ�
			PlayerPrefs.SetInt("SuperBallCount", _superBallCount);

			// _superBallCount���������ꍇ�A�S�ẴV�[������superball���폜
			DeleteAllSuperballs();
		}

		// �A�C�e�����폜
		Destroy(other.gameObject);
	}

	private void OnSceneLoaded(Scene scene, LoadSceneMode mode)
	{
		// Stage01�V�[�����ǂݍ��܂ꂽ�ꍇ
		if (scene.name == "Stage01")
		{
			// _superBallCount��������
			_superBallCount = 0;

			// PlayerPrefs�ɂ��������̏���ۑ�
			PlayerPrefs.SetInt("SuperBallCount", _superBallCount);
			PlayerPrefs.Save();
		}
	}

	private void OnApplicationQuit()
	{
		// �Q�[���I�����ɏ�����
		_superBallCount = 0;

		// PlayerPrefs�ɏ��������ꂽ�l��ۑ�
		PlayerPrefs.SetInt("SuperBallCount", _superBallCount);
		PlayerPrefs.Save();

		// �Q�[���I������superball���폜
		DeleteAllSuperballs();
	}

	private void DeleteAllSuperballs()
	{
		// �V�[�����̂��ׂĂ�superball�I�u�W�F�N�g��T���č폜
		Item[] superballs = FindObjectsOfType<Item>();  // �S�Ă�Item�I�u�W�F�N�g���擾

		foreach (var superball in superballs)
		{
			if (superball.Type == ItemType.superball)
			{
				Destroy(superball.gameObject);  // superball�I�u�W�F�N�g���폜
			}
		}
	}

}
