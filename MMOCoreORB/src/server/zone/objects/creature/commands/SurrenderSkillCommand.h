/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SURRENDERSKILLCOMMAND_H_
#define SURRENDERSKILLCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/skill/SkillManager.h"


class SurrenderSkillCommand : public QueueCommand {
public:

	SurrenderSkillCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		SkillManager* skillManager = SkillManager::instance();
		skillManager->surrenderSkill(arguments.toString(), creature, true);

		return SUCCESS;
	}

};

#endif //SURRENDERSKILLCOMMAND_H_

