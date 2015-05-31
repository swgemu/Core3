/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

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
						DroidObject* targetDroid = NULL;
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
											targetDroid = cast<DroidObject*>(agent);
											if(targetDroid != NULL ) {
												Reference<Task*> task = new DroidStimpackTask( targetDroid,creature,targetDroid->getDisplayedName());
												targetDroid->addPendingTask("droid_request_stimpack", task, 1);
												return SUCCESS;
											}
										}
									}
								} else if (member->isDroidObject()) {
									ManagedReference<DroidObject*> memberDroid = cast<DroidObject*>( member.get());
									if(memberDroid->getDisplayedName() == search) {
										locker.release();
										Reference<Task*> task = new DroidStimpackTask( memberDroid,creature,memberDroid->getDisplayedName());
										memberDroid->addPendingTask("droid_request_stimpack", task, 1);
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
									targetDroid = cast<DroidObject*>(agent);
									if(targetDroid != NULL ) {
										Reference<Task*> task = new DroidStimpackTask( targetDroid,creature,targetDroid->getDisplayedName());
										targetDroid->addPendingTask("droid_request_stimpack", task, 1);
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
