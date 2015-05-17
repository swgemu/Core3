/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef VOLLEYFIRECOMMAND_H_
#define VOLLEYFIRECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "SquadLeaderCommand.h"
#include "server/zone/managers/skill/SkillModManager.h"

class VolleyFireCommand : public SquadLeaderCommand {
public:

	VolleyFireCommand(const String& name, ZoneProcessServer* server)
		: SquadLeaderCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<CreatureObject*> player = creature;
		ManagedReference<GroupObject*> group = player->getGroup();

		if (!checkGroupLeader(player, group))
			return GENERALERROR;

		float skillMod = (float) creature->getSkillMod("volley");
		int hamCost = (int) (100.0f * (1.0f - (skillMod / 100.0f))) * calculateGroupModifier(group);

		int healthCost = creature->calculateCostAdjustment(CreatureAttribute::STRENGTH, hamCost);
		int actionCost = creature->calculateCostAdjustment(CreatureAttribute::QUICKNESS, hamCost);
		int mindCost = creature->calculateCostAdjustment(CreatureAttribute::FOCUS, hamCost);

		if (!inflictHAM(player, healthCost, actionCost, mindCost))
			return GENERALERROR;

		uint64 targetID = target;
		if (attemptVolleyFire(player, &targetID, skillMod))
			if (!doVolleyFire(player, group, &targetID))
				return GENERALERROR;

		return SUCCESS;
	}

	bool attemptVolleyFire(CreatureObject* player, uint64* target, int skillMod) const {
		if (player == NULL)
			return false;

		ManagedReference<WeaponObject*> weapon = player->getWeapon();

		String skillCRC;

		if (weapon != NULL) {
			if (!weapon->getCreatureAccuracyModifiers()->isEmpty()) {
				skillCRC = weapon->getCreatureAccuracyModifiers()->get(0);

				player->addSkillMod(SkillModManager::ABILITYBONUS, skillCRC, (int) skillMod * 2, false);
			}
		}

		int ret = doCombatAction(player, (uint64)target);

		if (!skillCRC.isEmpty())
			player->addSkillMod(SkillModManager::ABILITYBONUS, skillCRC, (int) skillMod * -2, false);

		return ret == SUCCESS;
	}

	bool doVolleyFire(CreatureObject* leader, GroupObject* group, uint64* target) const {
		if (leader == NULL || group == NULL)
			return false;

		for (int i = 0; i < group->getGroupSize(); i++) {
			ManagedReference<SceneObject*> member = group->getGroupMember(i);

			if (!member->isPlayerCreature() || !member->isInRange(leader, 128.0))
				continue;

			ManagedReference<CreatureObject*> memberPlayer = cast<CreatureObject*>( member.get());

			if (!isValidGroupAbilityTarget(leader, memberPlayer, false))
				continue;

			if (!memberPlayer->isInCombat())
				continue;

			Locker clocker(memberPlayer, leader);

			String queueAction = "volleyfireattack";
			uint64 queueActionCRC = queueAction.hashCode();

			memberPlayer->executeObjectControllerAction(queueActionCRC, (uint64)target, "");

			checkForTef(leader, memberPlayer);
		}

		return true;
	}

};

#endif //VOLLEYFIRECOMMAND_H_
