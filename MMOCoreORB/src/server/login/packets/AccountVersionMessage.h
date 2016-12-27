/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ACCOUNTVERSIONMESSAGE_H_
#define ACCOUNTVERSIONMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class AccountVersionMessage : public BaseMessage {

public:
	AccountVersionMessage(const String& username, const String& password, const String& version) : BaseMessage() {
		insertShort(0x04);
		insertInt(0x41131F96);

		insertAscii(username);
		insertAscii(password);
		insertAscii(version);
	}

	static void parse(Packet* pack, String& username, String& password, String& version) {
		pack->parseAscii(username);
		pack->parseAscii(password);

		pack->parseAscii(version);
	}

};

#endif /*ACCOUNTVERSIONMESSAGE_H_*/
