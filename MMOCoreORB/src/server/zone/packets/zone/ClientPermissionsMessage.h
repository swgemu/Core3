/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLIENTPERMISSIONSMESSAGE_H_
#define CLIENTPERMISSIONSMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class ClientPermissionsMessage : public BaseMessage {
public:
	ClientPermissionsMessage() : BaseMessage() {
		insertShort(0x04);
		insertInt(STRING_HASHCODE("ClientPermissionsMessage"));

		// Galaxy Available
		insertBoolean(true);

		// Allow to create character
		insertBoolean(true);

		insertBoolean(true); // Unknown
		insertBoolean(true); // Unknown
	}

	ClientPermissionsMessage(bool canConnect, bool canCreateCharacter) : BaseMessage() {
		insertShort(0x04);
		insertInt(STRING_HASHCODE("ClientPermissionsMessage"));

		// Galaxy Available
		insertBoolean(canConnect);

		// Allow to create character
		insertBoolean(canCreateCharacter);

		insertBoolean(true); // Unknown
		insertBoolean(true); // Unknown
	}
};

#endif /*CLIENTPERMISSIONSMESSAGE_H_*/
