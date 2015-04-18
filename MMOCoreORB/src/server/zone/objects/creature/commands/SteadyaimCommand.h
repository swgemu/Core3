/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STEADYAIMCOMMAND_H_
#define STEADYAIMCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "SquadLeaderCommand.h"

class SteadyaimCommand : public SquadLeaderCommand {
public:

	SteadyaimCommand(const String& name, ZoneProcessServer* server)
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
		ManagedReference<GroupObject*> group = player->getGroup();

		if (!checkGroupLeader(player, group))
			return GENERALERROR;

		float skillMod = (float) creature->getSkillMod("steadyaim");
		int hamCost = (int) (100.0f * (1.0f - (skillMod / 100.0f))) * calculateGroupModifier(group);

		int healthCost = creature->calculateCostAdjustment(CreatureAttribute::STRENGTH, hamCost);
		int actionCost = creature->calculateCostAdjustment(CreatureAttribute::QUICKNESS, hamCost);
		int mindCost = creature->calculateCostAdjustment(CreatureAttribute::FOCUS, hamCost);

		if (!inflictHAM(player, healthCost, actionCost, mindCost))
			return GENERALERROR;

//		shoutCommand(player, group);

		int amount = 5 + skillMod;

		if (!doSteadyAim(player, group, amount))
			return GENERALERROR;

		if (player->isPlayerCreature() && player->getPlayerObject()->getCommandMessageString(String("steadyaim").hashCode()).isEmpty()==false && creature->checkCooldownRecovery("command_message")) {
			UnicodeString shout(player->getPlayerObject()->getCommandMessageString(String("steadyaim").hashCode()));
 	 	 	server->getChatManager()->broadcastMessage(player, shout, 0, 0, 80);
 	 	 	creature->updateCooldownTimer("command_message", 30 * 1000);
		}

		return SUCCESS;
	}

	bool doSteadyAim(CreatureObject* leader, GroupObject* group, int amount) const {
		if (leader == NULL || group == NULL)
			return false;

		for (int i = 0; i < group->getGroupSize(); i++) {

			ManagedReference<SceneObject*> member = group->getGroupMember(i);

			if (!member->isPlayerCreature() || member == NULL || member->getZone() != leader->getZone())
				continue;

			ManagedReference<CreatureObject*> memberPlayer = cast<CreatureObject*>( member.get());

			if (!isValidGroupAbilityTarget(leader, memberPlayer))
				continue;

			Locker clocker(memberPlayer, leader);

			sendCombatSpam(memberPlayer);

			ManagedReference<WeaponObject*> weapon = memberPlayer->getWeapon();

			if (!weapon->isRangedWeapon())
				continue;

			int duration = 300;

			ManagedReference<Buff*> buff = new Buff(memberPlayer, actionCRC, duration, BuffType::SKILL);
			buff->setSkillModifier("private_aim", amount);
			buff->setStartFlyText("combat_effects", "go_steady", 0, 0xFF, 0); // there is no corresponding no_steady fly text

			memberPlayer->addBuff(buff);
			//			memberPlayer->showFlyText("combat_effects", "go_steadied", 0, 0xFF, 0); // there is no corresponding no_steady fly text

			checkForTef(leader, memberPlayer);
		}

		return true;
	}

};

#endif //STEADYAIMCOMMAND_H_
