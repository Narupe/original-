using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VolumSlider : MonoBehaviour
{
    //BGM�̃{�����[���ݒ�
    public void SetBGMVolume(float volume)
    {
        SoundManager.instance.SetBGMVolume(volume);
    }
}
