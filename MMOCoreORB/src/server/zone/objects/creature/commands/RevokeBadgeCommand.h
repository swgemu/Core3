/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REVOKEBADGECOMMAND_H_
#define REVOKEBADGECOMMAND_H_

class RevokeBadgeCommand : public QueueCommand {
public:

	RevokeBadgeCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (arguments.isEmpty() && target == 0) {
			creature->sendSystemMessage("Syntax: /revokeBadge badgeID");
			return GENERALERROR;
		}

		ZoneServer* zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		ManagedReference<SceneObject*> targetObject = zoneServer->getObject(target);

		if (targetObject == nullptr || !targetObject->isPlayerCreature())
			return GENERALERROR;

		StringTokenizer args(arguments.toString());

		int badgeId = args.getIntToken();

		if (badgeId <= 0) {
			creature->sendSystemMessage("Improper Badge ID.");
			return GENERALERROR;
		}

		ManagedReference<CreatureObject*> player = targetObject->asCreatureObject();

		if (player == nullptr)
			return GENERALERROR;

		PlayerObject* ghost = player->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		Locker clock(ghost, creature);

		ghost->revokeBadge(badgeId);

		player->sendSystemMessage("Badge #" + String::valueOf(badgeId) + " has been revoked by " + creature->getDisplayedName() + ".");
		creature->sendSystemMessage("Revoked badge " + String::valueOf(badgeId) + " from " + player->getDisplayedName() + ".");

		return SUCCESS;
	}

};

#endif //REVOKEBADGECOMMAND_H_
