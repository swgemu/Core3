/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LISTACTIVEQUESTSCOMMAND_H_
#define LISTACTIVEQUESTSCOMMAND_H_

class ListActiveQuestsCommand : public QueueCommand {
public:

	ListActiveQuestsCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		PlayerObject* ghost = creature->getPlayerObject();

		if (ghost == NULL)
			return GENERALERROR;

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		ManagedReference<CreatureObject*> targetObj = NULL;

		if (creature->getTargetID() != 0) {
			targetObj = server->getZoneServer()->getObject(creature->getTargetID()).castTo<CreatureObject*>();
		} else if (target != 0) {
			targetObj = server->getZoneServer()->getObject(target).castTo<CreatureObject*>();
		} else {
			StringTokenizer args(arguments.toString());

			if(!args.hasMoreTokens())
				return GENERALERROR;

			String targetName = "";
			args.getStringToken(targetName);

			targetObj = playerManager->getPlayer(targetName);
		}

		if (targetObj == NULL)
			return INVALIDTARGET;

		if (!targetObj->isPlayerCreature())
			return INVALIDTARGET;

		PlayerObject* targetGhost = targetObj->getPlayerObject();

		if (targetGhost == NULL)
			return INVALIDTARGET;

		ManagedReference<SuiListBox*> box = new SuiListBox(creature, 0);
		box->setPromptTitle("Active Quests");
		box->setPromptText("List of active quests for " + targetObj->getFirstName());
		box->setForceCloseDisabled();

		for (int i = 0; i < playerManager->getTotalPlayerQuests(); i++) {
			if (targetGhost->hasActiveQuestBitSet(i)) {
				QuestInfo* info = playerManager->getQuestInfo(i);
				box->addMenuItem(info->getJournalSummary() + " (" + info->getQuestName() + ")");
			}
		}

		ghost->addSuiBox(box);
		creature->sendMessage(box->generateMessage());

		return SUCCESS;
	}

};

#endif //LISTACTIVEQUESTSCOMMAND_H_
