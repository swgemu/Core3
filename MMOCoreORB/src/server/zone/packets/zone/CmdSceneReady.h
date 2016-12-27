/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CMDSCENEREADY_H_
#define CMDSCENEREADY_H_

#include "engine/service/proto/BaseMessage.h"

class CmdSceneReady : public BaseMessage {
public:
	CmdSceneReady() : BaseMessage(9) {
		insertShort(0x01);
		insertInt(0x43FD1C22);

	}

	static void parse(Packet* pack) {
		uint16 ackSequence = pack->parseShort();
	}

};

#endif /*CMDSCENEREADY_H_*/
