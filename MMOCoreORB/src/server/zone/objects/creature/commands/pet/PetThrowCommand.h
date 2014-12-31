
#ifndef PETTHROWCOMMAND_H_
#define PETTHROWCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/components/droid/DroidTrapModuleDataComponent.h"
#include "server/zone/templates/tangible/TrapTemplate.h"
#include "server/zone/objects/creature/events/DroidTrapTask.h"
#include "server/zone/managers/crafting/labratories/DroidMechanics.h"
#include "engine/engine.h"

class PetThrowCommand : public QueueCommand {
public:
	PetThrowCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& targetID, const UnicodeString& arguments) {

		ManagedReference<PetControlDevice*> controlDevice = creature->getControlDevice().castTo<PetControlDevice*>();

		if (controlDevice == NULL)
			return GENERALERROR;

		// Droid specific command
		if( controlDevice->getPetType() != PetManager::DROIDPET )
			return GENERALERROR;

		// droid must have a trap module
		ManagedReference<DroidObject*> droid = cast<DroidObject*>(creature);
		if( droid == NULL )
			return GENERALERROR;

		DroidTrapModuleDataComponent* module = cast<DroidTrapModuleDataComponent*>(droid->getModule("trap_module"));
		if(module == NULL) {
			return GENERALERROR;
		}

		// trap must be a trap
		TangibleObject* trap = module->getTrap();
		if (!trap->isTrapObject()) {
			droid->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
			return GENERALERROR;
		}

		// trap must have charges
		if(trap->getUseCount() <= 0) {
			droid->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
			return GENERALERROR;
		}

		// target must be a creature
		Reference<CreatureObject*> target = server->getZoneServer()->getObject(targetID, true).castTo<CreatureObject*>();
		if (target == NULL || !target->isCreature()) {
			droid->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
			return GENERALERROR;
		}

		// target must be attackable
		if (!(target->getPvpStatusBitmask() & CreatureFlag::ATTACKABLE)) {
			droid->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
			return GENERALERROR;
		}

		// Check range to target
		if (!droid->isInRange(target, 64.0f)){ // traps via launcher get their own range
			droid->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
			return GENERALERROR;
		}

		// check droid state
		if( droid->getLocalZone() == NULL ){  // Not outdoors
			ManagedWeakReference<SceneObject*> parent = droid->getParent();
			if( parent == NULL || !parent.get()->isCellObject() ){ // Not indoors either
				return GENERALERROR;
			}
		}

		// droid must not be dead or incapped
		if(droid->isIncapacitated() || droid->isDead()) {
			return GENERALERROR;
		}

		// Check if droid has power
		if( !droid->hasPower() ){
			droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
			return GENERALERROR;
		}

		// get trap meta data
		SharedObjectTemplate* templateData = TemplateManager::instance()->getTemplate(trap->getServerObjectCRC());
		if (templateData == NULL) {
			error("No template for: " + String::valueOf(trap->getServerObjectCRC()));
			return GENERALERROR;
		}

		// get trap template
		TrapTemplate* trapData = cast<TrapTemplate*> (templateData);
		if (trapData == NULL) {
			error("No TrapTemplate for: " + String::valueOf(trap->getServerObjectCRC()));
			return GENERALERROR;
		}
		// we nee the owner
		ManagedReference<CreatureObject*> owner = droid->getLinkedCreature();
		Locker olock(owner);
		try {
			int effectType = 0;

			// No skill Check
			int trappingSkill = owner->getSkillMod("trapping");
			if(trappingSkill < 1) {
				owner->sendSystemMessage("@pet/droid_modules:insufficient_skill");
				return GENERALERROR;
			}

			/// Skill too low check the player must be able to use the trap
			if(trappingSkill < trapData->getSkillRequired()) {
				owner->sendSystemMessage("@pet/droid_modules:insufficient_skill");
				return GENERALERROR;
			}

			int trapBonus = module->getTrapBonus();
			// trapping skill gets modified by the droids trap bonus
			int bonus = DroidMechanics::determineDroidSkillBonus(trappingSkill,trapBonus,trappingSkill);
			if (trapBonus > trappingSkill)
				trappingSkill += bonus;
			else
				trappingSkill -= bonus;
			if (trappingSkill < 0) {
				trappingSkill = 0;
			}

			int targetDefense = target->getSkillMod(trapData->getDefenseMod());
			Time* cooldown = droid->getCooldownTime("throwtrap");
			if((cooldown != NULL && !cooldown->isPast()) || 	droid->getPendingTask("throwtrap") != NULL) {
				StringIdChatParameter msg;
				msg.setStringId("@pet/droid_modules:cant_throw_yet");
				Time now;
				uint32 diff = cooldown->getTime() - now.getTime();
				msg.setDI(diff);
				owner->sendSystemMessage(msg);
				return GENERALERROR;
			}
			// place droid and owner in combat
			if(!CombatManager::instance()->startCombat(droid, target))
				return GENERALERROR;

			float hitChance = CombatManager::instance()->hitChanceEquation(trappingSkill, 0, targetDefense);

			if (hitChance > 100)
				hitChance = 100.0;
			else if (hitChance < 0)
				hitChance = 0;

			int roll = System::random(100);
			uint64 state = trapData->getState();
			bool hit = roll < hitChance && (state == 0 || (state != 0 && !target->hasState(state)));

			String animation = trapData->getAnimation();
			uint32 crc = String(animation).hashCode();
			CombatAction* action = new CombatAction(droid, target, crc, hit, 0L);
			creature->broadcastMessage(action, true);
			creature->addCooldown("throwtrap", 5000); // 5s cooldown on droid throwing traps
			// power usage for throw
			droid->usePower(1);
			// let module handle decrment so it can clear the trap when its out of charges
			module->decrementTrap();

			StringIdChatParameter message;
			ManagedReference<Buff*> buff = NULL;
			int damage = 0;

			if (hit) {

				message.setStringId("trap/trap" , trapData->getSuccessMessage());

				buff = new Buff(target, crc, trapData->getDuration(), BuffType::STATE);
				if(state != 0)
					buff->addState(state);

				VectorMap<String, int>* skillMods = trapData->getSkillMods();
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
				if(!trapData->getFailMessage().isEmpty()) {
					message.setStringId("trap/trap" , trapData->getFailMessage());
				}
			}

			message.setTT(target->getDisplayedName());


			Reference<DroidTrapTask*> trapTask = new DroidTrapTask(owner, target, droid, buff, message, trapData->getPoolToDamage(), damage, hit);
			droid->addPendingTask("throwtrap", trapTask, 2300);

			// droid dont take ham damage for use as far as i know i.e. no mention of it
			/*
			//Reduce cost based upon player's strength, quickness, and focus if any are over 300
				int healthCost = droid->calculateCostAdjustment(CreatureAttribute::STRENGTH, trapData->getHealthCost());
				int actionCost = droid->calculateCostAdjustment(CreatureAttribute::QUICKNESS, trapData->getActionCost());
				int mindCost = droid->calculateCostAdjustment(CreatureAttribute::FOCUS, trapData->getMindCost());

				droid->inflictDamage(droid, CreatureAttribute::HEALTH, healthCost, false);
				droid->inflictDamage(droid, CreatureAttribute::ACTION, actionCost, false);
				droid->inflictDamage(droid, CreatureAttribute::MIND, mindCost, false);
			*/
			return SUCCESS;

		} catch (Exception& e) {

		}
		return GENERALERROR;
	}

};


#endif /* PETTHROWCOMMAND_H_ */
