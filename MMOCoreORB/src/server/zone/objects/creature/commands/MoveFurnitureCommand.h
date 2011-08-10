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

	//returns false on collision detection
	bool checkCollision(SceneObject* object, Vector3& endPoint) {
		ManagedReference<SceneObject*> parent = object->getParent();

		if (parent == NULL || !parent->isCellObject())
			return true;

		CellObject* cell = (CellObject*) parent.get();

		SharedObjectTemplate* objectTemplate = parent->getRootParent()->getObjectTemplate();
		PortalLayout* portalLayout = objectTemplate->getPortalLayout();
		MeshAppearanceTemplate* appearanceMesh = NULL;

		if (portalLayout == NULL)
			return true;

		try {
			appearanceMesh = portalLayout->getMeshAppearanceTemplate(cell->getCellNumber());
		} catch (Exception& e) {
			return true;
		}

		if (appearanceMesh == NULL) {
			//info("null appearance mesh ");
			return true;
		}

		AABBTree* aabbTree = appearanceMesh->getAABBTree();

		if (aabbTree == NULL)
			return true;

		//switching Y<->Z, adding 0.1 to account floor
		Vector3 startPoint = object->getPosition();
		startPoint.set(startPoint.getX(), startPoint.getY(), startPoint.getZ() + 0.1f);

		endPoint.set(endPoint.getX(), endPoint.getY(), endPoint.getZ() + 0.1f);

		Vector3 dir = endPoint - startPoint;
		dir.normalize();

		float distance = endPoint.distanceTo(startPoint);
		float intersectionDistance;

		Ray ray(startPoint, dir);

		Triangle* triangle = NULL;

		//nothing in the middle
		if (aabbTree->intersects(ray, distance, intersectionDistance, triangle, true))
			return false;

		Ray ray2(endPoint, Vector3(0, -1, 0));

		//check if we are in the cell with dir (0, -1, 0)
		if (!aabbTree->intersects(ray2, 64000.f, intersectionDistance, triangle, true))
			return false;

		return true;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		ManagedReference<SceneObject*> rootParent = creature->getRootParent();

		BuildingObject* buildingObject = rootParent != NULL ? (rootParent->isBuildingObject() ? (BuildingObject*)rootParent.get() : NULL) : NULL;

		if (!creature->getPlayerObject()->isPrivileged()) {
			if (buildingObject == NULL) {
				creature->sendSystemMessage("@player_structure:must_be_in_building"); //You must be in a building to do that.
				return GENERALERROR;
			}

			if (!buildingObject->isOnAdminList(creature->getFirstName())) {
				creature->sendSystemMessage("@player_structure:must_be_admin"); //You must be a building admin to do that.
				return GENERALERROR;
			}
		}

		String dir;
		float dist = 0.f;

		try {
			UnicodeTokenizer tokenizer(arguments.toString());
			tokenizer.getStringToken(dir);
			dir = dir.toLowerCase();

			dist = tokenizer.getIntToken();

			if (dir != "up" && dir != "down" && dir != "forward" && dir != "back")
				throw Exception();

		} catch (Exception& e) {
			creature->sendSystemMessage("@player_structure:format_movefurniture_distance"); //Format: /moveFurniture <FORWARD/BACK/UP/DOWN> <distance>
			return INVALIDPARAMETERS;
		}

		if (dist < 1.f || dist > 500.f) {
			creature->sendSystemMessage("@player_structure:movefurniture_params"); //The amount to move must be between 1 and 500.
			return INVALIDPARAMETERS;
		}

		ZoneServer* zoneServer = creature->getZoneServer();
		ManagedReference<SceneObject*> obj = zoneServer->getObject(target);

		if (obj == NULL) {
			creature->sendSystemMessage("@player_structure:move_what"); //What do you want to move?
			return INVALIDTARGET;
		}

		if (!creature->getPlayerObject()->isPrivileged()) {
			if (obj->getRootParent() != buildingObject || obj->isTerminal() || obj->isVendor()) {
				if (obj->isVendor())
					creature->sendSystemMessage("@player_structure:cant_move_vendor"); // To move a vendor, pick it up and drop it again in the new location.
				else
					creature->sendSystemMessage("@player_structure:move_what"); //What do you want to move?
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
			x += (offsetX);
			y += (offsetY);
		} else if (dir == "back") {
			x -= (offsetX);
			y -= (offsetY);
		} else if (dir == "up") {
			z += dist;
		} else if (dir == "down") {
			z -= dist;
		}

		Vector3 endPoint(x, y, z);

		if (!checkCollision(obj, endPoint)) {
			creature->sendSystemMessage("@player_structure:not_valid_location"); //That is not a valid location.
			return GENERALERROR;
		}

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
