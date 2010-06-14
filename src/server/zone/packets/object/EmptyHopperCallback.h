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

		SceneObject* inventory = player->getSlottedObject("inventory");


		ManagedReference<ResourceSpawn*> resourceSpawn = dynamic_cast<ResourceSpawn*>(server->getZoneServer()->getObject(resourceId));

		if (resourceSpawn == NULL) {
			player->error("wrong spawn id");
			return;
		}

		ManagedReference<ResourceContainer*> container = harvester->getContainerFromHopper(resourceSpawn);

		if (container == NULL) {
			player->error("null container");
			return;
		}

		if (byte1 == 1) {
			harvester->removeResourceFromHopper(container);
		}

		GenericResponse* gr = new GenericResponse(player, 0xED, 1, byte2);
		player->sendMessage(gr);

		//if (byte1 == 0 && player->getInventory()->getUnequippedItemCount() >= InventoryImplementation::MAXUNEQUIPPEDCOUNT)


	}
};



#endif /* EMPTYHOPPERCALLBACK_H_ */
