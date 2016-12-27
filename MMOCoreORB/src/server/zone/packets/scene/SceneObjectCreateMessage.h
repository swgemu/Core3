/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SCENEOBJECTCREATEMESSAGE_H_
#define SCENEOBJECTCREATEMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

#include "server/zone/objects/scene/SceneObject.h"

class SceneObjectCreateMessage : public BaseMessage {
public:
	SceneObjectCreateMessage(SceneObject* scno) : BaseMessage() {
		insertShort(0x05);
		insertInt(0xFE89DDEA);  // CRC
		insertLong(scno->getObjectID());  // ObjectID
		insertFloat(scno->getDirectionX());
		insertFloat(scno->getDirectionY());
		insertFloat(scno->getDirectionZ());
		insertFloat(scno->getDirectionW());
/*
		insertFloat(0);
		insertFloat(0);
		insertFloat(0);
		insertFloat(1);
*/
		insertFloat(scno->getPositionX());
		insertFloat(scno->getPositionZ());
		//scno->info("sending z = " + String::valueOf(scno->getPositionZ()), true);
		insertFloat(scno->getPositionY());
		insertInt(scno->getClientObjectCRC());  // ObjectCRC
		insertByte(0);

		setCompression(true);
	}

	SceneObjectCreateMessage(uint64 oid, uint32 objCrc) : BaseMessage() {
		insertShort(0x05);
		insertInt(0xFE89DDEA);  // CRC
		insertLong(oid);  // ObjectID
		insertFloat(0);
		insertFloat(0);
		insertFloat(0);
		insertFloat(0); // was 1
		insertFloat(0);
		insertFloat(0);
		insertFloat(0);
		insertInt(objCrc);  // ObjectCRC
		insertByte(0x00);

		setCompression(true);
	}

	static void parseMessage(Message* pack, SceneObject* scno) {
		pack->shiftOffset(16);

		float x = pack->parseFloat();
		float z = pack->parseFloat();
		float y = pack->parseFloat();

		scno->setPosition(x, z, y);
	}
};

#endif /*SCENEOBJECTCREATEMESSAGE_H_*/
