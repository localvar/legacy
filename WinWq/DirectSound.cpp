// DirectSound.cpp: implementation of the CDirectSound class.
//
//////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include <mmsystem.h>
#include "DirectSound.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDirectSound::CDirectSound()
{
	m_bEnable = FALSE;
	m_bCreated = FALSE;
	/*for(int i=0;i<MAX_SOUND;i++)
		m_pMemory[i]=NULL;
	m_pData = NULL;
	m_pFormat = NULL;
	m_dwSize = 0;
	*/
}

CDirectSound::~CDirectSound()
{
	Close ();
}

BOOL CDirectSound::LoadFromDisk(EFFECT efx)
{
	/*
	if (!LoadFile(efx))
		return FALSE;

	if (!ParseWaveMemory(efx)) 
		return FALSE;

	DSBUFFERDESC BufferDesc;
	memset (&BufferDesc, 0, sizeof (BufferDesc));
	BufferDesc.lpwfxFormat = (LPWAVEFORMATEX) m_pFormat;
	BufferDesc.dwSize = sizeof (DSBUFFERDESC);
	BufferDesc.dwBufferBytes = m_dwSize;
	BufferDesc.dwFlags = DSBCAPS_STATIC;
	if (m_pDSoundObject->CreateSoundBuffer
		(&BufferDesc,&m_pDSoundBuffer[efx],0)!=DS_OK)
		return FALSE;

	if (!LoadData(efx))
	{
		m_pDSoundBuffer[efx]->Release ();
		return FALSE;
	}
*/
	return TRUE;
}

void CDirectSound::Play(EFFECT efx)
{
	/*
	ASSERT(efx<MAX_SOUND);

	if (!m_bEnable||m_pMemory[efx]==NULL)//||!m_bCreated)
		return;
	m_pDSoundBuffer[efx]->SetCurrentPosition(0);
	m_pDSoundBuffer[efx]->Play(0,0,0);
//TryPlay:
//if (m_pDSoundBuffer[efx]->Play (0, 0, 0) == DSERR_BUFFERLOST)
//	{
//		if (LoadData ())
//			goto TryPlay;
//	}
*/
}

void CDirectSound::Close (void)
{
	/*
	if (m_bCreated)
	{
		m_pData = NULL;
		m_pFormat = NULL;

		for(int i=0;i<MAX_SOUND;i++)
			if(m_pMemory[i]!=NULL)
			{
				delete []m_pMemory[i];
				m_pMemory[i]=NULL;
				m_pDSoundBuffer[i]->Release ();
			}

		m_pDSoundObject->Release();
		m_bCreated = FALSE;
	}
	*/
	m_bCreated = FALSE;
}

BOOL CDirectSound::LoadData (EFFECT efx)
{
	/*
	LPVOID lpPtr1, lpPtr2;
	DWORD dwLen1, dwLen2;
	HRESULT hResult;

TryLoad:
	hResult=m_pDSoundBuffer[efx]->Lock(0,m_dwSize,&lpPtr1,
		&dwLen1,&lpPtr2,&dwLen2,0);
	if (hResult == DS_OK)
	{
		memcpy (lpPtr1, m_pData, dwLen1);
		if (lpPtr2)
			memcpy (lpPtr2, m_pData + dwLen1, dwLen2);
		m_pDSoundBuffer[efx]->Unlock (lpPtr1, dwLen1, lpPtr2, dwLen2);
		return TRUE;
	}
	else if (hResult == DSERR_BUFFERLOST)
	{
		hResult = m_pDSoundBuffer[efx]->Restore ();
		if (hResult == DS_OK)
			goto TryLoad;
	}

	return FALSE;
	*/
	return TRUE;
}

BOOL CDirectSound::LoadFile(EFFECT efx)
{
	/*
	CFile File;
	DWORD dwSize;

 	CString Filename=AfxGetApp()->GetProfileString("Settings","StartUpDir","");

	char *fn[]=
	{
		"\\Highlite.wav",
		"\\AlreadyOne.wav",
		"\\Invalide.wav",
		"\\DaJie.wav",
		"\\GameOver.wav",
		"\\TimeOver.wav",
		"\\IsLost.wav",
		"\\RealyNonuser.wav",
		"\\TryAgain.wav",
		"\\SeeAnswer.wav",
		"\\ZhuHe.wav",
		"\\TimeWarn.wav",
		"\\BNonuser.wav",
		"\\WNonuser.wav",
		"\\BInvalide.wav",
		"\\WInvalide.wav",
		"\\ChgColor.wav",
		"\\DelPiece.wav"
	};

	Filename+=fn[efx];

	if(!File.Open(Filename,CFile::modeRead|CFile::shareDenyNone))
		return FALSE;
	dwSize=File.GetLength();
	m_pMemory[efx]=new char[dwSize];
	if(File.ReadHuge(m_pMemory[efx],dwSize)!=dwSize)
	{
		File.Close ();
		delete []m_pMemory[efx];
		m_pMemory[efx]=NULL;
		return FALSE;
	}
	File.Close();
*/
	return TRUE;
}

BOOL CDirectSound::ParseWaveMemory(EFFECT efx)
{
	/*
	LPDWORD pdw;
	LPDWORD pdwEnd;
	DWORD dwRiff;
	DWORD dwType;
	DWORD dwLength;

	m_pFormat = NULL;
	m_pData = NULL;
	m_dwSize = 0;

	pdw=(DWORD*)m_pMemory[efx];

	dwRiff = *pdw++;
	dwLength = *pdw++;
	dwType = *pdw++;

	if (dwRiff != mmioFOURCC ('R', 'I', 'F', 'F'))
		return FALSE;

	if (dwType != mmioFOURCC ('W', 'A', 'V', 'E'))
		return FALSE;

	// Find the pointer to the end of the chunk of memory
	pdwEnd = (DWORD *)((BYTE *) pdw + dwLength - 4);

	// Run through the bytes looking for the tags
	while (pdw < pdwEnd)
	{
		dwType = *pdw++;
		dwLength = *pdw++;

		switch (dwType)
		{
			case mmioFOURCC('f', 'm', 't', ' '):
				if (!m_pFormat)
				{
					if (dwLength < sizeof (WAVEFORMAT))
						return FALSE;

					// Set the lplpWaveHeader to point to this part of
					// the memory chunk
					m_pFormat = (LPWAVEFORMATEX) pdw;

					// Check to see if the other two items have been
					// filled out yet (the bits and the size of the
					// bits). If so, then this chunk of memory has
					// been parsed out and we can exit
					if (m_pData && m_dwSize)
						return TRUE;
				}
				break;

			// Found the samples
			case mmioFOURCC('d', 'a', 't', 'a'):
				if (!m_pData || !m_dwSize)
				{
					// Point the samples pointer to this part of the
					// chunk of memory.
					m_pData = (LPBYTE) pdw;

					// Set the size of the wave
					m_dwSize = dwLength;

					// Make sure we have our header pointer set up.
					// If we do, we can exit
					if (m_pFormat)
						return TRUE;
				}
				break;
		}

		// Move the pointer through the chunk of memory
		pdw = (DWORD *)((BYTE *) pdw + ((dwLength + 1) &~ 1));
	}

	// Failed! If we made it here, we did not get all the peices
	// of the wave
	return FALSE;
	*/
	return TRUE;
}

BOOL CDirectSound::Create(CWnd *pWnd)
{
/*	if (m_bCreated)
		Close();
	
	if(DirectSoundCreate(NULL,&m_pDSoundObject,NULL)==DS_OK)
	{
		m_pDSoundObject->SetCooperativeLevel(pWnd->m_hWnd,DSSCL_NORMAL);
		
		for(int i=0;i<MAX_SOUND;i++)
			if(LoadFromDisk((EFFECT)i)) m_bCreated=TRUE;
		
		if(!m_bCreated)
			m_pDSoundObject->Release();
	}

	return m_bCreated;
	*/
	m_bCreated = TRUE;
	return TRUE;
}

void CDirectSound::EnableSound(BOOL bEnable)
{
	m_bEnable=bEnable;
	if(!m_bCreated)
		m_bEnable=false;
}

