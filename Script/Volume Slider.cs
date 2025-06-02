using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VolumSlider : MonoBehaviour
{
    //BGM‚Ìƒ{ƒŠƒ…[ƒ€İ’è
    public void SetBGMVolume(float volume)
    {
        SoundManager.instance.SetBGMVolume(volume);
    }
}
