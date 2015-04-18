/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DELEGATEFACTIONPOINTSCOMMAND_H_
#define DELEGATEFACTIONPOINTSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/faction/FactionManager.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"
#include "server/zone/objects/player/sui/callbacks/DelegateSuiCallback.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "QueueCommand.h"

class DelegateFactionPointsCommand : public QueueCommand {
public:

	DelegateFactionPointsCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}

	static int doDelegate(CreatureObject* creature, CreatureObject* targetPlayer, uint32 tipAmount) {
		Locker clocker(targetPlayer, creature);

		uint32 currentFaction = creature->getFaction();

		if (currentFaction == 0) {
			creature->sendSystemMessage("@base_player:must_be_declared");
			return GENERALERROR;
		}

		String faction;

		if (creature->isImperial()) {
			faction = "imperial";
		} else
			faction = "rebel";

		PlayerObject* ownerPlayerObject = creature->getPlayerObject();
		PlayerObject* targetPlayerObject = targetPlayer->getPlayerObject();

		int delegateRatioFrom = FactionManager::instance()->getRankDelegateRatioFrom(creature->getFactionRank());
		int delegateRatioTo = FactionManager::instance()->getRankDelegateRatioTo(creature->getFactionRank());

		int currentFactionPoints = ownerPlayerObject->getFactionStanding(faction);

		float ratio = (float) delegateRatioFrom / (float)delegateRatioTo;

		uint32 charge = ceil((float)tipAmount * ratio);

		if (ownerPlayerObject->getFactionStanding(faction) < charge + 200) {
			//not sure of the message
			StringIdChatParameter param("faction_recruiter", "not_enough_standing_spend");
			param.setDI(200);
			param.setTO(faction);

			creature->sendSystemMessage(param);
			return GENERALERROR;
		}

		targetPlayerObject->increaseFactionStanding(faction, tipAmount);
		ownerPlayerObject->decreaseFactionStanding(faction, charge);

		return SUCCESS;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		StringTokenizer tokenizer(arguments.toString());
		tokenizer.setDelimeter(" ");

		uint32 tipAmount = 0;

		if (target == 0)
			return INVALIDTARGET;

		//The player has SOMETHING targetted.
		//Lets first check if its a player, cause if it is we can skip some stuff.
		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL)
			return INVALIDTARGET;

		CreatureObject* targetCreature = dynamic_cast<CreatureObject*>(object.get());

		if (targetCreature == NULL)
			return INVALIDTARGET;

		Locker clocker(targetCreature, creature);

		PlayerObject* targetPlayerObject = targetCreature->getPlayerObject();

		if (targetPlayerObject == NULL)
			return INVALIDTARGET;

		PlayerObject* ownerPlayerObject = creature->getPlayerObject();

		uint32 currentFaction = creature->getFaction();

		if (currentFaction == 0) {
			creature->sendSystemMessage("@base_player:must_be_declared");
			return GENERALERROR;
		}

		String faction;

		if (creature->isImperial()) {
			faction = "imperial";
		} else
			faction = "rebel";

		int delegateRatioFrom = FactionManager::instance()->getRankDelegateRatioFrom(creature->getFactionRank());
		int delegateRatioTo = FactionManager::instance()->getRankDelegateRatioTo(creature->getFactionRank());

		int currentFactionPoints = ownerPlayerObject->getFactionStanding(faction);

		if (currentFactionPoints < 200) {
			StringIdChatParameter param("faction_recruiter", "not_enough_standing_spend");
			param.setDI(200);
			param.setTO(faction);

			creature->sendSystemMessage(param);
			return GENERALERROR;
		}

		if (!tokenizer.hasMoreTokens()) {
			ManagedReference<SuiTransferBox*> sui = new SuiTransferBox(creature, SuiWindowType::DELEGATE_TRANSFER);
			sui->setCallback(new DelegateSuiCallback(server->getZoneServer()));
			sui->setPromptTitle("@player_structure:select_amount"); //Select Amount
			sui->setPromptText("Current faction points:" + String::valueOf(ownerPlayerObject->getFactionStanding(faction)));
			sui->addFrom("Total amount", String::valueOf(currentFactionPoints), String::valueOf(currentFactionPoints), String::valueOf(delegateRatioFrom));
			sui->addTo("Delegate amount", "0", "0", String::valueOf(delegateRatioTo));
			sui->setUsingObject(targetCreature);
			sui->setForceCloseDistance(15.f);

			ownerPlayerObject->addSuiBox(sui);
			creature->sendMessage(sui->generateMessage());

			return SUCCESS;
		}

		tipAmount = (uint32) tokenizer.getIntToken();

		if (tipAmount == 0)
			return GENERALERROR;

		return doDelegate(creature, targetCreature, tipAmount);
	}

};

#endif //DELEGATEFACTIONPOINTSCOMMAND_H_
