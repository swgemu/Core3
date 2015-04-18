/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEARTBEAT_H_
#define HEARTBEAT_H_

#include "engine/engine.h"

//Even though this opcode isnt in our tables, its required for some reason to make things work :(

class HeartBeat : public BaseMessage {
public:
	HeartBeat() : BaseMessage() {
		insertShort(0x01);
		insertInt(0xA16CF9AF); //opcode: HeartBeat
	}

};

#endif /*HEARTBEAT_H_*/
