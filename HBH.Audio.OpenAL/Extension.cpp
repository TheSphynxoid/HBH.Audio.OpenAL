#include "pch.h"
#include "Extension.h"

#define LOAD_PROC(T, x)  ((x) = (T)alGetProcAddress(#x))
#define GET_PROC(T,x) ((T)alGetProcAddress(#x))


/* Auxiliary Effect Slot object functions */
static LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots;
static LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots;
static LPALISAUXILIARYEFFECTSLOT alIsAuxiliaryEffectSlot;
static LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti;
static LPALAUXILIARYEFFECTSLOTIV alAuxiliaryEffectSlotiv;
static LPALAUXILIARYEFFECTSLOTF alAuxiliaryEffectSlotf;
static LPALAUXILIARYEFFECTSLOTFV alAuxiliaryEffectSlotfv;
static LPALGETAUXILIARYEFFECTSLOTI alGetAuxiliaryEffectSloti;
static LPALGETAUXILIARYEFFECTSLOTIV alGetAuxiliaryEffectSlotiv;
static LPALGETAUXILIARYEFFECTSLOTF alGetAuxiliaryEffectSlotf;
static LPALGETAUXILIARYEFFECTSLOTFV alGetAuxiliaryEffectSlotfv;

bool HBH::Audio::OpenAL::Effect::IsEffect(Effect^ e)
{
    return alIsEffect(e->EffectName) == AL_TRUE ? true : false;
}

void HBH::Audio::OpenAL::Effect::alGenEffect(int size)
{
    ALuint u[1] = { 0 };
    alGenEffects(1, u);
    auto ex = Error::GetError();
    if (ex != ErrorCode::No_Error) {
        throw Error::GetException(ex);
    }
    EffectName = u[0];
}

void HBH::Audio::OpenAL::Effect::alDeleteEffect(int size)
{
    ALuint i = EffectName;
    LOAD_PROC(LPALDELETEEFFECTS, alDeleteEffects);
    alDeleteEffects(size, &i);
    auto ex = Error::GetError();
    if (ex != ErrorCode::No_Error) {
        throw Error::GetException(ex);
    }
    EffectName = 0;
}

void HBH::Audio::OpenAL::Effect::alSetEffectI(ALenum e, int i)
{
    LOAD_PROC(LPALEFFECTI, alEffecti);
    alEffecti(EffectName, e, i);
    
    auto ex = Error::GetError();
    if (ex != ErrorCode::No_Error) {
        throw Error::GetException(ex);
    }
}

int HBH::Audio::OpenAL::Effect::alGetEffectI(ALenum e)
{
    ALint i;
    LOAD_PROC(LPALGETEFFECTI, alGetEffecti);
    alGetEffecti(EffectName, e, &i);
    auto ex = Error::GetError();
    if (ex != ErrorCode::No_Error) {
        throw Error::GetException(ex);
    }
    return i;
}

void HBH::Audio::OpenAL::Effect::alSetEffectIV(ALenum e, Vector i)
{
    auto fi = (int)System::Math::Round(*(i.ToALfloatPtr()));
    LOAD_PROC(LPALEFFECTIV, alEffectiv);
    alEffectiv(EffectName, e, &fi);
    auto ex = Error::GetError();
    if (ex != ErrorCode::No_Error) {
        throw Error::GetException(ex);
    }
}

HBH::Audio::OpenAL::Vector HBH::Audio::OpenAL::Effect::alGetEffectIV(ALenum e)
{
    ALint i[3];
    LOAD_PROC(LPALGETEFFECTIV, alGetEffectiv);
    alGetEffectiv(EffectName, e, i);
    auto ex = Error::GetError();
    if (ex != ErrorCode::No_Error) {
        throw Error::GetException(ex);
    }
    ALfloat f[3] = { i[0],i[1] ,i[2] };
    return Vector::FromFloatPtr(f);
}

void HBH::Audio::OpenAL::Effect::alSetEffectF(ALenum e, float f)
{
    LOAD_PROC(LPALEFFECTF, alEffectf);
    alEffectf(EffectName, e, f);
    auto ex = Error::GetError();
    if (ex != ErrorCode::No_Error) {
        throw Error::GetException(ex);
    }
}

float HBH::Audio::OpenAL::Effect::alGetEffectF(ALenum e)
{
    ALfloat f;
    LOAD_PROC(LPALGETEFFECTF, alGetEffectf);
    alGetEffectf(EffectName, e, &f);
    auto ex = Error::GetError();
    if (ex != ErrorCode::No_Error) {
        throw Error::GetException(ex);
    }
    return f;
}

void HBH::Audio::OpenAL::Effect::alSetEffectFV(ALenum e, Vector f)
{
    LOAD_PROC(LPALEFFECTFV, alEffectfv);
    alEffectfv(EffectName, e, f.ToALfloatPtr());
    auto ex = Error::GetError();
    if (ex != ErrorCode::No_Error) {
        throw Error::GetException(ex);
    }
}

HBH::Audio::OpenAL::Vector HBH::Audio::OpenAL::Effect::alGetEffectFV(ALenum e)
{
    ALfloat f[3];
    LOAD_PROC(LPALGETEFFECTFV, alGetEffectfv);
    alGetEffectfv(EffectName, e, f);
    auto ex = Error::GetError();
    if (ex != ErrorCode::No_Error) {
        throw Error::GetException(ex);
    }
    return Vector::FromFloatPtr(f);
}

HBH::Audio::OpenAL::AuxiliaryEffectSlot::AuxiliaryEffectSlot()
{
    ALuint ui;    
    LOAD_PROC(LPALGENAUXILIARYEFFECTSLOTS, alGenAuxiliaryEffectSlots);
    alGenAuxiliaryEffectSlots(1, &ui);
    auto ex = Error::GetError();
    if (ex != ErrorCode::No_Error) {
        throw Error::GetException(ex);
    }
    slot = ui;
}

int HBH::Audio::OpenAL::AuxiliaryEffectSlot::alGetSloti(ALenum e)
{
    ALint i;
    LOAD_PROC(LPALGETAUXILIARYEFFECTSLOTI, alGetAuxiliaryEffectSloti);
    alGetAuxiliaryEffectSloti(slot, e, &i);
    return i;
}

void HBH::Audio::OpenAL::AuxiliaryEffectSlot::alSetSloti(ALenum e, int value)
{
    LOAD_PROC(LPALAUXILIARYEFFECTSLOTI, alAuxiliaryEffectSloti);
    alAuxiliaryEffectSloti(slot, e, value);
}

float HBH::Audio::OpenAL::AuxiliaryEffectSlot::alGetSlotf(ALenum e)
{
    ALfloat f;
    LOAD_PROC(LPALGETAUXILIARYEFFECTSLOTF, alGetAuxiliaryEffectSlotf);
    alGetAuxiliaryEffectSlotf(slot, e, &f);
    return f;
}

void HBH::Audio::OpenAL::AuxiliaryEffectSlot::alSetSlotf(ALenum e, float value)
{
    LOAD_PROC(LPALAUXILIARYEFFECTSLOTF, alAuxiliaryEffectSlotf);
    alAuxiliaryEffectSlotf(slot, e, value);
}
