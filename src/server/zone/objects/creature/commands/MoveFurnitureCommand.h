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

#ifndef MOVEFURNITURECOMMAND_H_
#define MOVEFURNITURECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/packets/object/DataTransform.h"
#include "server/zone/packets/object/DataTransformWithParent.h"
#include "server/zone/templates/appearance/PortalLayout.h"
#include "server/zone/templates/appearance/FloorMesh.h"
#include "server/zone/templates/appearance/MeshAppearanceTemplate.h"

class MoveFurnitureCommand : public QueueCommand {
public:

	MoveFurnitureCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	const static int UP = 1;
	const static int DOWN = 2;
	const static int FORWARD = 3;
	const static int BACK = 4;

	//returns false on collision detection
	bool checkCollision(SceneObject* object, int dir, float dist, float radians) {
		ManagedReference<SceneObject*> parent = object->getParent();

		if (parent == NULL || !parent->isCellObject())
			return true;

		CellObject* cell = (CellObject*) parent.get();

		SharedObjectTemplate* objectTemplate = parent->getRootParent()->getObjectTemplate();
		PortalLayout* portalLayout = objectTemplate->getPortalLayout();

		if (portalLayout == NULL)
			return true;

		MeshAppearanceTemplate* appearanceMesh = portalLayout->getMeshAppearanceTemplate(cell->getCellNumber());

		if (appearanceMesh == NULL) {
			//info("null appearance mesh ");
			return true;
		}

		//doing a bruteforce test, TODO: implement sweep test

		float radius = 0.1;

		if (dist < radius)
			dist = radius;

		float checkedDistance = 0.1;

		Vector3 currentPosition = object->getPosition();

		if (dir != DOWN && dir != UP) {
			while (checkedDistance <= dist) {
				float offsetX = checkedDistance * sin(radians);
				float offsetY = checkedDistance * cos(radians);

				switch (dir) {
				case FORWARD: {
					float x = currentPosition.getX() + offsetX;
					float y = currentPosition.getY() + offsetY;

					if (appearanceMesh->testCollide(x, object->getPositionZ() + 0.1, y, radius))
						return false;

					break;
				}

				case BACK: {
					float x = currentPosition.getX() - offsetX;
					float y = currentPosition.getY() - offsetY;

					if (appearanceMesh->testCollide(x, object->getPositionZ() + 0.1, y, radius))
						return false;
					break;
				}
				}

				checkedDistance += radius;
			}
		} else if (dir == UP || dir == DOWN) {
			while (checkedDistance <= dist) {

				switch (dir) {
				case UP:
					if (appearanceMesh->testCollide(currentPosition.getX(), currentPosition.getZ() + checkedDistance + 0.1, currentPosition.getY(), radius))
						return false;

					break;


				case DOWN:
					if (appearanceMesh->testCollide(currentPosition.getX(), currentPosition.getZ() - checkedDistance + 0.1, currentPosition.getY(), radius))
						return false;

					break;
				}

				checkedDistance += radius;
			}
		}

		return true;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		if (!creature->isPlayerCreature())
			return INVALIDPARAMETERS;

		PlayerCreature* player = (PlayerCreature*) creature;

		ManagedReference<SceneObject*> rootParent = creature->getRootParent();

		BuildingObject* buildingObject = rootParent != NULL ? (rootParent->isBuildingObject() ? (BuildingObject*)rootParent.get() : NULL) : NULL;

		if (!player->getPlayerObject()->isPrivileged()) {
			if (buildingObject == NULL) {
				creature->sendSystemMessage("@player_structure:must_be_in_building"); //You must be in a building to do that.
				return GENERALERROR;
			}

			if (!buildingObject->isOnAdminList(creature)) {
				creature->sendSystemMessage("@player_structure:must_be_admin"); //You must be a building admin to do that.
				return GENERALERROR;
			}
		}

		StringTokenizer tokenizer(arguments.toString());
		tokenizer.setDelimeter(" ");

		if (!tokenizer.hasMoreTokens())
			return GENERALERROR;

		String dir;
		tokenizer.getStringToken(dir);

		if (dir != "up" && dir != "down" && dir != "forward" && dir != "back")
			return GENERALERROR;

		if (!tokenizer.hasMoreTokens())
			return GENERALERROR;

		float dist = tokenizer.getFloatToken();

		if (dist < 1 || dist > 500) {
			creature->sendSystemMessage("@player_structure:movefurniture_params"); //The amount to move must be between 1 and 500.
			return GENERALERROR;
		}

		ZoneServer* zoneServer = creature->getZoneServer();
		ManagedReference<SceneObject*> obj = zoneServer->getObject(target);

		if (obj == NULL) {
			creature->sendSystemMessage("@player_structure:rotate_what"); //What do you want to rotate?
			return false;
		}

		if (!player->getPlayerObject()->isPrivileged()) {
			if (obj->getRootParent() != buildingObject || obj->isTerminal()) {
				creature->sendSystemMessage("@player_structure:rotate_what"); //What do you want to rotate?
				return false;
			}
		}

		float degrees = creature->getDirectionAngle();
		float radians = Math::deg2rad(degrees);

		dist /= 100.0f;

		float offsetX = dist * sin(radians);
		float offsetY = dist * cos(radians);

		float x = obj->getPositionX();
		float y = obj->getPositionY();
		float z = obj->getPositionZ();

		if (dir == "forward") {
			if (!checkCollision(obj, FORWARD, dist, radians)) {
				player->sendSystemMessage("@player_structure:not_valid_location"); //That is not a valid location.
				return GENERALERROR;
			}

			x += (offsetX);
			y += (offsetY);
		} else if (dir == "back") {
			if (!checkCollision(obj, BACK, dist, radians)) {
				player->sendSystemMessage("@player_structure:not_valid_location"); //That is not a valid location.
				return GENERALERROR;
			}

			x -= (offsetX);
			y -= (offsetY);
		} else if (dir == "up") {
			if (!checkCollision(obj, UP, dist, radians)) {
				player->sendSystemMessage("@player_structure:not_valid_location"); //That is not a valid location.
				return GENERALERROR;
			}

			z += dist;
		} else if (dir == "down") {
			if (!checkCollision(obj, DOWN, dist, radians)) {
				player->sendSystemMessage("@player_structure:not_valid_location"); //That is not a valid location.
				return GENERALERROR;
			}

			z -= dist;
		}

		//TODO: Check to make sure the item is not being moved outside the range of the cell.
		//Need cell dimensions for this...

		/*StringBuffer msg;
		msg << "moving to x:" << x << " z:" << z << " y:" << y;
		obj->info(msg.toString(), true);*/

		obj->setPosition(x, z, y);
		obj->incrementMovementCounter();

		if (obj->getParent() != NULL)
			obj->teleport(x, z, y, obj->getParent()->getObjectID());
		else
			obj->teleport(x, z, y);

		return SUCCESS;
	}

};

#endif //MOVEFURNITURECOMMAND_H_
