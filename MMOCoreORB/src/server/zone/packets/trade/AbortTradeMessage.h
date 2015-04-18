/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ABORTTRADEMESSAGE_H_
#define ABORTTRADEMESSAGE_H_

class AbortTradeMessage : public BaseMessage {
public:
	AbortTradeMessage() : BaseMessage(6) {
		insertShort(1);
		insertInt(0x9CA80F98);
	}
};

#endif /*ABORTTRADEMESSAGE_H_*/
