/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TRADECOMPLETEMESSAGE_H_
#define TRADECOMPLETEMESSAGE_H_

class TradeCompleteMessage : public BaseMessage {
public:
	TradeCompleteMessage() : BaseMessage(0x06) {
		insertShort(0x01);
		insertInt(0xC542038B);
	}
};

#endif /*TRADECOMPLETEMESSAGE_H_*/
