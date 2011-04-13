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

#ifndef EJECTCOMMAND_H_
#define EJECTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class EjectCommand : public QueueCommand {
public:

	EjectCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		if (!creature->isPlayerCreature())
			return INVALIDPARAMETERS;

		PlayerCreature* player = (PlayerCreature*) creature;
		player->sendSystemMessage("@error_message:sys_eject_request"); //Processing eject request...


		/*
string/en/error_message.stf	122	sys_eject_fail_move	The ejection attempt failed because you moved.
		 */

		if (player->getParent() != NULL) {
			player->sendSystemMessage("@error_message:sys_eject_fail_contained"); //The ejection attempt failed because you are inside a building.
			return GENERALERROR;
		}

		ManagedReference<Zone*> zone = player->getZone();

		if (zone == NULL)
			return GENERALERROR;

		float x = player->getPositionX();
		float y = player->getPositionY();
		float terrainZ = zone->getHeight(x, y);

		if (terrainZ == player->getPositionZ()) {
			player->sendSystemMessage("@error_message:sys_eject_fail_ground"); //The ejection attempt failed because you were already on the ground.
			return GENERALERROR;
		}

		Locker _lock(zone);
		//Find nearest building.
		ManagedReference<BuildingObject*> closestBuilding = NULL;
		float minRange = 16000.f;

		for (int i = 0; i < player->inRangeObjectCount(); ++i) {
			ManagedReference<SceneObject*> obj = (SceneObject*) player->getInRangeObject(i);

			if (obj == NULL || !obj->isBuildingObject())
				continue;

			float objRange = obj->getDistanceTo(player);

			if (objRange < minRange)
				closestBuilding = (BuildingObject*) obj.get();
		}

		if (closestBuilding == NULL) {
			player->sendSystemMessage("@error_message:sys_eject_fail_proximity"); //The eject attempt failed because there isn't a building nearby.
			return GENERALERROR;
		}

		Vector3 pEject = closestBuilding->getEjectionPoint();
		player->teleport(pEject.getX(), pEject.getZ(), pEject.getY(), 0);

		player->sendSystemMessage("@error_message:sys_eject_success"); //You have been moved to the nearest building's ejection point.

		return SUCCESS;
	}

};

#endif //EJECTCOMMAND_H_

