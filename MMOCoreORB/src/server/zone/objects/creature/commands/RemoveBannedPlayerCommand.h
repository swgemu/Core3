/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REMOVEBANNEDPLAYERCOMMAND_H_
#define REMOVEBANNEDPLAYERCOMMAND_H_

class RemoveBannedPlayerCommand : public QueueCommand {
public:

	RemoveBannedPlayerCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<PlayerObject*> adminGhost = creature->getPlayerObject();

		if (adminGhost == NULL)
			return GENERALERROR;

		ManagedReference<CreatureObject*> targetCreature = NULL;
		ManagedReference<PlayerObject*> ghost = NULL;
		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		StringTokenizer args(arguments.toString());

		if (args.hasMoreTokens()) {
			String character;
			args.getStringToken(character);

			targetCreature = playerManager->getPlayer(character);

		} else {

			targetCreature =
					server->getZoneServer()->getObject(target).castTo<CreatureObject*>();

		}

		if (targetCreature == NULL || !targetCreature->isPlayerCreature())
			return INVALIDTARGET;

		ghost = targetCreature->getPlayerObject();

		if (ghost == NULL) {
			creature->sendSystemMessage("Player Ghost not found");
			return SUCCESS;
		}

		StringBuffer banReason;

		while (args.hasMoreTokens()) {
			String reason;
			args.getStringToken(reason);
			banReason << reason << " ";
		}

		if (banReason.toString().isEmpty()) {
			creature->sendSystemMessage("You must provide a reason for unbanning");
			return GENERALERROR;
		}

		ManagedReference<Account*> account = ghost->getAccount();
		if (account == NULL) {
			creature->sendSystemMessage("Account is NULL");
			return GENERALERROR;
		}

		Locker alocker(account);

		CharacterListEntry* entry = account->getCharacterBan(server->getZoneServer()->getGalaxyID(), targetCreature->getFirstName());

		if (entry == NULL) {
			creature->sendSystemMessage("Error getting CharacterListEntry");
			return GENERALERROR;
		}

		StringBuffer reason;
		reason << entry->getBanAdmin() << "=" << entry->getBanReason() << "|" << banReason.toString();

		playerManager->unbanCharacter(adminGhost, account, targetCreature->getFirstName(), entry->getGalaxyID(), banReason.toString());
		creature->sendSystemMessage(targetCreature->getFirstName() + " is unbanned");

		return SUCCESS;
	}

};

#endif //REMOVEBANNEDPLAYERCOMMAND_H_
