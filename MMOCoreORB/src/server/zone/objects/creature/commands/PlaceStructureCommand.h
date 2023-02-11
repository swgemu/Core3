/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLACESTRUCTURECOMMAND_H_
#define PLACESTRUCTURECOMMAND_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/deed/structure/StructureDeed.h"
#include "server/zone/managers/planet/PlanetManager.h"

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

		if (creature->getParent() != nullptr) {
			creature->sendSystemMessage("@player_structure:not_inside"); //You can not place a structure while you are inside a building.
			return GENERALERROR;
		}

		ManagedReference<CityRegion*> city = creature->getCityRegion().get();

		if (city != nullptr && city->isClientRegion()) {
			creature->sendSystemMessage("@player_structure:not_permitted"); //Building is not permitted here.
			return GENERALERROR;
		}

		Vector3 playerPosition = creature->getPosition();
		Vector3 placementLoc;

		uint64 deedID;
		int angle;

		try {
			UnicodeTokenizer tokenizer(arguments);

			deedID = tokenizer.getLongToken();
			placementLoc.setX(tokenizer.getFloatToken());
			placementLoc.setY(tokenizer.getFloatToken());
			angle = tokenizer.getIntToken();

			if (angle > 3)
				return GENERALERROR;

			// Validate player position -vs- attempted placement
			Zone* zone = creature->getZone();

			if (zone == nullptr)
				return GENERALERROR;

			placementLoc.setZ(CollisionManager::getWorldFloorCollision(placementLoc.getX(), placementLoc.getY(), zone, false));

			float distance = placementLoc.distanceTo(playerPosition);
			float heightDiff = playerPosition.getZ() - placementLoc.getZ();

			// Client will only scroll about 100m from the placement start position
			if ((distance > 100.0f) || (heightDiff > 10.f)) {
				StringBuffer msg;

				msg << "Player: " << creature->getFirstName() << " ID: " << creature->getObjectID() << " attempted invalid PlaceStructureCommand on "
					<< zone->getZoneName() << " at " << placementLoc.toString()	<< " With a Player Position of: " << playerPosition.toString()
					<< " Distance from placement Location: " << distance << " Height Difference: " << heightDiff;

				creature->error(msg.toString());
				creature->sendSystemMessage("@system_msg:out_of_range");

				return GENERALERROR;
			}

			SortedVector<ManagedReference<ActiveArea* > > activeAreas;

			zone->getInRangeActiveAreas(placementLoc.getX(), placementLoc.getY(), &activeAreas, true);

			for (int i = 0; i < activeAreas.size(); ++i) {
				ActiveArea* area = activeAreas.get(i);

				if (area == nullptr)
					continue;

				if (area->isNoBuildZone()) {
					creature->sendSystemMessage("@player_structure:not_permitted"); //Building is not permitted here.
					return GENERALERROR;
				}
			}

			PlanetManager* planetMan = zone->getPlanetManager();

			if (planetMan == nullptr)
				return GENERALERROR;

			if (planetMan->isInObjectsNoBuildZone(placementLoc.getX(), placementLoc.getY(), 15.0f)) {
				creature->sendSystemMessage("@player_structure:not_permitted"); //Building is not permitted here.
				return GENERALERROR;
			}
		} catch (Exception& e) {
			info(e.getMessage());
			return INVALIDPARAMETERS;
		}

		//We want to begin the session here.
		ManagedReference<StructureDeed*> deed = server->getZoneServer()->getObject(deedID).castTo<StructureDeed*>();

		if (deed != nullptr)
			deed->placeStructure(creature, placementLoc.getX(), placementLoc.getY(), angle * 90);

		return SUCCESS;
	}

};

#endif //PLACESTRUCTURECOMMAND_H_
