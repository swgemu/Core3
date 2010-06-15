/*
 * EmptyHopperCallback.h
 *
 *  Created on: 14/06/2010
 *      Author: victor
 */

#ifndef EMPTYHOPPERCALLBACK_H_
#define EMPTYHOPPERCALLBACK_H_

#include "ObjectControllerMessageCallback.h"
#include "server/zone/objects/installation/harvester/HarvesterObject.h"
#include "GenericResponse.h"


class EmptyHopperCallback : public MessageCallback {
	uint64 harvesterId;
	uint64 resourceId;
	uint32 quantity;
	uint8 byte1;
	uint8 byte2;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	EmptyHopperCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;
	}

	void parse(Message* message) {
		message->shiftOffset(12);
		 // skip passed player
		harvesterId = message->parseLong();
		resourceId = message->parseLong();
		quantity = message->parseInt(); // need to verify the quantity exists in the hopper
		byte1 = message->parseByte(); // Retrieve(0) vs Discard(1)
		byte2 = message->parseByte(); // checksum?
	}

	void run() {
		PlayerCreature* player = (PlayerCreature*) client->getPlayer();

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(harvesterId);

		if (object == NULL || !object->isInstallationObject())
			player->error("not parsing right");

		InstallationObject* inso = (InstallationObject*) object.get();

		if (!inso->isHarvesterObject())
			return;

		HarvesterObject* harvester = (HarvesterObject*) inso;

		try {
			harvester->wlock(player);

			if (!harvester->isOnAdminList(player)) {
				harvester->unlock();
				return;
			}

			if (!harvester->isInRange(player, 10)) {
				harvester->unlock();
				return;
			}


			SceneObject* inventory = player->getSlottedObject("inventory");


			ManagedReference<ResourceSpawn*> resourceSpawn = dynamic_cast<ResourceSpawn*>(server->getZoneServer()->getObject(resourceId));

			if (resourceSpawn == NULL) {
				player->error("wrong spawn id");
				harvester->unlock();
				return;
			}

			ManagedReference<ResourceContainer*> container = harvester->getContainerFromHopper(resourceSpawn);

			if (container == NULL) {
				player->error("null container");
				harvester->unlock();
				return;
			}

			if (byte1 == 0 && quantity > container->getQuantity()) {
				player->error("too much splitting");
				harvester->unlock();
				return;
			}

			if (byte1 == 1) {
				//harvester->removeResourceFromHopper(container);
				int oldQuantity = container->getQuantity();
				int newQuantity = oldQuantity - quantity;

				harvester->updateResourceContainerQuantity(container, newQuantity, true);
			} else if (byte1 == 0) {
				if (!inventory->hasFullContainerObjects()) {
					container->split(player, quantity);
					harvester->updateResourceContainerQuantity(container, container->getQuantity(), true);

				} else {
					ParameterizedStringId stringId("error_message", "inv_full");
					player->sendSystemMessage(stringId);
				}
			}

			GenericResponse* gr = new GenericResponse(player, 0xED, 1, byte2);
			player->sendMessage(gr);

			inventory->updateToDatabaseAllObjects(false);
			harvester->updateToDatabaseAllObjects(false);

			harvester->unlock();
		} catch (...) {
			harvester->unlock();
			player->error("unreported exception caught in EmptyHopperCallback::run");
		}

		//if (byte1 == 0 && player->getInventory()->getUnequippedItemCount() >= InventoryImplementation::MAXUNEQUIPPEDCOUNT)


	}
};



#endif /* EMPTYHOPPERCALLBACK_H_ */
