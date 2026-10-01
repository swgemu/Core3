/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef CREATEOBJECTTASK_H_
#define CREATEOBJECTTASK_H_

#include "server/zone/objects/transaction/TransactionLog.h"

// A crafting prototype is created transient, but PERSISTENT objects end up under it: the
// crafted_components container + ingredient hopper moved into it at assembly, and a crafting
// station prototype's own ingredient_hopper (created at a hardcoded persistence 1 by
// CraftingStation::createChildObjects). Dropping a transient prototype leaves all of them in the
// database under a parent row that never existed. destroyObjectFromDatabase(true) on the
// prototype walks its slotted, contained and child objects and deletes every one; on the
// prototype itself it only marks a never-written object (ObjectManager::destroyObjectFromDatabase).
// Call it BEFORE destroyObjectFromWorld / dropping the prototype. A persistent prototype -- a
// completed item, or a manufacture-schematic prototype at persistence 2 -- returns here and keeps
// everything. Caller holds the prototype lock.
static inline void cascadeTransientPrototypeFromDatabase(SceneObject* prototype) {
	if (prototype == nullptr || prototype->isPersistent()) {
		return;
	}

	prototype->destroyObjectFromDatabase(true);
}

class CreateObjectTask : public Task {

	ManagedReference<CraftingTool*> craftingTool;
	ManagedReference<CreatureObject*> crafter;
	bool practice;

public:
	CreateObjectTask(CreatureObject* player, CraftingTool* tool, bool pract) : Task() {

		craftingTool = tool;
		crafter = player;
		practice = pract;
	}

	void run() {
		Locker locker(crafter);
		Locker clocker(craftingTool, crafter);

		craftingTool->setCountdownTimer(0, true);

		auto prototype = craftingTool->getPrototype();

		if (prototype == nullptr || practice) {
			// A practice prototype is transient (created with persistence 0) and is simply
			// dropped here, but the crafted_components container + ingredient hopper moved into
			// it at assembly were created PERSISTENT -- so they stayed in the database with a
			// parent row that never existed. A station prototype also carries its own persistent
			// ingredient_hopper. Delete everything persistent under the prototype before it goes.
			if (practice && prototype != nullptr) {
				Locker plocker(prototype, craftingTool);
				cascadeTransientPrototypeFromDatabase(prototype);
			}

			craftingTool->removeAllContainerObjects();
			craftingTool->setReady();

			if (practice && prototype != nullptr)
				crafter->notifyObservers(ObserverEventType::PROTOTYPECREATED, prototype, 1);

			return;
		}

		ObjectManager* objectManager = crafter->getZoneServer()->getObjectManager();
		objectManager->persistSceneObjectsRecursively(prototype, 1);

		ManagedReference<SceneObject*> inventory = crafter->getInventory();

		// The check for space in the players inventory has to be done here instead of in isContainerFullRecursive due to the object being in the crafting tool already.
		if (inventory != nullptr && craftingTool->isASubChildOf(crafter) && !(inventory->getContainerVolumeLimit() <= (inventory->getCountableObjectsRecursive()))) {
			TransactionLog trx(crafter, inventory, prototype, TrxCode::CRAFTINGSESSION);

			if (inventory->transferObject(prototype, -1, true)) {
				crafter->sendSystemMessage("@system_msg:prototype_transferred");

				crafter->notifyObservers(ObserverEventType::PROTOTYPECREATED, prototype, 0);
				craftingTool->setReady();

				return;
			}
		}

		crafter->sendSystemMessage("@system_msg:prototype_not_transferred");
		craftingTool->setFinished();
	}
};

#endif /*CREATEOBJECTTASK_H_*/
