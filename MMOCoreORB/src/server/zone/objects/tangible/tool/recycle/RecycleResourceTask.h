
#ifndef RECYCLERESOURCETASK_H_
#define RECYCLERESOURCETASK_H_

#include "engine/engine.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/objects/resource/ResourceContainer.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/tool/recycle/RecycleTool.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/resource/resourcespawner/resourcetree/ResourceTreeEntry.h"
#include "server/zone/managers/resource/resourcespawner/resourcetree/ResourceTreeNode.h"
#include "server/zone/managers/resource/resourcespawner/resourcetree/ResourceTree.h"

class RecycleResourceTask : public Task {
private:
	ManagedReference<RecycleTool*> recycler;
	ManagedReference<TangibleObject*> insertedItem;
	ManagedReference<ResourceSpawn*> resource;
	ManagedReference<CreatureObject*> player;
	ManagedReference<SceneObject*> inventory;
	int resourceRecycleType;

public:
	RecycleResourceTask(RecycleTool* reco, TangibleObject* tano) : Task() {
		recycler = reco;
		insertedItem = tano;
		resource = NULL;
		player = NULL;
		inventory = NULL;
		resourceRecycleType = -1;
	}

	void run() {
		ManagedReference<SceneObject* > sceno = recycler->getParentRecursively(SceneObjectType::PLAYERCREATURE);
		if (!sceno->isPlayerCreature() || sceno == NULL) {
			return;
		} else {
			player = cast <CreatureObject*>(sceno.get());
		}

		Locker locker(player);

		inventory = player->getSlottedObject("inventory");

		if (inventory == NULL) {
			return;
		}

		if (!insertedItem->isResourceContainer()) {
			player->sendSystemMessage("@recycler_messages:no_resource"); // This processor can only recycle resources.
			removeFromRecycler();
			return;
		}

		ResourceContainer* resCon = cast<ResourceContainer*>(insertedItem.get());

		if(resCon == NULL) {
			removeFromRecycler();
			return;
		}

		resource = resCon->getSpawnObject();

		if(resource == NULL) {
			removeFromRecycler();
			return;
		}

		ResourceManager* manager = player->getZoneServer()->getResourceManager();

		if(manager == NULL) {
			removeFromRecycler();
			return;
		}

		int recyclerSelectedType = recycler->getSelectedResource();

		if (recyclerSelectedType == RecycleTool::NOTYPE) {
			player->sendSystemMessage("@ui:res_noresourceselected"); // No Resource Selected
			removeFromRecycler();
			return;
		}

		String selectedTypeName = recycler->getSelectedTypeName();

		resourceRecycleType = manager->getResourceRecycleType(resource);

		if (manager->isRecycledResource(resource)) {
			player->sendSystemMessage("@recycler_messages:already_recycled"); // You can not recycle a recycled resource.
			removeFromRecycler();
			return;
		}


		if (resourceRecycleType == RecycleTool::NOTYPE) {
			player->sendSystemMessage("@recycler_messages:no_type"); // That resource can not be recycled as it does not have a processed form.
			removeFromRecycler();
			return;
		}

		if(resourceRecycleType != recyclerSelectedType) {
			removeFromRecycler();
			String stub = "@recycler_messages:only_";
			if (recycler->getToolType() == RecycleTool::METAL) {
				stub = stub + "metal_";
			} else if (recycler->getToolType() == RecycleTool::ORE && selectedTypeName != "gemstone") {
				stub = stub + "ore_";
			}
			player->sendSystemMessage(stub + selectedTypeName); // This processor is set to recycle [resourceType] resources. You may need another type of processor for the resource you're trying to use, or you may try a different setting.
			return;
		}

		ResourceSpawn* recycledVersion = manager->getRecycledVersion(resource);

		manager->harvestResourceToPlayer(player, recycledVersion, resCon->getQuantity());

		insertedItem->destroyObjectFromWorld(false);

	}

	void removeFromRecycler() {

		StringBuffer args;
		args << inventory->getObjectID() << " -1 0 0 0";

		String stringArgs = args.toString();

		Locker locker(player);

		player->executeObjectControllerAction(String("transferitemmisc").hashCode(), insertedItem->getObjectID(), stringArgs);

	}

};

#endif /* RECYCLERESOURCETASK_H_ */
