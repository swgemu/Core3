/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef IGNORELISTMESSAGE_H_
#define IGNORELISTMESSAGE_H_

#include "engine/engine.h"

#include "server/zone/objects/player/PlayerObject.h"

class IgnoreListMessage : public BaseMessage {
public:
	IgnoreListMessage(PlayerObject* ghost) : BaseMessage() {
		insertShort(0x03);
		insertInt(0xF8C275B0); // CRC

		insertLong(ghost->getParentID());

		DeltaVector<String>* ignoreList = ghost->getIgnoreList();
		insertInt(ignoreList->size());

		for (int i = 0; i < ignoreList->size(); ++i) {
			insertAscii("SWG");
			insertAscii("Core3");
			insertAscii(ignoreList->get(i));
		}

		setCompression(true);
	}
};

#endif /*IGNORELISTMESSAGE_H_*/
