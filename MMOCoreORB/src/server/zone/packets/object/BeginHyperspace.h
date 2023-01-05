//
// Created by g on 12/20/17.
//

#ifndef CORE3_BEGINHYPERSPACE_H
#define CORE3_BEGINHYPERSPACE_H

#include "ObjectControllerMessage.h"


class BeginHyperspaceMessage : public ObjectControllerMessage {
public:
	BeginHyperspaceMessage(uint64 objid, const String& location, float x, float y, float z) : ObjectControllerMessage(objid, 0x1B, 0x3FE) {
		insertAscii(location);
		insertFloat(x);
		insertFloat(z);
		insertFloat(y);
	}
};

#endif //CORE3_BEGINHYPERSPACE_H
