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
	float maxMovement;
	bool needsConsent;
public:

	DragIncapacitatedPlayerCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

		maxMovement = 5.0;
		needsConsent = true;
	}

	void getCoordinates(SceneObject* object, SceneObject* targetObject, float maxMove, WorldCoordinates* newPosition) const {
		Vector3 objectPosition = object->getPosition();
		Vector3 tObjectPosition = targetObject->getPosition();

		float distance = objectPosition.distanceTo(tObjectPosition);
		float zPosition;

		if (distance <= maxMove) {
			newPosition->setX(objectPosition.getX());
			newPosition->setY(objectPosition.getY());
			zPosition = objectPosition.getZ();
		} else {
			float dx = objectPosition.getX() - tObjectPosition.getX();
			float dy = objectPosition.getY() - tObjectPosition.getY();
			float dz = objectPosition.getZ() - tObjectPosition.getZ();

			newPosition->setX(tObjectPosition.getX() + (maxMove * (dx / distance)));
			newPosition->setY(tObjectPosition.getY() + (maxMove * (dy / distance)));
			zPosition = (tObjectPosition.getZ() + (maxMove * (dz / distance)));
		}

		Zone* zone = object->getZone();

		if (zone == nullptr) {
			return;
		}

		IntersectionResults intersections;

		CollisionManager::getWorldFloorCollisions(newPosition->getX(), newPosition->getY(), zone, &intersections, (CloseObjectsVector*) object->getCloseObjects());
		float newZ = zone->getPlanetManager()->findClosestWorldFloor(newPosition->getX(), newPosition->getY(), zPosition, 0, &intersections, (CloseObjectsVector*) object->getCloseObjects());

		newPosition->setZ(newZ);

		return;
	}

	bool drag(CreatureObject* player, CreatureObject* targetPlayer, float maxRange, float maxMovement, bool needsConsent) const {
		if (targetPlayer == nullptr) {
			return false;
		}

		if (targetPlayer == player) {
			player->sendSystemMessage("@healing_response:healing_response_a5"); //"You must first have a valid target to drag before you can perform this command."
			return false;
		}

		float sqDistance = targetPlayer->getWorldPosition().squaredDistanceTo(player->getWorldPosition());

		//Check minimum range.
		if (sqDistance < 0.01f*0.01f) {
			return false;
		}

		if (sqDistance > maxRange*maxRange) {
			StringIdChatParameter stringId("healing_response", "healing_response_b1"); //"Your maximum drag range is %DI meters! Try getting closer."
			stringId.setDI(maxRange);
			player->sendSystemMessage(stringId);
			return false;
		}

		if (!targetPlayer->isDead() && !targetPlayer->isIncapacitated()) {
			player->sendSystemMessage("@healing_response:healing_response_a7"); //"You may only drag incapacitated or dying players!"
			return false;
		}

		PlayerObject* targetGhost = targetPlayer->getPlayerObject();

		if (targetGhost == nullptr) {
			return false;
		}

		if (needsConsent) {
			bool hasConsentFrom = targetGhost->hasInConsentList(player->getFirstName().toLowerCase());
			bool isGroupedWith = false;
			ManagedReference<GroupObject*> group = player->getGroup();

			if (group != nullptr && group->hasMember(targetPlayer))
				isGroupedWith = true;

			if (!hasConsentFrom && !isGroupedWith) {
				player->sendSystemMessage("@healing_response:healing_response_b4"); //"You must be grouped with or have consent from your drag target!"
				return false;
			}
		}

		Vector3 dragger = player->getWorldPosition();
		Vector3 target = targetPlayer->getWorldPosition();

		float heightDifference = dragger.getZ() - target.getZ();

		if (abs((int)heightDifference) > maxRange) {
			if (heightDifference > 0) {
				player->sendSystemMessage("@healing_response:healing_response_b2"); //"Your target is too far below you to drag"
				return false;
			} else {
				player->sendSystemMessage("@healing_response:healing_response_b3"); //"Your target is too far above you to drag."
				return false;
			}
		}

		targetGhost->setForcedTransform(true);
		targetPlayer->setSpeedMultiplierMod(1);

		WorldCoordinates newPosition;
		getCoordinates(player, targetPlayer, maxMovement, &newPosition);

		auto msg = player->info();
		msg << "Commenced drag with coordinates:  X = " << dragger.getX() << " Z = " << dragger.getZ() << "  Y = " << dragger.getY();
		msg << " On Player: " << targetPlayer->getFirstName() << " Player ID: " << targetPlayer->getObjectID();
		msg << " To position: X = " << newPosition.getX() << " Z = " << newPosition.getZ() << "  Y = " << newPosition.getY();
		msg.flush();

		float dx = dragger.getX() - target.getX();
		float dy = dragger.getY() - target.getY();
		float directionAngle = atan2(dy, dx);

		directionAngle = M_PI / 2 - directionAngle;

		if (directionAngle < 0) {
			float a = M_PI + directionAngle;
			directionAngle = M_PI + a;
		}

		targetPlayer->setDirection(directionAngle);
		targetPlayer->setPosition(newPosition.getX(), newPosition.getZ(), newPosition.getY());
		targetPlayer->incrementMovementCounter();

		DataTransform* pack = new DataTransform(targetPlayer);
		targetPlayer->broadcastMessage(pack, true, false);

		targetPlayer->showFlyText("base_player", "fly_drag", 255, 0, 0);

		StringIdChatParameter stringId("healing_response", "healing_response_b5"); //"Attempting to drag %TT to your location..."
		stringId.setTT(targetPlayer->getObjectID());
		player->sendSystemMessage(stringId);

		targetPlayer->setSpeedMultiplierMod(0);

		return true;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		int result = doCommonMedicalCommandChecks(creature);

		if (result != SUCCESS) {
			return result;
		}

		if (!creature->isPlayerCreature()) {
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == nullptr || !object->isPlayerCreature() || object == creature) {
			creature->sendSystemMessage("@healing_response:healing_response_a5"); //"You must first have a valid target to drag before you can perform this command."
			return GENERALERROR;
		}

		CreatureObject* targetPlayer = cast<CreatureObject*>( object.get());
		CreatureObject* player = cast<CreatureObject*>(creature);

		Locker clocker(targetPlayer, player);

		if (player->getZone() == nullptr) {
			return GENERALERROR;
		}

		if (targetPlayer->getZone() == nullptr) {
			return GENERALERROR;
		}

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

		if (player->getLocalZone() == nullptr) {
			if (targetPlayer->getLocalZone() != nullptr) {
				player->sendSystemMessage("@error_message:corpse_drag_into"); //You cannot drag a corpse into a structure.
				return GENERALERROR;
			} else {
				player->sendSystemMessage("@error_message:corpse_drag_inside"); //You cannot drag a corpse within a building. Go outside to have your corpse ejected.
				return GENERALERROR;
			}
		} else if (targetPlayer->getLocalZone() == nullptr) {
			player->sendSystemMessage("@error_message:corpse_drag_inside"); //You cannot drag a corpse within a building. Go outside to have your corpse ejected.
			return GENERALERROR;
		}

		float maxRange = 10.f;
		float rangeMod = player->getSkillMod("healing_ability");

		maxRange += (rangeMod * 0.2);

		if (drag(player, targetPlayer, maxRange, maxMovement, needsConsent)) {

			checkForTef(player, targetPlayer);

			return SUCCESS;
		}

		return GENERALERROR;
	}

};

#endif //DRAGINCAPACITATEDPLAYERCOMMAND_H_
