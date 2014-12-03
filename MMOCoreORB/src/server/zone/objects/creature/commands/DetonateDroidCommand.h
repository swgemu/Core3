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

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

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
