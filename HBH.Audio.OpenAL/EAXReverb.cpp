#include "pch.h"
#include "EAXReverb.h"

HBH::Audio::OpenAL::EAXReverbProperties HBH::Audio::OpenAL::EAXReverbProperties::fromNativeProp(EFXEAXREVERBPROPERTIES prop)
{
	EAXReverbProperties p = EAXReverbProperties();
	p.Density = prop.flDensity;
	p.Diffusion = prop.flDiffusion;
	p.Gain = prop.flGain;
	p.GainHF = prop.flGainHF;
	p.GainLF = prop.flGainLF;
	p.DecayTime = prop.flDecayTime;
	p.DecayHFRatio = prop.flDecayHFRatio;
	p.DecayLFRatio = prop.flDecayLFRatio;
	p.ReflectionsGain = prop.flReflectionsGain;
	p.ReflectionsDelay = prop.flReflectionsDelay;
	p.ReflectionsPan = Vector::FromFloatPtr(prop.flReflectionsPan);
	p.LateReverbGain = prop.flLateReverbGain;
	p.LateReverbDelay = prop.flLateReverbDelay;
	p.LateReverbPan = Vector::FromFloatPtr(prop.flLateReverbPan);
	p.EchoTime = prop.flEchoTime;
	p.EchoDepth = prop.flEchoDepth;
	p.ModulationTime = prop.flModulationTime;
	p.ModulationDepth = prop.flModulationDepth;
	p.AirAbsorptionGainHF = prop.flAirAbsorptionGainHF;
	p.HFReference = prop.flHFReference;
	p.LFReference = prop.flLFReference;
	p.RoomRolloffFactor = prop.flRoomRolloffFactor;
	p.DecayHFLimit = prop.iDecayHFLimit;
	return p;
}

HBH::Audio::OpenAL::EAXReverb::EAXReverb()
{
	alGenEffect(1);
}

HBH::Audio::OpenAL::EAXReverb::EAXReverb(EAXReverbProperties reverb)
{
	alGenEffect(1);
	if (alGetEnumValue("AL_EFFECT_EAXREVERB") != 0) {
		alSetEffectI(AL_EFFECT_TYPE, AL_EFFECT_EAXREVERB);
		alSetEffectF(AL_EAXREVERB_DENSITY, reverb.Density);
		alSetEffectF(AL_EAXREVERB_DIFFUSION, reverb.Diffusion);
		alSetEffectF(AL_EAXREVERB_GAIN, reverb.Gain);
		alSetEffectF(AL_EAXREVERB_GAINHF, reverb.GainHF);
		alSetEffectF(AL_EAXREVERB_GAINLF, reverb.GainLF);
		alSetEffectF(AL_EAXREVERB_DECAY_TIME, reverb.DecayTime);
		alSetEffectF(AL_EAXREVERB_DECAY_HFRATIO, reverb.DecayHFRatio);
		alSetEffectF(AL_EAXREVERB_DECAY_LFRATIO, reverb.DecayLFRatio);
		alSetEffectF(AL_EAXREVERB_REFLECTIONS_GAIN, reverb.ReflectionsGain);
		alSetEffectF(AL_EAXREVERB_REFLECTIONS_DELAY, reverb.ReflectionsDelay);
		alSetEffectFV(AL_EAXREVERB_REFLECTIONS_PAN, reverb.ReflectionsPan);
		alSetEffectF(AL_EAXREVERB_LATE_REVERB_GAIN, reverb.LateReverbGain);
		alSetEffectF(AL_EAXREVERB_LATE_REVERB_DELAY, reverb.LateReverbDelay);
		alSetEffectFV(AL_EAXREVERB_LATE_REVERB_PAN, reverb.LateReverbPan);
		alSetEffectF(AL_EAXREVERB_ECHO_TIME, reverb.EchoTime);
		alSetEffectF(AL_EAXREVERB_ECHO_DEPTH, reverb.EchoDepth);
		alSetEffectF(AL_EAXREVERB_MODULATION_TIME, reverb.ModulationTime);
		alSetEffectF(AL_EAXREVERB_MODULATION_DEPTH, reverb.ModulationDepth);
		alSetEffectF(AL_EAXREVERB_AIR_ABSORPTION_GAINHF, reverb.AirAbsorptionGainHF);
		alSetEffectF(AL_EAXREVERB_HFREFERENCE, reverb.HFReference);
		alSetEffectF(AL_EAXREVERB_LFREFERENCE, reverb.LFReference);
		alSetEffectF(AL_EAXREVERB_ROOM_ROLLOFF_FACTOR, reverb.RoomRolloffFactor);
		alSetEffectI(AL_EAXREVERB_DECAY_HFLIMIT, reverb.DecayHFLimit);
	}
}

void HBH::Audio::OpenAL::EAXReverb::SetProperties(EAXReverbProperties reverb)
{
	if (alGetEnumValue("AL_EFFECT_EAXREVERB") != 0) {
		alSetEffectI(AL_EFFECT_TYPE, AL_EFFECT_EAXREVERB);
		alSetEffectF(AL_EAXREVERB_DENSITY, reverb.Density);
		alSetEffectF(AL_EAXREVERB_DIFFUSION, reverb.Diffusion);
		alSetEffectF(AL_EAXREVERB_GAIN, reverb.Gain);
		alSetEffectF(AL_EAXREVERB_GAINHF, reverb.GainHF);
		alSetEffectF(AL_EAXREVERB_GAINLF, reverb.GainLF);
		alSetEffectF(AL_EAXREVERB_DECAY_TIME, reverb.DecayTime);
		alSetEffectF(AL_EAXREVERB_DECAY_HFRATIO, reverb.DecayHFRatio);
		alSetEffectF(AL_EAXREVERB_DECAY_LFRATIO, reverb.DecayLFRatio);
		alSetEffectF(AL_EAXREVERB_REFLECTIONS_GAIN, reverb.ReflectionsGain);
		alSetEffectF(AL_EAXREVERB_REFLECTIONS_DELAY, reverb.ReflectionsDelay);
		alSetEffectFV(AL_EAXREVERB_REFLECTIONS_PAN, reverb.ReflectionsPan);
		alSetEffectF(AL_EAXREVERB_LATE_REVERB_GAIN, reverb.LateReverbGain);
		alSetEffectF(AL_EAXREVERB_LATE_REVERB_DELAY, reverb.LateReverbDelay);
		alSetEffectFV(AL_EAXREVERB_LATE_REVERB_PAN, reverb.LateReverbPan);
		alSetEffectF(AL_EAXREVERB_ECHO_TIME, reverb.EchoTime);
		alSetEffectF(AL_EAXREVERB_ECHO_DEPTH, reverb.EchoDepth);
		alSetEffectF(AL_EAXREVERB_MODULATION_TIME, reverb.ModulationTime);
		alSetEffectF(AL_EAXREVERB_MODULATION_DEPTH, reverb.ModulationDepth);
		alSetEffectF(AL_EAXREVERB_AIR_ABSORPTION_GAINHF, reverb.AirAbsorptionGainHF);
		alSetEffectF(AL_EAXREVERB_HFREFERENCE, reverb.HFReference);
		alSetEffectF(AL_EAXREVERB_LFREFERENCE, reverb.LFReference);
		alSetEffectF(AL_EAXREVERB_ROOM_ROLLOFF_FACTOR, reverb.RoomRolloffFactor);
		alSetEffectI(AL_EAXREVERB_DECAY_HFLIMIT, reverb.DecayHFLimit);
	}
}
