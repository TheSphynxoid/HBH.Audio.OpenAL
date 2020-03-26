#include "pch.h"
#include "Context.h"

HBH::Audio::OpenAL::Context::Context(System::IntPtr ptr) {
	Context_ptr = ptr;
}

HBH::Audio::OpenAL::Context::Context(Device^ dev, array<ContextAttributes>^ attribs, array<int>^ params)
{
	ALCint* attrib = new ALCint[1];
	if (attribs != nullptr) {
		int size = attribs->Length;
		attrib = new ALCint[size * 2]();
		for (int i = 0; i < size * 2; i++)
		{
			if (i % 2 == 0)attrib[i] = (int)attribs[i / 2];
			else attrib[i] = params[(i - 1) / 2];
		}
	}
	else attrib = (int)ContextAttributes::None;
	Context_ptr = (System::IntPtr)alcCreateContext((ALCdevice*)dev->device.ToPointer(), attrib);
	delete[] attrib;
}

HBH::Audio::OpenAL::Context::!Context()
{
	alcDestroyContext((ALCcontext*)Context_ptr.ToPointer());
}

bool HBH::Audio::OpenAL::Context::MakeContextCurrent()
{
	return (bool)alcMakeContextCurrent((ALCcontext*)Context_ptr.ToPointer());
}

void HBH::Audio::OpenAL::Context::ProcessContext()
{
	alcProcessContext((ALCcontext*)Context_ptr.ToPointer());
}

void HBH::Audio::OpenAL::Context::SuspendContext()
{
	alcSuspendContext((ALCcontext*)Context_ptr.ToPointer());
}

HBH::Audio::OpenAL::Device^ HBH::Audio::OpenAL::Context::GetDevice()
{
	return Device::OpenDevice(gcnew System::String(alcGetString(alcGetContextsDevice((ALCcontext*)Context_ptr.ToPointer()), ALC_DEVICE_SPECIFIER)));
}

HBH::Audio::OpenAL::Context^ HBH::Audio::OpenAL::Context::GetCurrentContext()
{
	return gcnew Context((IntPtr)alcGetCurrentContext());
}
