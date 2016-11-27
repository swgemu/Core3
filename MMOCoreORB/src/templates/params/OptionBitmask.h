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
		HYBERNATE      = 0x00000010, // Remnant flag from early BETA? (Needs to be researched more)
		YELLOW         = 0x00000020, // Yellow items in tangibles -- should be set whenever an item is modified (pup, SEA, BE, etc) and probably also legendary/exceptional loot
		FACTIONAGGRO   = 0x00000040, // Sets color of mobs if they have a pvp faction and can aggro a player
		AIENABLED      = 0x00000080, // Default bitmask for mobiles
		INVULNERABLE   = 0x00000100, // Shows no information about condition or HAM
		DISABLED       = 0x00000200, // Used to add (disabled) text to vehicles client-side. TODO: Change vehicle disable code to use this
		UNINSURED      = 0x00000400,
		INTERESTING    = 0x00000800, // Info Icon 1, denotes a quest giver
		VEHICLE        = 0x00001000, // Vehicles will only appear with this bit enabled
		HASSERIAL      = 0x00002000, // Has a serial number, like from crafting
		OPENWINGS      = 0x00004000, // JTL client-side bit denoting when ship 'wings' are open?
		JTLINTERESTING = 0x00008000, // Info Icon 2, denotes a JTL quest giver
		SHIPDOCKING    = 0x00010000,
		SHIPDESTROY    = 0x00020000,
		HASCOMMS       = 0x00040000, // JTL ship to ship (player to AI) communication ability?
		SHIPDOCKABLE   = 0x00080000,
		SHIPEJECT      = 0x00100000,
		SHIPINSPECT    = 0x00200000,
		TRANSFERABLE   = 0x00400000,
		SHIPTUTORIAL   = 0x00800000,
		JTLMUSIC       = 0x01000000, // Client-side when AI ship aggros/combats player ship?
		LOCKOUTINST    = 0x02000000, // When players are 'locked out' of a certain instance?
		CREATURESPAWND = 0x04000000,
		HOLINTERESTING = 0x08000000, // Info Icon 3, denotes a HOLIDAY event quest giver
		LOCKED         = 0x10000000, // For containers??
		UNKNOWN27      = 0x20000000,
		UNKNOWN28      = 0x40000000,
		UNKNOWN29      = 0x80000000
	};
};

#endif /*OptionBitmask_H_*/
