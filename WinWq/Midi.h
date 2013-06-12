// Midi.h: interface for the CMidi class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIDI_H__C16F1784_0241_11D4_B1EB_E0DB7F481023__INCLUDED_)
#define AFX_MIDI_H__C16F1784_0241_11D4_B1EB_E0DB7F481023__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMidi  
{
private:
	int mErrorCode;
	CString mFileName;
	UINT mDeviceID;
public:
	void Stop();
	BOOL Restart();
	BOOL IsPlaying();
	BOOL Play();
	CMidi(CString fileName="");
	virtual ~CMidi();
};

#endif // !defined(AFX_MIDI_H__C16F1784_0241_11D4_B1EB_E0DB7F481023__INCLUDED_)
