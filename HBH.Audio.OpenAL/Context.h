#pragma once
#include "pch.h"
#include "Device.h"
namespace HBH {
	namespace Audio {
		namespace OpenAL {
			public enum class ContextAttributes
			{
				Frequancy = ALC_FREQUENCY,
				MonoSources = ALC_MONO_SOURCES,
				Refresh = ALC_REFRESH,
				StereoSources = ALC_STEREO_SOURCES,
				Sync = ALC_SYNC,
				None = 0
			};
			//Not Finished
			public ref class Context {
			public:
				System::IntPtr Context_ptr;		
				Context(Device^ dev, array<ContextAttributes>^ attribs, array<int>^ params);
				!Context();
				~Context() { this->!Context(); }
				///<summary>
				///This function makes a specified context the current context.
				///</summary>
				bool MakeContextCurrent();
				///<summary>
				///This function tells a context to begin processing.
				///</summary>
				void ProcessContext();
				///<summary>
				///This function suspends processing on a specified context.
				///</summary>
				void SuspendContext();
				Device^ GetDevice();
				static Context^ GetCurrentContext();
			private:
				Context(System::IntPtr ptr);
			};
		}
	}
}