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

		PACK                = 0x01,
		HERD                = 0x02,
		KILLER              = 0x04,
		STALKER             = 0x08,
		BABY                = 0x10,
		LAIR                = 0x20,
		HEALER              = 0x40,
		STATIC              = 0x80,
		PET                 = 0x100,
		DROID_PET           = 0x200,
		FACTION_PET         = 0x400,
		WANDER				= 0x800,

		CARNIVORE           = 0x01,
		HERBIVORE           = 0x02
	};
};


#endif /* CREATUREFLAG_H_ */
