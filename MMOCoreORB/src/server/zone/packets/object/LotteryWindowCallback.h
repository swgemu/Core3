/*
 * LotteryWindowCallback.h
 *
 *  Created on: Mar 16, 2015
 *      Author: swgemu
 */

#ifndef LOTTERYWINDOWCALLBACK_H_
#define LOTTERYWINDOWCALLBACK_H_


#include "server/zone/packets/MessageCallback.h"
#include "server/zone/objects/player/sessions/LootLotterySession.h"

class LotteryWindowCallback : public MessageCallback {
	uint64 containerID;

	uint32 listSize;
	Vector<uint64> lootIDs;

	ObjectControllerMessageCallback* objectControllerMain;

public:
	LotteryWindowCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()),
		containerID(0), listSize(0), objectControllerMain(objectControllerCallback) {
	}

	void parse(Message* msg) {
		msg->parseInt();
		containerID = msg->parseLong();
		listSize = msg->parseInt();

		for (int i = 0; i < listSize; i++)
			lootIDs.add(msg->parseLong());
	}

	void run() {
		//Get the player sending the loot selections.
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == NULL)
			return;

		//Get the corpse the lottery is for.
		ManagedReference<AiAgent*> corpse = server->getZoneServer()->getObject(containerID)->getParent().get().castTo<AiAgent*>();
		if (corpse == NULL)
			return;

		Locker locker(corpse);

		//Make sure there is an active lottery in progress.
		if (corpse->containsActiveSession(SessionFacadeType::LOOTLOTTERY)) {
			Reference<LootLotterySession*> session = corpse->getActiveSession(SessionFacadeType::LOOTLOTTERY).castTo<LootLotterySession*>();
			if (session == NULL || session->isLotteryFinished())
				return;

			if (!session->containsEligiblePlayer(player))
				return;

			//If player made no selections, remove them from the Lottery.
			if (listSize < 1) {
				session->removeEligiblePlayer(player);
				return;
			}

			//Create a new Lottery Ballot with the player's item selections.
			LootLotteryBallot* ballot = new LootLotteryBallot(player, lootIDs);
			session->addPlayerSelections(player, ballot);

		} else {
			return;
		}
	}
};


#endif /* LOTTERYWINDOWCALLBACK_H_ */
