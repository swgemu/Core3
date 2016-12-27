/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLIENTLOGOUT_H_
#define CLIENTLOGOUT_H_

#include "engine/service/proto/BaseMessage.h"

class ClientLogout : public BaseMessage {
public:
	ClientLogout() : BaseMessage(20) {
		insertShort(0x01);
		insertInt(0x42FD19DD);
	}
	
};

#endif /*CLIENTLOGOUT_H_*/
