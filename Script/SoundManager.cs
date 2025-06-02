using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundManager : MonoBehaviour
{
    public static SoundManager instance;

    //BGMのボリューム
    [SerializeField] AudioSource bgmAudioSource01;
    [SerializeField] AudioSource bgmAudioSource02;
    [SerializeField] AudioSource bgmAudioSource03;
    [SerializeField] AudioSource bgmAudioSource04;
    [SerializeField] AudioSource bgmAudioSource05;
    [SerializeField] AudioSource bgmAudioSource06;
    [SerializeField] AudioSource bgmAudioSource07;
    [SerializeField] AudioSource bgmAudioSource08;

    void Awake()     //全シーンに反映
    {
        if (instance == null)
        {
            instance = this;
            DontDestroyOnLoad(gameObject);
        }
        else
        {
            Destroy(gameObject);
        }
    }
    
    //ボリュームを変える
    public void SetBGMVolume(float volume)
    {
        bgmAudioSource01.volume = volume;
        bgmAudioSource02.volume = volume;
        bgmAudioSource03.volume = volume;
        bgmAudioSource04.volume = volume;
        bgmAudioSource05.volume = volume;
        bgmAudioSource06.volume = volume;
        bgmAudioSource07.volume = volume;
        bgmAudioSource08.volume = volume;
    }
}
