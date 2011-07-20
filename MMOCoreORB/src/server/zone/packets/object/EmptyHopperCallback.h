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
#include "server/zone/packets/harvester/HarvesterObjectMessage7.h"


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
		ManagedReference<CreatureObject*> player = (CreatureObject*) client->getPlayer();

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(harvesterId);

		if (object == NULL || !object->isInstallationObject())
			player->error("not parsing right");

		GenericResponse* gr = new GenericResponse(player, 0xED, 1, byte2);
		player->sendMessage(gr);

		InstallationObject* inso = (InstallationObject*) object.get();

		/*if (!inso->isHarvesterObject())
			return;

		HarvesterObject* harvester = (HarvesterObject*) inso;*/

		try {
			Locker clocker(inso, player);

			if (!inso->isOnAdminList(player)) {
				return;
			}

			if (!inso->isInRange(player, 20)) {
				player->sendSystemMessage("You are too far away");
				return;
			}


			SceneObject* inventory = player->getSlottedObject("inventory");

			ManagedReference<ResourceSpawn*> resourceSpawn = dynamic_cast<ResourceSpawn*>(server->getZoneServer()->getObject(resourceId));

			if (resourceSpawn == NULL) {
				player->error("wrong spawn id");
				return;
			}

			ManagedReference<ResourceContainer*> container = inso->getContainerFromHopper(resourceSpawn);

			if (container == NULL) {
				player->error("null container");
				return;
			}

			if (byte1 == 0 && quantity > container->getQuantity()) {
				player->error("too much splitting");
				return;
			}

			if (byte1 == 1) {
				//inso->removeResourceFromHopper(container);
				int oldQuantity = container->getQuantity();
				int newQuantity = oldQuantity - quantity;

				inso->updateResourceContainerQuantity(container, newQuantity, true);
			} else if (byte1 == 0) {
				if (!inventory->hasFullContainerObjects()) {
					container->split(quantity, player);
					inso->updateResourceContainerQuantity(container, container->getQuantity(), true);
				} else {
					StringIdChatParameter stringId("error_message", "inv_full");
					player->sendSystemMessage(stringId);
				}
			}

			inventory->updateToDatabaseAllObjects(false);
			inso->updateToDatabaseAllObjects(false);

			inso->broadcastToOperators(new HarvesterObjectMessage7(inso));

		} catch (Exception& e) {
			player->error("unreported exception caught in EmptyHopperCallback::run");
		}

		//if (byte1 == 0 && player->getInventory()->getUnequippedItemCount() >= InventoryImplementation::MAXUNEQUIPPEDCOUNT)


	}
};



#endif /* EMPTYHOPPERCALLBACK_H_ */
