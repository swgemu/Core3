/*
 * CreateTicketResponseMessage.h
 *
 *  Created on: Nov 22, 2008
 *      Author: swgemu
 */

#ifndef CREATETICKETRESPONSEMESSAGE_H_
#define CREATETICKETRESPONSEMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class CreateTicketResponseMessage : public BaseMessage {
public:
   CreateTicketResponseMessage(int unknown = 0) : BaseMessage() {
		insertShort(0x09);
		insertInt(0x550A407A);  // CRC

		insertInt(unknown);
   }
};

#endif /* CREATETICKETRESPONSEMESSAGE_H_ */
