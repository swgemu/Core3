#ifndef UPDATESHIPTARGETSLOT_H_
#define UPDATESHIPTARGETSLOT_H_

#include "server/zone/packets/object/ObjectControllerMessageCallback.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/ship/ShipObject.h"

class UpdateShipTargetSlotCallback : public MessageCallback {
	int size;
	int targetSlot;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	UpdateShipTargetSlotCallback(ObjectControllerMessageCallback* objectControllerCallback) : MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()), objectControllerMain(objectControllerCallback) {
		size = 0;
		targetSlot = Components::SIZE;
	}

	void parse(Message* message) {
		size = message->parseInt();
		targetSlot = message->parseInt();
	}

	void run() {
		if (targetSlot <= Components::CHASSIS || targetSlot >= Components::SIZE) {
			return;
		}

		ManagedReference<CreatureObject*> creature = client->getPlayer();

		if (creature == nullptr || !creature->isPilotingShip()) {
			return;
		}

		ManagedReference<SceneObject*> rootParent = creature->getRootParent();

		if (rootParent == nullptr || !rootParent->isShipObject()) {
			return;
		}

		auto ship = rootParent->asShipObject();

		if (ship == nullptr || ship->getShipTargetSlot() == targetSlot) {
			return;
		}

		Locker cLock(ship, creature);
		ship->setShipTargetSlot(targetSlot, true);
	}
};

#endif // UPDATESHIPTARGETSLOT_H_
