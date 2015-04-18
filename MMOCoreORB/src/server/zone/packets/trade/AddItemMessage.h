/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ADDITEMMESSAGE_H_
#define ADDITEMMESSAGE_H_

class AddItemMessage : public BaseMessage {
public:
	AddItemMessage(uint64 itemID) : BaseMessage(14) {
		insertShort(1);
		insertInt(0x1E8D1356);
		insertLong(itemID);
	}
};

#endif /*ADDITEMMESSAGE_H_*/
