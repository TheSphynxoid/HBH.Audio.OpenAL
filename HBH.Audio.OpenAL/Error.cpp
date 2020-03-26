#include "pch.h"
#include "Error.h"
#include "Device.h"

HBH::Audio::OpenAL::ErrorCode HBH::Audio::OpenAL::Error::GetError()
{
	ErrorCode code = (ErrorCode)((int)alGetError());
	return code;
}

System::Exception^ HBH::Audio::OpenAL::Error::GetException(ErrorCode code)
{
	switch (code)
	{
    case HBH::Audio::OpenAL::ErrorCode::No_Error:
        return nullptr;
    case HBH::Audio::OpenAL::ErrorCode::Invalid_Name:
        return gcnew System::Exception("Invalid Name.");
    case HBH::Audio::OpenAL::ErrorCode::Invalid_Enum:
        return gcnew System::Exception("Invalid Enum.");
    case HBH::Audio::OpenAL::ErrorCode::Invalid_Value:
        return gcnew System::Exception("Invalid Value.");
    case HBH::Audio::OpenAL::ErrorCode::Invalid_Operation:
        return gcnew System::InvalidOperationException("Invalid Operation.");
    case HBH::Audio::OpenAL::ErrorCode::Out_Of_Memory:
        return gcnew System::OutOfMemoryException("Out of Memory.");
    default:
        return nullptr;
	}
}

HBH::Audio::OpenAL::ContextErrorCode HBH::Audio::OpenAL::Error::GetContextError(Device^ dev)
{
	auto d = (ALCdevice*)dev->device.ToPointer();
	return (ContextErrorCode)alcGetError(d);
}

System::Exception^ HBH::Audio::OpenAL::Error::GetException(ContextErrorCode code)
{
	switch (code)
	{
	case HBH::Audio::OpenAL::ContextErrorCode::No_Error:
		return nullptr;
	case HBH::Audio::OpenAL::ContextErrorCode::Invalid_Device:
		return gcnew System::Exception("Invalid Device.");
	case HBH::Audio::OpenAL::ContextErrorCode::Invalid_Context:
		return gcnew System::Exception("Invalid Context.");
	case HBH::Audio::OpenAL::ContextErrorCode::Invalid_Enum:
		return gcnew System::Exception("Invalid Enum.");
	case HBH::Audio::OpenAL::ContextErrorCode::Invalid_Value:
		return gcnew System::Exception("Invalid Value.");
	case HBH::Audio::OpenAL::ContextErrorCode::Out_Of_Memory:
		return gcnew System::OutOfMemoryException("Out of Memory.");
	default:
		return nullptr;
	}
}
