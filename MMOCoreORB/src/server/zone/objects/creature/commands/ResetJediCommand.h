/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RESETJEDICOMMAND_H_
#define RESETJEDICOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ResetJediCommand : public QueueCommand {
public:

	ResetJediCommand(const String& name, ZoneProcessServer* server)
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

		SkillList* skillList = targetCreature->getSkillList();

		for (int i = 0; i < skillList->size(); ++i) {
			Skill* skill = skillList->get(i);
			if (skill->getSkillName().indexOf("force_") != -1){
				SkillManager::instance()->surrenderSkill(skill->getSkillName(), targetCreature, true);
			}
		}

		// Jedi State.s

		ManagedReference<PlayerObject*> targetGhost = targetCreature->getPlayerObject();

		if (targetGhost == NULL)
			return GENERALERROR;

		targetGhost->setJediState(0);

		return SUCCESS;
	}

};

#endif //RESETJEDICOMMAND_H_
