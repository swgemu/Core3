/*
 Copyright (C) 2007 <SWGEmu>

 This File is part of Core3.

 This program is free software; you can redistribute
 it and/or modify it under the terms of the GNU Lesser
 General Public License as published by the Free Software
 Foundation; either version 2 of the License,
 or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for
 more details.

 You should have received a copy of the GNU Lesser General
 Public License along with this program; if not, write to
 the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

 Linking Engine3 statically or dynamically with other modules
 is making a combined work based on Engine3.
 Thus, the terms and conditions of the GNU Lesser General Public License
 cover the whole combination.

 In addition, as a special exception, the copyright holders of Engine3
 give you permission to combine Engine3 program with free software
 programs or libraries that are released under the GNU LGPL and with
 code included in the standard release of Core3 under the GNU LGPL
 license (or modified versions of such code, with unchanged license).
 You may copy and distribute such a system following the terms of the
 GNU LGPL for Engine3 and the licenses of the other code concerned,
 provided that you include the source code of that other code when
 and as the GNU LGPL requires distribution of source code.

 Note that people who make modified versions of Engine3 are not obligated
 to grant this special exception for their modified versions;
 it is their choice whether to do so. The GNU Lesser General Public License
 gives permission to release a modified version without this exception;
 this exception also makes it possible to release a modified version
 which carries forward this exception.
 */

#ifndef THROWTRAPCOMMAND_H_
#define THROWTRAPCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/events/ThrowTrapTask.h"
#include "server/zone/templates/tangible/TrapTemplate.h"

class ThrowTrapCommand: public CombatQueueCommand {
public:

	ThrowTrapCommand(const String& name, ZoneProcessServer* server) :
		CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target,
			const UnicodeString& arguments) {

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

		if (!tokenizer.hasMoreTokens())
			return INVALIDPARAMETERS;

		try {

			uint64 trapId = tokenizer.getLongToken();
			ManagedReference<TangibleObject*> trap = cast<TangibleObject*> (
					server->getZoneServer()->getObject(trapId));

			if (trap == NULL)
				return INVALIDPARAMETERS;

			if (!trap->isTrapObject())
				return INVALIDPARAMETERS;

			if (!trap->isASubChildOf(creature))
				return GENERALERROR;

			ManagedReference<CreatureObject*> targetCreature = cast<
					CreatureObject*> (
					server->getZoneServer()->getObject(target));

			if (targetCreature == NULL || !targetCreature->isCreature()) {
				creature->sendSystemMessage("@trap/trap:sys_creatures_only");
				return GENERALERROR;
			}

			if (!(targetCreature->getPvpStatusBitmask() & CreatureFlag::ATTACKABLE)) {
				creature->sendSystemMessage("@trap/trap:sys_no_pets");
				return GENERALERROR;
			}

			SharedObjectTemplate* templateData =
					TemplateManager::instance()->getTemplate(
							trap->getServerObjectCRC());
			if (templateData == NULL) {
				error("No template for: " + String::valueOf(trap->getServerObjectCRC()));
				return GENERALERROR;
			}

			TrapTemplate* trapData = cast<TrapTemplate*> (templateData);
			if (trapData == NULL) {
				error("No TrapTemplate for: " + String::valueOf(trap->getServerObjectCRC()));
				return GENERALERROR;
			}

			/// Check Range
			if(creature->getDistanceTo(targetCreature) > trapData->getMaxRange())
			{
				StringIdChatParameter tooFar("cmd_err", "target_range_prose");
				tooFar.setTO("Throw Trap");

				creature->sendSystemMessage(tooFar);
				return GENERALERROR;
			}

			int effectType = 0;

			// No skill Check
			int trappingSkill = creature->getSkillMod("trapping");
			if(trappingSkill < 1) {
				creature->sendSystemMessage("@trap/trap:trap_no_skill");
				return GENERALERROR;
			}

			/// Skill too low check
			if(trappingSkill < trapData->getSkillRequired()) {
				creature->sendSystemMessage("@trap/trap:trap_no_skill_this");
				return GENERALERROR;
			}

			int targetDefense = targetCreature->getSkillMod(trapData->getDefenseMod());
			Time* cooldown = creature->getCooldownTime("throwtrap");
			if((cooldown != NULL && !cooldown->isPast()) ||
					creature->getPendingTask("throwtrap") != NULL) {
				creature->sendSystemMessage("@trap/trap:sys_not_ready");
				return GENERALERROR;
			}

			if(!CombatManager::instance()->startCombat(creature, targetCreature))
				return GENERALERROR;

			float hitChance = CombatManager::instance()->hitChanceEquation(trappingSkill, 0, targetDefense);

			if (hitChance > 100)
				hitChance = 100.0;
			else if (hitChance < 0)
				hitChance = 0;

			int roll = System::random(100);
			uint64 state = trapData->getState();
			bool hit = roll < hitChance && (state == 0 || (state != 0 && !targetCreature->hasState(state)));

			String animation = trapData->getAnimation();
			uint32 crc = String(animation).hashCode();
			CombatAction* action = new CombatAction(creature, targetCreature, crc, hit, 0L);
			creature->broadcastMessage(action, true);
			creature->addCooldown("throwtrap", 1500);

			trap->decreaseUseCount(creature);

			StringIdChatParameter message;
			ManagedReference<Buff*> buff = NULL;
			int damage = 0;

			if (hit) {

				message.setStringId("trap/trap" , trapData->getSuccessMessage());

				buff = new Buff(targetCreature, crc, trapData->getDuration(), BuffType::STATE);
				if(state != 0)
					buff->addState(state);

				VectorMap<String, int64>* skillMods = trapData->getSkillMods();
				for(int i = 0; i < skillMods->size(); ++i) {
					buff->setSkillModifier(skillMods->elementAt(i).getKey(), skillMods->get(i));
				}

				String startSpam = trapData->getStartSpam();
				if(!startSpam.isEmpty())
					buff->setStartFlyText("trap/trap", startSpam,  0, 0xFF, 0);

				String stopSpam = trapData->getStopSpam();
				if(!stopSpam.isEmpty())
					buff->setEndFlyText("trap/trap", stopSpam,  0xFF, 0, 0);

				damage = System::random(trapData->getMaxDamage() - trapData->getMinDamage()) + trapData->getMinDamage();

			} else {
				message.setStringId("trap/trap" , trapData->getFailMessage());
			}

			message.setTT(targetCreature->getDisplayedName());


			ThrowTrapTask* trapTask = new ThrowTrapTask(creature, targetCreature, buff, message, trapData->getPoolToDamage(), damage, hit);
			creature->addPendingTask("throwtrap", trapTask, 2300);

			creature->inflictDamage(creature, CreatureAttribute::HEALTH, trapData->getHealthCost(), false);
			creature->inflictDamage(creature, CreatureAttribute::ACTION, trapData->getActionCost(), false);
			creature->inflictDamage(creature, CreatureAttribute::MIND, trapData->getMindCost(), false);

			return SUCCESS;

		} catch (Exception& e) {

		}

		return GENERALERROR;
	}

};

#endif //THROWTRAPCOMMAND_H_
