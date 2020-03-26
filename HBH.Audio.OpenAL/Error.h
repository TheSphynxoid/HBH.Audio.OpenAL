#pragma once


namespace HBH {
	namespace Audio {
		namespace OpenAL {
			ref class Device;
			public enum class ErrorCode
			{
				No_Error = AL_NO_ERROR,
				Invalid_Name = AL_INVALID_NAME,
				Invalid_Enum = AL_INVALID_ENUM,
				Invalid_Value = AL_INVALID_VALUE,
				Invalid_Operation = AL_INVALID_OPERATION,
				Out_Of_Memory = AL_OUT_OF_MEMORY
			};
			public enum class ContextErrorCode : int
			{
				No_Error = ALC_NO_ERROR,
				Invalid_Device = ALC_INVALID_DEVICE,
				Invalid_Context = ALC_INVALID_CONTEXT,
				Invalid_Enum = ALC_INVALID_ENUM,
				Invalid_Value = ALC_INVALID_VALUE,
				Out_Of_Memory = ALC_OUT_OF_MEMORY
			};
			public ref class Error {
			public:
				static ErrorCode GetError();
				static System::Exception^ GetException(ErrorCode code);
				static ContextErrorCode GetContextError(HBH::Audio::OpenAL::Device^ dev);
				static System::Exception^ GetException(ContextErrorCode code);
			};
		}
	}
}

