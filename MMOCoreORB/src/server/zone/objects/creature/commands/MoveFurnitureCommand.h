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
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"

class MoveFurnitureCommand : public QueueCommand {
public:

	MoveFurnitureCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	//returns false on collision detection
	bool checkCollision(SceneObject* object, Vector3& endPoint) {
		return CollisionManager::checkLineOfSightInParentCell(object, endPoint);
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == NULL)
			return GENERALERROR;

		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(target);

		if (obj == NULL || !obj->isTangibleObject() || obj->isPlayerCreature() || obj->isPet()) {
			creature->sendSystemMessage("@player_structure:move_what"); //What do you want to move?
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> rootParent = obj->getRootParent();
		ManagedReference<SceneObject*> creatureParent = creature->getRootParent();

		if (creatureParent == NULL || !creatureParent->isBuildingObject()) {
			creature->sendSystemMessage("@player_structure:must_be_in_building"); //You must be in a building to do that.
			return GENERALERROR;
		}

		if (obj->isVendor()) {
			creature->sendSystemMessage("@player_structure:cant_move_vendor"); // To move a vendor, pick it up and drop it again at the new location.
			return GENERALERROR;
		}

		BuildingObject* buildingObject = cast<BuildingObject*>( creatureParent.get());

		if (buildingObject == NULL || obj->getRootParent() != buildingObject || buildingObject->containsChildObject(obj)) {
			creature->sendSystemMessage("@player_structure:move_what"); //What do you want to move?
			return GENERALERROR;
		}

		if (buildingObject != rootParent || !buildingObject->isOnAdminList(creature)) {
			creature->sendSystemMessage("@player_structure:must_be_admin"); //You must be a building admin to do that.
			return GENERALERROR;
		}

		if (buildingObject->isGCWBase()) {
			creature->sendSystemMessage("@player_structure:no_move_hq"); // You may not move or rotate objects inside a factional headquarters.
			return GENERALERROR;
		}

		String dir;
		float dist = 0.f;

		try {
			UnicodeTokenizer tokenizer(arguments);
			tokenizer.getStringToken(dir);
			dir = dir.toLowerCase();

			if (Character::isDigit(dir.charAt(0)))
				throw Exception("Please specify the name of the object before the direction and distance.");

			if (dir != "up" && dir != "down" && dir != "forward" && dir != "back")
				throw Exception("@player_structure:format_movefurniture_distance"); //Format: /moveFurniture <FORWARD/BACK/UP/DOWN> <distance>

			dist = tokenizer.getIntToken();

			if (dist < 1.f || dist > 500.f)
				throw Exception("@player_structure:movefurniture_params"); //The amount to move must be between 1 and 500.

		} catch (ArrayIndexOutOfBoundsException& e) {
			throw Exception("@player_structure:format_movefurniture_distance"); //Format: /moveFurniture <FORWARD/BACK/UP/DOWN> <distance>
			return INVALIDPARAMETERS;

		} catch (Exception& e) {
			creature->sendSystemMessage(e.getMessage());
			return INVALIDPARAMETERS;
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

		obj->incrementMovementCounter();

		if (obj->getParent() != NULL)
			obj->teleport(x, z, y, obj->getParent().get()->getObjectID());
		else
			obj->teleport(x, z, y);


		return SUCCESS;
	}

};

#endif //MOVEFURNITURECOMMAND_H_
