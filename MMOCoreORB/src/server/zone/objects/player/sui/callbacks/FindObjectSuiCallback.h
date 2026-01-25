
#ifndef FINDOBJECTSUICALLBACK_H_
#define FINDOBJECTSUICALLBACK_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"


class FindObjectSuiCallback : public SuiCallback {

public:
	FindObjectSuiCallback(ZoneServer* serv) : SuiCallback(serv) {

	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);
		if (!sui->isListBox() || cancelPressed || server == nullptr)
			return;

		SuiListBox* listBox = cast<SuiListBox*>( sui);

		if(!creature->isPlayerCreature())
			return;

		bool otherPressed = Bool::valueOf(args->get(0).toString());

		int index = Integer::valueOf(args->get(1).toString());

		if(index < 0)
			return;

		uint64 objectID = listBox->getMenuObjectID(index);

		ManagedReference<SceneObject*> object = server->getObject(objectID);

		if (object == nullptr)
			return;

		auto zone = object->getZone();

		if (zone == nullptr) {
			return;
		}

		auto worldPosition = object->getWorldPosition();

		if (otherPressed) {
			StringBuffer arguments;

			Locker locker(object, creature);

			if (object->getParent().get() != nullptr) {
				arguments << String::valueOf(object->getPositionX()) << " " << String::valueOf(object->getPositionY());

				arguments << " " << zone->getZoneName();
				arguments << " " << String::valueOf(object->getPositionZ());
				arguments << " " << String::valueOf(object->getParentID());
			} else {
				arguments << String::valueOf(worldPosition.getX()) << " " << String::valueOf(worldPosition.getY());
				arguments << " " << zone->getZoneName();
			}

			ManagedReference<ObjectController*> objectController = server->getObjectController();
			objectController->activateCommand(creature, STRING_HASHCODE("teleport"), 0, 0, arguments.toString());

		} else {
			Reference<PlayerObject*> ghost = creature->getPlayerObject();

			if (ghost == nullptr) {
				return;
			}

			ManagedReference<WaypointObject*> waypoint = server->createObject(0xc456e788, 1).castTo<WaypointObject*>();

			if (waypoint == nullptr) {
				return;
			}

			Locker locker(waypoint);

			waypoint->setPlanetCRC(object->getPlanetCRC());

			if (zone->isSpaceZone()) {
				waypoint->setPosition(worldPosition.getX(), worldPosition.getZ(), worldPosition.getY());
				waypoint->setColor(WaypointObject::COLOR_SPACE);
			} else {
				waypoint->setPosition(worldPosition.getX(), 0.f, worldPosition.getY());
				waypoint->setColor(WaypointObject::COLOR_GREEN);
			}

			waypoint->setCustomObjectName(object->getDisplayedName(), false);
			waypoint->setActive(true);

			ghost->addWaypoint(waypoint, false, true);
		}
	}
};

#endif /* FINDOBJECTSUICALLBACK_H_ */
