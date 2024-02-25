//
// Created by g on 12/20/17.
//

#ifndef CORE3_HYPERSPACE_H
#define CORE3_HYPERSPACE_H

#include "engine/service/proto/BaseMessage.h"

class HyperspaceMessage : public BaseMessage {
public:
	HyperspaceMessage(uint64 shpid, int operand) : BaseMessage() {
		insertShort(operand);
		insertInt(0xCBF88482);  // Opcode
		insertLong(shpid);
	}
};
#endif //CORE3_HYPERSPACE_H
