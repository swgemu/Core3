/*
 * ShipComponentFlag.h
 *
 * Author: H
 */

#ifndef SHIPCOMPONENTFLAG_H
#define SHIPCOMPONENTFLAG_H

namespace ShipComponentFlag {
	enum {
		DISABLED				= 0x0001,
		LOW_POWER				= 0x0002,
		ACTIVE					= 0x0004,
		DEMOLISHED				= 0x0008,
		REVERSE_ENGINEERED		= 0x0010,
		SHIELD_FRONT			= 0x0020,
		SHIELD_BACK				= 0x0040,
		DISABLED_NEEDS_POWER	= 0x0080
	};
}
#endif //SHIPCOMPONENTFLAG_H
