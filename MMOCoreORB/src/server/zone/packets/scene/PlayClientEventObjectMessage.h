/*
 * PlayClientEventObjectMessage.h
 *
 *  Created on: 09/01/2012
 *      Author: victor
 */

#ifndef PLAYCLIENTEVENTOBJECTMESSAGE_H_
#define PLAYCLIENTEVENTOBJECTMESSAGE_H_


#include "engine/engine.h"

#include "server/zone/objects/scene/SceneObject.h"

class PlayClientEventObjectMessage : public BaseMessage {
public:
	PlayClientEventObjectMessage(SceneObject* obj, const String& file, const String& aux) : BaseMessage() {
		insertShort(0x05);
		insertInt(0xAF83C3F2);  // CRC
		insertAscii(file.toCharArray());
		insertAscii(aux.toCharArray());
		insertLong(obj->getObjectID());
	}

};


#endif /* PLAYCLIENTEVENTOBJECTMESSAGE_H_ */
