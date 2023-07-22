/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#ifndef SHIPFLAG_H_
#define SHIPFLAG_H_

class ShipFlag {
public:
	enum {
		NONE 				= 0x00,
		ATTACKABLE			= 0x01,
		AGGRESSIVE			= 0x02,
		OVERT				= 0x04,
		TEF					= 0x08,
		PLAYER				= 0x10,
		ENEMY				= 0x20,
		WILLBEDECLARED		= 0x40,
		WASDECLARED			= 0x80,


		ESCORT				= 0x000001,
		FOLLOW				= 0x000002,
		TEST 				= 0x000004,
		LASTAIMASK 			= 0x000008, // keep this updated so we can loop through the masks
	};
};

#endif /* SHIPFLAG_H_ */
