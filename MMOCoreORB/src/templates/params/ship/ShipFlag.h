/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#ifndef SHIPFLAG_H_
#define SHIPFLAG_H_

class ShipFlag {
public:
	enum {
		ESCORT				= 0x000001,
		FOLLOW				= 0x000002,
		TURRETSHIP			= 0x000004,
		TEST 				= 0x000008,
		LASTAIMASK 			= 0x000010, // keep this updated so we can loop through the masks
	};
};

#endif /* SHIPFLAG_H_ */
