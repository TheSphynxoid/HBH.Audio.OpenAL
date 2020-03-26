#include "pch.h"
#include "Device.h"
#include <string.h>

#define MARSHAL System::Runtime::InteropServices::Marshal

using namespace HBH::Audio::OpenAL;


HBH::Audio::OpenAL::Device^ HBH::Audio::OpenAL::Device::OpenDevice(System::String^ name)
{
	Device^ device = gcnew Device();
	if (name == name->Empty)device->device = (IntPtr)alcOpenDevice(nullptr);
	else {
		device->device = (IntPtr)alcOpenDevice((const ALCchar*)MARSHAL::StringToHGlobalAnsi(name).ToPointer());
	}
	auto ex = Error::GetContextError(device);
	if (ex != ContextErrorCode::No_Error) {
		throw Error::GetException(ex);
	}
	device->IsCaptureDevice = false;
	return device;
}

HBH::Audio::OpenAL::Device^ HBH::Audio::OpenAL::Device::OpenCaptureDevice(System::String^ devicename, unsigned int frequancy, BufferFormats format, int buffersize)
{
	Device^ device = gcnew Device();
	if (devicename == devicename->Empty) {
		auto cdn = alcGetString(nullptr, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER);
		device->device = (IntPtr)alcCaptureOpenDevice(cdn, frequancy, (ALCenum)format, buffersize);
	}
	else {
		device->device = (IntPtr)alcCaptureOpenDevice((const ALCchar*)MARSHAL::StringToHGlobalAnsi(devicename).ToPointer()
			, frequancy, (ALCenum)format, buffersize);
	}
	auto ex = Error::GetContextError(device);
	if (ex != ContextErrorCode::No_Error) {
		throw Error::GetException(ex);
	}
	device->IsCaptureDevice = true;
	device->cbf = format;
	device->capbufsize = buffersize;
	return device;
}

HBH::Audio::OpenAL::Device::!Device()
{
	if (IsCaptureDevice) {
		alcCaptureCloseDevice((ALCdevice*)device.ToPointer());
	}
	else {
		alcCloseDevice((ALCdevice*)device.ToPointer());
	}
}

void HBH::Audio::OpenAL::Device::CaptureStart()
{
	alcCaptureStart((ALCdevice*)device.ToPointer());
	auto ex = Error::GetContextError(this);
	if (ex != ContextErrorCode::No_Error) {
		throw Error::GetException(ex);
	}
}

void HBH::Audio::OpenAL::Device::CaptureStop()
{
	alcCaptureStop((ALCdevice*)device.ToPointer());
	auto ex = Error::GetContextError(this);
	if (ex != ContextErrorCode::No_Error) {
		throw Error::GetException(ex);
	}
}

void HBH::Audio::OpenAL::Device::CaptureSamples(IntPtr% buffer, int samples)
{
	char* buf = new char();
	if (cbf == BufferFormats::Mono16 ||cbf == BufferFormats::Stereo16) {
		buf = new char[samples * 2];
	}
	if (cbf == BufferFormats::Mono8 || cbf == BufferFormats::Stereo8) {
		buf = new char[samples];
	}
	alcCaptureSamples((ALCdevice*)device.ToPointer(), buf, samples);
	auto ex = Error::GetContextError(this);
	if (ex != ContextErrorCode::No_Error) {
		throw Error::GetException(ex);
	}
	else {
		buffer = IntPtr(buf);
	}
}

bool HBH::Audio::OpenAL::Device::IsCaptureAvailable()
{
	auto c = alcGetCurrentContext();
	auto d = alcGetContextsDevice(c);
	return alcIsExtensionPresent(d, "ALC_EXT_CAPTURE") == ALC_TRUE ? true : false;
}

int HBH::Audio::OpenAL::Device::GetAvailableSamples()
{
	ALCint i = 0;
	alcGetIntegerv((ALCdevice*)device.ToPointer(), ALC_CAPTURE_SAMPLES, 1, &i);
	return i;
}

System::String^ HBH::Audio::OpenAL::Device::GetName()
{
	const char* n = alcGetString((ALCdevice*)device.ToPointer(), ALC_DEVICE_SPECIFIER);
	return gcnew System::String(n);
}

array<String^>^ HBH::Audio::OpenAL::Device::GetAllDevicesNames()
{
	System::Collections::Generic::List<String^>^ l= gcnew System::Collections::Generic::List<String^>();
	if (alcIsExtensionPresent(nullptr, "ALC_ENUMERATE_ALL_EXT") == AL_TRUE) {
		const ALCchar* devices;
		devices = alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER);
		char* ds;
		char* c;
		ds = strtok_s((char*)devices, "\n", &c);
		l->Add(gcnew String(ds));
		while (ds != 0) {
			ds = strtok_s(nullptr, "\n",&c);
		}
	}
	return l->ToArray();
}

array<String^>^ HBH::Audio::OpenAL::Device::GetAllCaputureDeviceNames()
{
	System::Collections::Generic::List<String^>^ l = gcnew System::Collections::Generic::List<String^>();
	if (alcIsExtensionPresent(nullptr, "ALC_ENUMERATE_ALL_EXT") == AL_TRUE) {
		const ALCchar* devices;
		devices = alcGetString(nullptr, ALC_CAPTURE_DEVICE_SPECIFIER);
		char* ds;
		char* c = "";
		ds = strtok_s((char*)devices, "\n", &c);
		l->Add(gcnew String(ds));
		while (ds != 0) {
			ds = strtok_s(nullptr, "\n", &c);
		}
		delete c;
	}
	return l->ToArray();
}
