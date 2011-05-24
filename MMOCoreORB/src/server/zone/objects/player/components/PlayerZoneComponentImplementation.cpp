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

#include "PlayerZoneComponent.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/building/BuildingObject.h"

void PlayerZoneComponentImplementation::notifyInsert(QuadTreeEntry* entry) {
	SceneObject* scno = (SceneObject*) entry;

	if (scno == NULL || scno == sceneObject)
		return;

	if (scno->isPlayerCreature()) {
		PlayerCreature* player = (PlayerCreature*) scno;

		if (player->isInvisible())
			return;

	}

	//TODO: fix cell movement for this to not happen
	/*SceneObject* grandParent = getRootParent();

	if (parent != NULL) {
		if (grandParent == scno) { // we already should have sent our grandParent to owner

			if (grandParent->isBuildingObject())
				((BuildingObject*)grandParent)->addNotifiedSentObject(sceneObject);

			return;
		}
	}

	if (scno->getParent() != NULL) {
		//check the parent if its building
		//check if the building has me as notified
		//if it has me than send the object without the buio
		//if it hasnt me than dont send me and wait for the building to be sent
		//TODO: check if we need this for every object or only for buildings
		SceneObject* scnoGrandParent = scno->getRootParent();

		if (scnoGrandParent->isBuildingObject()) {
			BuildingObject* building = (BuildingObject*)scnoGrandParent;

			if (!building->hasNotifiedSentObject(sceneObject))
				return;
		} else // we wait for the Objects parent to get sent
			return;
	}

	if (scno->isBuildingObject())
		((BuildingObject*)scno)->addNotifiedSentObject(sceneObject);*/

	SceneObject* rootParent = scno->getRootParent();

	if (rootParent != NULL && rootParent->isInQuadTree()) {
		if (hasNotifiedSentObject(rootParent) && addNotifiedSentObject(scno) != -1)
			scno->sendTo(sceneObject, true);
		else {
			if (addNotifiedSentObject(rootParent) != -1)
				rootParent->sendTo(sceneObject, true);
		}
	} else if (addNotifiedSentObject(scno) != -1)
		scno->sendTo(sceneObject, true);
}

void PlayerZoneComponentImplementation::notifyDissapear(QuadTreeEntry* entry) {
	SceneObject* scno = (SceneObject*) entry;

	if (scno == NULL || scno == sceneObject)
		return;

	scno->sendDestroyTo(sceneObject);

	removeNotifiedSentObject(scno);
}


void PlayerZoneComponentImplementation::teleport(float newPositionX, float newPositionZ, float newPositionY, uint64 parentID) {
	//sceneObject->setTeleporting(true);

	ZoneComponentImplementation::teleport(newPositionX, newPositionZ, newPositionY, parentID);

	if (sceneObject->isPlayerCreature()) {
		PlayerCreature* player = (PlayerCreature*) sceneObject.get();

		player->setTeleporting(true);
		player->updateLastValidatedPosition();
		player->setMovementCounter(0);
		player->setClientLastMovementStamp(0);
	}
}

/**
 * Updates position of this object to the rest of in range objects
 * @pre { this object is locked}
 * @post { this object is locked, in range objects are updated with the new position }
 * @param lightUpdate if true a standalone message is sent to the in range objects
 */
void PlayerZoneComponentImplementation::updateZone(bool lightUpdate, bool sendPackets) {
	ZoneComponentImplementation::updateZone(lightUpdate, sendPackets);

	if (sceneObject->isPlayerCreature()) {
		PlayerCreature* player = (PlayerCreature*) sceneObject.get();
		player->setSavedParentID(0);
	}
}

void PlayerZoneComponentImplementation::updateZoneWithParent(SceneObject* newParent, bool lightUpdate, bool sendPackets) {
	ZoneComponentImplementation::updateZoneWithParent(newParent, lightUpdate, sendPackets);

	if (sceneObject->getParent() != NULL && sceneObject->isPlayerCreature()) {
		PlayerCreature* player = (PlayerCreature*) sceneObject.get();

		player->setSavedParentID(sceneObject->getParentID());
	}
}

void PlayerZoneComponentImplementation::insertToBuilding(BuildingObject* building) {
	ZoneComponentImplementation::insertToBuilding(building);

	building->onEnter(dynamic_cast<PlayerCreature*>(sceneObject.get()));
}

void PlayerZoneComponentImplementation::removeFromBuilding(BuildingObject* building) {
	ZoneComponentImplementation::removeFromBuilding(building);

	building->onExit(dynamic_cast<PlayerCreature*>(sceneObject.get()));
}

