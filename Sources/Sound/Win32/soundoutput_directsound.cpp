/*
**  ClanLib SDK
**  Copyright (c) 1997-2011 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
*/

#include "Sound/precomp.h"
#include "soundoutput_directsound.h"
#include "API/Core/System/exception.h"
#include "API/Core/Text/logger.h"
#include "Core/System/Win32/init_win32.h"
#include <mmreg.h>

// KSDATAFORMAT_SUBTYPE_IEEE_FLOAT is not available on some old headers
#ifndef KSDATAFORMAT_SUBTYPE_IEEE_FLOAT
struct __declspec(uuid("00000003-0000-0010-8000-00aa00389b71")) KSDATAFORMAT_SUBTYPE_IEEE_FLOAT_STRUCT;
#define KSDATAFORMAT_SUBTYPE_IEEE_FLOAT __uuidof(KSDATAFORMAT_SUBTYPE_IEEE_FLOAT_STRUCT)
#endif

/////////////////////////////////////////////////////////////////////////////
// CL_SoundOutput_DirectSound construction:

CL_SoundOutput_DirectSound::CL_SoundOutput_DirectSound(int mixing_frequency, int mixing_latency)
: CL_SoundOutput_Impl(mixing_frequency, mixing_latency), directsound(0), soundbuffer(0),
  frag_size(0), sleep_event(0), hwnd(0), notify(0), has_sound(true), last_write_pos(-1)
{
	try
	{
		create_directsound_object();
		set_cooperative_level();
		set_fragment_size();
		create_sound_buffer();
		verify_sound_buffer_capabilities();
		clear_sound_buffer();
		create_notify_event();
		retrieve_notify_interface();
		set_notify_positions();
		play_sound_buffer();
	}
	catch (CL_Exception &e)
	{
		release_resources();
		cl_log_event("mixer", e.message);
		frag_size = mixing_frequency/2;
		has_sound = false;
	}
}

CL_SoundOutput_DirectSound::~CL_SoundOutput_DirectSound()
{
	stop_mixer_thread();
	if (soundbuffer)
		soundbuffer->Stop();
	release_resources();
}

/////////////////////////////////////////////////////////////////////////////
// CL_SoundOutput_DirectSound attributes:


/////////////////////////////////////////////////////////////////////////////
// CL_SoundOutput_DirectSound operations:

void CL_SoundOutput_DirectSound::silence()
{
}

int CL_SoundOutput_DirectSound::get_fragment_size()
{
	return frag_size;
}

void CL_SoundOutput_DirectSound::write_fragment(float *data)
{
	if (has_sound)
	{
		int write_pos = find_fragment_write_position();
		write_to_sound_buffer(write_pos, data, frag_size);
	}
}

void CL_SoundOutput_DirectSound::wait()
{
	if (has_sound)
	{
		WaitForSingleObject(sleep_event, INFINITE);
		ResetEvent(sleep_event);
	}
	else
	{
		CL_System::sleep(100);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CL_SoundOutput_DirectSound implementation:

int CL_SoundOutput_DirectSound::find_fragment_write_position()
{
	DWORD play = 0, write = 0;
	HRESULT err = soundbuffer->GetCurrentPosition(&play, &write);
	if (FAILED(err))
		throw CL_Exception("IDirectSoundBuffer8::GetCurrentPosition failed");

	int fragment_index = ((play/get_bytes_per_sample() + frag_size + frag_size/2) / frag_size) % get_fragment_count();
	return fragment_index * frag_size;
}

void CL_SoundOutput_DirectSound::write_to_sound_buffer(int write_pos, const float *data, int size)
{
	DWORD size1 = 0, size2 = 0;
	void *ptr1 = 0, *ptr2 = 0;
	HRESULT err = soundbuffer->Lock(write_pos*get_bytes_per_sample(), size*get_bytes_per_sample(), (void **) &ptr1, &size1, (void **) &ptr2, &size2, 0);
	if (FAILED(err))
		throw CL_Exception("IDirectSoundBuffer8::Lock failed");

	char *_data = (char *) data;
	if (ptr1)
		memcpy(ptr1, _data, size1);
	if (ptr2)
		memcpy(ptr2, _data+size1, size2);

	err = soundbuffer->Unlock(ptr1, size1, ptr2, size2);
	if (FAILED(err))
		throw CL_Exception("IDirectSoundBuffer8::Unlock failed");
}

void CL_SoundOutput_DirectSound::release_resources()
{
	if (notify)
		notify->Release();
	if (soundbuffer)
		soundbuffer->Release();
	if (directsound)
		directsound->Release();
	if (sleep_event)
		CloseHandle(sleep_event);
	if (hwnd)
		DestroyWindow(hwnd);
}

void CL_SoundOutput_DirectSound::create_directsound_object()
{
	HRESULT err = DirectSoundCreate(0, &directsound, 0);
	if (FAILED(err))
		throw CL_Exception("DirectSoundCreate failed");
}

void CL_SoundOutput_DirectSound::set_cooperative_level()
{
	// We need a hwnd for our directsound interface:
	WNDCLASS wndclass;
	wndclass.style = 0;
	wndclass.lpfnWndProc = DefWindowProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = GetModuleHandle(0);
	wndclass.hIcon = NULL;
	wndclass.hCursor = LoadCursor (NULL,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wndclass.lpszMenuName = TEXT("ClanSound");
	wndclass.lpszClassName = TEXT("ClanSound");
	RegisterClass(&wndclass);

	hwnd = CreateWindow(
		TEXT("ClanSound"),
		TEXT("ClanSound"),
		0, // WS_POPUP,
		0,
		0,
		1,
		1,
		NULL,
		NULL,
		GetModuleHandle(0),
		NULL);
	if (hwnd == 0)
		throw CL_Exception("CreateWindow failed for DirectSound object");

	HRESULT err = directsound->SetCooperativeLevel(hwnd, DSSCL_NORMAL);
	if (FAILED(err))
		throw CL_Exception("IDirectSound8::SetCooperativeLevel failed");
}

void CL_SoundOutput_DirectSound::set_fragment_size()
{
	frag_size = mixing_frequency * mixing_latency / 1000;
	frag_size = (frag_size + 3) & ~3;	// Force to be a multiple of 4
}

int CL_SoundOutput_DirectSound::get_fragment_count() const
{
	return 2;
}

int CL_SoundOutput_DirectSound::get_bytes_per_sample() const
{
	return 2 * sizeof(float);
}

int CL_SoundOutput_DirectSound::get_buffer_size() const
{
	return frag_size * get_bytes_per_sample() * get_fragment_count();
}

void CL_SoundOutput_DirectSound::create_sound_buffer()
{
	WAVEFORMATEXTENSIBLE wave_format;
	wave_format.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
	wave_format.Format.nChannels = 2;
	wave_format.Format.nSamplesPerSec = mixing_frequency;
	wave_format.Format.nBlockAlign = get_bytes_per_sample();
	wave_format.Format.nAvgBytesPerSec = wave_format.Format.nSamplesPerSec * wave_format.Format.nBlockAlign;
	wave_format.Format.wBitsPerSample = sizeof(float)*8;
	wave_format.Format.cbSize = 22;
	wave_format.Samples.wValidBitsPerSample = wave_format.Format.wBitsPerSample;
	wave_format.dwChannelMask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT;
	wave_format.SubFormat = KSDATAFORMAT_SUBTYPE_IEEE_FLOAT;

	DSBUFFERDESC desc;
	desc.dwSize = sizeof(DSBUFFERDESC); 
	desc.dwFlags = DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GLOBALFOCUS | DSBCAPS_GETCURRENTPOSITION2;
	desc.dwBufferBytes = get_buffer_size();
	desc.dwReserved = 0;
	desc.lpwfxFormat = &wave_format.Format; 
	desc.guid3DAlgorithm = GUID_NULL;

	HRESULT err = directsound->CreateSoundBuffer(&desc, &soundbuffer, NULL);
	if (FAILED(err))
		throw CL_Exception("IDirectSound8::CreateSoundBuffer failed");
}

void CL_SoundOutput_DirectSound::verify_sound_buffer_capabilities()
{
	DSBCAPS caps;
	memset(&caps, 0, sizeof(DSBCAPS));
	caps.dwSize = sizeof(DSBCAPS);
	
	HRESULT err = soundbuffer->GetCaps(&caps);
	if (FAILED(err))
		throw CL_Exception("Could not retrieve direct sound buffer capabilities.");

	if (caps.dwBufferBytes != get_buffer_size())
		throw CL_Exception("Direct sound buffer size does not match our request.");
}

void CL_SoundOutput_DirectSound::clear_sound_buffer()
{
	DWORD size1 = 0, size2 = 0;
	void *ptr1 = 0;
	void *ptr2 = 0;
	HRESULT err = soundbuffer->Lock(0, get_buffer_size(), &ptr1, &size1, &ptr2, &size2, 0);
	if (FAILED(err))
		throw CL_Exception("Unable to lock DirectSound buffer.");

	memset(ptr1, 0, size1);
	if (ptr2)
		memset(ptr2, 0, size2);

	err = soundbuffer->Unlock(ptr1, size1, ptr2, size2);
	if (FAILED(err))
		throw CL_Exception("Could not unlock DirectSound buffer.");
}

void CL_SoundOutput_DirectSound::create_notify_event()
{
	// Setup some sleeping :)
	sleep_event = CreateEvent(0, TRUE, FALSE, 0);
	if (sleep_event == 0)
		throw CL_Exception("CreateEvent failed");
}

void CL_SoundOutput_DirectSound::retrieve_notify_interface()
{
	HRESULT err = soundbuffer->QueryInterface(IID_IDirectSoundNotify, (void **) &notify);
	if (FAILED(err))
		throw CL_Exception("Direct sound buffer does not support needed IDirectSoundNotify interface.");
}

void CL_SoundOutput_DirectSound::set_notify_positions()
{
	int num_fragments = get_fragment_count();
	if (num_fragments > 0)
	{
		std::vector<DSBPOSITIONNOTIFY> notify_positions;
		for (int i=0; i<num_fragments; i++)
		{
			DSBPOSITIONNOTIFY notify;
			notify.dwOffset = i*frag_size*get_bytes_per_sample();
			notify.hEventNotify = sleep_event;
			notify_positions.push_back(notify);
		}
		HRESULT result = notify->SetNotificationPositions(num_fragments, &notify_positions[0]);
		if (FAILED(result))
			throw CL_Exception("IDirecTsoundNotify::SetNotificationPositions failed");
	}
}

void CL_SoundOutput_DirectSound::play_sound_buffer()
{
	start_mixer_thread();
	HRESULT err = soundbuffer->Play(0, 0, DSBPLAY_LOOPING);
	if (FAILED(err))
	{
		stop_mixer_thread();
		throw CL_Exception("Could not start sound buffer playback");
	}
}
