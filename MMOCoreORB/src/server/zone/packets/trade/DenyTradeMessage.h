/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DENYTRADEMESSAGE_H_
#define DENYTRADEMESSAGE_H_

class DenyTradeMessage : public BaseMessage {
public:
	DenyTradeMessage() : BaseMessage(6) {
		insertShort(1);
		insertInt(0x6EC28670);
	}
};

#endif /*DENYTRADEMESSAGE_H_*/
