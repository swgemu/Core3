/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ACCEPTTRANSACTIONMESSAGE_H_
#define ACCEPTTRANSACTIONMESSAGE_H_

class AcceptTransactionMessage : public BaseMessage {
public:
	AcceptTransactionMessage() : BaseMessage(6) {
		insertShort(1);
		insertInt(0xB131CA17);
	}
};

#endif /*ACCEPTTRANSACTIONMESSAGE_H_*/
