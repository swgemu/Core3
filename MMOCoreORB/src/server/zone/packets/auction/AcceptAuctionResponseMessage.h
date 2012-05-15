/*
 * AcceptAuctionResponseMessage.h
 *
 *  Created on: Apr 29, 2012
 *      Author: swgemu
 */

#ifndef ACCEPTAUCTIONRESPONSEMESSAGE_H_
#define ACCEPTAUCTIONRESPONSEMESSAGE_H_

#include "engine/engine.h"

class AcceptAuctionResponseMessage : public BaseMessage {
public:
	AcceptAuctionResponseMessage(uint64 objectID, uint32 errorCode) {
		insertShort(0x03);
		insertInt(0xC58A446E); //AcceptAuctionResponseMessage

		insertLong(objectID);
		insertInt(errorCode);
	}
};


#endif /* ACCEPTAUCTIONRESPONSEMESSAGE_H_ */
