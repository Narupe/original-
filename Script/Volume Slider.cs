using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VolumSlider : MonoBehaviour
{
    //BGMのボリューム設定
    public void SetBGMVolume(float volume)
    {
        SoundManager.instance.SetBGMVolume(volume);
    }
}
