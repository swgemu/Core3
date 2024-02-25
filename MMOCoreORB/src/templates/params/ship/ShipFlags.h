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
		TEST 				= 0x000004,
		LASTAIMASK 			= 0x000008, // keep this updated so we can loop through the masks
	};
};

#endif /* SHIPFLAG_H_ */
