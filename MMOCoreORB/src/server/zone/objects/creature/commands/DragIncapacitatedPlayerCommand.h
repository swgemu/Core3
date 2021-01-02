/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DRAGINCAPACITATEDPLAYERCOMMAND_H_
#define DRAGINCAPACITATEDPLAYERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/collision/PathFinderManager.h"
#include "server/zone/packets/object/DataTransform.h"

class DragIncapacitatedPlayerCommand : public QueueCommand {
	float maxRange, maxMovement;
	bool needsConsent;
public:

	DragIncapacitatedPlayerCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

		maxRange = 20.0;
		maxMovement = 5.0;
		needsConsent = true;
	}

	void getCoordinates(SceneObject* object1, SceneObject* object2, float distanceFromObject1, WorldCoordinates* newPosition) const {
		Vector3 object1Position = object1->getPosition();
		Vector3 object2Position = object2->getPosition();

		float distance = object1Position.distanceTo(object2Position);

		if (distanceFromObject1 == 0 || distance == 0) {
			newPosition->setCoordinates(object1Position);
			return;

		} else if (distance < distanceFromObject1) {
			newPosition->setCoordinates(object2Position);
			return;
		}

		float dx = object2Position.getX() - object1Position.getX();
		float dy = object2Position.getY() - object1Position.getY();

		newPosition->setX(object1Position.getX() + (distanceFromObject1 * (dx / distance)));
		newPosition->setY(object1Position.getY() + (distanceFromObject1 * (dy / distance)));

		Zone* zone = object1->getZone();

		if (zone != nullptr) {
			IntersectionResults intersections;
			CollisionManager::getWorldFloorCollisions(newPosition->getX(), newPosition->getY(), zone, &intersections, (CloseObjectsVector*) object1->getCloseObjects());
			newPosition->setZ(zone->getPlanetManager()->findClosestWorldFloor(newPosition->getX(), newPosition->getY(), object1->getWorldPositionZ(), 0, &intersections, (CloseObjectsVector*) object1->getCloseObjects()));
		}

		return;
	}

	void drag(CreatureObject* player, CreatureObject* targetPlayer, float maxRange, float maxMovement, bool needsConsent, bool canDragLiveTarget) const {
		if (targetPlayer == nullptr) {
			return;
		}

		if (targetPlayer == player) {
			player->sendSystemMessage("@healing_response:healing_response_a5"); //"You must first have a valid target to drag before you can perform this command."
			return;
		}

		float sqDistance = targetPlayer->getWorldPosition().squaredDistanceTo(player->getWorldPosition());

		//Check minimum range.
		if (sqDistance < 0.01f*0.01f) {
			return;
		}

		//Check maximum range.
		if (sqDistance > maxRange*maxRange) {
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

		if (targetGhost == nullptr) {
			return;
		}

		if (needsConsent) {
			bool hasConsentFrom = targetGhost->hasInConsentList(player->getFirstName().toLowerCase());
			bool isGroupedWith = false;
			ManagedReference<GroupObject*> group = player->getGroup();

			if (group != nullptr && group->hasMember(targetPlayer))
				isGroupedWith = true;

			if (!hasConsentFrom && !isGroupedWith) {
				player->sendSystemMessage("@healing_response:healing_response_b4"); //"You must be grouped with or have consent from your drag target!"
				return;
			}
		}

		Vector3 dragger = player->getWorldPosition();
		Vector3 target = targetPlayer->getWorldPosition();

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

		WorldCoordinates newPosition;
		getCoordinates(player, targetPlayer, maxMovement, &newPosition);
		targetPlayer->setPosition(newPosition.getX(), newPosition.getZ(), newPosition.getY());
		targetPlayer->incrementMovementCounter();

		targetPlayer->updateZone(false, true);
		targetPlayer->teleport(newPosition.getX(), newPosition.getZ(), newPosition.getY(), 0); //Updates targetPlayer with the new location.

		targetPlayer->showFlyText("base_player", "fly_drag", 255, 0, 0);

		StringIdChatParameter stringId("healing_response", "healing_response_b5"); //"Attempting to drag %TT to your location..."
		stringId.setTT(targetPlayer->getObjectID());
		player->sendSystemMessage(stringId);
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		int result = doCommonMedicalCommandChecks(creature);

		if (result != SUCCESS)
			return result;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == nullptr || !object->isPlayerCreature() || object == creature) {
			creature->sendSystemMessage("@healing_response:healing_response_a5"); //"You must first have a valid target to drag before you can perform this command."
			return GENERALERROR;
		}

		CreatureObject* targetPlayer = cast<CreatureObject*>( object.get());
		CreatureObject* player = cast<CreatureObject*>(creature);

		Locker clocker(targetPlayer, player);

		if (player->getZone() == nullptr)
			return GENERALERROR;

		if (targetPlayer->getZone() == nullptr)
			return GENERALERROR;

		if (!player->hasSkill("science_medic_injury_speed_02")) {
			player->sendSystemMessage("@healing_response:healing_response_a9"); //"You lack the ability to drag incapacitated players!"
			return GENERALERROR;
		}

		if (checkForArenaDuel(targetPlayer)) {
			player->sendSystemMessage("@jedi_spam:no_help_target"); // You are not permitted to help that target.
			return GENERALERROR;
		}

		if (!targetPlayer->isHealableBy(creature)) {
			player->sendSystemMessage("@healing:pvp_no_help"); //It would be unwise to help such a patient.
			return GENERALERROR;
		}

		if (!CollisionManager::checkLineOfSight(creature, targetPlayer)) {
			StringIdChatParameter nocansee;
			nocansee.setStringId("@container_error_message:container18_prose"); //You can't see %TT. You may have to move closer to it.
			nocansee.setTT(target);
			player->sendSystemMessage(nocansee);
			return GENERALERROR;
		}

		if (targetPlayer->getLocalZone() == nullptr) {
			player->sendSystemMessage("@error_message:corpse_drag_inside"); //You cannot drag a corpse within a building. Go outside to have your corpse ejected.
			return GENERALERROR;
		}

		if (creature->getLocalZone() == nullptr) {
			if (targetPlayer->getLocalZone() != nullptr) {
				player->sendSystemMessage("@error_message:corpse_drag_into"); //You cannot drag a corpse into a structure.
				return GENERALERROR;
			} else

			return true;
		}

		Reference<CellObject*> targetCell = targetPlayer->getParent().get().castTo<CellObject*>();

		if (targetCell != nullptr) {
			auto perms = targetCell->getContainerPermissions();

			if (!perms->hasInheritPermissionsFromParent()) {
				if (!targetCell->checkContainerPermission(player, ContainerPermissions::WALKIN)) {
					StringIdChatParameter nocansee;
					nocansee.setStringId("@container_error_message:container18_prose");
					nocansee.setTT(target);
					player->sendSystemMessage(nocansee);
					return GENERALERROR;
				}
			}
		}

		drag(player, targetPlayer, maxRange, maxMovement, needsConsent, false);

		checkForTef(player, targetPlayer);

		return SUCCESS;
	}

};

#endif //DRAGINCAPACITATEDPLAYERCOMMAND_H_
