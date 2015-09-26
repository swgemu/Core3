/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef EJECTCOMMAND_H_
#define EJECTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class EjectCommand : public QueueCommand {
public:

	EjectCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		creature->sendSystemMessage("@error_message:sys_eject_request"); //Processing eject request...

		/*
string/en/error_message.stf	122	sys_eject_fail_move	The ejection attempt failed because you moved.
		 */

		if (creature->getParent() != NULL) {
			creature->sendSystemMessage("@error_message:sys_eject_fail_contained"); //The ejection attempt failed because you are inside a building.
			return GENERALERROR;
		}

		ManagedReference<Zone*> zone = creature->getZone();

		if (zone == NULL)
			return GENERALERROR;

		float x = creature->getPositionX();
		float y = creature->getPositionY();
		float terrainZ = zone->getHeight(x, y);

		if (terrainZ == creature->getPositionZ()) {
			creature->sendSystemMessage("@error_message:sys_eject_fail_ground"); //The ejection attempt failed because you were already on the ground.
			return GENERALERROR;
		}

		Locker _lock(zone);

		//Find nearest building.
		ManagedReference<BuildingObject*> closestBuilding = NULL;
		float minRange = 16000.f;

		CloseObjectsVector* vec = (CloseObjectsVector*) creature->getCloseObjects();

		SortedVector<QuadTreeEntry*> closeObjects;
		vec->safeCopyTo(closeObjects);

		for (int i = 0; i < closeObjects.size(); ++i) {
			ManagedReference<SceneObject*> obj = cast<SceneObject*>( closeObjects.get(i));

			if (obj == NULL || !obj->isBuildingObject())
				continue;

			float objRange = obj->getDistanceTo(creature);

			if (objRange < minRange) {
				closestBuilding = cast<BuildingObject*>( obj.get());
				minRange = objRange;
			}
		}

		if (closestBuilding == NULL) {
			creature->sendSystemMessage("@error_message:sys_eject_fail_proximity"); //The eject attempt failed because there isn't a building nearby.
			return GENERALERROR;
		}

		closestBuilding->ejectObject(creature);
		creature->sendSystemMessage("@error_message:sys_eject_success"); //You have been moved to the nearest building's ejection point.

		return SUCCESS;
	}

};

#endif //EJECTCOMMAND_H_

