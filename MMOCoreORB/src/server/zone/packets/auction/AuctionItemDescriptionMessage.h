/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef AUCTIONITEMDESCRIPTIONMESSAGE_H_
#define AUCTIONITEMDESCRIPTIONMESSAGE_H_

#include "engine/engine.h"

class AuctionItemDescriptionMessage : public BaseMessage {
	
public:
	AuctionItemDescriptionMessage(uint64 objectid, UnicodeString& description) {
		insertShort(2);
		insertInt(0xFE0E644B);
		
		insertLong(objectid);
		
		setCompression(true);

		insertUnicode(description);
		insertInt(0);
		insertInt(0);
	}
	
};

#endif /*AUCTIONITEMDESCRIPTIONMESSAGE_H_*/
