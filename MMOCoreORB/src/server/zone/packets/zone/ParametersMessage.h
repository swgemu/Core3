/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PARAMETERSMESSAGE_H_
#define PARAMETERSMESSAGE_H_

#include "engine/engine.h"

#include "../MessageCallback.h"

class ParametersMessage : public BaseMessage {
public:
	ParametersMessage() : BaseMessage(7) {
		insertShort(0x02);
		insertInt(0x487652DA);
	    insertInt(0x00000384);

	}

	static void parse(Packet* pack) {
		uint16 ackSequence = pack->parseShort();
	}
	
};

class ParametersMessageCallback : public MessageCallback {
	uint16 ackSequence;
public:
	ParametersMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server), ackSequence(0) {
	}

	void parse(Message* msg) {
		ackSequence = msg->parseShort();
	}

	void execute() {

	}
};

#endif /*PARAMETERSMESSAGE_H_*/
