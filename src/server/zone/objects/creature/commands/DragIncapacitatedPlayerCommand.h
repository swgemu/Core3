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
		defaultTime = 0;
		maxRange = 31.0;
		maxMovement = 5.0;
		needsConsent = true;
	}

	Vector3 getCoordinate(SceneObject* object1, SceneObject* object2, float distanceFromObject1) {
		Vector3 newPosition;

		float dx = object2->getPositionX() - object1->getPositionX();
		float dy = object2->getPositionY() - object1->getPositionY();

		float distance = sqrt((dx * dx) + (dy * dy));

		if (distanceFromObject1 == 0 || distance == 0) {
			newPosition.set(object1->getPositionX(), object1->getPositionZ(), object1->getPositionY());
			return newPosition;

		} else if (distance < distanceFromObject1) {
			newPosition.set(object2->getPositionX(), object2->getPositionZ(), object2->getPositionY());
			return newPosition;
		}

		float newPositionX = object1->getPositionX() + (distanceFromObject1 * (dx / distance));
		float newPositionY = object1->getPositionY() + (distanceFromObject1 * (dy / distance));
		float newPositionZ = object1->getZone()->getHeight(newPositionX, newPositionY);

		newPosition.set(newPositionX, newPositionZ, newPositionY);

		return newPosition;
	}

	void drag(PlayerCreature* player, PlayerCreature* targetPlayer, float maxRange, float maxMovement, bool needsConsent, bool canDragLiveTarget) {
		if (targetPlayer == NULL) {
			return;
		}

		if (targetPlayer == player) {
			player->sendSystemMessage("healing_response", "healing_response_a5"); //"You must first have a valid target to drag before you can perform this command."
			return;
		}

		//Check minimum range.
		if (player->isInRange(targetPlayer, 0.01f)) {
			return;
		}

		//Check maximum range.
		if (!player->isInRange(targetPlayer, maxRange)) {
			StringIdChatParameter stringId("healing_response", "healing_response_b1");
			stringId.setDI(maxRange);
			player->sendSystemMessage(stringId); //"Your maximum drag range is %DI meters! Try getting closer."
			return;
		}

		//Check if target is dead or incapacitated.
		if (!canDragLiveTarget) {
			if (!targetPlayer->isDead() && !targetPlayer->isIncapacitated()) {
				player->sendSystemMessage("healing_response", "healing_response_a7"); //"You may only drag incapacitated or dying players!"
				return;
			}
		}

		//Check for consent to drag.
		if (needsConsent) {
			bool hasConsentFrom = targetPlayer->hasInConsentList(player->getFirstName().toLowerCase());
			bool isGroupedWith = false;
			ManagedReference<GroupObject*> group = player->getGroup();

			if (group != NULL && group->hasMember(targetPlayer))
				isGroupedWith = true;

			if (!hasConsentFrom && !isGroupedWith) {
				player->sendSystemMessage("healing_response", "healing_response_b4"); //"You must be grouped with or have consent from your drag target!"
				return;
			}
		}

		//Collect locations of the dragger and the target player.
		Vector3 dragger = player->getPosition();
		Vector3 target = targetPlayer->getPosition();

		//Check for height being too far above or below.
		float heightDifference = dragger.getZ() - target.getZ();

		if (abs((int)heightDifference) > maxRange) {
			if (heightDifference > 0) {
				player->sendSystemMessage("healing_response", "healing_response_b2"); //"Your target is too far below you to drag"
				return;
			} else {
				player->sendSystemMessage("healing_response", "healing_response_b3"); //"Your target is too far above you to drag."
				return;
			}
		}

		//Set the proper orientation of the target (feet toward the dragger).
		float dx = dragger.getX() - target.getX();
		float dy = dragger.getY() - target.getY();
		float directionangle = atan2(dy, dx);
		float radangle = M_PI / 2 - directionangle;
		//targetPlayer->setDirection()
		targetPlayer->setDirection(radangle);

		//Set the new location of the target player.
		Vector3 newPosition = getCoordinate(targetPlayer, player, maxMovement);
		targetPlayer->setPosition(newPosition.getX(), newPosition.getZ(), newPosition.getY());
		targetPlayer->incrementMovementCounter();
		SceneObject* parent = player->getParent();
		//targetPlayer->updatePlayerPosition(false); //Updates everyone except targetPlayer of their movement.
		if (parent != NULL && parent->isCellObject()) {
			targetPlayer->updateZoneWithParent(parent, false);
		} else {
			targetPlayer->updateZone(false);
		}

		targetPlayer->teleport(newPosition.getX(), newPosition.getZ(), newPosition.getY(), player->getParentID()); //Updates targetPlayer with the new location.

		//Visuals.
		targetPlayer->showFlyText("base_player", "fly_drag", 255, 0, 0);

		StringIdChatParameter stringId("healing_response", "healing_response_b5");
		stringId.setTT(targetPlayer->getObjectID());
		player->sendSystemMessage(stringId);
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL || !object->isPlayerCreature() || object == creature) {
			creature->sendSystemMessage("healing_response", "healing_response_a5"); //"You must first have a valid target to drag before you can perform this command."
			return GENERALERROR;
		}

		PlayerCreature* targetPlayer = (PlayerCreature*) object.get();
		PlayerCreature* player = (PlayerCreature*) creature;

		Locker clocker(targetPlayer, creature);

		//Determine if the player has the proper skill.
		if (!player->hasSkillBox("science_medic_injury_speed_02")) {
			player->sendSystemMessage("healing_response", "healing_response_a9"); //"You lack the ability to drag incapacitated players!"
			return GENERALERROR;
		}


		/*if (target->isPlayer()) {
			targetPlayer = (Player*)target;
		} else {
			player->sendSystemMessage("healing_response", "healing_response_a6"); //"You may only drag players!"
			return GENERALERROR;
		}

		if (targetPlayer == player) {
			player->sendSystemMessage("healing_response", "healing_response_a5"); //"You must first have a valid target to drag before you can perform this command."
			return GENERALERROR;
		}*/

		//Determine the maximum drag range.
		/*int skillMod = player->getSkillMod("healing_injury_speed");

		float actualRange = (float)skillMod / 3.75f;

		if (actualRange > maxRange) {
			actualRange = maxRange;
		}*/

		//Attempt to drag the target player.
		drag(player, targetPlayer, maxRange, maxMovement, needsConsent, false);

		return SUCCESS;
	}

};

#endif //DRAGINCAPACITATEDPLAYERCOMMAND_H_
