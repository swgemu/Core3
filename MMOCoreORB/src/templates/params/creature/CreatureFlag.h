/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATUREFLAG_H_
#define CREATUREFLAG_H_

class CreatureFlag {
public:
	enum {
		NONE                    = 0x00,
		ATTACKABLE              = 0x01,
		AGGRESSIVE              = 0x02,
		OVERT                   = 0x04,
		TEF                     = 0x08,
		PLAYER                  = 0x10,
		ENEMY                   = 0x20,
		WILLBEDECLARED          = 0x40,
		WASDECLARED             = 0x80,

		NPC						= 0x000001,
		PACK					= 0x000002,
		HERD					= 0x000004,
		KILLER					= 0x000008,
		STALKER					= 0x000010,
		BABY					= 0x000020,
		LAIR					= 0x000040,
		HEALER					= 0x000080,
		SCOUT					= 0x000100,
		PET						= 0x000200,
		DROID_PET				= 0x000400,
		FACTION_PET				= 0x000800,
		ESCORT					= 0x001000,
		FOLLOW					= 0x002000,
		STATIC					= 0x004000,
		STATIONARY				= 0x008000,
		NOAIAGGRO				= 0x010000,
		SCANNING_FOR_CONTRABAND = 0x020000,
		IGNORE_FACTION_STANDING = 0x040000,
		SQUAD					= 0x080000,
		TEST					= 0x100000,
		LASTAIMASK				= 0x200000, // keep this updated so we can loop through the masks

		CARNIVORE               = 0x01,
		HERBIVORE               = 0x02
	};
};

#endif /* CREATUREFLAG_H_ */
