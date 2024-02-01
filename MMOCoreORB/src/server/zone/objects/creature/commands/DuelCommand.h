/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DUELCOMMAND_H_
#define DUELCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/combat/CombatManager.h"

class DuelCommand : public QueueCommand {
public:
	DuelCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		auto zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		auto targetObject = server->getZoneServer()->getObject(target);

		if (targetObject == nullptr || !targetObject->isPlayerCreature() || targetObject == creature)
			return INVALIDTARGET;

		// Check for no duel area
		SortedVector<ManagedReference<ActiveArea*> >* areas = creature->getActiveAreas();

		if (areas != nullptr) {
			for (int i = 0; i < areas->size(); i++) {
				ActiveArea* area = areas->get(i);

				if (area == nullptr || !area->isNoDuelArea())
					continue;

				creature->sendSystemMessage("@duel:not_here"); // You cannot duel here.
				return GENERALERROR;
			}
		}

		if (!checkDistance(creature, targetObject, 25.0f))
			return TOOFAR;

		auto combatManager = CombatManager::instance();

		if (combatManager == nullptr)
			return GENERALERROR;

		auto targetPlayer = targetObject->asCreatureObject();

		if (targetPlayer == nullptr)
			return GENERALERROR;

		if (combatManager->areInDuel(creature, targetPlayer)) {
			StringIdChatParameter stringId("duel", "already_dueling");
			stringId.setTT(targetPlayer->getObjectID());
			creature->sendSystemMessage(stringId);

			return GENERALERROR;
		}

		auto ghost = targetPlayer->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		if (ghost->isIgnoring(creature->getFirstName()))
			return GENERALERROR;


		combatManager->requestDuel(creature, targetPlayer);

		return SUCCESS;
	}
};

#endif // DUELCOMMAND_H_
