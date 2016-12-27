/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef POPULATEMISSIONBROWSERMESSAGE_H_
#define POPULATEMISSIONBROWSERMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class PopulateMissionBrowserMessage : public BaseMessage {
public:
	PopulateMissionBrowserMessage() : BaseMessage() {
		insertShort(3);
		insertInt(0x88D9885C);
		insertInt(0); // list begin?
	}
};


#endif /*POPULATEMISSIONBROWSERMESSAGE_H_*/
