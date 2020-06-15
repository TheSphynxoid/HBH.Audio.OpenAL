#pragma once
#include "Buffer.h"

namespace HBH {
	namespace Audio {
		namespace OpenAL {

			ref class AuxiliaryEffectSlot;

			public enum class SourceType : int
			{
				Undetermined = AL_UNDETERMINED,
				Static = AL_STATIC,
				Streaming = AL_STREAMING
			};
			/// <summary>
			/// An Enum depicting the State of a source.
			/// </summary>
			public enum class SourceState : int
			{
				Playing = AL_PLAYING,
				Paused = AL_PAUSED,
				Stopped = AL_STOPPED,
				Initial = AL_INITIAL
			};
			/// <summary>
			/// A Class That defines Function do manipulate sources.
			/// </summary>
			public ref class Source sealed
			{
			public:
				//Floats
				property float Pitch {
					float get() {
						ALfloat f;
						alGetSourcef(srcname, AL_PITCH, &f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return f;
					}
					void set(float value) {
						alSourcef(srcname, AL_PITCH, value);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				property float Gain {
					float get() {
						ALfloat f;
						alGetSourcef(srcname, AL_GAIN, &f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return f;
					}
					void set(float value) {
						alSourcef(srcname, AL_GAIN, value);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				property float MaxDistance {
					float get() {
						ALfloat f;
						alGetSourcef(srcname, AL_MAX_DISTANCE, &f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return f;
					}
					void set(float value) {
						alSourcef(srcname, AL_MAX_DISTANCE, value);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				property float RolloffFactor {
					float get() {
						ALfloat f;
						alGetSourcef(srcname, AL_ROLLOFF_FACTOR, &f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return f;
					}
					void set(float value) {
						alSourcef(srcname, AL_ROLLOFF_FACTOR, value);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				property float ReferenceDistance {
					float get() {
						ALfloat f;
						alGetSourcef(srcname, AL_REFERENCE_DISTANCE, &f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return f;
					}
					void set(float value) {
						alSourcef(srcname, AL_REFERENCE_DISTANCE, value);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				property float MinGain {
					float get() {
						ALfloat f;
						alGetSourcef(srcname, AL_MIN_GAIN, &f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return f;
					}
					void set(float value) {
						alSourcef(srcname, AL_MIN_GAIN, value);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				property float MaxGain {
					float get() {
						ALfloat f;
						alGetSourcef(srcname, AL_MAX_GAIN, &f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return f;
					}
					void set(float value) {
						alSourcef(srcname, AL_MAX_GAIN, value);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				property float ConeOuterGain {
					float get() {
						ALfloat f;
						alGetSourcef(srcname, AL_CONE_OUTER_GAIN, &f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return f;
					}
					void set(float value) {
						alSourcef(srcname, AL_CONE_OUTER_GAIN, value);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				property float ConeInnerAngle {
					float get() {
						ALfloat f;
						alGetSourcef(srcname, AL_CONE_INNER_ANGLE, &f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return f;
					}
					void set(float value) {
						alSourcef(srcname, AL_CONE_INNER_ANGLE, value);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				property float ConeOuterAngle {
					float get() {
						ALfloat f;
						alGetSourcef(srcname, AL_CONE_OUTER_ANGLE, &f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return f;
					}
					void set(float value) {
						alSourcef(srcname, AL_CONE_OUTER_ANGLE, value);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				//Vectors
				property Vector Position {
					Vector get() {
						ALfloat fs[3];
						alGetSourcefv(srcname, AL_POSITION, fs);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return Vector(fs[0], fs[1], fs[2]);
					}
					void set(Vector value) {
						float f[3];
						memcpy_s(f, sizeof(float) * 3, value.ToALfloatPtr(), sizeof(float) * 3);
						alSourcefv(srcname, AL_POSITION, f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				property Vector Velocity {
					Vector get(){
						ALfloat fs[3];
						alGetSourcefv(srcname, AL_VELOCITY, fs);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return Vector(fs[0], fs[1], fs[2]);
					}
					void set(Vector value) {
						float f[3];
						memcpy_s(f, sizeof(float) * 3, value.ToALfloatPtr(), sizeof(float) * 3);
						alSourcefv(srcname, AL_VELOCITY, f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				property Vector Direction {
					Vector get() {
						ALfloat fs[3];
						alGetSourcefv(srcname, AL_DIRECTION, fs);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return Vector(fs[0], fs[1], fs[2]);
					}
					void set(Vector value) {
						float f[3];
						memcpy_s(f, sizeof(float) * 3, value.ToALfloatPtr(), sizeof(float) * 3);
						alSourcefv(srcname, AL_DIRECTION, f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				//Source State Information
				property bool SourceRelative {
					bool get() {
						ALint i;
						alGetSourcei(srcname, AL_SOURCE_RELATIVE, &i);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						bool b = i == AL_TRUE ? true : false;
						return b;
					}
					void set(bool value) {
						int b = value ? AL_TRUE : AL_FALSE;
						alSourcei(srcname, AL_SOURCE_RELATIVE, b);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				property SourceType SourceType {
					HBH::Audio::OpenAL::SourceType get() {
						ALint i;
						alGetSourcei(srcname, AL_SOURCE_TYPE, &i);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return (HBH::Audio::OpenAL::SourceType)i;
					}
				}
				property bool Looping {
					bool get() {
						return m_looping;
					}
					void set(bool value) {
						m_looping = value;
						int b = value ? AL_TRUE : AL_FALSE;
						alSourcei(srcname, AL_LOOPING, b);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				property Buffer^ AttachedBuffer {
					HBH::Audio::OpenAL::Buffer^ get() {
						ALint i;
						alGetSourcei(srcname, AL_BUFFER, &i);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return gcnew HBH::Audio::OpenAL::Buffer((unsigned int)i);
					}
					void set(HBH::Audio::OpenAL::Buffer^ value) {
						ALint i = (int)value->Buffername;
						alSourcei(srcname, AL_BUFFER, i);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				property SourceState SourceState {
					HBH::Audio::OpenAL::SourceState get() {
						ALint i;
						alGetSourcei(srcname, AL_SOURCE_STATE, &i);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return (HBH::Audio::OpenAL::SourceState)i;
					}
					void set(HBH::Audio::OpenAL::SourceState value) {
						alSourcei(srcname, AL_SOURCE_STATE, (int)value);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				property int BuffersQueued {
					int get() {
						ALint i;
						alGetSourcei(srcname, AL_BUFFERS_QUEUED, &i);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return i;
					}
				}
				/// <summary>
				///Is Also the maximum number of buffers that can be unqueued.
				/// </summary>
				property int BuffersProcessed {
					int get() {
						ALint i;
						alGetSourcei(srcname, AL_BUFFERS_PROCESSED, &i);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return i;
					}
				}
				property float SecondsOffset {
					float get() {
						ALfloat f;
						alGetSourcef(srcname, AL_SEC_OFFSET, &f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return f;
					}
				}
				property float SampleOffset {
					float get() {
						ALfloat f;
						alGetSourcef(srcname, AL_SAMPLE_OFFSET, &f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return f;
					}
				}
				property float ByteOffset {
					float get() {
						ALfloat f;
						alGetSourcef(srcname, AL_BYTE_OFFSET, &f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return f;
					}
				}
				Source();
				!Source();
				~Source() { this->!Source(); };
				/// <summary>
				///Starts playing the attached buffer on the current sources and
				/// Sets its state to <see cref="HBH::Audio::OpenAL::SourceState::Playing"/>.
				/// </summary>
				void Play();
				///<summary>
				///Starts playing the attached buffer on the current sources asynchronously.
				/// Sets its state to <see cref="HBH::Audio::OpenAL::SourceState::Playing"/>.
				/// </summary>
				void PlayAsync();
				/// <summary>
				///Starts playing Sources. When called on a source which is already playing, the source will restart at the beginning
				/// </summary>
				/// <param name="number">The Number of sources to be played. if "number" is 0 nothing happens.</param>
				static void PlayAsync(unsigned int number,array<Source^>^ src);
				/// <summary>
				///Starts playing Sources. When called on a source which is already playing, the source will restart at the beginning
				/// </summary>
				/// <param name="number">The Number of sources to be played. if "number" is 0 nothing happens.</param>
				static void Play(unsigned int number, array<Source^>^ src);
				/// <summary>
				///Pauses The Current Source and Sets its state to <see cref="HBH::Audio::OpenAL::SourceState::Paused"/>.
				/// </summary>
				void Pause();
				/// <summary>
				///Stops The Current Source and Sets its state to <see cref="HBH::Audio::OpenAL::SourceState::Stopped"/>.
				/// </summary>
				void Stop();
				/// <summary>
				///Rewinds The Current Source and Sets its state to <see cref="HBH::Audio::OpenAL::SourceState::Initial"/>.
				/// </summary>
				void Rewind();
				/// <summary>
				///Attachs a buffer to the current source. An attatched buffer cannot be Disposed of until unqueued or detattached (using the AttachedBuffer Property).
				/// </summary>
				void AttachBuffer(HBH::Audio::OpenAL::Buffer^ buf);
				///<summary>
				///This function queues a set of buffers on a source.  All buffers attached to a source will be played in sequence
				///</summary>
				void QueueBuffers(unsigned int number, array<HBH::Audio::OpenAL::Buffer^>^ buf);
				///<summary>
				///Queues One Buffer to the source.
				///</summary>
				void QueueBuffer(Buffer^ buf);
				///<summary>
				///This function unqueues a set of buffers attached to a source. 
				///</summary>
				void UnQueueBuffers(unsigned int number, array<HBH::Audio::OpenAL::Buffer^>^ buf);
				///<summary>
				///This function generates one or more sources.
				///</summary>
				static void GenerateSources(ALuint number, array<Source^>^% src);
				///<summary>
				///This function deletes one or more sources.
				///</summary>
				static void DeleteSources(unsigned int number, array<Source^>^ src);
				///<summary>
				///Checks whether the source is valid or not.
				///</summary>
				static bool IsSource(Source^ src);
				///<summary>
				///Checks whether the source is valid or not.
				///</summary>
				static bool IsSource(unsigned int srcname);

				//Extentions
				///<summary>
				///This is used to establish connections between Sources and Auxiliary Effect Slots.(Implement Filter Class and Parameter)
				///</summary>
				void SetAuxiliarySend(AuxiliaryEffectSlot^ effect, int SendNumber);
			internal:
				Source(unsigned int src);
				unsigned int srcname;
				bool m_looping;
			};
		}
	}
}
