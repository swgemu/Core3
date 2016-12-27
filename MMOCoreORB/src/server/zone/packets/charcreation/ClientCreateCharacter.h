/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLIENTCREATECHARACTER_H_
#define CLIENTCREATECHARACTER_H_

#include "engine/service/proto/BaseMessage.h"

class ClientCreateCharacter : public BaseMessage {
public:
	ClientCreateCharacter(const UnicodeString& name) {
		insertShort(12);
		insertInt(0xB97F3074);

		insertAscii(""); // customization
		insertUnicode(name); // name

		insertAscii("object/creature/player/human_male.iff"); // racefile
		insertAscii(""); // location
		insertAscii(""); // hairobj
		insertAscii(""); // haircust
		insertAscii("crafting_artisan"); // profession
		insertByte(0); // unknown byte
		insertFloat(1); // height
		insertInt(0); // bio
		insertByte(0); // char
	}
};

#endif /*CLIENTCREATECHARACTER_H_*/
