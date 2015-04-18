/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORAGEAREACOLLECTION_H_
#define FORAGEAREACOLLECTION_H_

#include "ForageArea.h"
#include "server/zone/managers/minigames/events/ForageCleanupEvent.h"


class ForageAreaCollection : public Object {

protected:

	Vector<Reference<ForageArea*> > forageAreas;
	Reference<Task*> cleanupEvent;


public:
	ForageAreaCollection(CreatureObject* player, short forageX, short forageY, const String& planet, int forageAreaType ) {
    	//Player is foraging for the first time, so make a new forage area.
		Reference<ForageArea*> newArea = new ForageArea(forageX, forageY, planet, forageAreaType);
    	forageAreas.add(newArea);

    	//Queue cleanup event.
    	cleanupEvent = new ForageCleanupEvent(player->getFirstName(), player->getZoneProcessServer());
    	cleanupEvent->schedule(1800000); //30 minutes
	}


	bool checkForageAreas(short forageX, short forageY, const String& planet, int forageAreaType) {
		Reference<ForageArea*> forageArea;
		int8 zoneStatus = -1;
		int8 authorized = -1;

		//Reschedule the cleanup event.
		cleanupEvent->reschedule(1800000); //30 minutes

		//Check forage areas for permission to forage.
		for (int i = 0; i < forageAreas.size(); i++) {
			forageArea = forageAreas.get(i);
			zoneStatus = forageArea->checkPermission(forageX, forageY, planet, forageAreaType);

			switch (zoneStatus) {

				case 0: //Zone is time expired, delete.
					forageAreas.remove(i);
					i -= 1; //Indexes of remaining areas shift down 1 when deleting an element, so compensate.
					break;

				case 1: //Player is not in area, but it's not expired either.
					break;

				case 2: //Player is in this zone but was allowed to forage.
					authorized = i; //Remember which zone gave permission.
					break;

				case 3: //Player is not allowed to forage in this zone, deny.
					return false;

				default: //Shouldn't happen.
					return false;

			}
		}

		//Check if a zone gave permission to forage.
	    if (authorized != -1) {
	    	forageArea = forageAreas.get(authorized);
	    	forageArea->uses += 1; //Add 1 use to the last zone to allow forage (zones can overlap).

	    } else { //Player is not in any zones, so make a new one.
	    	if (forageAreas.size() == 120) //Cap how many zones we remember.
	    		forageAreas.remove(0); //If at capacity, delete the oldest zone.

	    	Reference<ForageArea*> newArea = new ForageArea(forageX, forageY, planet, forageAreaType);
	    	forageAreas.add(newArea);
	    }

	    return true;
	}

};

#endif /*FORAGEAREACOLLECTION_H_*/
