using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class LifeCounter : MonoBehaviour
{
	// �C�x���g���`
	public System.Action<int> HpChanged;

	public static int _hpCount;

	// HP�̐���ǂ߂�悤�ɂ���
	public int HpCount { get { return _hpCount; } }

	private static LifeCounter _instance;

	public Image fadePanel;             // �t�F�[�h�p��UI�p�l���iImage�j
	public float fadeDuration = 3.0f;   // �t�F�[�h�̊����ɂ����鎞��
	public string nextSceneName = "GameOver";  // ���ɑJ�ڂ���V�[����

	void Awake()
	{
		// �V���O���g�����������邽�߂�
		if (_instance != null)
		{
			// ���łɃC���X�^���X�����݂��Ă����ꍇ�͂��̃I�u�W�F�N�g���폜����
			Destroy(gameObject);
		}
		else
		{
			// �V�����C���X�^���X��ێ�
			_instance = this;

			// �V�[�����؂�ւ��O�ɑO�̃V�[����LifeCounter���폜
			SceneManager.sceneUnloaded += OnSceneUnloaded;
		}
	}

	void Start()
	{
		// HP��30�Ŏn�܂�
		if(_hpCount == 0)_hpCount = 30;
		fadePanel.enabled = false;  // ���߂̓t�F�[�h�p�l�����\���ɂ��Ă���
	}

	// �V�[�����؂�ւ�钼�O�ɌĂ΂��
	private void OnSceneUnloaded(Scene scene)
	{
		// HP�̒l�����̃V�[���ɓn�����߁A�V�[�����؂�ւ��O�ɒl��ۑ�
		PlayerPrefs.SetInt("HPCount", _hpCount);
	}

	// �V�[�������[�h���ꂽ�Ƃ��ɌĂ΂��
	void OnEnable()
	{
		SceneManager.sceneLoaded += OnSceneLoaded;
	}

	void OnDisable()
	{
		SceneManager.sceneLoaded -= OnSceneLoaded;
	}

	// �V�[�������[�h���ꂽ��ɌĂ΂��
	void OnSceneLoaded(Scene scene, LoadSceneMode mode)
	{
		// �V�[����Stage01�Ȃ�HP��������
		if (scene.name == "Stage01")
		{
			_hpCount = 30;  // ������
			PlayerPrefs.SetInt("HPCount", _hpCount);  // PlayerPrefs�̒l��������
		}
		else
		{
			// �v���C���[��HP��ۑ����畜��
			_hpCount = PlayerPrefs.GetInt("HPCount", 30);

			// HP�ύX�C�x���g���Ăяo��
			HpChanged?.Invoke(_hpCount);
		}

		// �V�[����Stage12�Ȃ�HP��������
		if (scene.name == "Stage12")
		{
			_hpCount = 30;  // ������
			PlayerPrefs.SetInt("HPCount", _hpCount);  // PlayerPrefs�̒l��������
		}
		else
		{
			// �v���C���[��HP��ۑ����畜��
			_hpCount = PlayerPrefs.GetInt("HPCount", 30);

			// HP�ύX�C�x���g���Ăяo��
			HpChanged?.Invoke(_hpCount);
		}
	}

	// �g���K�[�ɓ������Ƃ�
	private void OnTriggerEnter(Collider other)
	{
		// "Box" �^�O�������Ă���ꍇ�͉������Ȃ�
		if (other.CompareTag("Box"))
			return;

		// HP��0�Ȃ牽�����Ȃ�
		if (_hpCount == 0)
			return;

		_hpCount -= 1;
		PlayerPrefs.SetInt("HPCount", _hpCount);  // PlayerPrefs��HP��ۑ�
		HpChanged?.Invoke(_hpCount);

		// �����AHP��0�ɂȂ�����
		if (_hpCount == 0)
		{
			StartCoroutine(FadeOutAndLoadScene());
		}
	}

	private void OnCollisionEnter(Collision collision)
	{
		// "Enemy" �^�O�ȊO�͖���
		if (!collision.gameObject.CompareTag("Enemy"))
			return;

		// HP��0�Ȃ牽�����Ȃ�
		if (_hpCount == 0)
			return;

		_hpCount -= 1;
		PlayerPrefs.SetInt("HPCount", _hpCount);
		HpChanged?.Invoke(_hpCount);

		if (_hpCount == 0)
		{
			StartCoroutine(FadeOutAndLoadScene());
		}
	}

	// �Q�[���I������HP�����Z�b�g���鏈��
	public void ResetHpCountOnGameExit()
	{
		_hpCount = 30;  // �����l�Ƀ��Z�b�g
		PlayerPrefs.SetInt("HPCount", _hpCount);  // PlayerPrefs�ł����Z�b�g
	}

	public IEnumerator FadeOutAndLoadScene()
	{
		fadePanel.enabled = true;                 // �p�l����L����
		float elapsedTime = 0.0f;                 // �o�ߎ��Ԃ�������
		Color startColor = fadePanel.color;       // �t�F�[�h�p�l���̊J�n�F���擾
		Color endColor = new Color(startColor.r, startColor.g, startColor.b, 1.0f); // �t�F�[�h�p�l���̍ŏI�F��ݒ�

		// �t�F�[�h�A�E�g�A�j���[�V���������s
		while (elapsedTime < fadeDuration)
		{
			elapsedTime += Time.deltaTime;                        // �o�ߎ��Ԃ𑝂₷
			float t = Mathf.Clamp01(elapsedTime / fadeDuration);  // �t�F�[�h�̐i�s�x���v�Z
			fadePanel.color = Color.Lerp(startColor, endColor, t); // �p�l���̐F��ύX���ăt�F�[�h�A�E�g
			yield return null;                                     // 1�t���[���ҋ@
		}

		fadePanel.color = endColor;  // �t�F�[�h������������ŏI�F�ɐݒ�
		SceneManager.LoadScene(nextSceneName); // �V�[�������[�h���ă��j���[�V�[���ɑJ��
	}
}