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

#ifndef DRAGINCAPACITATEDPLAYERCOMMAND_H_
#define DRAGINCAPACITATEDPLAYERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DragIncapacitatedPlayerCommand : public QueueCommand {
	float maxRange, maxMovement;
	bool needsConsent;
public:

	DragIncapacitatedPlayerCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
		
		maxRange = 31.0;
		maxMovement = 5.0;
		needsConsent = true;
	}

	void getCoordinate(SceneObject* object1, SceneObject* object2, float distanceFromObject1, WorldCoordinates* newPosition) {
		ManagedReference<SceneObject*> object1Cell = object1->getParent().get();
		ManagedReference<SceneObject*> object2Cell = object2->getParent().get();
		Vector3 object1Position = object1->getPosition();
		Vector3 object2Position = object2->getPosition();

		if (object2Cell != NULL) {
			if (object1Cell == NULL)
				object1Position = PathFinderManager::transformToModelSpace(object1Position, object2Cell->getParent().get());
		} else {
			object1Position = object1->getWorldPosition();
		}

		float distance = object1Position.distanceTo(object2Position);

		if (distanceFromObject1 == 0 || distance == 0) {
			newPosition->setCoordinates(object1Position);
			newPosition->setCell(object1Cell);
			return;

		} else if (distance < distanceFromObject1) {
			newPosition->setCoordinates(object2Position);
			newPosition->setCell(object2Cell);
			return;
		}

		float dx = object2Position.getX() - object1Position.getX();
		float dy = object2Position.getY() - object1Position.getY();

		newPosition->setX(object1Position.getX() + (distanceFromObject1 * (dx / distance)));
		newPosition->setY(object1Position.getY() + (distanceFromObject1 * (dy / distance)));
		newPosition->setCell(object2Cell);

		if (object2Cell == NULL) {
			Zone* zone = object1->getZone();
			if (zone != NULL) {
				IntersectionResults intersections;
				CollisionManager::getWorldFloorCollisions(newPosition->getX(), newPosition->getY(), zone, &intersections, (CloseObjectsVector*) object1->getCloseObjects());
				newPosition->setZ(zone->getPlanetManager()->findClosestWorldFloor(newPosition->getX(), newPosition->getY(), object1->getWorldPositionZ(), 0, &intersections, (CloseObjectsVector*) object1->getCloseObjects()));
			}

		} else {
			newPosition->setZ(object2Position.getZ());
		}

		return;
	}

	void drag(CreatureObject* player, CreatureObject* targetPlayer, float maxRange, float maxMovement, bool needsConsent, bool canDragLiveTarget) {
		if (targetPlayer == NULL) {
			return;
		}

		if (targetPlayer == player) {
			player->sendSystemMessage("@healing_response:healing_response_a5"); //"You must first have a valid target to drag before you can perform this command."
			return;
		}

		//Check minimum range.
		if (player->isInRange(targetPlayer, 0.01f)) {
			return;
		}

		//Check maximum range.
		if (!player->isInRange(targetPlayer, maxRange)) {
			StringIdChatParameter stringId("healing_response", "healing_response_b1"); //"Your maximum drag range is %DI meters! Try getting closer."
			stringId.setDI(maxRange);
			player->sendSystemMessage(stringId); 
			return;
		}

		//Check if target is dead or incapacitated.
		if (!canDragLiveTarget) {
			if (!targetPlayer->isDead() && !targetPlayer->isIncapacitated()) {
				player->sendSystemMessage("@healing_response:healing_response_a7"); //"You may only drag incapacitated or dying players!"
				return;
			}
		}

		PlayerObject* targetGhost = targetPlayer->getPlayerObject();

		//Check for consent to drag.
		if (needsConsent) {
			bool hasConsentFrom = targetGhost->hasInConsentList(player->getFirstName().toLowerCase());
			bool isGroupedWith = false;
			ManagedReference<GroupObject*> group = player->getGroup();

			if (group != NULL && group->hasMember(targetPlayer))
				isGroupedWith = true;

			if (!hasConsentFrom && !isGroupedWith) {
				player->sendSystemMessage("@healing_response:healing_response_b4"); //"You must be grouped with or have consent from your drag target!"
				return;
			}
		}

		//Collect locations of the dragger and the target player.
		Vector3 dragger = player->getWorldPosition();
		Vector3 target = targetPlayer->getWorldPosition();

		//Check for height being too far above or below.
		float heightDifference = dragger.getZ() - target.getZ();

		if (abs((int)heightDifference) > maxRange) {
			if (heightDifference > 0) {
				player->sendSystemMessage("@healing_response:healing_response_b2"); //"Your target is too far below you to drag"
				return;
			} else {
				player->sendSystemMessage("@healing_response:healing_response_b3"); //"Your target is too far above you to drag."
				return;
			}
		}

		//Set the proper orientation of the target (feet toward the dragger).
		float dx = dragger.getX() - target.getX();
		float dy = dragger.getY() - target.getY();
		float directionangle = atan2(dy, dx);
		float radangle = M_PI / 2 - directionangle;
		targetPlayer->setDirection(radangle);

		//Set the new location of the target player.
		WorldCoordinates newPosition;
		getCoordinate(targetPlayer, player, maxMovement, &newPosition);
		targetPlayer->setPosition(newPosition.getX(), newPosition.getZ(), newPosition.getY());
		targetPlayer->incrementMovementCounter();
		ManagedReference<SceneObject*> cell = newPosition.getCell();
		uint64 parentID = 0;

		if (cell != NULL) {
			parentID = cell->getObjectID();
			targetPlayer->updateZoneWithParent(cell, false);
		} else {
			targetPlayer->updateZone(false);
		}

		targetPlayer->teleport(newPosition.getX(), newPosition.getZ(), newPosition.getY(), parentID); //Updates targetPlayer with the new location.

		//Visuals.
		targetPlayer->showFlyText("base_player", "fly_drag", 255, 0, 0);

		StringIdChatParameter stringId("healing_response", "healing_response_b5"); //"Attempting to drag %TT to your location..."
		stringId.setTT(targetPlayer->getObjectID());
		player->sendSystemMessage(stringId);
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		int result = doCommonMedicalCommandChecks(creature);

		if (result != SUCCESS)
			return result;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL || !object->isPlayerCreature() || object == creature) {
			creature->sendSystemMessage("@healing_response:healing_response_a5"); //"You must first have a valid target to drag before you can perform this command."
			return GENERALERROR;
		}

		CreatureObject* targetPlayer = cast<CreatureObject*>( object.get());
		CreatureObject* player = cast<CreatureObject*>(creature);

		Locker clocker(targetPlayer, creature);
		
		if (creature->getZone() == NULL)
			return GENERALERROR;
			
		if (targetPlayer->getZone() == NULL)
			return GENERALERROR;

		//Determine if the player has the proper skill.
		if (!player->hasSkill("science_medic_injury_speed_02")) {
			player->sendSystemMessage("@healing_response:healing_response_a9"); //"You lack the ability to drag incapacitated players!"
			return GENERALERROR;
		}

		if (!targetPlayer->isHealableBy(creature)) {
			player->sendSystemMessage("@healing:pvp_no_help"); //It would be unwise to help such a patient.
			return GENERALERROR;
		}		

		//Attempt to drag the target player.
		drag(player, targetPlayer, maxRange, maxMovement, needsConsent, false);

		return SUCCESS;
	}

};

#endif //DRAGINCAPACITATEDPLAYERCOMMAND_H_
