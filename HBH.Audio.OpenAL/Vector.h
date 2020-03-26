#pragma once
namespace HBH {
	namespace Audio {
		namespace OpenAL {
			public value struct Vector {
			public:
				float x, y, z;
				Vector(float X, float Y);
				Vector(float X, float Y, float Z);
				void Add(int i);
				System::String^ ToString() override;
				static initonly Vector empty = Vector(0,0,0);
			internal:
				ALfloat* ToALfloatPtr();
				static Vector FromFloatPtr(float* f);
			};
		}
	}
}
