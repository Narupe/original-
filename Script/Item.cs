using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//アイテムの種類（あくまで定義）
public enum ItemType  //enum : 列挙型
{
	superball,

}

public class Item : MonoBehaviour
{
	//種類をInspectorで定義
	[SerializeField]
	private ItemType _type; //具体的どれなのか？

	//種類を外から読めるようにする
	public ItemType Type { get { return _type; } }
}
