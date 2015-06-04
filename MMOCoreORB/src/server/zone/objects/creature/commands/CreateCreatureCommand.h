/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATECREATURECOMMAND_H_
#define CREATECREATURECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/AiMap.h"


class CreateCreatureCommand : public QueueCommand {
public:

	CreateCreatureCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		Zone* zone = creature->getZone();

		if (zone == NULL)
			return GENERALERROR;

		float posX = creature->getPositionX(), posY = creature->getPositionY(), posZ = creature->getPositionZ();
		uint64 parID = creature->getParentID();

		String objName = "", tempName = "object/mobile/boba_fett.iff";
		bool baby = false;
		String aiTemplate = "";
		bool event = false;
		int level = -1;

		if (!arguments.isEmpty()) {
			UnicodeTokenizer tokenizer(arguments);
			tokenizer.setDelimeter(" ");

			if (tokenizer.hasMoreTokens())
				tokenizer.getStringToken(tempName);

			if (!tempName.isEmpty() && tempName == "checkThreads") {
				creature->sendSystemMessage("Current number of AiMoveEvents: " + String::valueOf(AiMap::instance()->activeMoveEvents.get()));
				creature->sendSystemMessage("Current number of scheduled AiMoveEvents: " + String::valueOf(AiMap::instance()->scheduledMoveEvents.get()));
				creature->sendSystemMessage("Current number of scheduled AiMoveEvents with followObject: " + String::valueOf(AiMap::instance()->moveEventsWithFollowObject.get()));
				creature->sendSystemMessage("Current number of scheduled AiMoveEvents retreating: " + String::valueOf(AiMap::instance()->moveEventsRetreating.get()));
				creature->sendSystemMessage("Current number of AiAwarenessEvents: " + String::valueOf(AiMap::instance()->activeAwarenessEvents.get()));
				creature->sendSystemMessage("Current number of scheduled AiAwarenessEvents: " + String::valueOf(AiMap::instance()->scheduledAwarenessEvents.get()));
				creature->sendSystemMessage("Current number of AiRecoveryEvents: " + String::valueOf(AiMap::instance()->activeRecoveryEvents.get()));
				creature->sendSystemMessage("Current number of AiWaitEvents: " + String::valueOf(AiMap::instance()->activeWaitEvents.get()));
				return SUCCESS;
			}

			if (tokenizer.hasMoreTokens())
				tokenizer.getStringToken(objName);

			if (!objName.isEmpty() && objName == "baby")
				baby = true;

			if (!objName.isEmpty() && objName == "event") {
				event = true;

				if (tokenizer.hasMoreTokens()) {
					level = tokenizer.getIntToken();

					if (level > 500)
						level = 500;
				}
			}

			if (!objName.isEmpty() && objName.indexOf("object") == -1 && !baby && !event) {
				if (objName.length() < 6)
					posX = Float::valueOf(objName);
				else
					aiTemplate = objName;

				objName = "";
			} else if (tokenizer.hasMoreTokens()) {
					posX = tokenizer.getFloatToken();
			}

			if (tokenizer.hasMoreTokens())
				posZ = tokenizer.getFloatToken();

			if (tokenizer.hasMoreTokens())
				posY = tokenizer.getFloatToken();

			if (tokenizer.hasMoreTokens()) {
				int planet = tokenizer.getIntToken();
				zone = creature->getZoneServer()->getZone(planet);
			}

			if (tokenizer.hasMoreTokens())
				parID = tokenizer.getLongToken();
		} else {
			creature->sendSystemMessage("Usage: /createCreature <template> [object template | ai template | baby | event [level] ] [X] [Z] [Y] [planet] [cellID]");
			return GENERALERROR;
		}

		CreatureManager* creatureManager = zone->getCreatureManager();

		uint32 templ = tempName.hashCode();
		uint32 objTempl = objName.length() > 0 ? objName.hashCode() : 0;

		AiAgent* npc = NULL;
		if (baby)
			npc = cast<AiAgent*>(creatureManager->spawnCreatureAsBaby(templ, posX, posZ, posY, parID));
		else if (event)
			npc = cast<AiAgent*>(creatureManager->spawnCreatureAsEventMob(templ, level, posX, posZ, posY, parID));
		else if (tempName.indexOf(".iff") != -1)
			npc = cast<AiAgent*>(creatureManager->spawnCreatureWithAi(templ, posX, posZ, posY, parID));
		else {
			npc = cast<AiAgent*>(creatureManager->spawnCreature(templ, objTempl, posX, posZ, posY, parID));
			if (npc != NULL)
				npc->activateLoad("");
		}

		if (baby && npc == NULL) {
			creature->sendSystemMessage("You cannot spawn " + tempName + " as a baby.");
			return GENERALERROR;
		} else if (npc == NULL) {
			creature->sendSystemMessage("could not spawn " + arguments.toString());
			return GENERALERROR;
		}

		if (!aiTemplate.isEmpty()) {
			npc->activateLoad(aiTemplate);
		}

		npc->updateDirection(Math::deg2rad(creature->getDirectionAngle()));

		return SUCCESS;
	}

};

#endif //CREATECREATURECOMMAND_H_
