/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/objects/intangible/IntangibleObject.h"

#include "../../managers/object/ObjectManager.h"
#include "server/zone/packets/intangible/IntangibleObjectMessage3.h"
#include "server/zone/packets/intangible/IntangibleObjectMessage6.h"
#include "server/zone/packets/intangible/IntangibleObjectDeltaMessage3.h"

void IntangibleObjectImplementation::initializeTransientMembers() {
	SceneObjectImplementation::initializeTransientMembers();

	setLoggingName("IntangibleObject");
}

void IntangibleObjectImplementation::sendBaselinesTo(SceneObject* player) {
	info("sending intangible object baselines");

	BaseMessage* itno3 = new IntangibleObjectMessage3(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(itno3);

	BaseMessage* itno6 = new IntangibleObjectMessage6(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(itno6);
}

void IntangibleObjectImplementation::updateStatus(int newStatus, bool notifyClient) {
	if (status == newStatus)
		return;

	status = newStatus;

	if (!notifyClient)
		return;

	ManagedReference<SceneObject*> strongParent = getParent().get();
	if (strongParent == NULL)
		return;

	ManagedReference<SceneObject*> player = strongParent->getParent();

	if (player == NULL)
		return;

	IntangibleObjectDeltaMessage3* delta = new IntangibleObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
	delta->updateStatus(newStatus);
	delta->close();
	player->sendMessage(delta);
}

void IntangibleObjectImplementation::setCustomObjectName(const UnicodeString& name, bool notifyClient) {
	customName = name;

	if (!notifyClient)
		return;

	IntangibleObjectDeltaMessage3* ditno3 = new IntangibleObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());
	ditno3->updateName(name);
	ditno3->close();

	broadcastMessage(ditno3, true);
}
