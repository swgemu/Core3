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

#ifndef REQUESTSTIMPACKCOMMAND_H_
#define REQUESTSTIMPACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/events/DroidStimpackTask.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/group/GroupObject.h"

class RequestStimpackCommand : public QueueCommand {
public:

	RequestStimpackCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		// determine target is name or targetted
		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);
		if (object != NULL) {
			if(object->isDroidObject()) {
				DroidObject* droid = cast<DroidObject*>(object.get());
				Reference<Task*> task = new DroidStimpackTask( droid,creature,droid->getDisplayedName());
				droid->addPendingTask("droid_request_stimpack", task, 1);
				return SUCCESS;
			} else {
				creature->sendSystemMessage("@pet/droid_modules:stimpack_no_target");
				return GENERALERROR;
			}
		} else {
			// no target check for a droid name
			if (!arguments.isEmpty()) {
				// determine name of droid
				String droidName = arguments.toString();
				if (!droidName.isEmpty()) {
					if(droidName.beginsWith("(") && droidName.endsWith(")")) {
						// find it in 20 meter range
						String search = droidName.subString(1,droidName.length()-1);
						GroupObject* group = creature->getGroup();
						DroidObject* target = NULL;
						if(group != NULL) {
							// find it in the group
							Locker locker(group);
							for(int i=0;i<group->getGroupSize();i++) {
								ManagedReference<SceneObject*> member = group->getGroupMember(i);
								if(member->isPlayerObject()) {
									ManagedReference<PlayerObject*> memberPlayer = cast<PlayerObject*>( member.get());
									// it is one of his active droids?
									int x = memberPlayer->getActivePetsSize();
									for(int j=0;j<x;j++) {
										AiAgent* agent = memberPlayer->getActivePet(j);
										if(agent->isDroidObject() && agent->getDisplayedName() == search) {
											target = cast<DroidObject*>(agent);
											if(target != NULL ) {
												Reference<Task*> task = new DroidStimpackTask( target,creature,target->getDisplayedName());
												target->addPendingTask("droid_request_stimpack", task, 1);
												return SUCCESS;
											}
										}
									}
								} else if (member->isDroidObject()) {
									ManagedReference<DroidObject*> memberDroid = cast<DroidObject*>( member.get());
									if(memberDroid->getDisplayedName() == search) {
										locker.release();
										Reference<Task*> task = new DroidStimpackTask( memberDroid,creature,memberDroid->getDisplayedName());
										target->addPendingTask("droid_request_stimpack", task, 1);
										return SUCCESS;
									}
								}
							}
						} else {
							// is it his droid?
							PlayerObject* x;
							int activeDroids = creature->getPlayerObject()->getActivePetsSize();
							for(int i=0;i<activeDroids;i++) {
								AiAgent* agent = creature->getPlayerObject()->getActivePet(i);
								if(agent->isDroidObject() && agent->getDisplayedName() == search) {
									target = cast<DroidObject*>(agent);
									if(target != NULL ) {
										Reference<Task*> task = new DroidStimpackTask( target,creature,target->getDisplayedName());
										target->addPendingTask("droid_request_stimpack", task, 1);
										return SUCCESS;
									}
								}
							}
						}
					}
					creature->sendSystemMessage("@pet/droid_modules:stimpack_no_target");
					return GENERALERROR;
				} else {
					creature->sendSystemMessage("@pet/droid_modules:stimpack_no_target");
					return GENERALERROR;
				}
			} else {
				creature->sendSystemMessage("@pet/droid_modules:stimpack_no_target");
				return GENERALERROR;
			}
		}
		return SUCCESS;
	}

};

#endif //REQUESTSTIMPACKCOMMAND_H_
