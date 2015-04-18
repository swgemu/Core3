/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RALLYCOMMAND_H_
#define RALLYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "SquadLeaderCommand.h"

class RallyCommand : public SquadLeaderCommand {
public:

	RallyCommand(const String& name, ZoneProcessServer* server)
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

		int hamCost = (int) (100.0f * calculateGroupModifier(group));

		int healthCost = creature->calculateCostAdjustment(CreatureAttribute::STRENGTH, hamCost);
		int actionCost = creature->calculateCostAdjustment(CreatureAttribute::QUICKNESS, hamCost);
		int mindCost = creature->calculateCostAdjustment(CreatureAttribute::FOCUS, hamCost);

		if (!inflictHAM(player, healthCost, actionCost, mindCost))
			return GENERALERROR;

		int chance = 75;

		if (System::random(100) > chance) {
			player->sendSystemMessage("@cbt_spam:rally_fail_single"); //"You fail to rally the group!"
			sendRallyCombatSpam(player, group, false);
		} else {
			if (!doRally(player, group))
				return GENERALERROR;
		}

		return SUCCESS;
	}

	bool doRally(CreatureObject* leader, GroupObject* group) const {
		if (leader == NULL || group == NULL)
			return false;

		int duration = 30;

		leader->sendSystemMessage("@cbt_spam:rally_success_single"); //"You rally the group!"
		sendRallyCombatSpam(leader, group, true);

		for (int i = 0; i < group->getGroupSize(); i++) {

			ManagedReference<SceneObject*> member = group->getGroupMember(i);

			if (member == NULL || !member->isPlayerCreature() || member->getZone() != leader->getZone())
				continue;

			ManagedReference<CreatureObject*> memberPlayer = cast<CreatureObject*>( member.get());

			if (!isValidGroupAbilityTarget(leader, memberPlayer))
				continue;

			Locker clocker(memberPlayer, leader);

			if (memberPlayer != leader)
				memberPlayer->sendSystemMessage("@cbt_spam:rally_success_group_msg"); //"Your group rallies to the attack!"

			ManagedReference<Buff*> buff = new Buff(memberPlayer, actionCRC, duration, BuffType::SKILL);

			ManagedReference<WeaponObject*> weapon = memberPlayer->getWeapon();

			if (weapon != NULL) {
				if (!weapon->getCreatureAccuracyModifiers()->isEmpty()) {
					String skillCRC = weapon->getCreatureAccuracyModifiers()->get(0);

					buff->setSkillModifier(skillCRC, 50);
				}
			}

			buff->setSkillModifier("private_group_ranged_defense", 30);
			buff->setSkillModifier("private_group_melee_defense", 30);

			memberPlayer->addBuff(buff);

			memberPlayer->setRalliedState(duration);

			checkForTef(leader, memberPlayer);
		}

//		What is this used for?		
//		leader->updateCooldownTimer("rally", (duration + 30) * 1000);

		return true;
	}

	void sendRallyCombatSpam(CreatureObject* leader, GroupObject* group, bool success) const {
		if (leader == NULL || group == NULL)
			return;

		Zone* zone = leader->getZone();
		if (zone == NULL)
			return;

		String stringName = combatSpam;
		byte color = 0;

		if (success)
			stringName += "_success";
		else
			stringName += "_fail";


		/*To get this spam to come out properly:
		  For all, attacker in packet is squad leader.
		  For leader or group member, defender has to be any third party object.
		  For bystanders, the defender is themselves.*/


		//Send to group members if they are on the same planet.
		for (int i = 0; i < group->getGroupSize(); i++) {
			ManagedReference<SceneObject*> member = group->getGroupMember(i);
			if (member == NULL || !member->isPlayerCreature() || member->getZone() != leader->getZone())
								continue;
			CreatureObject* memberPlayer = cast<CreatureObject*>( member.get());
			CombatSpam* spam = new CombatSpam(leader, leader->getWeapon(), memberPlayer, NULL, 0, "cbt_spam", stringName, color);
			memberPlayer->sendMessage(spam);
		}

		//Send to players near the leader and not in group.
		CloseObjectsVector* vec = (CloseObjectsVector*) leader->getCloseObjects();
		SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;
		if (vec != NULL) {
			closeObjects.removeAll(vec->size(), 10);
			vec->safeCopyTo(closeObjects);
		} else {
			info("Null closeobjects vector in RallyCommand::sendRallyCombatSpam", true);
			zone->getInRangeObjects(leader->getWorldPositionX(), leader->getWorldPositionY(), 70, &closeObjects, true);
		}

		for (int i = 0; i < closeObjects.size(); ++i) {
			SceneObject* object = cast<SceneObject*>( closeObjects.get(i).get());
			if (object == NULL || !object->isPlayerCreature() || !leader->isInRange(object, 70) || group->hasMember(object))
				continue;

			CreatureObject* receiver = cast<CreatureObject*>( object); //in range player who isn't in group.

			CombatSpam* spam = new CombatSpam(leader, receiver, receiver, NULL, 0, "cbt_spam", stringName, color);
			receiver->sendMessage(spam);
		}
	}

};

#endif //RALLYCOMMAND_H_
