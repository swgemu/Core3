/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef EMPTYMAILTARGETCOMMAND_H_
#define EMPTYMAILTARGETCOMMAND_H_

class EmptyMailTargetCommand : public QueueCommand {
public:

	EmptyMailTargetCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<CreatureObject* > targetCreature = server->getZoneServer()->getObject(creature->getTargetID()).castTo<CreatureObject*>();
		StringTokenizer args(arguments.toString());
		String firstName;

		if (args.hasMoreTokens()) {
			args.getStringToken(firstName);
			targetCreature = server->getZoneServer()->getPlayerManager()->getPlayer(firstName);
		}

		if (targetCreature == NULL || !targetCreature->isPlayerCreature()) {
			creature->sendSystemMessage("@player/player_utility:invalid_target"); // "Target for this command is invalid."
			return INVALIDTARGET;
		}

		PlayerObject* ghost = targetCreature->getPlayerObject();

		if (ghost == NULL)
			return GENERALERROR;

		uint64 selfID = creature->getObjectID();
		if (targetCreature->getObjectID() == selfID) {
			creature->sendSystemMessage("Please use the /emptyMail command to empty your own mailbox.");
			return GENERALERROR;
		}

		StringIdChatParameter emptyPass("ui_pm", "delete_all_mail_success"); // "You have successfully emptied the mailbox of %TT."
		emptyPass.setTT(targetCreature->getDisplayedName());

		Locker clocker(targetCreature, creature);

		ghost->deleteAllPersistentMessages();
		creature->sendSystemMessage(emptyPass);

		return SUCCESS;
	}

};

#endif //EMPTYMAILTARGETCOMMAND_H_
