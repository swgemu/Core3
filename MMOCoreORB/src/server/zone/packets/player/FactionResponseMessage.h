/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FACTIONRESPONSEMESSAGE_H_
#define FACTIONRESPONSEMESSAGE_H_

#include "engine/engine.h"

class FactionResponseMessage : public BaseMessage {
public:

	FactionResponseMessage(FactionStandingList* fpl) : BaseMessage() {
		insertShort(0x07);
		insertInt(0x5DD53957);  // CRC

		fpl->insertToMessage(this);
		
		setCompression(true);

	}
};

#endif /*FACTIONRESPONSEMESSAGE_H_*/
