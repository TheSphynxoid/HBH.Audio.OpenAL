#include "pch.h"
#include "Buffer.h"

HBH::Audio::OpenAL::Buffer::Buffer(unsigned int buf)
{
	Buffername = buf;
}

HBH::Audio::OpenAL::Buffer::Buffer()
{
	ALuint buf;
	alGenBuffers(1, &buf);
	Buffername = buf;
	auto ex = Error::GetException(Error::GetError());
	if (ex != nullptr)throw ex;
}

HBH::Audio::OpenAL::Buffer::!Buffer()
{
	ALuint ui = (ALuint)Buffername;
	alDeleteBuffers(1, &ui);
	auto ex = Error::GetException(Error::GetError());
	if (ex != nullptr)throw ex;
}

void HBH::Audio::OpenAL::Buffer::FillData(BufferFormats format, IntPtr data, int size, int frequency)
{
	ALuint b = Buffername;
	alBufferData(b, (int)format, data.ToPointer(), size, frequency);
	auto ex = Error::GetException(Error::GetError());
	if (ex != nullptr)throw ex;
}

void HBH::Audio::OpenAL::Buffer::GenerateBuffers(unsigned int number, array<Buffer^>^% buffs)
{
	if (number != 0) {
		buffs = gcnew array<Buffer^>(number);
		ALuint* buf = new ALuint[number];
		alGenBuffers(number, buf);
		for (unsigned int i = 0; i < number; i++) {
			buffs[i] = gcnew Buffer(buf[i]);
		}
		auto ex = Error::GetException((Error::GetError()));
		if (ex != nullptr) {
			if (ex->GetType()->Name == "OutOfMemoryException") {
				ex = gcnew OutOfMemoryException("There is not enough memory available to generate all the buffers requested.");
				throw ex;
			}
			else { throw ex; }
		}
		delete[] buf;
	}
}

void HBH::Audio::OpenAL::Buffer::DeleteBuffers(unsigned int number, array<Buffer^>^ buffs)
{
	ALuint* buffers = new ALuint[number];
	for (int i = 0; i < buffs->Length; i++) {
		buffers[i] = buffs[i]->Buffername;
	}
	alDeleteBuffers(number, buffers);
	auto ex = Error::GetException(Error::GetError());
	if (ex != nullptr)throw ex;
}
