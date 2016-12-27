/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GAMESCENECHANGEDMESSAGE_H_
#define GAMESCENECHANGEDMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class GameSceneChangedMessage : public BaseMessage {
public:
	GameSceneChangedMessage() : BaseMessage(8) {
		insertShort(0x01);
		insertInt(0xBBADAEB9);
	}
	
};

#endif /*GAMESCENECHANGEDMESSAGE_H_*/
