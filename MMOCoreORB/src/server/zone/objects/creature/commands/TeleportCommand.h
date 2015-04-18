/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TELEPORTCOMMAND_H_
#define TELEPORTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class TeleportCommand : public QueueCommand {
public:

	TeleportCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		float x, y;
		float z = 0;

		Zone* zone = creature->getZone();

		if (zone == NULL)
			return GENERALERROR;

		String zoneName = zone->getZoneName();
		uint64 parentID = 0;

		try {
			UnicodeTokenizer tokenizer(arguments);

			x = tokenizer.getFloatToken();
			y = tokenizer.getFloatToken();

			if (tokenizer.hasMoreTokens())
				tokenizer.getStringToken(zoneName);

			if (tokenizer.hasMoreTokens()) {
				z = tokenizer.getFloatToken();
				parentID = tokenizer.getLongToken();
			}

			creature->setDirection(0);

			creature->switchZone(zoneName, x, z, y, parentID);
		} catch (Exception& e) {
			creature->sendSystemMessage("SYNTAX: /teleport <x> <y> [<planet>] [<z> <parentID>]");
		}

		return SUCCESS;
	}

};

#endif //TELEPORTCOMMAND_H_
