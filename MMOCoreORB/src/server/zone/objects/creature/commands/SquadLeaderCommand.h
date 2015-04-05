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
#include "server/zone/managers/stringid/StringIdManager.h"
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

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

	bool checkGroupLeader(CreatureObject* player, GroupObject* group) const {
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

	bool isValidGroupAbilityTarget(CreatureObject* leader, CreatureObject* target) const {
		if (!target->isPlayerCreature())
			return false;

		if (target == leader)
			return true;

		if (target->getParentRecursively(SceneObjectType::BUILDING) != leader->getParentRecursively(SceneObjectType::BUILDING))
			return false;

		PlayerObject* leaderGhost = leader->getPlayerObject();
		PlayerObject* targetGhost = target->getPlayerObject();

		if (leaderGhost == NULL || targetGhost == NULL)
			return false;

		if (targetGhost->getFactionStatus() == FactionStatus::CHANGINGSTATUS || leaderGhost->getFactionStatus() == FactionStatus::CHANGINGSTATUS)
			return false;

		if (leader->getFaction() != 0 && target->getFaction() != 0) {
			if (leader->getFaction() != target->getFaction() && targetGhost->getFactionStatus() != FactionStatus::ONLEAVE)
				return false;

			if (leader->getFaction() == target->getFaction() && leaderGhost->getFactionStatus() == FactionStatus::COVERT && targetGhost->getFactionStatus() == FactionStatus::OVERT)
				return false;

			if (leaderGhost->getFactionStatus() == FactionStatus::ONLEAVE && targetGhost->getFactionStatus() != FactionStatus::ONLEAVE)
				return false;
		}

		if (leader->getFaction() == 0 && target->getFaction() != 0 && targetGhost->getFactionStatus() != FactionStatus::ONLEAVE)
			return false;

		return true;
	}

/*	bool shoutCommand(CreatureObject* player, GroupObject* group) {
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
*/
	float calculateGroupModifier(GroupObject* group) const {
		if (group == NULL)
			return 0;

		float modifier = (float)(group->getGroupSize()) / 10.0f;
			if(modifier < 1.0)
				modifier += 1.0f;

			return modifier;
    }
    bool inflictHAM(CreatureObject* player, int health, int action, int mind) const {
        if (player == NULL)
			return false;
        if(health < 0 || action < 0 || mind < 0)
            return false;

        if(player->getHAM(CreatureAttribute::ACTION) <= action || player->getHAM(CreatureAttribute::HEALTH) <= health || player->getHAM(CreatureAttribute::MIND) <= mind)
            return false;

        if(health > 0)
            player->inflictDamage(player, CreatureAttribute::HEALTH, health, true);

        if(action > 0)
            player->inflictDamage(player, CreatureAttribute::ACTION, action, true);

        if(mind > 0)
            player->inflictDamage(player, CreatureAttribute::MIND, mind, true);

        return true;
    }
	
    void sendCombatSpam(CreatureObject* player) const {
        if (player == NULL)
			return;
        if(combatSpam == "")
            return;

        player->sendSystemMessage("@cbt_spam:" + combatSpam);
    }
	
/*    bool setCommandMessage(CreatureObject* creature, String message){
        if(!creature->isPlayerCreature())
            return false;
			
        ManagedReference<CreatureObject*> player = (creature);
        ManagedReference<PlayerObject*> playerObject = player->getPlayerObject();	
			
		if (message.length()>128){
			player->sendSystemMessage("Your message can only be up to 128 characters long.");
			return false;
		}
		if (NameManager::instance()->isProfane(message)){
			player->sendSystemMessage("Your message has failed the profanity filter.");
			return false;				
		}
		
        if(message.isEmpty()) {
            playerObject->removeCommandMessageString(actionCRC);
			player->sendSystemMessage("Your message has been removed.");
		} else {
            playerObject->setCommandMessageString(actionCRC, message);
			player->sendSystemMessage("Your message was set to :-\n" + message);
		}		
		
        return true;
    }
*/	
    bool isSquadLeaderCommand(){
        return true;
    }

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime;
	}

    String getAction() const {
        return action;
    }

    void setAction(String action) {
        this->action = action;
    }
};

#endif /* SQUADLEADERCOMMAND_H_ */
