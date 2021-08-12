
#ifndef RECYCLERESOURCETASK_H_
#define RECYCLERESOURCETASK_H_

#include "engine/engine.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/objects/resource/ResourceContainer.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/tool/recycle/RecycleTool.h"
#include "server/zone/objects/transaction/TransactionLog.h"
#include "server/zone/objects/creature/commands/TransferItemMiscCommand.h"

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
		resource = nullptr;
		player = nullptr;
		inventory = nullptr;
		resourceRecycleType = -1;
	}

	void run() {
		ManagedReference<SceneObject* > sceno = recycler->getParentRecursively(SceneObjectType::PLAYERCREATURE);
		if (!sceno->isPlayerCreature() || sceno == nullptr) {
			return;
		} else {
			player = cast <CreatureObject*>(sceno.get());
		}

		Locker locker(player);

		inventory = player->getSlottedObject("inventory");

		if (inventory == nullptr) {
			return;
		}

		if (!insertedItem->isResourceContainer()) {
			player->sendSystemMessage("@recycler_messages:no_resource"); // This processor can only recycle resources.
			removeFromRecycler("wrong resource");
			return;
		}

		ResourceContainer* resCon = cast<ResourceContainer*>(insertedItem.get());

		if(resCon == nullptr) {
			removeFromRecycler("resource container nullptr");
			return;
		}

		resource = resCon->getSpawnObject();

		if(resource == nullptr) {
			removeFromRecycler("spawn object nullptr");
			return;
		}

		ResourceManager* manager = player->getZoneServer()->getResourceManager();

		if(manager == nullptr) {
			removeFromRecycler("failed to get resourceManager");
			return;
		}

		int recyclerSelectedType = recycler->getSelectedResource();

		if (recyclerSelectedType == RecycleTool::NOTYPE) {
			player->sendSystemMessage("@ui:res_noresourceselected"); // No Resource Selected
			removeFromRecycler("no resource selected");
			return;
		}

		String selectedTypeName = recycler->getSelectedTypeName();

		resourceRecycleType = manager->getResourceRecycleType(resource);

		if (manager->isRecycledResource(resource)) {
			player->sendSystemMessage("@recycler_messages:already_recycled"); // You can not recycle a recycled resource.
			removeFromRecycler("already recycled");
			return;
		}


		if (resourceRecycleType == RecycleTool::NOTYPE) {
			player->sendSystemMessage("@recycler_messages:no_type"); // That resource can not be recycled as it does not have a processed form.
			removeFromRecycler("invalid resource");
			return;
		}

		if(resourceRecycleType != recyclerSelectedType) {
			removeFromRecycler("mismatched resource type");
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

		TransactionLog trx(TrxCode::RECYCLED, player);
		if (!manager->harvestResourceToPlayer(trx, player, recycledVersion, resCon->getQuantity())) {
			trx.abort() << "Recycle error: harvestResourceToPlayer failed.";
			return;
		}

		Locker clocker(insertedItem, player);

		insertedItem->destroyObjectFromWorld(true);
		insertedItem->destroyObjectFromDatabase(true);

		trx.commit(true);
	}

	void removeFromRecycler(const String& reason) {
		TransactionLog trx(recycler, player, insertedItem, TrxCode::TRANSFERITEMMISC);
		trx.addState("reason", "removeFromRecycler: " + reason);
		TransferItemMiscCommand::doTransferItemMisc(player, insertedItem, inventory, -1, trx);
	}
};

#endif /* RECYCLERESOURCETASK_H_ */
