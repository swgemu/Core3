/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BIDAUCTIONRESPONSEMESSAGE_H_
#define BIDAUCTIONRESPONSEMESSAGE_H_

/*
 * Status codes
 * 0  - Suceeded
 * 1  - Auctioner is invalid 
 * 2  - Invalid item 
 * 9  - Not enough credits
 * 
 */

#include "engine/engine.h"


class BidAuctionResponseMessage : public BaseMessage {
public:
	const static int SUCCEDED = 0;
	const static int INVALIDAUCTIONER = 1;
	const static int INVALIDITEM = 2;
	const static int INVALIDPRICE = 4;
	const static int NOTENOUGHCREDITS = 9;
	const static int PURCHASEFAILED = 10;
	const static int PURCHASEREJECTED = 11;
	const static int PURCHASEHIGHERTHAN20000 = 13;
	const static int PRICEOVERFLOW = 14;

public:
    BidAuctionResponseMessage(uint64 objectid, int status) : BaseMessage() {
		insertShort(0x03);
		insertInt(0x8FCBEF4A);  // opcode
		
		insertLong(objectid); //ObjectID player is bidding on.
		insertInt(status);
	}
	
};

#endif /*BIDAUCTIONRESPONSEMESSAGE_H_*/
