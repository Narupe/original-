using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//�A�C�e���̎�ށi�����܂Œ�`�j
public enum ItemType  //enum : �񋓌^
{
	superball,

}

public class Item : MonoBehaviour
{
	//��ނ�Inspector�Œ�`
	[SerializeField]
	private ItemType _type; //��̓I�ǂ�Ȃ̂��H

	//��ނ��O����ǂ߂�悤�ɂ���
	public ItemType Type { get { return _type; } }
}
