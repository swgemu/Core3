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

	static const int FLASH_SPEEDER_COST = 20000;

	ReplaceFlashSpeederSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {

		if( cancelPressed )
			return;

		// Player must have enough credits
		if( player->getCashCredits() + player->getBankCredits() < FLASH_SPEEDER_COST ){
			player->sendSystemMessage( "@veteran:flash_speeder_no_credits" ); // "You do not have enough credits to receive a replacement."
			return;
		}

		// Generate new deed
		SceneObject* inventory = player->getSlottedObject("inventory");
		String speederDeedTemplate = "object/tangible/deed/vehicle_deed/speederbike_flash_deed.iff";
		Reference<SceneObject*> speederDeed = server->createObject(speederDeedTemplate.hashCode(), 1);
		if( speederDeed == NULL || inventory == NULL ){
			player->sendSystemMessage( "@veteran:flash_speeder_grant_failed" ); // "Flash Speeder deed grant has failed. This could be the result of being ineligible or not having enough credits to pay for the replacement fee."
			return;
		}

		// Transfer to player
		if( !inventory->transferObject(speederDeed, -1, false, false) ){ // No overflow
			player->sendSystemMessage( "@veteran:flash_speeder_no_inv_space" ); // "You do not have any inventory space remaining for the Flash Speeder deed."
			return;
		}

		inventory->broadcastObject(speederDeed, true);

		// Deduct replacement cost
		if( player->getCashCredits() >= FLASH_SPEEDER_COST ){
			player->setCashCredits(player->getCashCredits() - FLASH_SPEEDER_COST, true);
		}
		else{
			int fromBank = FLASH_SPEEDER_COST - player->getCashCredits();
			player->setCashCredits(0, true);
			player->setBankCredits(player->getBankCredits() - fromBank, true);
		}

		player->sendSystemMessage( "@veteran:flash_speeder_granted");  // "A Flash Speeder deed has been placed in your inventory."

	}
};

#endif /* REPLACEFLASHSPEEDERSUICALLBACK_H_ */
