/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ITEMSOLDMESSAGE_H_
#define ITEMSOLDMESSAGE_H_

#include "engine/engine.h"

/*
 * Status codes
 * 0  - Sale succeeded
 * 1  - Auctioner is invalid
 * 2  - Invalid item
 * 3  - Vendor is malfunctioning
 * 4  - Must specify a valid sale price
 * 5  - Invalid sale Duration
 * 6  - Already for sale
 * 7  - Unknown error
 * 8  - Do not own
 * 9  - Not enough credits (5)
 * 10 - Unknown error
 * 11 - Unknown error
 * 12 - Unknown error
 * 13 - Too many items
 * 14 - Over 20,000 credits
*/

class ItemSoldMessage : public BaseMessage {

public:

	const static int SUCCESS = 0;
	const static int INVALIDAUCTIONER = 1;
	const static int INVALIDITEM = 2;
	const static int VENDORNOTWORKING = 3;
	const static int INVALIDSALEPRICE = 4;
	const static int INVALIDSALEDURATION = 5;
	const static int ALREADYFORSALE = 6;
	const static int UNKNOWNERROR = 7;
	const static int NOTOWN = 8;
	const static int NOTENOUGHCREDITS = 9;
	const static int TOOMANYITEMS = 13;
	const static int OVER20000 = 14;

public:
	ItemSoldMessage(uint64 objectid, int status) {
		insertShort(3);
		insertInt(0x0E61CC92);

		insertLong(objectid);
		insertInt(status);
	}

	static String statusToString(int status) {
		switch (status) {
		case SUCCESS: return String("SUCCESS");
		case INVALIDAUCTIONER: return String("INVALIDAUCTIONER");
		case INVALIDITEM: return String("INVALIDITEM");
		case VENDORNOTWORKING: return String("VENDORNOTWORKING");
		case INVALIDSALEPRICE: return String("INVALIDSALEPRICE");
		case INVALIDSALEDURATION: return String("INVALIDSALEDURATION");
		case ALREADYFORSALE: return String("ALREADYFORSALE");
		case UNKNOWNERROR: return String("UNKNOWNERROR");
		case NOTOWN: return String("NOTOWN");
		case NOTENOUGHCREDITS: return String("NOTENOUGHCREDITS");
		case TOOMANYITEMS: return String("TOOMANYITEMS");
		case OVER20000: return String("OVER20000");
		}

		StringBuffer msg;
		msg << "ItemSoldMessage::Unknown(" << status << ")";
		return msg.toString();
	}
};

#endif /*ITEMSOLDMESSAGE_H_*/
