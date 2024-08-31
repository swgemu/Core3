/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef THROWTRAPCOMMAND_H_
#define THROWTRAPCOMMAND_H_

#include "server/zone/objects/creature/events/ThrowTrapTask.h"
#include "templates/tangible/TrapTemplate.h"

class ThrowTrapCommand : public CombatQueueCommand {
public:
	ThrowTrapCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		int skillLevel = creature->getSkillMod("trapping");

		if (skillLevel < 1 || !creature->hasSkill("outdoors_scout_novice")) {
			creature->sendSystemMessage("@trap/trap:trap_no_skill");
			return GENERALERROR;
		}

		StringTokenizer tokenizer(arguments.toString());

		if (!tokenizer.hasMoreTokens()) {
			return INVALIDPARAMETERS;
		}

		auto zoneServer = server->getZoneServer();

		if (zoneServer == nullptr) {
			return GENERALERROR;
		}

		try {
			// Check for pending cooldowns
			const Time* cooldown = creature->getCooldownTime("throwtrap");

			if ((cooldown != nullptr && !cooldown->isPast()) || creature->getPendingTask("throwtrap") != nullptr) {
				creature->sendSystemMessage("@trap/trap:sys_not_ready");
				return GENERALERROR;
			}

			// Get trap to be used
			uint64 trapId = tokenizer.getLongToken();

			ManagedReference<TangibleObject*> trap = zoneServer->getObject(trapId).castTo<TangibleObject*>();

			if (trap == nullptr || !trap->isTrapObject() || !trap->isASubChildOf(creature)) {
				return GENERALERROR;
			}

			ManagedReference<SceneObject*> targetObject = zoneServer->getObject(target);

			if (targetObject == nullptr || !targetObject->isAiAgent()) {
				return INVALIDTARGET;
			}

			// Get trap target agent
			auto targetAgent = targetObject->asAiAgent();

			if (targetAgent == nullptr) {
				return GENERALERROR;
			}

			if (targetAgent->isDead() || !targetAgent->isAttackableBy(creature)) {
				return INVALIDTARGET;
			}

			// Check for validity of target
			if (targetAgent->isPet()) {
				creature->sendSystemMessage("@trap/trap:sys_no_pets");
				return GENERALERROR;
			} else if (!targetAgent->isCreature() || !targetAgent->isMonster()) {
				creature->sendSystemMessage("@trap/trap:sys_creatures_only");
				return GENERALERROR;
			}

			// Trapping skill mod check
			int trappingSkill = creature->getSkillMod("trapping");

			// Player is not able to use traps
			if (trappingSkill < 1) {
				creature->sendSystemMessage("@trap/trap:trap_no_skill");
				return GENERALERROR;
			}

			SharedObjectTemplate* templateData = TemplateManager::instance()->getTemplate(trap->getServerObjectCRC());

			if (templateData == nullptr) {
				error("No template for: " + String::valueOf(trap->getServerObjectCRC()));
				return GENERALERROR;
			}

			TrapTemplate* trapData = cast<TrapTemplate*>(templateData);

			if (trapData == nullptr) {
				error("No TrapTemplate for: " + String::valueOf(trap->getServerObjectCRC()));
				return GENERALERROR;
			}

			// Check Range
			if (!checkDistance(creature, targetAgent, trapData->getMaxRange())) {
				StringIdChatParameter tooFar("cmd_err", "target_range_prose");
				tooFar.setTO("Throw Trap");

				creature->sendSystemMessage(tooFar);
				return GENERALERROR;
			}

			// Skill too low check
			if (trappingSkill < trapData->getSkillRequired()) {
				creature->sendSystemMessage("@trap/trap:trap_no_skill_this");
				return GENERALERROR;
			}

			Reference<ThrowTrapTask*> trapTask = new ThrowTrapTask(creature, targetAgent, trap);

			if (trapTask == nullptr) {
				return GENERALERROR;
			}

			creature->addPendingTask("throwtrap", trapTask, 2000);

			return SUCCESS;
		} catch (Exception& e) {
			e.printStackTrace();
		}

		return GENERALERROR;
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime;
	}
};

#endif // THROWTRAPCOMMAND_H_
