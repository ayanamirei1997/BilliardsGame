#pragma once
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <string>
#pragma comment(lib, "winmm.lib")

// ≈ˆ◊≤“Ù–ß
void shootsound() {
	PlaySound(TEXT("shoot.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

// ±≥æ∞“Ù¿÷
void playbgm()
{

	//mciSendCommand(m_nDeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)&mciPlay);
	// º”‘ÿ±≥æ∞“Ù¿÷
	mciSendString(TEXT("open .\\bgm.wav alias song"), NULL, 0, NULL);
	// ≤•∑≈“Ù¿÷
	//mciSendString(TEXT("play MySong"), NULL, 0, NULL);
	mciSendString("play Song", NULL, 0, NULL);

	return;
}
