// StartupVolumeReset.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <Audioclient.h>
#include <audiopolicy.h>

int _tmain()
{
	double intendedVolume = 0.0;
	CoInitialize(NULL);
	IMMDeviceEnumerator *devicesEnum = NULL;
	HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, _uuidof(IMMDeviceEnumerator), (LPVOID *)&devicesEnum);
	IMMDevice *defaultDevice = NULL;
	hr = devicesEnum->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	IAudioEndpointVolume *endpointVolume = NULL;
	devicesEnum->Release();
	devicesEnum = NULL;
	hr = defaultDevice->Activate(_uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
	defaultDevice->Release();
	defaultDevice = NULL;

	endpointVolume->SetMasterVolumeLevelScalar(0, NULL);
	endpointVolume->Release();
	endpointVolume = NULL;
	CoUninitialize();
	return 0;
}
