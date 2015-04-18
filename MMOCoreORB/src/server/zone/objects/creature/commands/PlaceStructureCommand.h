/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLACESTRUCTURECOMMAND_H_
#define PLACESTRUCTURECOMMAND_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/deed/Deed.h"
#include "server/zone/objects/tangible/deed/structure/StructureDeed.h"

class PlaceStructureCommand : public QueueCommand {
public:

	PlaceStructureCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (creature->isRidingMount()) {
			creature->sendSystemMessage("@player_structure:cant_place_mounted");
			return INVALIDLOCOMOTION;
		}

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->getParent() != NULL) {
			creature->sendSystemMessage("@player_structure:not_inside"); //You can not place a structure while you are inside a building.
			return GENERALERROR;
		}

		uint64 deedID;
		float x, y;
		int angle;

		try {
			UnicodeTokenizer tokenizer(arguments);

			deedID = tokenizer.getLongToken();
			x = tokenizer.getFloatToken();
			y = tokenizer.getFloatToken();
			angle = tokenizer.getIntToken() * 90;

			// Validate player position -vs- attemped placement
			Zone* zone = creature->getZone();

			if (zone == NULL)
				return GENERALERROR;

			Vector3 position(x, y, zone->getHeight(x, y));
			Vector3 playerPosition = creature->getPosition();
			float distance = position.distanceTo(playerPosition);

			// Client will only scoll about 100m from the placement start position
			if (distance > 100.0f) {
				CreatureObject* player = cast<CreatureObject*>(creature);

				player->sendSystemMessage("@system_msg:out_of_range");

				player->error(player->getFirstName()
					+ " attemped invalid placeStructure on "
					+ zone->getZoneName()
					+ " @ x: " + String::valueOf(x)
					+ ", y: " + String::valueOf(y)
					+ ", z: " + String::valueOf(zone->getHeight(x, y))
					+ " while player @ x: " + String::valueOf(playerPosition.getX())
					+ ", y: " + String::valueOf(playerPosition.getY())
					+ ", z: " + String::valueOf(playerPosition.getZ())
					+ " range: " + String::valueOf(position.distanceTo(playerPosition)) + "m"
				);

				return GENERALERROR;
			}
		} catch (Exception& e) {
			info(e.getMessage());
			return INVALIDPARAMETERS;
		}

		//We want to begin the session here.

		ManagedReference<StructureDeed*> deed = server->getZoneServer()->getObject(deedID).castTo<StructureDeed*>();

		if (deed != NULL)
			deed->placeStructure(creature, x, y, angle);

		return SUCCESS;
	}

};

#endif //PLACESTRUCTURECOMMAND_H_
