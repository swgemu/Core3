/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SITSERVERCOMMAND_H_
#define SITSERVERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

#include "server/zone/packets/object/SitOnObject.h"
#include "server/zone/objects/creature/CreatureState.h"

class SitServerCommand : public QueueCommand {
public:

	SitServerCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->isInCombat())
			return INVALIDSTATE;

		if (arguments.isEmpty()) {
			creature->setPosture(CreaturePosture::SITTING);
		} else {
			StringTokenizer tokenizer(arguments.toString());
			tokenizer.setDelimeter(",");
			float x = tokenizer.getFloatToken();
			float y = tokenizer.getFloatToken();
			float z = tokenizer.getFloatToken();

			uint64 coID = 0;
			if (tokenizer.hasMoreTokens())
				coID = tokenizer.getLongToken();

			if (x < -8192 || x > 8192)
				x = 0;
			if (y < -8192 || y > 8192)
				y = 0;
			if (z < -8192 || z > 8192)
				z = 0;

			//creature->sendSystemMessage(arguments.toString());

			Vector3 position(x, z, y);
			Vector3 playerPosition = creature->getPosition();

			/*if (position.squaredDistanceTo(playerPosition) > 9.f) {
				creature->sendSystemMessage("@ui:chair_out_of_range");
				return GENERALERROR;
			}*/

/*			ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

			if (object != NULL && !object->isCreatureObject())*/
			//creature->sendSystemMessage("Pos: " + String::valueOf(position.getX()) + " " + String::valueOf(position.getY()) + " " + String::valueOf(position.getZ()));
			//creature->sendSystemMessage("PPos: " + String::valueOf(playerPosition.getX()) + " " + String::valueOf(playerPosition.getY()) + " " + String::valueOf(playerPosition.getZ()));

			if (position.squaredDistanceTo(playerPosition) > 5.f)
				return GENERALERROR;

			creature->teleport(position.getX(), position.getZ(), position.getY(), creature->getParentID());
			//creature->setDirection()
			creature->setState(CreatureState::SITTINGONCHAIR);
			//no longer needed: creature->setPosture(CreaturePosture::SITTING);
		}

		return SUCCESS;
	}

};

#endif //SITSERVERCOMMAND_H_

