/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef OPTIONBITMASK_H_
#define OPTIONBITMASK_H_

class OptionBitmask {
public:
	enum {
		NONE                 = 0x00000000,
		ACTIVATED            = 0x00000001, // Used to turn structures on/off (harvesters)
		VENDOR               = 0x00000002, // Vendor flag in creatures
		INSURED              = 0x00000004,
		CONVERSE             = 0x00000008, // Converse flag in creatures
		HIBERNATING          = 0x00000010,
		YELLOW               = 0x00000020, // Yellow items in tangibles -- should be set whenever an item is modified (pup, SEA, BE, etc) and probably also legendary/exceptional loot
		FACTIONAGGRO         = 0x00000040, // Sets color of mobs if they have a pvp faction and can aggro a player
		AIENABLED            = 0x00000080, // Default bitmask for mobiles
		INVULNERABLE         = 0x00000100, // Shows no information about condition or HAM
		DISABLED             = 0x00000200, // Used to add (disabled) text to vehicles client-side. TODO: Change vehicle disable code to use this
		UNINSURABLE          = 0x00000400,
		INTERESTING          = 0x00000800, // Info Icon 1, denotes a quest giver
		VEHICLE              = 0x00001000, // Vehicles will only appear with this bit enabled
		HASSERIAL            = 0x00002000, // Has a serial number
		WINGS_OPEN           = 0x00004000,
		JTLINTERESTING       = 0x00008000, // Info Icon 2, denotes a JTL quest giver
		DOCKING              = 0x00010000,
		DESTROYING           = 0x00020000,
		COMMABLE             = 0x00040000,
		DOCKABLE             = 0x00080000,
		EJECT                = 0x00100000,
		INSPECTABLE          = 0x00200000,
		TRANSFERABLE         = 0x00400000,
		INFLIGHT_TUTORIAL    = 0x00800000,
		SPACE_COMBAT_MUS     = 0x01000000,
		ENCOUNTER_LOCKED     = 0x02000000,
		SPAWNED_CREATURE     = 0x04000000,
		HOLIDAY_INTERESTING  = 0x08000000,
		LOCKED               = 0x10000000,
	};
};

#endif /*OptionBitmask_H_*/
