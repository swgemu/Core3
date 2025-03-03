/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/objects/intangible/IntangibleObject.h"
#include "server/zone/objects/intangible/TheaterObject.h"

#include "server/zone/packets/intangible/IntangibleObjectMessage3.h"
#include "server/zone/packets/intangible/IntangibleObjectMessage6.h"
#include "server/zone/packets/intangible/IntangibleObjectDeltaMessage3.h"
#include "server/zone/packets/intangible/IntangibleObjectDeltaMessage6.h"
#include "server/zone/packets/scene/IsFlattenedTheaterMessage.h"

void IntangibleObjectImplementation::initializeTransientMembers() {
	SceneObjectImplementation::initializeTransientMembers();

	setLoggingName("IntangibleObject");
}

void IntangibleObjectImplementation::sendBaselinesTo(SceneObject* player) {
	debug("sending intangible object baselines");

	BaseMessage* itno3 = new IntangibleObjectMessage3(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(itno3);

	BaseMessage* itno6 = new IntangibleObjectMessage6(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(itno6);

	if (isTheaterObject()) {
		TheaterObject* theater = cast<TheaterObject*>(_this.getReferenceUnsafeStaticCast());

		if (theater != nullptr && theater->shouldFlattenTheater()) {
			BaseMessage* ift = new IsFlattenedTheaterMessage(getObjectID(), true);
			player->sendMessage(ift);
		}
	}
}

void IntangibleObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player) {
	if (datapadSize > 0) {
		alm->insertAttribute("droid_command_program_size", datapadSize);
	}

	if (!itemIdentifier.isEmpty()) {
		alm->insertAttribute("droid_command_name", itemIdentifier);
	}
}

void IntangibleObjectImplementation::updateStatus(int newStatus, bool notifyClient) {
	if (status == newStatus)
		return;

	status = newStatus;

	if (!notifyClient)
		return;

	ManagedReference<SceneObject*> strongParent = getParent().get();
	if (strongParent == nullptr)
		return;

	ManagedReference<SceneObject*> player = strongParent->getParent().get();

	if (player == nullptr)
		return;

	IntangibleObjectDeltaMessage3* intangibleDelta3 = new IntangibleObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());

	if (intangibleDelta3 == nullptr) {
		return;
	}

	intangibleDelta3->updateStatus(newStatus);
	intangibleDelta3->close();

	player->sendMessage(intangibleDelta3);
}

void IntangibleObjectImplementation::setCustomObjectName(const UnicodeString& name, bool notifyClient) {
	customName = name;

	if (!notifyClient) {
		return;
	}

	IntangibleObjectDeltaMessage3* intangibleDelta3 = new IntangibleObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());

	if (intangibleDelta3 == nullptr) {
		return;
	}

	intangibleDelta3->updateName(name);
	intangibleDelta3->close();

	broadcastMessage(intangibleDelta3, true);
}

void IntangibleObjectImplementation::setDataSize(const float dataSize, bool notifyClient) {
	datapadSize = dataSize;

	if (!notifyClient) {
		return;
	}

	IntangibleObjectDeltaMessage3* intangibleDelta3 = new IntangibleObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());

	if (intangibleDelta3 == nullptr) {
		return;
	}

	intangibleDelta3->updateDataSize(datapadSize);
	intangibleDelta3->close();

	broadcastMessage(intangibleDelta3, true);
}

void IntangibleObjectImplementation::setItemIdentifier(const String& itemName, bool notifyClient) {
	itemIdentifier = itemName;

	if (!notifyClient) {
		return;
	}

	IntangibleObjectDeltaMessage6* intangibleDelta6 = new IntangibleObjectDeltaMessage6(_this.getReferenceUnsafeStaticCast());

	if (intangibleDelta6 == nullptr) {
		return;
	}

	intangibleDelta6->updateItemIdentifier(itemIdentifier);
	intangibleDelta6->close();

	broadcastMessage(intangibleDelta6, true);
}
