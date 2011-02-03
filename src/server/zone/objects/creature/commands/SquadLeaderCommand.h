/*
 * SquadLeaderCommand.h
 *
 *  Created on: Aug 21, 2010
 *      Author: swgemu
 */

#ifndef SQUADLEADERCOMMAND_H_
#define SQUADLEADERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/chat/ChatManager.h"
#include "CombatQueueCommand.h"

class SquadLeaderCommand : public CombatQueueCommand {
protected:
	String action;
	uint32 actionCRC;

public:

	SquadLeaderCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

		combatSpam = "";
		action = "";
		actionCRC = 0;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		return SUCCESS;
	}

	bool checkGroupLeader(PlayerCreature* player, GroupObject* group) {
		if (player == NULL)
			return false;

		if (group == NULL) {
			player->sendSystemMessage("@error_message:not_grouped");
			return false;
		}

		if (group->getLeader() == NULL) {
			player->sendSystemMessage("@error_message:not_group_leader");
			return false;
		}

		if (group->getLeader() != player) {
			player->sendSystemMessage("@error_message:not_group_leader");
			return false;
		}

		return true;
	}

	bool shoutCommand(PlayerCreature* player, GroupObject* group) {
		if (player == NULL || group == NULL)
			return false;

		ManagedReference<ChatManager*> chatManager = server->getChatManager();
		if (chatManager == NULL)
			return false;

		if (!player->getPlayerObject()->hasCommandMessageString(actionCRC))
			return false;

		UnicodeString shout = player->getPlayerObject()->getCommandMessageString(actionCRC);
		chatManager->broadcastMessage(player, shout, 0, 0, 80);

		return true;
	}

	float calculateGroupModifier(GroupObject* group) {
		if (group == NULL)
			return 0;

		float modifier = (float) group->getGroupSize() / 10.0f;

		if (modifier < 1.0)
			modifier += 1.0f;

		return modifier;
	}

	bool inflictHAM(PlayerCreature* player, int health, int action, int mind) {
		if (player == NULL)
			return false;

		if (health < 0 || action < 0 || mind < 0)
			return false;

		if (player->getHAM(CreatureAttribute::ACTION) < action
				|| player->getHAM(CreatureAttribute::HEALTH) < health
				|| player->getHAM(CreatureAttribute::MIND) < mind)
			return false;

		if (health > 0)
			player->inflictDamage(player, CreatureAttribute::HEALTH, health, true);

		if (action > 0)
			player->inflictDamage(player, CreatureAttribute::ACTION, action, true);

		if (mind > 0)
			player->inflictDamage(player, CreatureAttribute::MIND, mind, true);

		return true;
	}

	void sendCombatSpam(PlayerCreature* player) {
		if (player == NULL)
			return;

		if (combatSpam == "")
			return;

		player->sendSystemMessage("@cbt_spam:" + combatSpam);
	}

	bool setCommandMessage(CreatureObject* creature, String message) {
		if (!creature->isPlayerCreature())
			return false;

		ManagedReference<PlayerCreature*> player = (PlayerCreature*) creature;
		ManagedReference<PlayerObject*> playerObject = player->getPlayerObject();

		if (message.isEmpty())
			playerObject->removeCommandMessageString(actionCRC);
		else
			playerObject->setCommandMessageString(actionCRC, message);

		return true;
	}
};

#endif /* SQUADLEADERCOMMAND_H_ */
