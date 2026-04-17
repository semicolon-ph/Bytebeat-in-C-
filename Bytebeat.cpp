#include <Windows.h>
#pragma comment(lib, "winmm.lib")



VOID
WINAPI
AudioSequence1(VOID)
{
	HWAVEOUT hwo = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30];
		for (DWORD t = 0; t < sizeof(buffer); t++)
			buffer[t] = static_cast<char>(t&t>>8);
		WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
		waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
		waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
		waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
		Sleep(-1);
}

INT
WINAPI
WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	INT nShowCmd
)
{
	AudioSequence1();
}