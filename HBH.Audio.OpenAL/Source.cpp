#include "pch.h"
#include "Source.h"
#include "Buffer.h"
#include "Extension.h"
using namespace System;

void HBH::Audio::OpenAL::Source::SetAuxiliarySend(AuxiliaryEffectSlot^ effect, int SendNumber)
{
	alSource3i(srcname, AL_AUXILIARY_SEND_FILTER, effect->slot, SendNumber, AL_FILTER_NULL);
}

HBH::Audio::OpenAL::Source::Source(unsigned int src)
{
	srcname = src;
}

HBH::Audio::OpenAL::Source::Source()
{
	ALuint a;
	alGenSources(1, &a);
	srcname = a;
	auto ex = Error::GetException(Error::GetError());
	if (ex != nullptr)throw ex;
}

HBH::Audio::OpenAL::Source::!Source()
{
	ALuint ui = srcname;
	alDeleteSources(1, &ui);
	auto ex = Error::GetException(Error::GetError());
	if (ex != nullptr)throw ex;
}

void HBH::Audio::OpenAL::Source::Play()
{
	alSourcePlay(srcname);
	auto ex = Error::GetException(Error::GetError());
	if (ex != nullptr)throw ex;
	ALint state;
	alGetSourcei(srcname, AL_SOURCE_STATE, &state);
	while (state == AL_PLAYING) {
		alGetSourcei(srcname, AL_SOURCE_STATE, &state);
		// check for errors
		auto ex = Error::GetException(Error::GetError());
		if (ex != nullptr)throw ex;
	}
}

void HBH::Audio::OpenAL::Source::PlayAsync()
{
	alSourcePlay(srcname);
	auto ex = Error::GetException(Error::GetError());
	if (ex != nullptr)throw ex;
}

void HBH::Audio::OpenAL::Source::PlayAsync(unsigned int number, array<Source^>^ src)
{
	ALuint* srcs = new ALuint[number];
	for (int i = 0; i < src->Length; i++) {
		srcs[i] = src[i]->srcname;
	}
	alSourcePlayv(number, srcs);
}

void HBH::Audio::OpenAL::Source::Play(unsigned int number, array<Source^>^ src)
{
	ALuint* srcs = new ALuint[number];
	for (int i = 0; i < src->Length; i++) {
		srcs[i] = src[i]->srcname;
	}
	alSourcePlayv(number, srcs);
	ALint state;
	alGetSourcei(srcs[number - 1], AL_SOURCE_STATE, &state);
	while (state == AL_PLAYING) {
		alGetSourcei(srcs[number - 1 ], AL_SOURCE_STATE, &state);
		// check for errors
		auto ex = Error::GetException(Error::GetError());
		if (ex != nullptr)throw ex;
	}
}

void HBH::Audio::OpenAL::Source::Pause()
{
	alSourcePause(srcname);
}

void HBH::Audio::OpenAL::Source::Stop()
{
	alSourceStop(srcname);
}

void HBH::Audio::OpenAL::Source::Rewind()
{
	alSourceRewind(srcname);
}

void HBH::Audio::OpenAL::Source::AttachBuffer(Buffer^ buf)
{
	alSourcei(srcname, AL_BUFFER, buf->Buffername);
	auto ex = Error::GetException(Error::GetError());
	if (ex != nullptr)throw ex;
}

void HBH::Audio::OpenAL::Source::QueueBuffers(unsigned int number, array<Buffer^>^ buf)
{
	ALuint* bufs = new ALuint[number];
	for (int i = 0; i < buf->Length; i++) {
		bufs[i] = buf[i]->Buffername;
	}
	alSourceQueueBuffers(srcname, number, bufs);
	auto ex = Error::GetException(Error::GetError());
	if (ex != nullptr)throw ex;
}

void HBH::Audio::OpenAL::Source::QueueBuffer(Buffer^ buf)
{
	ALuint ui = buf->Buffername;
	alSourceQueueBuffers(srcname, 1, &ui);
	auto ex = Error::GetException(Error::GetError());
	if (ex != nullptr)throw ex;
}

void HBH::Audio::OpenAL::Source::UnQueueBuffers(unsigned int number, array<Buffer^>^ buf)
{
	throw gcnew System::NotImplementedException();
}

void HBH::Audio::OpenAL::Source::GenerateSources(ALuint number, array<Source^>^% src)
{
	if (number != 0) {
		src = gcnew array<Source^>(number);
		ALuint* s = new ALuint[number];
		alGenSources(number, s);
		for (unsigned int i = 0; i < number; i++) {
			src[i] = gcnew Source(s[i]);
		}
		auto ex = Error::GetException((Error::GetError()));
		if (ex != nullptr) {
			if (ex->GetType()->Name == "OutOfMemoryException") {
				ex = gcnew OutOfMemoryException("There is not enough memory available to generate all the Sources requested.");
				throw ex;
			}
			else { throw ex; }
		}
		delete[] s;
	}
}

void HBH::Audio::OpenAL::Source::DeleteSources(unsigned int number, array<Source^>^ src)
{
	ALuint* srcs = new ALuint[number];
	for (int i = 0; i < src->Length; i++) {
		srcs[i] = src[i]->srcname;
	}
	alDeleteBuffers(number, srcs);
}

bool HBH::Audio::OpenAL::Source::IsSource(Source^ src)
{
	return alIsSource(src->srcname) == AL_TRUE ? true : false;
}

bool HBH::Audio::OpenAL::Source::IsSource(unsigned int srcname)
{
	return alIsSource(srcname) == AL_TRUE ? true : false;
}
