//
// Created by g on 12/20/17.
//

#ifndef CORE3_ORIENTFORHYPERSPACE_H
#define CORE3_ORIENTFORHYPERSPACE_H
#include "ObjectControllerMessage.h"


class OrientForHyperspaceMessage : public ObjectControllerMessage {
public:
	OrientForHyperspaceMessage(uint64 objid, const String& zone, float x, float y, float z) : ObjectControllerMessage(objid, 0x1B, 0x42D) {
		insertShort(0x09);
		insertInt(0xCA2A548B);  // CRC

		insertAscii(zone);
		insertFloat(x);
		insertFloat(z);
		insertFloat(y);
	}
};
#endif //CORE3_ORIENTFORHYPERSPACE_H
