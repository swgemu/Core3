/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLIENTOPENCONTAINERMESSAGE_H_
#define CLIENTOPENCONTAINERMESSAGE_H_

#include "engine/engine.h"

#include "server/zone/objects/scene/SceneObject.h"

class ClientOpenContainerMessage : public BaseMessage {
public:
	/*ClientOpenContainerMessage(Container* container) : BaseMessage() {
		insertShort(0x04);
		insertInt(0xDCA57409);

		insertLong(container->getObjectID());
		insertInt(0);
		insertShort(0);
	}*/

	ClientOpenContainerMessage(SceneObject* container, bool cloose) : BaseMessage() {
		insertShort(0x04);
		insertInt(0xDCA57409);

		insertLong(container->getObjectID());
		insertInt(0);
		insertShort(2);
	}

	ClientOpenContainerMessage(SceneObject* container) : BaseMessage() {
		insertShort(0x04);
		insertInt(0xDCA57409);

		insertLong(container->getObjectID());
		insertInt(0);
		insertShort(0);
	}

	/*ClientOpenContainerMessage(SceneObjectImplementation* container) : BaseMessage() {
		insertShort(0x04);
		insertInt(0xDCA57409);

		insertLong(container->getObjectID());
		insertInt(0);
		insertShort(0);
	}

	ClientOpenContainerMessage(ContainerImplementation* container) : BaseMessage() {
		insertShort(0x04);
		insertInt(0xDCA57409);

		insertLong(container->getObjectID());
		insertInt(0);
		insertShort(0);
	}*/

	ClientOpenContainerMessage(uint64 oid, const String& ascii, int test) : BaseMessage() {
		insertShort(0x04);
		insertInt(0xDCA57409);

		insertLong(oid);
		insertAscii(ascii);
	}
};

#endif /*CLIENTOPENCONTAINERMESSAGE_H_*/
