/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef OPTIONBITMASK_H_
#define OPTIONBITMASK_H_

class OptionBitmask {
public:
	enum {
		NONE           = 0x00000000,
		ACTIVATED      = 0x00000001, // Used to turn structures on/off (harvesters)
		VENDOR         = 0x00000002, // Vendor flag in creatures
		INSURED        = 0x00000004,
		CONVERSE       = 0x00000008, // Converse flag in creatures
		UNKNOWN1       = 0x00000010,
		YELLOW         = 0x00000020, // Yellow items in tangibles -- should be set whenever an item is modified (pup, SEA, BE, etc) and probably also legendary/exceptional loot
		FACTIONAGGRO   = 0x00000040, // Sets color of mobs if they have a pvp faction and can aggro a player
		AIENABLED      = 0x00000080, // Default bitmask for mobiles
		INVULNERABLE   = 0x00000100, // Shows no information about condition or HAM
		DISABLED       = 0x00000200, // Used to add (disabled) text to vehicles client-side. TODO: Change vehicle disable code to use this
		UNKNOWN3       = 0x00000400,
		INTERESTING    = 0x00000800, // Info Icon 1, denotes a quest giver
		VEHICLE        = 0x00001000, // Vehicles will only appear with this bit enabled
		HASSERIAL      = 0x00002000, // Has a serial number
		UNKNOWN13      = 0x00004000,
		JTLINTERESTING = 0x00008000, // Info Icon 2, denotes a JTL quest giver
		UNKNOWN14      = 0x00010000,
		UNKNOWN15      = 0x00020000,
		UNKNOWN16      = 0x00040000,
		UNKNOWN17      = 0x00080000,
		UNKNOWN18      = 0x00100000,
		UNKNOWN19      = 0x00200000,
		UNKNOWN20      = 0x00400000,
		UNKNOWN21      = 0x00800000,
		UNKNOWN22      = 0x01000000,
		UNKNOWN23      = 0x02000000,
		UNKNOWN24      = 0x04000000,
		UNKNOWN25      = 0x08000000,
		UNKNOWN26      = 0x10000000,
		UNKNOWN27      = 0x20000000,
		UNKNOWN28      = 0x40000000,
		UNKNOWN29      = 0x80000000
	};
};

#endif /*OptionBitmask_H_*/
