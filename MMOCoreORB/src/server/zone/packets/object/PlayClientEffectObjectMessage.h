/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLAYCLIENTEFFECTOBJECTMESSAGE_H_
#define PLAYCLIENTEFFECTOBJECTMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

#include "server/zone/objects/scene/SceneObject.h"

class PlayClientEffectObjectMessage : public BaseMessage {
public:
	PlayClientEffectObjectMessage(SceneObject* obj, const String& file, const String& aux) : BaseMessage() {
		insertShort(0x05);
		insertInt(0x8855434A);  // CRC
		insertAscii(file.toCharArray());
		insertAscii(aux.toCharArray());
		insertLong(obj->getObjectID());
	}

};

#endif /*PLAYCLIENTEFFECTOBJECTMESSAGE_H_*/
