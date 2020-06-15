#pragma once

using namespace System;

namespace HBH {
	namespace Audio {
		namespace OpenAL {
			public enum class BufferFormats
			{
				Mono8 = AL_FORMAT_MONO8,
				Mono16 = AL_FORMAT_MONO16,
				Stereo8 = AL_FORMAT_STEREO8,
				Stereo16 = AL_FORMAT_STEREO16,
			};
			/// <summary>
			///Buffers attached cannot be disposed, attempting to do so will throw an exception.
			/// </summary>
			public ref class Buffer {
			internal:
				Buffer(unsigned int buf);
			public:
				property int Frequancy {
					int get() {
						ALint i = 0;
						alBufferi(Buffername, AL_FREQUENCY, i);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return i;
					}
				};
				property int Bits {
					int get() {
						ALint i = 0;
						alBufferi(Buffername, AL_BITS, i);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return i;
					}
				};
				property int Channels {
					int get() {
						ALint i = 0;
						alBufferi(Buffername, AL_CHANNELS, i);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return i;
					}
				};
				property int Size {
					int get() {
						ALint i = 0;
						alBufferi(Buffername, AL_SIZE, i);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return i;
					}
				};
				Buffer();
				/// <summary>
				///Buffers attached cannot be disposed, attempting to do so will throw an exception.
				/// </summary>
				!Buffer();
				/// <summary>
				///Buffers attached cannot be disposed, attempting to do so will throw an exception.
				/// </summary>
				~Buffer() { this->!Buffer(); }
				/// <summary> 
				///Fills the buffer with PCM data.
				/// </summary>
				void FillData(BufferFormats format, IntPtr data, int size, int frequency);
				///<summary> 
				///This function generates one or more buffers, which contain audio data.
				///</summary>
				static void GenerateBuffers(unsigned int number, array<Buffer^>^% buffs);
				///<summary>
				///This function deletes one or more buffers, freeing the resources used by the buffer.
				/// Buffers which are attached to a source can not be deleted.
				///</summary>
				static void DeleteBuffers(unsigned int number, array<Buffer^>^ buffs);

				static BufferFormats GetBufferFormat(unsigned int numchannels);
			internal:
				unsigned int Buffername;
			};
		}
	}
}

