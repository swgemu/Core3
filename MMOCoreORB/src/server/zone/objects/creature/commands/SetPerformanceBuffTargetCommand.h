/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETPERFORMANCEBUFFTARGETCOMMAND_H_
#define SETPERFORMANCEBUFFTARGETCOMMAND_H_

class SetPerformanceBuffTargetCommand : public QueueCommand {
public:

	SetPerformanceBuffTargetCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if(!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		ZoneServer* zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		ManagedReference<SceneObject*> targetObject = zoneServer->getObject(target);

		if (targetObject == nullptr || targetObject == creature || !targetObject->isPlayerCreature()) {
			creature->sendSystemMessage("@performance:buff_invalid_target_self");
			return GENERALERROR;
		}

		if (!CollisionManager::checkLineOfSight(targetObject, creature)) {
			creature->sendSystemMessage("@healing:no_line_of_sight"); // You cannot see your target.
			return GENERALERROR;
		}

		CreatureObject* targetCreature = targetObject->asCreatureObject();

		if (targetCreature == nullptr)
			return GENERALERROR;

		StringIdChatParameter selfMessage;
		StringIdChatParameter otherMessage;
		selfMessage.setStringId("performance", "buff_set_target_self");
		selfMessage.setTT(targetCreature->getDisplayedName());

		otherMessage.setStringId("performance", "buff_set_target_other");
		otherMessage.setTU(creature->getDisplayedName());
		creature->sendSystemMessage(selfMessage);
		targetCreature->sendSystemMessage(otherMessage);

		ghost->setPerformanceBuffTarget(target);
		return SUCCESS;
	}

};

#endif //SETPERFORMANCEBUFFTARGETCOMMAND_H_
