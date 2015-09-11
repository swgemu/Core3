/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef CREATEOBJECTTASK_H_
#define CREATEOBJECTTASK_H_

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

		ManagedReference<TangibleObject*> prototype = craftingTool->getPrototype();

		if (prototype == NULL || practice) {
			craftingTool->removeAllContainerObjects();
			craftingTool->setReady();
			return;
		}

		ObjectManager* objectManager = crafter->getZoneServer()->getObjectManager();
		objectManager->persistSceneObjectsRecursively(prototype, 1);

		ManagedReference<SceneObject*> inventory = crafter->getSlottedObject("inventory");

		if (inventory != NULL && !inventory->isContainerFullRecursive()) {

			if(inventory->transferObject(prototype, -1, true)) {
				crafter->sendSystemMessage("@system_msg:prototype_transferred");
				craftingTool->setReady();
				return;
			}
		}

		crafter->sendSystemMessage("@system_msg:prototype_not_transferred");
		craftingTool->setFinished();
	}
};

#endif /*CREATEOBJECTTASK_H_*/
