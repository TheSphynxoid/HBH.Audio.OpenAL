#pragma once
#define AL_METERS_PER_UNIT 0x20004

namespace HBH {
	namespace Audio {
		namespace OpenAL {
			public value struct Vector6 {
				Vector v1, v2;
				static Vector6 FromVectors(Vector v, Vector vv) {
					auto v6 = Vector6();
					v6.v1 = v;
					v6.v2 = vv;
					return v6;
				}
			internal:
				float* ToFloatPtr() {
					float* f = new float[6]();
					f[0] = v1.x;
					f[1] = v1.y;
					f[2] = v1.z;
					f[3] = v2.x;
					f[4] = v2.y;
					f[5] = v2.z;
					return f;
				}
			};
			public enum class DistanceModel
			{
				None = AL_NONE,
				Inverse_Distance = AL_INVERSE_DISTANCE,
				Inverse_Distance_Clamped = AL_INVERSE_DISTANCE_CLAMPED,
				Linear_Distance = AL_LINEAR_DISTANCE,
				Linear_Distance_Clamped = AL_LINEAR_DISTANCE_CLAMPED,
				Exponent_Distance = AL_EXPONENT_DISTANCE,
				Exponent_Distance_Clamped = AL_EXPONENT_DISTANCE_CLAMPED
			};
			public ref class Listener abstract sealed {
			public:
				static property float Gain {
					float get() {
						ALfloat f;
						alGetListenerf(AL_GAIN, &f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return f;
					}
					void set(float value) {
						alListenerf(AL_GAIN, value);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				static property Vector Position {
					Vector get() {
						float f[3];
						alGetListenerfv(AL_POSITION, f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						System::IntPtr ptr = System::IntPtr(f);
						array<float>^ fs = gcnew array<float>(3);
						fs[0] = f[0];
						fs[1] = f[1];
						fs[2] = f[2];
						return Vector(fs[0], fs[1], fs[2]);
					}
					void set(Vector value) {
						float f[3];
						memcpy_s(f, sizeof(float) * 3, value.ToALfloatPtr(), sizeof(float) * 3);
						alListenerfv(AL_POSITION, f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				static property Vector Velocity {
					Vector get() {
						float f[3];
						alGetListenerfv(AL_VELOCITY, f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						return Vector::FromFloatPtr(f);
					}
					void set(Vector value) {
						float f[3];
						memcpy_s(f, sizeof(float) * 3, value.ToALfloatPtr(), sizeof(float) * 3);
						alListenerfv(AL_VELOCITY, f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				static property Vector6 Orientation {
					Vector6 get() {
						float f[6];
						alGetListenerfv(AL_ORIENTATION, f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
						auto v = Vector6::FromVectors(Vector(f[0], f[1], f[2]), Vector(f[3], f[4], f[5]));
						return v;
					}
					void set(Vector6 value) {
						float f[6];
						memcpy_s(f, sizeof(float) * 6, value.ToFloatPtr(), sizeof(float) * 6);
						alListenerfv(AL_ORIENTATION, f);
						auto ex = Error::GetException(Error::GetError());
						if (ex != nullptr)throw ex;
					}
				}
				static property DistanceModel DistanceModel {
					HBH::Audio::OpenAL::DistanceModel get(){
						int i = alGetInteger(AL_DISTANCE_MODEL);
						return (HBH::Audio::OpenAL::DistanceModel)i;
					}
					void set(HBH::Audio::OpenAL::DistanceModel value) {
						alDistanceModel((ALenum)value);
					}
				}
				static property float DopplerFactor {
					float get() {
						return m_dopplerfactor;
					}
					void set(float value) {
						m_dopplerfactor = value;
						alDopplerFactor(value);
					}
				}
				static property float SpeedOfSound {
					float get() {
						return m_speedofsound;
					}
					void set(float value) {
						m_speedofsound = value;
						alSpeedOfSound(value);
					}
				}
				static property float MetersPerUnit
				{
					float get() {
						float f;
						alGetListenerf(AL_METERS_PER_UNIT, &f);
						return f;
					}
					void set(float value) {
						alListenerf(AL_METERS_PER_UNIT, value);
					}
				}
			private:
				static float m_dopplerfactor;
				static float m_speedofsound;
			};
		}
	}
}

