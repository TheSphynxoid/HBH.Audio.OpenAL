#pragma once
#include "Extension.h"

 

namespace HBH {
	namespace Audio {
		namespace OpenAL {
			public value struct EAXReverbProperties {
                float Density;
                float Diffusion;
                float Gain;
                float GainHF;
                float GainLF;
                float DecayTime;
                float DecayHFRatio;
                float DecayLFRatio;
                float ReflectionsGain;
                float ReflectionsDelay;
                Vector ReflectionsPan;
                float LateReverbGain;
                float LateReverbDelay;
                Vector LateReverbPan;
                float EchoTime;
                float EchoDepth;
                float ModulationTime;
                float ModulationDepth;
                float AirAbsorptionGainHF;
                float HFReference;
                float LFReference;
                float RoomRolloffFactor;
                int   DecayHFLimit;
            internal:
                static EAXReverbProperties fromNativeProp(EFXEAXREVERBPROPERTIES prop);
			};
			public ref class EAXReverb :
				public Effect
			{
            public:
#pragma region Presets
#define CreatePreset(name , p) static EAXReverbProperties name = EAXReverbProperties::fromNativeProp(p);    
                static EAXReverbProperties Generic = EAXReverbProperties::fromNativeProp( EFX_REVERB_PRESET_GENERIC );
                static EAXReverbProperties PaddedCell = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_PADDEDCELL);
                static EAXReverbProperties Room = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_ROOM);
                static EAXReverbProperties BathRoom = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_BATHROOM);
                static EAXReverbProperties LivingRoom = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_LIVINGROOM);
                static EAXReverbProperties StoneRoom = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_STONEROOM);
                static EAXReverbProperties Auditorium = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_AUDITORIUM);
                static EAXReverbProperties ConcertHall = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_CONCERTHALL);
                static EAXReverbProperties Cave = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_CAVE);
                static EAXReverbProperties Arena = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_ARENA);
                static EAXReverbProperties Hangar = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_HANGAR);
                static EAXReverbProperties CarpetedHallway = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_CARPETEDHALLWAY);
                static EAXReverbProperties Hallway = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_HALLWAY);
                static EAXReverbProperties StoneCorridor = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_STONECORRIDOR);
                static EAXReverbProperties Alley = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_ALLEY);
                static EAXReverbProperties Forest = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_FOREST);
                static EAXReverbProperties City = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_CITY);
                static EAXReverbProperties Mountain = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_MOUNTAINS);
                static EAXReverbProperties Quarry = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_QUARRY);
                static EAXReverbProperties Plain = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_PLAIN);
                static EAXReverbProperties Parkinglot = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_PARKINGLOT);
                static EAXReverbProperties UnderWater = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_UNDERWATER);
                static EAXReverbProperties Drugged = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_DRUGGED);
                static EAXReverbProperties Psychotic = EAXReverbProperties::fromNativeProp(EFX_REVERB_PRESET_PSYCHOTIC);
                CreatePreset(CastleSmallRoom, EFX_REVERB_PRESET_CASTLE_SMALLROOM);
                CreatePreset(CastleShortPassage, EFX_REVERB_PRESET_CASTLE_SHORTPASSAGE);
                CreatePreset(CastleMediumRoom, EFX_REVERB_PRESET_CASTLE_MEDIUMROOM);
                CreatePreset(CastleLargeRoom, EFX_REVERB_PRESET_CASTLE_LARGEROOM);
                CreatePreset(CastleLongPassage, EFX_REVERB_PRESET_CASTLE_LONGPASSAGE);
                CreatePreset(CastleHall, EFX_REVERB_PRESET_CASTLE_HALL);
                CreatePreset(CastleCupBoard, EFX_REVERB_PRESET_CASTLE_CUPBOARD);
                CreatePreset(CastleCourtYard, EFX_REVERB_PRESET_CASTLE_COURTYARD);
                CreatePreset(CastleAlcove, EFX_REVERB_PRESET_CASTLE_ALCOVE);
                CreatePreset(FactorySmallRoom, EFX_REVERB_PRESET_FACTORY_SMALLROOM);
                CreatePreset(FactoryShortPassage, EFX_REVERB_PRESET_FACTORY_SHORTPASSAGE);
                CreatePreset(FactoryMediumRoom, EFX_REVERB_PRESET_FACTORY_MEDIUMROOM);
                CreatePreset(FactoryLargeRoom, EFX_REVERB_PRESET_FACTORY_LARGEROOM);
                CreatePreset(FactoryLongPassage, EFX_REVERB_PRESET_FACTORY_LONGPASSAGE);
                CreatePreset(FactoryHall, EFX_REVERB_PRESET_FACTORY_HALL);
                CreatePreset(FactoryCupBoard, EFX_REVERB_PRESET_FACTORY_CUPBOARD);
                CreatePreset(FactoryCourtYard, EFX_REVERB_PRESET_FACTORY_COURTYARD);
                CreatePreset(FactoryAlcove, EFX_REVERB_PRESET_FACTORY_ALCOVE);
                CreatePreset(IcePalaceSmallRoom, EFX_REVERB_PRESET_ICEPALACE_SMALLROOM);
                CreatePreset(IcePalaceShortPassage, EFX_REVERB_PRESET_ICEPALACE_SHORTPASSAGE);
                CreatePreset(IcePalaceMediumRoom, EFX_REVERB_PRESET_ICEPALACE_MEDIUMROOM);
                CreatePreset(IcePalaceLargeRoom, EFX_REVERB_PRESET_ICEPALACE_LARGEROOM);
                CreatePreset(IcePalaceLongPassage, EFX_REVERB_PRESET_ICEPALACE_LONGPASSAGE);
                CreatePreset(IcePalaceHall, EFX_REVERB_PRESET_ICEPALACE_HALL);
                CreatePreset(IcePalaceCupBoard, EFX_REVERB_PRESET_ICEPALACE_CUPBOARD);
                CreatePreset(IcePalaceCourtYard, EFX_REVERB_PRESET_ICEPALACE_COURTYARD);
                CreatePreset(IcePalaceAlcove, EFX_REVERB_PRESET_ICEPALACE_ALCOVE);
                CreatePreset(SpaceStationSmallRoom, EFX_REVERB_PRESET_SPACESTATION_SMALLROOM);
                CreatePreset(SpaceStationShortPassage, EFX_REVERB_PRESET_SPACESTATION_SHORTPASSAGE);
                CreatePreset(SpaceStationMediumRoom, EFX_REVERB_PRESET_SPACESTATION_MEDIUMROOM);
                CreatePreset(SpaceStationLargeRoom, EFX_REVERB_PRESET_SPACESTATION_LARGEROOM);
                CreatePreset(SpaceStationLongPassage, EFX_REVERB_PRESET_SPACESTATION_LONGPASSAGE);
                CreatePreset(SpaceStationHall, EFX_REVERB_PRESET_SPACESTATION_HALL);
                CreatePreset(SpaceStationCourtYard, EFX_REVERB_PRESET_SPACESTATION_ALCOVE);
                CreatePreset(SpaceStationAlcove, EFX_REVERB_PRESET_ICEPALACE_ALCOVE);
#pragma endregion
                EAXReverb();
                EAXReverb(EAXReverbProperties reverb);
                void SetProperties(EAXReverbProperties reverb);
			};
		}
	}
}

