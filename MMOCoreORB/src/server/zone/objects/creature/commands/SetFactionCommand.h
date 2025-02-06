/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETFACTIONCOMMAND_H_
#define SETFACTIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/FactionStatus.h"

class SetFactionCommand : public QueueCommand {
public:
	SetFactionCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return INVALIDPARAMETERS;

		auto zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		ManagedReference<SceneObject*> obj = zoneServer->getObject(target);

		if (obj == nullptr || !obj->isTangibleObject())
			return INVALIDTARGET;

		TangibleObject* targetObject = obj->asTangibleObject();

		if (targetObject == nullptr) {
			creature->sendSystemMessage("Invalid target for setFaction command.");
			return GENERALERROR;
		}

		StringBuffer commandMsg;
		commandMsg << "SetFaction Command on Target: " << targetObject->getDisplayedName() << " ID: " << targetObject->getObjectID();
		creature->sendSystemMessage(commandMsg.toString());

		uint32 pvpStatus = targetObject->getPvpStatusBitmask();
		uint32 optionsBitmask = targetObject->getOptionsBitmask();

		uint32 targetFaction = targetObject->getFaction();
		int targetFactionStatus = targetObject->getFactionStatus();
		int targetRank = 0;

		CreatureObject* targetPlayer = nullptr;
		PlayerObject* targetGhost = nullptr;

		if (targetObject->isPlayerCreature()) {
			targetPlayer = targetObject->asCreatureObject();

			if (targetPlayer != nullptr) {
				targetRank = targetPlayer->getFactionRank();

				targetGhost = targetPlayer->getPlayerObject();
			}
		}

		//First, check if they passed a name with the command.
		UnicodeTokenizer tokenizer(arguments);
		tokenizer.setDelimeter(" ");

		// if no parameters are given, just send the flags
		if (!tokenizer.hasMoreTokens()) {
			StringBuffer msg;
			msg << "PvP Status Bitmask = " << String::valueOf(pvpStatus) << endl;
			msg << "Options Bitmask = " << String::valueOf(optionsBitmask) << endl;
			msg <<  "Faction = " << String::valueOf(targetFaction) << endl;
			msg << "Faction Status: " << String::valueOf(targetFactionStatus) << endl;
			msg << "Faction Rank: " << String::valueOf(targetRank) << endl;

			creature->sendSystemMessage(msg.toString());
			return SUCCESS;
		}

		String factionArgs;
		tokenizer.getStringToken(factionArgs);

		if (!tokenizer.hasMoreTokens()) {
			creature->sendSystemMessage("SYNTAX: /setfaction <name> [imperial | rebel | neutral] [onleave | covert | overt ] [rank]");
			return INVALIDPARAMETERS;
		}

		Locker clocker(targetObject, creature);

		if (factionArgs == "neutral") {
			targetFactionStatus = FactionStatus::ONLEAVE;
			targetFaction = Factions::FACTIONNEUTRAL;
			targetRank = 0;
		}else if (factionArgs == "imperial" || factionArgs == "rebel" || factionArgs == "hutt") {
			targetFaction = factionArgs.hashCode();
		}

		if (tokenizer.hasMoreTokens()) {
			//The next argument should be whether they are overt, onleave, or covert
			String status;
			tokenizer.getStringToken(status);

			if (status == "overt") {
				targetFactionStatus = FactionStatus::OVERT;
			} else if (status == "covert") {
				targetFactionStatus = FactionStatus::COVERT;
			} else if (status == "onleave") {
				targetFactionStatus = FactionStatus::ONLEAVE;
			}
		}

		if (tokenizer.hasMoreTokens()) {
			int rank = tokenizer.getIntToken();

			if (rank < 0)
				rank = 0;
			else if (rank > 15)
				rank = 15;

			targetRank = rank;
		}

		if (targetObject->isShipObject()) {
			auto targetShip = targetObject->asShipObject();

			if (targetShip != nullptr) {
				auto pilot = targetShip->getPilot();

				if (pilot != nullptr) {
					Locker pilotLock(pilot, creature);

					pilot->setFaction(targetFaction);
					pilot->setFactionStatus(targetFactionStatus);

					pilot->setFactionRank(targetRank, true);
					pilot->broadcastPvpStatusBitmask();

					StringBuffer newFaction;
					newFaction << "Your faction has been modified by " << creature->getDisplayedName();
					pilot->sendSystemMessage(newFaction.toString());
				}

				targetShip->setFactionStatus(targetFactionStatus);
				targetShip->setShipFactionString(factionArgs, true);
			}
		} else {
			targetObject->setFaction(targetFaction);
			targetObject->setFactionStatus(targetFactionStatus);

			if (targetPlayer != nullptr) {
				targetPlayer->setFactionRank(targetRank, false);

				StringBuffer newFaction;
				newFaction << "Your faction has been modified by " << creature->getDisplayedName();
				targetPlayer->sendSystemMessage(newFaction.toString());

				if (targetPlayer->isPilotingShip()) {
					auto targetRoot = targetPlayer->getRootParent();

					if (targetRoot != nullptr && targetRoot->isShipObject()) {
						auto targetShipParent = targetRoot->asShipObject();

						if (targetShipParent != nullptr) {
							Locker slocker(targetShipParent, creature);

							targetShipParent->setFactionStatus(targetFactionStatus);
							targetShipParent->setShipFactionString(factionArgs, true);

							targetShipParent->broadcastPvpStatusBitmask();
						}
					}
				}
			}
		}

		targetObject->broadcastPvpStatusBitmask();

		return SUCCESS;
	}
};

#endif //SETFACTIONCOMMAND_H_
