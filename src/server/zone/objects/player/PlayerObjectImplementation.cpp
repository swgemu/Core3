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

#include "PlayerObject.h"

#include "../../managers/object/ObjectManager.h"
#include "server/zone/ZoneClientSession.h"
#include "server/zone/packets/player/PlayerObjectMessage3.h"
#include "server/zone/packets/player/PlayerObjectDeltaMessage3.h"
#include "server/zone/packets/player/PlayerObjectDeltaMessage8.h"

#include "server/zone/packets/player/PlayerObjectMessage6.h"
#include "server/zone/packets/player/PlayerObjectMessage8.h"

#include "server/zone/objects/waypoint/WaypointObject.h"


void PlayerObjectImplementation::initializeTransientMembers() {
	IntangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("PlayerObject");
}

void PlayerObjectImplementation::loadTemplateData(LuaObject* templateData) {
	characterBitmask = ANONYMOUS;

	adminLevel = 0;

	forcePower = 0;
	forcePowerMax = 0;
}

void PlayerObjectImplementation::sendBaselinesTo(SceneObject* player) {
	info("sending player object baselines");

	BaseMessage* play3 = new PlayerObjectMessage3(_this);
	player->sendMessage(play3);

	BaseMessage* play6 = new PlayerObjectMessage6(_this);
	player->sendMessage(play6);

	BaseMessage* play8 = new PlayerObjectMessage8(this);
	player->sendMessage(play8);
}

void PlayerObjectImplementation::sendMessage(BasePacket* msg) {
	if (parent == NULL)
		delete msg;

	parent->sendMessage(msg);
}

bool PlayerObjectImplementation::setCharacterBit(uint32 bit, bool notifyClient) {
	if (!(characterBitmask & bit)) {
		characterBitmask |= bit;

		if (notifyClient) {
			PlayerObjectDeltaMessage3* delta = new PlayerObjectDeltaMessage3((PlayerObject*) _this);
			delta->updateCharacterBitmask(characterBitmask);
			delta->close();

			broadcastMessage(delta, true);
		}
		return true;
	} else
		return false;
}

bool PlayerObjectImplementation::clearCharacterBit(uint32 bit, bool notifyClient) {
	if (characterBitmask & bit) {
		characterBitmask &= ~bit;

		if (notifyClient) {
			PlayerObjectDeltaMessage3* delta = new PlayerObjectDeltaMessage3((PlayerObject*) _this);
			delta->updateCharacterBitmask(characterBitmask);
			delta->close();

			broadcastMessage(delta, true);
		}

		return true;
	} else
		return false;
}


void PlayerObjectImplementation::addExperience(const String& xpType, int xp, bool notifyClient) {
	if (experienceList.contains(xpType)) {
		xp += experienceList.get(xpType);

		if (xp <= 0) {
			removeExperience(xpType, notifyClient);
			return;
		}
	}

	if (notifyClient) {
		PlayerObjectDeltaMessage8* dplay8 = new PlayerObjectDeltaMessage8(this);
		dplay8->startUpdate(0);
		experienceList.set(xpType, xp, dplay8, 1);
		dplay8->close();

		sendMessage(dplay8);
	} else {
		experienceList.set(xpType, xp);
	}
}

void PlayerObjectImplementation::removeExperience(const String& xpType, bool notifyClient) {
	if (!experienceList.contains(xpType))
		return;

	if (notifyClient) {
		PlayerObjectDeltaMessage8* dplay8 = new PlayerObjectDeltaMessage8(this);
		dplay8->startUpdate(0);
		experienceList.drop(xpType, dplay8, 1);
		dplay8->close();

		sendMessage(dplay8);
	} else {
		experienceList.drop(xpType);
	}
}

void PlayerObjectImplementation::addWaypoint(WaypointObject* waypoint, bool notifyClient) {
	uint64 waypointID = waypoint->getObjectID();

	if (waypointList.contains(waypointID)) {
		error("this contains this waypoint ID");
		return;
	}

	if (notifyClient) {
		PlayerObjectDeltaMessage8* msg = new PlayerObjectDeltaMessage8(this);
		msg->startUpdate(1);
		waypointList.set(waypointID, waypoint, msg, 1);
		msg->close();

		sendMessage(msg);
	} else {
		waypointList.set(waypointID, waypoint);
	}

	waypoint->updateToDatabase();
}

void PlayerObjectImplementation::addWaypoint(const String& planet, float positionX, float positionY, bool notifyClient) {
	ManagedReference<WaypointObject*> obj = (WaypointObject*) ObjectManager::instance()->createObject(3038003230, 2, "waypoints");
	obj->setPlanetCRC(planet.hashCode());
	obj->setPosition(positionX, 0, positionY);
	obj->setActive(true);

	addWaypoint(obj, notifyClient);
}

