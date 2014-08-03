/*
 * ReplaceFlashSpeederSuiCallback.h
 *
 *  Created on: 8/3/2014
 *      Author: Klivian
 */

#ifndef REPLACEFLASHSPEEDERSUICALLBACK_H_
#define REPLACEFLASHSPEEDERSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"

class ReplaceFlashSpeederSuiCallback : public SuiCallback {

public:

	ReplaceFlashSpeederSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {

		if( cancelPressed )
			return;

		// Player must have 20k credits
		if( player->getBankCredits() < 20000 ){
			player->sendSystemMessage( "@veteran:flash_speeder_no_credits" ); // "You do not have enough credits to receive a replacement."
			return;
		}

		// Generate new deed
		SceneObject* inventory = player->getSlottedObject("inventory");
		String speederDeedTemplate = "object/tangible/deed/vehicle_deed/speederbike_flash_deed.iff";
		Reference<SceneObject*> speederDeed = server->createObject(speederDeedTemplate.hashCode(), 1);
		if( speederDeed == NULL || inventory == NULL ){
			player->sendSystemMessage( "Error generating replacement flash speeder deed" );
			return;
		}

		// Transfer to player
		if( !inventory->transferObject(speederDeed, -1, false, true) ){ // Allow overflow
			player->sendSystemMessage( "Error generating replacement flash speeder deed" );
			return;
		}

		inventory->broadcastObject(speederDeed, true);

		// Deduct replacement cost
		player->setBankCredits(player->getBankCredits() - 20000, true);

		player->sendSystemMessage( "A deed for a new Flash Speeder has been placed in your inventory at a cost of 20,000cr");

	}
};

#endif /* REPLACEFLASHSPEEDERSUICALLBACK_H_ */
