/*
 * DnaSampleRange.h
 *
 *  Created on: Jul 14, 2013
 *      Author: washu
 */

#ifndef DNASAMPLERANGE_H_
#define DNASAMPLERANGE_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace managers {
namespace creature {

class DnaSampleRange : public Object {

protected:
	uint32 vhqMax;
	uint32 vhqMin;
	uint32 hqMax;
	uint32 hqMin;
	uint32 aaMax;
	uint32 aaMin;
	uint32 aMax;
	uint32 aMin;
	uint32 baMax;
	uint32 baMin;
	uint32 lqMax;
	uint32 lqMin;
	uint32 vlqMax;
	uint32 vlqMin;

public:
	DnaSampleRange(LuaObject& obj);
	virtual ~DnaSampleRange();
	enum {
		VHQ = 1,
		HQ  = 2,
		AA  = 3,
		A   = 4,
		BA  = 5,
		LQ  = 6,
		VLQ = 7
	};
	int generateValue(int quality);
	String toString();
	bool inRange(int amount);
};

}
}
}
}

using namespace server::zone::managers::creature;

#endif /* DNASAMPLERANGE_H_ */
