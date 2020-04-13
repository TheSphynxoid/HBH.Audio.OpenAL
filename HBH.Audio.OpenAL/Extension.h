#pragma once
#include "alext.h"
#include "efx.h"
#include "efx-presets.h"

namespace HBH {
	namespace Audio {
		namespace OpenAL {
			//Base Effect Class.
			public ref class Effect {
			public:
#define Create_Proc(T,x) static T x = ((T)alGetProcAddress(#x));
				/* Effect object functions */
				Create_Proc(LPALGENEFFECTS,alGenEffects);
				static LPALDELETEEFFECTS alDeleteEffects;
				static LPALISEFFECT alIsEffect;
				static LPALEFFECTI alEffecti;
				static LPALEFFECTIV alEffectiv;
				static LPALEFFECTF alEffectf;
				static LPALEFFECTFV alEffectfv;
				static LPALGETEFFECTI alGetEffecti;
				static LPALGETEFFECTIV alGetEffectiv;
				static LPALGETEFFECTF alGetEffectf;
				static LPALGETEFFECTFV alGetEffectfv;
#undef NULL
				static initonly Effect^ NULL = gcnew Effect(0);
				ALuint EffectName;
				static bool IsEffect(Effect^ e);
				Effect() {};
			internal:
				Effect(ALuint id) { EffectName = id; };
				void alGenEffect(int size);
				void alDeleteEffect(int size);
				void alSetEffectI(ALenum e, int i);
				int alGetEffectI(ALenum e);
				void alSetEffectIV(ALenum e, Vector i);
				Vector alGetEffectIV(ALenum e);
				void alSetEffectF(ALenum e, float f);
				float alGetEffectF(ALenum e);
				void alSetEffectFV(ALenum e, Vector f);
				Vector alGetEffectFV(ALenum e);
			private:
				!Effect() {
					alDeleteEffect(1);
					EffectName = -1;
				};
				~Effect() { this->!Effect(); };
			};
			public ref class AuxiliaryEffectSlot {
			public:
#define GET_PROC(T,x) ((T)alGetProcAddress(#x))
				property Effect^ effect {
					Effect^ get() {
						ALint i;
						GET_PROC(LPALGETAUXILIARYEFFECTSLOTI, alGetAuxiliaryEffectSloti)(slot, AL_EFFECTSLOT_EFFECT, &i);
						return gcnew Effect((ALuint)i);
					}
					void set(Effect^ value) {
						alSetSloti(AL_EFFECTSLOT_EFFECT, (ALint)value->EffectName);
					}
				}
#undef GET_PROC
				ALuint slot;
				AuxiliaryEffectSlot();
			private:
				int alGetSloti(ALenum e);
				void alSetSloti(ALenum e, int value);
				float alGetSlotf(ALenum e);
				void alSetSlotf(ALenum e , float value);
			};
		}
	}
}

