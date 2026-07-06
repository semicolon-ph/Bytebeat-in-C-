#include <Windows.h>
#include <math.h>
#pragma comment(lib, "winmm.lib")

/* Credits to Wipet for the Code. */
/* 8000 hz = 16000 hz in this code. so it's multiplied by 2 */
/* removing "*2" doesnt change it. */

INT
WINAPI
wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmd, INT nShowCmd)
{
	INT nSamplesPerSec = 8000;
	INT nSampleCount = 8000 * 500; /* 500 = 500 seconds */
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = HeapAlloc(hHeap, 0, nSampleCount * 2);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec * 2, 2, 16, 0 };
	WAVEHDR waveHdr = { (PSHORT)psSamples, nSampleCount * 2, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);

	/* if it's Bytebeat, then put it to nSampleCount * 2 */
	/* but, if it's using sinf() or using something that will
	keep it running, use nSampleCount. (yes... just nSampleCount, no * 2)*/

	for (INT t = 0; t < nSampleCount * 2; t++)
	{
		BYTE bFreq = (BYTE)((t & ((t >> 18) + ((t >> 11) & t))) * t + (((t >> 8 & t) - (t >> 3 & t >> 8 | t >> 16)) & 128));
		((BYTE*)psSamples)[t] = bFreq;
	}

	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));

	Sleep(nSampleCount * 1000 / nSamplesPerSec);

	while (!(waveHdr.dwFlags & WHDR_DONE))
	{
		Sleep(1);
	}

	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}