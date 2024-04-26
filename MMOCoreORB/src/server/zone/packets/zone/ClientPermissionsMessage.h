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
		insertInt(0xE00730E5);
		insertByte(0x01); // Galaxy_Open_Flag

		// Send this as 0 disallows a player to create anymore players on the selected galaxy
		insertByte(0x00); // CharacterSlot_Open_Flag

		// This flag will override the flag above and allow unlimited characters
		insertByte(0x01); // Unlimited_CharCreation_Flag
	}

	ClientPermissionsMessage(bool maxChars) : BaseMessage() {
		insertShort(0x05);
		insertInt(0xE00730E5);

		insertByte(0x01); // Galaxy_Open_Flag

		// Send this as 0 disallows a player to create anymore players on the selected galaxy
		byte charsMax = (maxChars ? 0x00 : 0x01);
		insertByte(charsMax); // CharacterSlot_Open_Flag

		// This flag will override the flag above and allow unlimited characters
		insertByte(0x00); // Unlimited_CharCreation_Flag

		insertByte(0x01); // Unknown
	}
};

#endif /*CLIENTPERMISSIONSMESSAGE_H_*/
