/*
*			Copyright <SWGEmu>
*	See file COPYING for copying conditions.
*/

#ifndef CLIENTCREATECHARACTER_H_
#define CLIENTCREATECHARACTER_H_

#include "engine/service/proto/BaseMessage.h"

class ClientCreateCharacter : public BaseMessage {
public:
	ClientCreateCharacter(const UnicodeString& name) {
		insertShort(12);
		insertInt(STRING_HASHCODE("ClientCreateCharacter"));

		insertAscii(""); // customization
		insertUnicode(name); // name

		insertAscii("object/creature/player/human_male.iff"); // Template File
		insertAscii(""); // Starting Location
		insertAscii(""); // Hair Object
		insertAscii(""); // Hair Customization
		insertAscii("crafting_artisan"); // profession
		insertByte(0x00); // unknown byte
		insertFloat(1.f); // Height
		insertUnicode(""); // Biography
		insertByte(0x00); // Tutorial Flag
	}
};

#endif /*CLIENTCREATECHARACTER_H_*/
