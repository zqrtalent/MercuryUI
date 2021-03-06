#pragma once
#include "../_platformCompat/PlatformCompat.h"
#include "Mmsystem.h"
#pragma comment(lib, "winmm.lib")

#pragma pack(1)
typedef struct __WAVEDESCR{
	BYTE riff[4];
	DWORD size;
	BYTE wave[4];
	} _WAVEDESCR, *_LPWAVEDESCR;

typedef struct __WAVEFORMAT{
	BYTE id[4];
	DWORD size;
	SHORT format;
	SHORT channels;
	DWORD sampleRate;
	DWORD byteRate;
	SHORT blockAlign;
	SHORT bitsPerSample;
} _WAVEFORMAT, *_LPWAVEFORMAT;
#pragma pack()


class CWave
{
public:
	CWave(void);
	virtual ~CWave(void);
	/*
public:
	virtual ~CWave(void);

	static CWave* GetInstance(){
		static CWave waveInst;
		return &waveInst;
		}
		*/
public:
	// Public methods
	BOOL	Load			(const TCHAR* lpszFilePath);
	BOOL	Save			(const TCHAR* lpszFilePath);
	BOOL	Play			();
	BOOL	Stop			();
	BOOL	Pause			();
	BOOL	Mix				(CWave& wave);
	// Set volume.
	// float value valid range is [0 ... 100]. volume percent.
	void	SetVolume		(BYTE btVolLeft, BYTE btVolRight);

	BOOL	IsValid			()			{return (m_lpData != NULL);}
	BOOL	IsPlaying		()			{return (!m_bStopped && !m_bPaused);}
	BOOL	IsStopped		()			{return m_bStopped;}
	BOOL	IsPaused		()			{return m_bPaused;}
	LPBYTE	GetData			()			{return m_lpData;}
	DWORD	GetSize			()			{return m_dwSize;}
	SHORT	GetChannels		()			{return m_Format.channels;}
	DWORD	GetSampleRate	()			{return m_Format.sampleRate;}
	SHORT	GetBitsPerSample()			{return m_Format.bitsPerSample;}

private:
	// Pribate methods
	BOOL Open							(SHORT channels, DWORD sampleRate, SHORT bitsPerSample);
	BOOL Close							();
	BOOL static CALLBACK WaveOut_Proc	(HWAVEOUT hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

private:
	std::string	m_sFileLoaded;
	// Private members
	_WAVEDESCR	m_Descriptor;
	_WAVEFORMAT m_Format;
	LPBYTE		m_lpData;
	DWORD		m_dwSize;
	HWAVEOUT	m_hWaveout;
	WAVEHDR		m_WaveHeader;
	BOOL		m_bStopped;
	BOOL		m_bPaused;
	DWORD		m_dwVolume;
};
