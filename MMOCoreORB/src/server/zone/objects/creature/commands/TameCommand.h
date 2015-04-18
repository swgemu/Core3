/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TAMECOMMAND_H_
#define TAMECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/Creature.h"

class TameCommand : public QueueCommand {
public:

	TameCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<SceneObject* > object = server->getZoneServer()->getObject(target);

		if (object == NULL || !object->isCreature()) {
			creature->sendSystemMessage("@pet/pet_menu:sys_cant_tame"); // You can't tame that
			return INVALIDTARGET;
		}

		Creature* baby = cast<Creature*>(object.get());

		if (!object->isInRange(creature, 8.0f + object->getTemplateRadius() + creature->getTemplateRadius())){
			creature->sendSystemMessage("@system_msg:out_of_range"); // You are out of range
			return TOOFAR;
		}

		bool force = false;

		UnicodeTokenizer args(arguments);

		if (args.hasMoreTokens()) {
			if (creature->isPlayerCreature()) {
				PlayerObject* ghost = creature->getPlayerObject();

				if (ghost == NULL)
					return GENERALERROR;

				if (ghost->hasAbility("admin")) {
					force = true;
				}
			}
		}

		Locker clocker(baby, creature);

		ManagedReference<CreatureManager*> manager = creature->getZone()->getCreatureManager();
		manager->tame(baby, creature, force);

		return SUCCESS;
	}

};

#endif //TAMECOMMAND_H_
