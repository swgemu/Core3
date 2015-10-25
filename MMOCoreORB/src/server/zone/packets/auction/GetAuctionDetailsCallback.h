/*
 * GetAuctionDetailsCallback.h
 *
 *  Created on: 13/03/2010
 *      Author: victor
 */

#ifndef GETAUCTIONDETAILSCALLBACK
#define GETAUCTIONDETAILSCALLBACK

#include "../MessageCallback.h"
#include "server/zone/managers/auction/AuctionManager.h"


class GetAuctionDetailsCallback : public MessageCallback {
	uint64 objectid;

public:
	GetAuctionDetailsCallback(ZoneClientSession* client, ZoneProcessServer* server) :
			MessageCallback(client, server), objectid(0) {

	}

	void parse(Message* message) {
		objectid = message->parseLong();
	}

	void run() {
		ManagedReference<SceneObject*> scene = client->getPlayer();

		if (scene == NULL)
			return;

		CreatureObject* player = cast<CreatureObject*>(scene.get());

		if (player == NULL)
			return;

		AuctionManager* auctionManager = server->getZoneServer()->getAuctionManager();
		auctionManager->getItemAttributes(player, objectid);
	}

};

#endif

