/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SCENEOBJECTDESTROYMESSAGE_H_
#define SCENEOBJECTDESTROYMESSAGE_H_

#include "engine/engine.h"

#include "server/zone/objects/scene/SceneObject.h"

class SceneObjectDestroyMessage : public BaseMessage {
public:
	SceneObjectDestroyMessage(SceneObject* scno) : BaseMessage(18) {
		insertShort(0x03);
		insertInt(0x4D45D504);  // CRC
		insertLong(scno->getObjectID());  // ObjectID
		insertByte(0);
	}
	
	SceneObjectDestroyMessage(uint64 oid) : BaseMessage(18) {
		insertShort(0x03);
		insertInt(0x4D45D504);  // CRC
		insertLong(oid);  // ObjectID
		insertByte(0);
	}
	
};

#endif /*SCENEOBJECTDESTROYMESSAGE_H_*/
