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

	DetonateDroidCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		// we must have a target
		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);
		if (object != NULL) {
			if(object->isDroidObject()) {
				DroidObject* droid = cast<DroidObject*>(object.get());

				if( !droid->hasPower() ){
					droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
					return SUCCESS;
				}

				if(droid->isDead()) {
					creature->sendSystemMessage("@pet/droid_modules:droid_bomb_failed");
					return SUCCESS;
				}

				if ( !(creature->hasSkill("combat_bountyhunter_novice") || creature->hasSkill("combat_smuggler_novice"))){
					creature->sendSystemMessage("@pet/droid_modules:insufficient_skill_detonate");
					return GENERALERROR;
				}
				if (droid->getLinkedCreature() == creature) {
					// does it have the module?
					if (droid->getModule("detonation_module") == NULL) {
						creature->sendSystemMessage("@pet/droid_modules:no_bomb_module");
						return GENERALERROR;
					} else {
						DroidDetonationModuleDataComponent* module = cast<DroidDetonationModuleDataComponent*>(droid->getModule("detonation_module"));
						if(droid->getPendingTask("droid_detonation") != NULL) {
							if(module->countdownInProgress())
								creature->sendSystemMessage("@pet/droid_modules:countdown_already_started");
							else
								creature->sendSystemMessage("@pet/droid_modules:detonation_warmup");
							return SUCCESS;
						}
						Reference<Task*> task = new DroidDetonationTask( module,creature);
						droid->addPendingTask("droid_detonation", task, 0);
					}
				} else {
					creature->sendSystemMessage("@pet/droid_modules:must_be_owner_droid_bomb");
					return INVALIDTARGET;
				}
			} else {
				creature->sendSystemMessage("@pet/droid_modules:invalid_droid_bomb");
				return INVALIDTARGET;
			}
		} else {
			creature->sendSystemMessage("@pet/droid_modules:invalid_droid_bomb");
			return INVALIDTARGET;
		}


		return SUCCESS;
	}

};

#endif //DETONATEDROIDCOMMAND_H_
