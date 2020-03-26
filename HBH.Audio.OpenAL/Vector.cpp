#include "pch.h"
#include "Vector.h"

HBH::Audio::OpenAL::Vector::Vector(float X, float Y)
{
	x = X;
	y = Y;
}

HBH::Audio::OpenAL::Vector::Vector(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}

void HBH::Audio::OpenAL::Vector::Add(int i)
{
	x += i;
	y += i;
	z += i;
}

System::String^ HBH::Audio::OpenAL::Vector::ToString()
{
	return gcnew System::String("X = " + x + " Y = " + y + " Z = " + z);
}

ALfloat* HBH::Audio::OpenAL::Vector::ToALfloatPtr()
{
	ALfloat fs[3];
	fs[0] = x;
	fs[1] = y;
	fs[2] = z;
	return fs;
}

HBH::Audio::OpenAL::Vector HBH::Audio::OpenAL::Vector::FromFloatPtr(float* f)
{
	return Vector(f[0], f[1], f[2]);
}
