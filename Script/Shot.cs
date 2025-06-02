using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class Shot : MonoBehaviour
{
	public float forceMultiplier = 7f;  // �{�[���ɉ�����͂̔{��
	private Vector3 dragStartPos;        // �h���b�O�̊J�n�ʒu
	private Vector3 dragEndPos;          // �h���b�O�̏I���ʒu
	private Rigidbody rb;
	private bool isDragging = false;
	private GameObject draggedObject = null;  // ���݃h���b�O���Ă���I�u�W�F�N�g

	public AudioClip sound1;
	AudioSource audioSource;

	private bool canDrag = true;  // �h���b�O�\���ǂ����̃t���O
	private float dragCooldownTime = 10f;  // �h���b�O�\�ɂȂ�܂ł̃N�[���_�E������
	private float dragCooldownTimer = 0f;  // �N�[���_�E���p�^�C�}�[

	private int jumpCount = 0;      // �W�����v��
	private int maxJumps = 5;       // �ő�W�����v��

	private LineRenderer lineRenderer;  // LineRenderer�̎Q��

	//�C���^�[�o���Q�[�W
	public Image UIobj;
	public bool roop;
	public float countTime = 10.0f;

	//�G��HP
	public Slider slider;

	public Image fadePanel;             // �t�F�[�h�p��UI�p�l���iImage�j
	public float fadeDuration = 3.0f;   // �t�F�[�h�̊����ɂ����鎞��
	public string nextSceneName = "AllClear";  // ���ɑJ�ڂ���V�[����

	void Start()
	{
		fadePanel.enabled = false;  // ���߂̓t�F�[�h�p�l�����\���ɂ��Ă���

		slider.value = 100;

		rb = GetComponent<Rigidbody>();
		audioSource = GetComponent<AudioSource>();

		// LineRenderer�Ńh���b�O�����Ƃ��̐���`��
		lineRenderer = GetComponent<LineRenderer>();
		lineRenderer.positionCount = 0;  // �ŏ��͐���\�����Ȃ�
		lineRenderer.startColor = Color.red;  // ���̊J�n�F��Ԃɐݒ�
		lineRenderer.endColor = Color.red;    // ���̏I���F��Ԃɐݒ�
		lineRenderer.startWidth = 0.05f; // ���̑���
		lineRenderer.endWidth = 0.05f;   // ���̑���
	}

	void Update()
	{
		// �h���b�O�\�Ȏ��Ԃ��ǂ������m�F
		if (!canDrag)
		{
			dragCooldownTimer += Time.deltaTime;
			if (dragCooldownTimer >= dragCooldownTime)
			{
				canDrag = true;  // 10�b�o�߂�����h���b�O�\�ɂ���
				dragCooldownTimer = 0f;  // �^�C�}�[���Z�b�g
			}
		}

		if (canDrag)
		{
			Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
			RaycastHit hit;

			// Raycast�ŃI�u�W�F�N�g�Ƀq�b�g�����ꍇ
			if (Physics.Raycast(ray, out hit, 10.0f))
			{
				// �q�b�g�����I�u�W�F�N�g���{�[���̏ꍇ
				if (hit.collider.gameObject.CompareTag("Player"))
				{
					// ���N���b�N�Ńh���b�O�J�n
					if (Input.GetMouseButtonDown(0))
					{
						StartDrag(hit.collider.gameObject);  // �q�b�g�����{�[�����h���b�O�Ώۂɂ���
					}
				}

				// �h���b�O��
				if (isDragging)
				{
					Dragging();
				}

				// ���N���b�N�𗣂��ăh���b�O�I��
				if (Input.GetMouseButtonUp(0))
				{
					EndDrag();

					// ���� roop �� true �Ȃ��
					if (roop)
					{
						// �ŏ��̏��� (UIobj.fillAmount �� 0 �ɐݒ�)
						UIobj.fillAmount = 0.0f;

						// fillAmount �� 0 �̂Ƃ��ɉ��Z���J�n����
						if (UIobj.fillAmount == 0.0f)
						{
							StartCoroutine(IncrementFillAmount());
						}
					}
				}

				// Coroutine �� fillAmount �����Z
				IEnumerator IncrementFillAmount()
				{
					while (UIobj.fillAmount < 1.0f)  // 1.0f �ɒB����܂ŌJ��Ԃ����Z
					{
						UIobj.fillAmount += 1.0f / countTime * Time.deltaTime;
						yield return null;  // ���̃t���[���܂őҋ@
					}
				}

			}
			else
			{
				// �{�[���ȊO�̃I�u�W�F�N�g�ɓ������Ă���΁A�h���b�O������
				if (Input.GetMouseButtonUp(0))
				{
					EndDrag();
				}
			}
		}

		// �X�y�[�X�L�[�܂���Jump�{�^���ŃW�����v����
		if (Input.GetKeyDown(KeyCode.Space) && jumpCount < maxJumps)
		{
			Jump();
		}
	}

	void StartDrag(GameObject hitObject)
	{
		// �h���b�O�J�n���A�{�[����F�����Ă��̃I�u�W�F�N�g���h���b�O�Ώۂɂ���
		draggedObject = hitObject;
		dragStartPos = GetMouseWorldPosition();
		isDragging = true;  // �h���b�O�J�n

		// LineRenderer�̐ݒ�
		lineRenderer.positionCount = 2;  // ���̒��_��2�ݒ�i�J�n�_�ƌ��݈ʒu�j
		lineRenderer.SetPosition(0, dragStartPos);  // �J�n�ʒu��ݒ�
	}

	void Dragging()
	{
		// �h���b�O���̈ʒu���擾
		Vector3 currentPos = GetMouseWorldPosition();

		// LineRenderer�̌��݈ʒu���X�V
		lineRenderer.SetPosition(1, currentPos);
	}

	void EndDrag()
	{
		// �h���b�O�I���ʒu���擾
		dragEndPos = GetMouseWorldPosition();
		isDragging = false;  // �h���b�O�I��

		// LineRenderer������
		lineRenderer.positionCount = 0;

		if (draggedObject != null)
		{
			// �h���b�O���������ƕ������v�Z���ă{�[���ɗ͂�������
			Vector3 dragVector = dragStartPos - dragEndPos;
			Rigidbody rb = draggedObject.GetComponent<Rigidbody>();
			if (rb != null)
			{
				rb.AddForce(dragVector * forceMultiplier, ForceMode.Impulse);
			}

			draggedObject = null;  // �h���b�O�Ώۂ̃I�u�W�F�N�g�����Z�b�g

			// �h���b�O���I��������N�[���_�E�����J�n
			canDrag = false;  // �ăh���b�O�s�ɂ���
		}

		// ��(sound1)��炷
		audioSource.PlayOneShot(sound1);
	}

	void Jump()
	{
		if (rb != null && jumpCount < maxJumps)
		{
			// ������ɗ͂������ăW�����v
			rb.AddForce(Vector3.up * 10f, ForceMode.Impulse);
			jumpCount++;  // �W�����v�񐔂𑝉�

			// ��(sound1)��炷
			audioSource.PlayOneShot(sound1);
		}
	}

	Vector3 GetMouseWorldPosition()
	{
		// �}�E�X�ʒu�����[���h���W�ɕϊ�
		Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
		RaycastHit hit;

		// �n�ʂɓ��������ꏊ���擾
		if (Physics.Raycast(ray, out hit))
		{
			return hit.point;
		}

		return Vector3.zero;  // ����������Ȃ������ꍇ
	}

	//������R���C�_�[�ɂ���Č���ʂ��ς��
	void OnCollisionEnter(Collision other)
	{
		if (other.gameObject.name == "Props_Roof Helipad")
		{
			slider.value -= 10;
		}

		if (other.gameObject.name == "Props_Roof Helipad2")
		{
			slider.value -= 20;
		}

		if (slider.value == 0)
		{
			StartCoroutine(FadeOutAndLoadScene());
		}
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
