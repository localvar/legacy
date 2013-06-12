// DirectSound.h: interface for the CDirectSound class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __DIRECTSOUND_H__
#define __DIRECTSOUND_H__

#define MAX_SOUND 18

enum EFFECT
{
	PUTPIECE=0,
	ALREADYONE,
	INVALIDE,
	DAJIE,
	GAMEOVER,
	TIMEOVER,
	REALYGIVEUP,
	REALYNONUSER,
	TRYAGAIN,
	SEEANSWER,
	CONGRATULATIONS,
	TIMEWARNING,
	BLACKNONUSER,
	WHITENONUSER,
	BLACKINVALIDE,
	WHITEINVALIDE,
	CHANGECOLOR,
	DELETEPIECE
};

class CDirectSound  
{
public:
	inline BOOL IsSoundEnable();
	void EnableSound(BOOL bEnable=TRUE);
	BOOL Create(CWnd* pWnd);
	CDirectSound();
	virtual ~CDirectSound();

	BOOL LoadFromDisk (EFFECT);
	void Play (EFFECT);
	void Close (void);

private:
	BOOL LoadFile(EFFECT);
	BOOL ParseWaveMemory(EFFECT);
	BOOL LoadData(EFFECT);
	//LPDIRECTSOUND m_pDSoundObject;
private:
	BOOL m_bEnable;
	BOOL m_bCreated;
	/*/LPDIRECTSOUNDBUFFER m_pDSoundBuffer[MAX_SOUND];
	LPWAVEFORMATEX m_pFormat;
	DWORD m_dwSize;
	LPBYTE m_pData;
	LPVOID m_pMemory[MAX_SOUND];*/
};

inline BOOL CDirectSound::IsSoundEnable()
{
	return m_bEnable;
}
#endif //__DIRECTSOUND_H__
