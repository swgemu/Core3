/*
 * GroupLootTask.h
 *
 *  Created on: March 8, 2015
 *      Author: Anakis
 */

#ifndef GROUPLOOTTASK_H_
#define GROUPLOOTTASK_H_

#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/managers/group/GroupManager.h"
#include "server/zone/objects/player/sessions/LootLotterySession.h"

class GroupLootTask : public Task {
	ManagedReference<GroupObject*> group;
	ManagedReference<CreatureObject*> player;
	ManagedReference<AiAgent*> corpse;

	bool lootAll;

public:
	GroupLootTask(GroupObject* gr, CreatureObject* pl, AiAgent* ai, bool all) {
		group = gr;
		player = pl;
		corpse = ai;
		lootAll = all;
	}

	void run() {
		if (group == NULL || player == NULL || corpse == NULL)
			return;

		Locker clocker(corpse);
		Locker gclocker(group, corpse);

		//Get the corpse's inventory.
		SceneObject* lootContainer = corpse->getSlottedObject("inventory");
		if (lootContainer == NULL)
			return;

		switch (group->getLootRule()) {
		case GroupManager::FREEFORALL:
			//GO GET 'EM, NINJA! YEEEHAW!!!
			break;
		case GroupManager::MASTERLOOTER:
			if (!group->checkMasterLooter(player)) {
				StringIdChatParameter masterOnly("group","master_only"); //"Only the Master Looter is allowed to loot!"
				masterOnly.setTO(group->getMasterLooterID());
				player->sendSystemMessage(masterOnly);
				return;
			}
			break;
		case GroupManager::LOTTERY:
			//Allow player to open corpse if there is nothing in it.
			if (lootContainer->getContainerObjectsSize() < 1)
				break;

			//Stop player looting corpse if lottery in progress, otherwise open corpse to player.
			if (corpse->containsActiveSession(SessionFacadeType::LOOTLOTTERY)) {
				ManagedReference<LootLotterySession*> session = cast<LootLotterySession*>(corpse->getActiveSession(SessionFacadeType::LOOTLOTTERY).get());
				if (session == NULL) {
					corpse->dropActiveSession(SessionFacadeType::LOOTLOTTERY);
				} else if (!session->isLotteryFinished()) {
					StringIdChatParameter msg("group","still_waiting"); //"Still waiting for your group members..."
					player->sendSystemMessage(msg);
					return;
				} else
					break; //Allow player to open the corpse.
			}

			//Corpse doesn't have an existing lottery, so check if we should make one.
			if (!membersInRange())
				break; //If no other group members in range, function as if free for all.

			gclocker.release();
			splitCredits();
			GroupManager::instance()->createLottery(group, corpse);
			return;
		case GroupManager::RANDOM:
			gclocker.release();
			splitCredits();
			if (lootContainer->getContainerObjectsSize() < 1) {
				StringIdChatParameter noItems("group", "corpse_empty");
				player->sendSystemMessage(noItems); //"This corpse has no items in its inventory."
				player->getZoneServer()->getPlayerManager()->rescheduleCorpseDestruction(player, corpse);
				return;
			}
			GroupManager::instance()->doRandomLoot(group, corpse);
			return;
		default:
			return;
		}

		//At this point, allow player to loot the corpse.
		if (lootAll) {
			gclocker.release();
			splitCredits();

			Locker lootAllLocker(player, corpse);
			player->getZoneServer()->getPlayerManager()->lootAll(player, corpse);
			lootAllLocker.release();

			Locker groupLocker(group, corpse);
			if (group->getLootRule() == GroupManager::MASTERLOOTER && lootContainer->getContainerObjectsSize() <= 0) {
				StringIdChatParameter msg("group","master_loot_all"); //"The master looter has looted all items from the corpse."
				group->sendSystemMessage(msg, false);
			}
		} else {
			gclocker.release();
			Locker lootlocker(player, corpse);
			corpse->notifyObservers(ObserverEventType::LOOTCREATURE, player, 0);
			lootContainer->openContainerTo(player);
		}

	}

	void splitCredits() {
		//Pre: Corpse is locked.
		//Post: Corpse is locked.

		int lootCredits = corpse->getCashCredits();

		if (lootCredits < 1)
			return;

		int luck = player->getSkillMod("force_luck");

		if (luck > 0)
			lootCredits += (lootCredits * luck) / 20;

		Locker clocker(group, corpse);

		//Determine eligible group members to give credits.
		Vector<CreatureObject*> payees;
		for (int i = 0; i < group->getGroupSize(); ++i) {
			ManagedReference<CreatureObject*> object = group->getGroupMember(i);
			if (object == NULL || !object->isPlayerCreature())
				continue;

			if (!object->isInRange(corpse, 128.f))
				continue;

			payees.add(object);
		}

		if (payees.size() == 0)
			return;

		//Send initial system message to the looter.
		StringIdChatParameter lootSelf("base_player", "prose_coin_loot"); //"You loot %DI credits from %TT."
		lootSelf.setDI(lootCredits);
		lootSelf.setTT(corpse->getObjectID());
		player->sendSystemMessage(lootSelf);

		//Send initial system message to everyone in group except the looter.
		StringIdChatParameter lootMember("group", "notify_coin_loot_int"); //"[GROUP] %TU looted %DI credits from %TT."
		lootMember.setTU(player->getDisplayedName());
		lootMember.setDI(lootCredits);
		lootMember.setTT(corpse->getDisplayedName());
		group->sendSystemMessage(lootMember, player);

		clocker.release();

		//Figure out how many credits each member gets.
		int memberBaseCredits = lootCredits / payees.size();
		int memberOddCredits = lootCredits % payees.size();

		//Create one cash payout per payee.
		Vector<int> cashPayouts;
		for (int i = 0; i < payees.size(); ++i) {
			int payout = memberBaseCredits;
			if (memberOddCredits > 0) {
				payout += 1;
				memberOddCredits -= 1;
			}
			cashPayouts.add(payout);
		}

		//Hand out the payouts randomly since some may be larger.
		for (int i = 0; i < payees.size(); ++i) {
			CreatureObject* payee = payees.get(i);
			int random = System::random(cashPayouts.size() - 1);
			int payout = cashPayouts.get(random);
			cashPayouts.remove(random);

			Locker plocker(payee, corpse);

			payee->addCashCredits(payout, true);

			//Send credit split system message.
			if (payee == player) {
				StringIdChatParameter splitLooter("group", "prose_split_coins_self"); //"[GROUP] You split %TU credits and receive %TT credits as your share."
				splitLooter.setTU(String::valueOf(lootCredits));
				splitLooter.setTT(String::valueOf(payout));
				player->sendSystemMessage(splitLooter);
			} else {
				StringIdChatParameter splitMember("group", "prose_split"); //"[GROUP] You receive %DI credits as your share."
				splitMember.setDI(payout);
				payee->sendSystemMessage(splitMember);
			}
		}

		corpse->setCashCredits(0);

	}

	bool membersInRange() {
		for (int i = 0; i < group->getGroupSize(); ++i) {
			ManagedReference<CreatureObject*> member = group->getGroupMember(i);
			if (member == NULL || !member->isPlayerCreature())
				continue;

			if (member != player && member->isInRange(corpse, 128.f))
				return true;
		}

		return false;
	}

};

#endif /* GROUPLOOTTASK_H_ */
