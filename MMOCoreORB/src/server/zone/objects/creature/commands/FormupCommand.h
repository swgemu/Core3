/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORMUPCOMMAND_H_
#define FORMUPCOMMAND_H_

#include "SquadLeaderCommand.h"

class FormupCommand : public SquadLeaderCommand {
public:

	FormupCommand(const String& name, ZoneProcessServer* server)
		: SquadLeaderCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(creature);

		if (player == NULL)
			return GENERALERROR;

		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		if (ghost == NULL)
			return GENERALERROR;

		ManagedReference<GroupObject*> group = player->getGroup();

		if (!checkGroupLeader(player, group))
			return GENERALERROR;

		int hamCost = (int) (50.0f * calculateGroupModifier(group));

		int healthCost = creature->calculateCostAdjustment(CreatureAttribute::STRENGTH, hamCost);
		int actionCost = creature->calculateCostAdjustment(CreatureAttribute::QUICKNESS, hamCost);
		int mindCost = creature->calculateCostAdjustment(CreatureAttribute::FOCUS, hamCost);

		if (!inflictHAM(player, healthCost, actionCost, mindCost))
			return GENERALERROR;

//		shoutCommand(player, group);

		if (!doFormUp(player, group))
			return GENERALERROR;

		if (!ghost->getCommandMessageString(STRING_HASHCODE("formup")).isEmpty() && creature->checkCooldownRecovery("command_message")) {
			UnicodeString shout(ghost->getCommandMessageString(STRING_HASHCODE("formup")));
 	 	 	server->getChatManager()->broadcastChatMessage(player, shout, 0, 80, player->getMoodID(), 0, ghost->getLanguageID());
 	 	 	creature->updateCooldownTimer("command_message", 30 * 1000);
		}

		return SUCCESS;
	}

	bool doFormUp(CreatureObject* leader, GroupObject* group) const {
		if (leader == NULL || group == NULL)
			return false;

		for (int i = 0; i < group->getGroupSize(); i++) {

			ManagedReference<CreatureObject*> member = group->getGroupMember(i);

			if (member == NULL || !member->isPlayerCreature())
				continue;

			if (!isValidGroupAbilityTarget(leader, member, false))
				continue;

			Locker clocker(member, leader);

			sendCombatSpam(member);

			if (member->isDizzied())
				member->removeStateBuff(CreatureState::DIZZY);
					
			if (member->isStunned())
				member->removeStateBuff(CreatureState::STUNNED);

			checkForTef(leader, member);
		}

		return true;
	}

};

#endif //FORMUPCOMMAND_H_
