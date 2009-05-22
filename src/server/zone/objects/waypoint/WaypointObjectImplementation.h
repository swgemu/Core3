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

#ifndef WAYPOINTOBJECTIMPLEMENTATION_H_
#define WAYPOINTOBJECTIMPLEMENTATION_H_

#include "WaypointObject.h"

#include "../player/Player.h"

#include "../../packets.h"

#include "../terrain/PlanetNames.h"

class WaypointObjectImplementation : public WaypointObjectServant {
	String internalNote;
	String planetName;

	uint8 waypointType;
	bool activated;

	void init();

public:
	static const uint8 WAYPOINT_WHITE = 0x00; //White is used for what?
	static const uint8 WAYPOINT_NORMAL = 0x01;
	static const uint8 WAYPOINT_GREEN = 0x02; //Quest?

public:
	WaypointObjectImplementation(uint64 objid);
	WaypointObjectImplementation(uint64 objid, SceneObject* obj);

	virtual void insertToZone(Zone* zone);

	//virtual void serialize();
	//virtual void deserialize();

	virtual void activate(Player* player);
	virtual void deactivate(Player* player);
	virtual void updateWaypoint(Player* player);

	virtual void updateCustomName(Player* player, const String& value);

	inline bool toggleActivation() {
		return (activated = !activated);
	}

	//Setters
	inline void setPlanetName(const String& planetname) {
		planetName = planetname;
	}

	inline void setInternalNote(const String& note) {
		internalNote = note;
	}

	inline void setWaypointType(uint8 type) {
		waypointType = type;
	}

	inline void setActivated(bool active) {
		activated = active;
	}

	//Getters
	inline String& getPlanetName() {
		return planetName;
	}

	inline uint32 getPlanetCRC() {
		return planetName.hashCode();
	}

	inline String& getInternalNote() {
		return internalNote;
	}

	inline uint8 getWaypointType() {
		return waypointType;
	}

	inline bool isActivated() {
		return activated;
	}

};

#endif /*WAYPOINTOBJECTIMPLEMENTATION_H_*/
