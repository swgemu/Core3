/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef EMOTE_H_
#define EMOTE_H_

#include "ObjectControllerMessage.h"

class Emote : public ObjectControllerMessage {
public:
	Emote(uint64 senderID, uint64 targetID, uint64 emoteTargetID, uint32 emoteID, bool doAnim = true, bool doText = true)
			: ObjectControllerMessage(targetID, 0x0B, 0x12E) {

		insertLong(senderID);
		insertLong(emoteTargetID);
		insertInt(emoteID);
		insertByte((doAnim ? 0x01 : 0) | (doText ? 0x02 : 0));
	}

};

#endif /*EMOTE_H_*/
