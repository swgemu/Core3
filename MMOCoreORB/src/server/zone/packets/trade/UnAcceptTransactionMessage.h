/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UNACCEPTTRANSACTIONMESSAGE_H_
#define UNACCEPTTRANSACTIONMESSAGE_H_

class UnAcceptTransactionMessage : public BaseMessage {
public:
	UnAcceptTransactionMessage() : BaseMessage(6) {
		insertShort(1);
		insertInt(0xE81E4382);
	}
};

#endif /*ACCEPTTRANSACTIONMESSAGE_H_*/
