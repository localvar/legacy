// Midi.cpp: implementation of the CMidi class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "winwq.h"
#include "Midi.h"
#include "mmsystem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMidi::CMidi(CString fileName)
{
	mDeviceID=0;
	mFileName=fileName;
}

CMidi::~CMidi()
{
	Stop();
}

BOOL CMidi::Play()
{
	if(mFileName.IsEmpty()) return false;
	{
		CFile cf;
		if(!cf.Open(mFileName,CFile::modeRead))
		{
			mFileName.Empty();
			return false;
		}
	}
	if(mDeviceID) Stop();

	MCI_OPEN_PARMS OpenParms;
	MCI_PLAY_PARMS PlayParms;
	MCI_STATUS_PARMS StatusParms;
	OpenParms.lpstrDeviceType="sequencer";
	OpenParms.lpstrElementName=(LPCSTR)mFileName;
//////////
	if(mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_TYPE|MCI_OPEN_ELEMENT,(DWORD)(LPVOID)&OpenParms))
		return false;
	mDeviceID=OpenParms.wDeviceID;
//////////
	StatusParms.dwItem=MCI_SEQ_STATUS_PORT;
	if(mciSendCommand(mDeviceID,MCI_STATUS,MCI_STATUS_ITEM,(DWORD)(LPVOID)&StatusParms)||
		mciSendCommand(mDeviceID,MCI_PLAY,MCI_NOTIFY,(DWORD)(LPVOID)&PlayParms))
	{
		mciSendCommand(mDeviceID,MCI_CLOSE,0,NULL);
		mDeviceID=0;
		return false;
	}
//////////
	return true;
}

BOOL CMidi::IsPlaying()
{
	if(!mDeviceID) return false;
	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem=MCI_STATUS_MODE;
	mciSendCommand(mDeviceID,MCI_STATUS,MCI_STATUS_ITEM,(DWORD)(LPVOID)&StatusParms);
	if(StatusParms.dwReturn==MCI_MODE_STOP) return false;
	return true;
}

BOOL CMidi::Restart()
{
	MCI_PLAY_PARMS PlayParms;
	MCI_SEEK_PARMS SeekParms;
	if(!mDeviceID) return Play();
	if(mciSendCommand(mDeviceID,MCI_SEEK,MCI_SEEK_TO_START,(DWORD)(LPVOID)&SeekParms)||
		mciSendCommand(mDeviceID,MCI_PLAY,MCI_NOTIFY,(DWORD)(LPVOID)&PlayParms))
	{
		mciSendCommand(mDeviceID,MCI_CLOSE,0,NULL);
		mDeviceID=0;
		return false;
	}
	return true;
}

void CMidi::Stop()
{
	if(mDeviceID)
	{
		mciSendCommand(mDeviceID,MCI_CLOSE,0,NULL);
		mDeviceID=0;
	}
}
