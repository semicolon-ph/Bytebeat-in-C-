#include <Windows.h>
#pragma comment(lib, "winmm.lib")

VOID
WINAPI
AudioSequence1()
{
    HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };

    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

    unsigned char buffer[8000 * 31];

    for (DWORD t = 0; t < sizeof(buffer); t++)
        buffer[t] = (char)(t&t>>8);

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };

    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));

    Sleep(31000);
}

int main()
{
  AudioSequence1();
}
