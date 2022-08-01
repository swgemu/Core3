/*
 * EmptyHopperCallback.h
 *
 *  Created on: 14/06/2010
 *      Author: victor
 */

#ifndef EMPTYHOPPERCALLBACK_H_
#define EMPTYHOPPERCALLBACK_H_

#include "../harvester/HarvesterObjectMessage7.h"
#include "ObjectControllerMessageCallback.h"
#include "GenericResponse.h"

class EmptyHopperCallback : public MessageCallback {
	uint64 playerId;
	uint64 harvesterId;
	uint64 resourceId;
	int quantity;
	bool discard;
	uint8 sequenceId;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	EmptyHopperCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()),
		playerId(0), harvesterId(0), resourceId(0), quantity(0), discard(false), sequenceId(0), objectControllerMain(objectControllerCallback) {
	}

	void parse(Message* message) {
		playerId = message->parseLong();
		harvesterId = message->parseLong();
		resourceId = message->parseLong();
		quantity = message->parseInt();
		discard = message->parseByte();
		sequenceId = message->parseByte();
	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == nullptr)
			return;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(harvesterId);

		if (object == nullptr || !object->isHarvesterObject())
			return;
		
		HarvesterObject* harvester = cast<HarvesterObject*>( object.get());

		if (harvester == nullptr)
			return;

		try {
			Locker clocker(harvester, player);

			if (!harvester->isOnAdminList(player)) {
				return;
			}

			if (!harvester->isInRange(player, 20)) {
				player->sendSystemMessage("You are too far away to use that.");
				return;
			}

			harvester->emptyHopper(player, resourceId, quantity, discard, sequenceId);

		} catch (Exception& e) {
			player->error("unreported exception caught in EmptyHopperCallback::run");
		}
	}
};


#endif /* EMPTYHOPPERCALLBACK_H_ */
