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
	static const int VHQ = 1;
	static const int HQ  = 2;
	static const int AA  = 3;
	static const int A   = 4;
	static const int BA  = 5;
	static const int LQ  = 6;
	static const int VLQ = 7;
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
