#pragma once
#include "Buffer.h"

using namespace System;

namespace HBH {
	namespace Audio {
		namespace OpenAL {
			public ref class Device {
			public:
				IntPtr device;
				bool IsCaptureDevice = false;
				///<summary>
				///Gets The Device by it's name , empty for default.
				///</summary>
				static Device^ OpenDevice(System::String^ name);
				static Device^ OpenCaptureDevice(System::String^ devicename, unsigned int Frequancy, HBH::Audio::OpenAL::BufferFormats format, int buffersize);
				!Device();
				~Device() { this->!Device(); };
				void CaptureStart();
				void CaptureStop();
				void CaptureSamples(IntPtr% buffer,int samples);
				/// <summary>
				///Is Capture Available.
				/// </summary>
				bool IsCaptureAvailable();
				/// <summary>
				///Returns the number Available Capture Samples
				/// </summary>
				int GetAvailableSamples();
				System::String^ GetName();
				static array<String^>^ GetAllDevicesNames();
				static array<String^>^ GetAllCaputureDeviceNames();
			private:
				Device() {};
				//Capture Buffer Size.
				int capbufsize;
				BufferFormats cbf;
			};
		}
	}
}

