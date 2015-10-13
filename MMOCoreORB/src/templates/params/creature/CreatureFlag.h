/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATUREFLAG_H_
#define CREATUREFLAG_H_

#include "engine/engine.h"

class CreatureFlag {
public:
	enum {
		NONE                = 0x00,
		ATTACKABLE          = 0x01,
		AGGRESSIVE          = 0x02,
		OVERT               = 0x04,
		TEF                 = 0x08,
		PLAYER              = 0x10,
		ENEMY               = 0x20,
		CHANGEFACTIONSTATUS = 0x40,
		BLINK_GREEN         = 0x80,

		NPC					= 0x00001,
		PACK                = 0x00002,
		HERD                = 0x00004,
		KILLER              = 0x00008,
		STALKER             = 0x00010,
		BABY                = 0x00020,
		LAIR                = 0x00040,
		HEALER              = 0x00080,
		SCOUT	            = 0x00100,
		PET                 = 0x00200,
		DROID_PET           = 0x00400,
		FACTION_PET         = 0x00800,
		ESCORT              = 0x01000,
		FOLLOW              = 0x02000,
		STATIC				= 0x04000,
		STATIONARY			= 0x08000,
		NOAIAGGRO			= 0x10000,
		TEST				= 0x20000,
		LASTAIMASK			= 0x40000, // keep this updated so we can loop through the masks

		CARNIVORE           = 0x01,
		HERBIVORE           = 0x02
	};
};


#endif /* CREATUREFLAG_H_ */
