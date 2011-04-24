/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef FORAGEAREACOLLECTION_H_
#define FORAGEAREACOLLECTION_H_

#include "ForageArea.h"
#include "server/zone/managers/minigames/events/ForageCleanupEvent.h"


class ForageAreaCollection : public Object {

protected:

	Vector<Reference<ForageArea*> > forageAreas;
	Reference<Task*> cleanupEvent;


public:
	ForageAreaCollection(PlayerCreature* player, short forageX, short forageY, const String& planet) {
    	//Player is foraging for the first time, so make a new forage area.
		Reference<ForageArea*> newArea = new ForageArea(forageX, forageY, planet);
    	forageAreas.add(newArea);

    	//Queue cleanup event.
    	cleanupEvent = new ForageCleanupEvent(player->getFirstName(), player->getZoneServer());
    	cleanupEvent->schedule(1800000); //30 minutes
	}


	bool checkForageAreas(short forageX, short forageY, const String& planet) {
		Reference<ForageArea*> forageArea;
		int8 zoneStatus = -1;
		int8 authorized = -1;

		//Reschedule the cleanup event.
		cleanupEvent->reschedule(1800000); //30 minutes

		//Check forage areas for permission to forage.
		for (int i = 0; i < forageAreas.size(); i++) {
			forageArea = forageAreas.get(i);
			zoneStatus = forageArea->checkPermission(forageX, forageY, planet);

			switch (zoneStatus) {

				case 0: //Zone is time expired, delete.
					forageAreas.remove(i);
					i -= 1; //Indexes of remaining areas shift down 1 when deleting an element, so compensate.

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

	    	Reference<ForageArea*> newArea = new ForageArea(forageX, forageY, planet);
	    	forageAreas.add(newArea);
	    }

	    return true;
	}

};

#endif /*FORAGEAREACOLLECTION_H_*/
