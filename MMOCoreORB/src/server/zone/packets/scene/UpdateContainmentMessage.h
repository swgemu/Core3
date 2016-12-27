/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UPDATECONTAINMENTMESSAGE_H_
#define UPDATECONTAINMENTMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

#include "server/zone/objects/scene/SceneObject.h"

class UpdateContainmentMessage : public BaseMessage {
public:
	UpdateContainmentMessage(SceneObject* object, SceneObject* container, uint32 type) : BaseMessage(30) {
		uint64 parId = 0;

		if (container != NULL)
			parId = container->getObjectID();

		insertShort(0x04);
		insertInt(0x56CBDE9E);  // CRC
		insertLong(object->getObjectID());  // ObjectID
		insertLong(parId);  // ObjectID
		insertInt(type);

		/*StringBuffer msg;
		msg << hex << "UpdateContainmentMessage [Object = " << object->getObjectID() << "]" << " container to (" << container->getObjectID() <<  ")\n";
		System::out << msg.toString();*/
	}

	UpdateContainmentMessage(uint64 object, uint64 container, uint32 type) : BaseMessage(30) {
		insertShort(0x04);
		insertInt(0x56CBDE9E);  // CRC
		insertLong(object);  // ObjectID
		insertLong(container);  // ObjectID
		insertInt(type);

		/*StringBuffer msg;
		msg << hex << "UpdateContainmentMessage [Object = " << object << "]" << " container to (" << container <<  ")\n";
		System::out << msg.toString();*/

	}

};

#endif /*UPDATECONTAINMENTMESSAGE_H_*/
