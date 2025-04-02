/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DETONATEDROIDCOMMAND_H_
#define DETONATEDROIDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/components/droid/DroidDetonationModuleDataComponent.h"
#include "server/zone/objects/creature/events/DroidDetonationTask.h"

class DetonateDroidCommand : public QueueCommand {
public:
	DetonateDroidCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!creature->isPlayerCreature() || creature->isDead() || (creature->isIncapacitated() && !creature->isFeigningDeath())) {
			return INVALIDSTATE;
		}

		if (creature->isFrozen()) {
			return INVALIDLOCOMOTION;
		}

		auto zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr) {
			return GENERALERROR;
		}

		// we must have a target
		ManagedReference<SceneObject*> object = zoneServer->getObject(target);

		if (object == nullptr || !object->isDroidObject()) {
			creature->sendSystemMessage("@pet/droid_modules:invalid_droid_bomb");
			return INVALIDTARGET;
		}

		DroidObject* droid = cast<DroidObject*>(object.get());

		if (droid == nullptr || !droid->isBombDroid()) {
			creature->sendSystemMessage("@pet/droid_modules:invalid_droid_bomb");
			return INVALIDTARGET;
		}

		// Player must be droid owner
		if (droid->getLinkedCreature().get() != creature) {
			creature->sendSystemMessage("@pet/droid_modules:must_be_owner_droid_bomb");
			return GENERALERROR;
		}

		if (!creature->hasSkill("combat_bountyhunter_novice") && !creature->hasSkill("combat_smuggler_novice")) {
			creature->sendSystemMessage("@pet/droid_modules:insufficient_skill_detonate");
			return GENERALERROR;
		}

		// Check to make sure droid has power
		if (!droid->hasPower()){
			droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
			return GENERALERROR;
		}

		// Check for detonation module
		auto module = droid->getModule("detonation_module").castTo<DroidDetonationModuleDataComponent*>();

		if (module == nullptr) {
			creature->sendSystemMessage("@pet/droid_modules:no_bomb_module");
			return INVALIDTARGET;
		}

		// Check to make sure droid is not dead
		if (droid->isDead()) {
			creature->sendSystemMessage("@pet/droid_modules:droid_bomb_failed");
			return GENERALERROR;
		}

		// Make sure detonation module is ready
		if (!module->readyForDetonation()) {
			creature->sendSystemMessage("@pet/droid_modules:detonation_warmup");
			return GENERALERROR;
		}

		if (droid->getPendingTask("droid_detonation") != nullptr) {
			creature->sendSystemMessage("@pet/droid_modules:countdown_already_started");
			return GENERALERROR;
		}

		Reference<Task*> task = new DroidDetonationTask(module, creature);

		if (task == nullptr) {
			return GENERALERROR;
		}

		droid->addPendingTask("droid_detonation", task, 0);

		return SUCCESS;
	}
};

#endif //DETONATEDROIDCOMMAND_H_
