/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GRANTSKILLCOMMAND_H_
#define GRANTSKILLCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/skill/SkillManager.h"

class GrantSkillCommand : public QueueCommand {
public:

	GrantSkillCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL || !object->isCreatureObject())
			return INVALIDTARGET;

		CreatureObject* targetCreature = cast<CreatureObject*>( object.get());

		Locker clocker(targetCreature, creature);

		SkillManager* skillManager = SkillManager::instance();
		skillManager->surrenderSkill(arguments.toString(), targetCreature, true);
		bool skillGranted = skillManager->awardSkill(arguments.toString(), targetCreature, true, true, true);

		if (skillGranted) {
			StringIdChatParameter params;
			params.setTO(arguments.toString());
			params.setStringId("skill_teacher", "skill_terminal_grant");

			targetCreature->sendSystemMessage(params);

			creature->sendSystemMessage("Granted skill " + arguments.toString()
					+ "to " + targetCreature->getFirstName());
		} else {
			StringIdChatParameter params;
			params.setTO(arguments.toString());
			params.setStringId("skill_teacher", "prose_train_failed");

			targetCreature->sendSystemMessage(params);

			creature->sendSystemMessage("Failed to grant skill " + arguments.toString()
					+ "to " + targetCreature->getFirstName());
		}
		return SUCCESS;
	}

};

#endif //GRANTSKILLCOMMAND_H_
