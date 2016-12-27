/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef TEACHCOMMAND_H_
#define TEACHCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class TeachCommand : public QueueCommand {
public:

	TeachCommand(const String& name, ZoneProcessServer* server)
	: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* teacher, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(teacher))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(teacher))
			return INVALIDLOCOMOTION;

		ZoneServer* zoneServer = server->getZoneServer();

		ManagedReference<SceneObject*> student = zoneServer->getObject(target);
		zoneServer->getPlayerManager()->promptTeachableSkills(teacher, student);


		/**
		experience_received You have received %DI Apprenticeship experience.
		learning_failed Learning failed.

		//no_skills_for_student You have no skills that  %TT can currently learn."
		offer_given You offer to teach %TT %TO.
		offer_refused %TT has refused your offer to teach.
		student_skill_learned You learn %TO from %TT.
		teacher_skill_learned %TT learns %TO from you.
		teacher_too_far Your teacher must be nearby in order to learn.
		teacher_too_far_target You are too far away from %TT to learn.
		teaching_failed Teaching failed.
		 */

		return SUCCESS;
	}

};

#endif //TEACHCOMMAND_H_
