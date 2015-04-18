/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TRADECOMPLETEMESSAGE_H_
#define TRADECOMPLETEMESSAGE_H_

class TradeCompleteMessage : public BaseMessage {
public:
	TradeCompleteMessage() : BaseMessage(6) {
		insertShort(1);
		insertInt(0xC542038B);
	}
};

#endif /*TRADECOMPLETEMESSAGE_H_*/
