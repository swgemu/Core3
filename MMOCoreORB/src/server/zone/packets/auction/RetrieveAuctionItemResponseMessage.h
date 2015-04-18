/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RETRIEVEAUCTIONITEMRESPONSEMESSAGE_H_
#define RETRIEVEAUCTIONITEMRESPONSEMESSAGE_H_

#include "engine/engine.h"

// Status:
//  0 - Success
//  1 - You are not allowed to retrieve that item
// 12 - Inventory full

class RetrieveAuctionItemResponseMessage : public BaseMessage {
public:
	const static int NOTALLOWED = 1;
	const static int FULLINVENTORY = 12;

	const static int TOOFAR = 0x100;
	const static int DONTRETRIEVE = 0x200;
public:
    RetrieveAuctionItemResponseMessage(uint64 objectid, int status) : BaseMessage() {
		insertShort(0x03);
		insertInt(0x9499EF8C);  // opcode
		
		insertLong(objectid); //ObjectID player retrieved.
		insertInt(status); //status 0 - succeed, 12 - inventory full
	}
	
};
#endif /*RETRIEVEAUCTIONITEMRESPONSEMESSAGE_H_*/
