/*
 * GotoSuiCallback.h
 *
 * Created: Sun Feb 28 07:01:21 EST 2016
 *  Author: lordkator
 */

#ifndef GOTOSUICALLBACK_H_
#define GOTOSUICALLBACK_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/waypoint/WaypointObject.h"

class GotoSuiCallback : public SuiCallback {

public:
	GotoSuiCallback(ZoneServer* serv) : SuiCallback(serv) {

	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		if (server == NULL || server->isServerLoading())
			return;

		bool cancelPressed = (eventIndex == 1);

		if (!sui->isListBox() || cancelPressed)
			return;

		SuiListBox* listBox = cast<SuiListBox*>( sui);

		if(!creature->isPlayerCreature())
			return;

		int index = Integer::valueOf(args->get(0).toString());

		if(index < 0)
			return;

		uint64 objectID = listBox->getMenuObjectID(index);

		ManagedReference<SceneObject*> object = server->getObject(objectID);

		if (object == NULL)
			return;

		ManagedReference<WaypointObject*> wp = cast<WaypointObject*>(object.get());

		if (wp == NULL)
		    return;

		Locker locker(wp, creature);

		String zoneName = "";

		for (int i = 0; i < server->getZoneCount(); ++i) {
			Zone* zone = server->getZone(i);

			if (zone == NULL)
				continue;

			if (zone->getZoneName().hashCode() == wp->getPlanetCRC()) {
				zoneName = zone->getZoneName();
				break;
			}
		}

		if (zoneName != "")
		    creature->switchZone(zoneName, wp->getPositionX(), wp->getPositionZ(), wp->getPositionY(), 0);
	}
};

#endif /* GOTOSUICALLBACK_H_ */
