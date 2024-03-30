/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETBIOGRAPHYADMINCOMMAND_H_
#define SETBIOGRAPHYADMINCOMMAND_H_

class SetBiographyAdminCommand : public QueueCommand {
public:
	SetBiographyAdminCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		auto ghost = creature->getPlayerObject();

		if (ghost == nullptr || !ghost->isPrivileged()) {
			return GENERALERROR;
		}

		StringTokenizer args(arguments.toString());

		// Check for more arguments
		if (!args.hasMoreTokens()) {
			creature->sendSystemMessage("Invalid target. Syntax: Target the player and \"/setBiographyAdmin \"New biography Content\" or with the player not in range \"/setBiographyAdmin playerName \"New biography Content\"");
			return INVALIDPARAMETERS;
		}

		auto zoneServer = server->getZoneServer();

		if (zoneServer == nullptr) {
			return GENERALERROR;
		}

		ManagedReference<CreatureObject*> targetPlayer = nullptr;

		if (target > 0) {
			auto targetObject = zoneServer->getObject(target, false);

			if (targetObject == nullptr || !targetObject->isPlayerCreature()) {
				creature->sendSystemMessage("Invalid target. Syntax: Target the player and \"/setBiographyAdmin \"New biography Content\" or with the player not in range \"/setBiographyAdmin playerName \"New biography Content\"");
				return INVALIDTARGET;
			}

			targetPlayer = targetObject->asCreatureObject();
		} else {
			auto playerManager = zoneServer->getPlayerManager();

			if (playerManager == nullptr) {
				return GENERALERROR;
			}

			String playerName = args.getStringToken();

			targetPlayer = playerManager->getPlayer(playerName);
		}

		if (targetPlayer == nullptr) {
			creature->sendSystemMessage("Invalid target. Syntax: Target the player and \"/setBiographyAdmin \"New biography Content\" or with the player not in range \"/setBiographyAdmin playerName \"New biography Content\"");
			return INVALIDTARGET;
		}

		auto targetGhost = targetPlayer->getPlayerObject();

		if (targetGhost == nullptr) {
			return GENERALERROR;
		}

		Locker clock(targetPlayer, creature);

		auto objectController = zoneServer->getObjectController();

		if (objectController == nullptr) {
			return GENERALERROR;
		}

		// Log the command use
		objectController->logAdminCommand(creature, this, targetPlayer->getObjectID(), arguments);

		// Get new Bio string
		String newBio = args.getRemainingString();

		// Set the target players biogrpahy
		targetGhost->setBiography(newBio);

		auto newBioMsg = new Biography(targetPlayer, targetPlayer);

		if (newBioMsg != nullptr) {
			targetPlayer->sendMessage(newBioMsg);
		}

		// Confirm output to privileged player using the command.
		StringBuffer output;
		output << "You succesfully set " << targetPlayer->getFirstName() << "'s Biography to: " << newBio;

		creature->sendSystemMessage(output.toString());

		return SUCCESS;
	}
};

#endif // SETBIOGRAPHYADMINCOMMAND_H_
