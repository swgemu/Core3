/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETCURRENTSKILLTITLECOMMAND_H_
#define SETCURRENTSKILLTITLECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetCurrentSkillTitleCommand : public QueueCommand {
public:

	SetCurrentSkillTitleCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == NULL)
			return GENERALERROR;

		String titleSkill = arguments.toString().toLowerCase();

		if (!titleSkill.isEmpty() && !creature->hasSkill(titleSkill))
			return GENERALERROR;

		ghost->setTitle(titleSkill, true);

		return SUCCESS;
	}

};

#endif //SETCURRENTSKILLTITLECOMMAND_H_
