/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ROTATEFURNITURECOMMAND_H_
#define ROTATEFURNITURECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/components/EventPerkDataComponent.h"

class RotateFurnitureCommand : public QueueCommand {
public:

	RotateFurnitureCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		bool enhancedRotate = ConfigManager::instance()->getBool("Core3.StructureManager.EnhancedFurnitureRotate", false);

		String dir;
		int degrees = 0;
		bool rotateYaw = false;
		bool rotatePitch = false;
		bool rotateRoll = false;
		bool resetRotate = false;

		try {
			UnicodeTokenizer tokenizer(arguments.toString());
			tokenizer.getStringToken(dir);
			degrees = tokenizer.getIntToken();

			dir = dir.toLowerCase();

			if (enhancedRotate) {
				if (dir == "yaw" || dir == "right" || dir == "left")
					rotateYaw = true;
				else if (dir == "pitch")
					rotatePitch = true;
				else if (dir == "roll")
					rotateRoll = true;
				else if (dir == "reset")
					resetRotate = true;
				else
					throw Exception();
			} else {
				if (dir == "left" || dir == "right")
					rotateYaw = true;
				else
					throw Exception();
			}
		} catch (Exception& e) {
			if (enhancedRotate) {
				creature->sendSystemMessage("Format: /rotateFurniture <yaw/pitch/roll> [degrees]. Degrees can be -180 to 180 when using this format.");
				creature->sendSystemMessage("Reset position: /rotateFurniture reset 1");
			} else {
				creature->sendSystemMessage("@player_structure:formet_rotratefurniture_degrees"); //Format: /rotateFurniture <LEFT/RIGHT> <degrees>
			}

			return INVALIDPARAMETERS;
		}

		if (enhancedRotate && (rotatePitch || rotateRoll || rotateYaw) && (degrees < -180 || degrees > 180)) {
			creature->sendSystemMessage("The amount to rotate must be between -180 and 180.");
			return INVALIDPARAMETERS;
		} else if (!enhancedRotate && (degrees < 1 || degrees > 180)) {
			creature->sendSystemMessage("@player_structure:rotate_params"); // The amount to rotate must be between 1 and 180.
			return INVALIDPARAMETERS;
		}

		ZoneServer* zoneServer = creature->getZoneServer();
		ManagedReference<SceneObject*> obj = zoneServer->getObject(target);

		if (obj == nullptr) {
			creature->sendSystemMessage("@player_structure:rotate_what"); // What do you want to rotate?
			return GENERALERROR;
		}

		if (!isValidMoveable(creature, obj, rotateYaw, rotatePitch, rotateRoll, resetRotate, enhancedRotate))
			return GENERALERROR;

		if (rotateYaw) {
			if (dir == "right")
				obj->rotate(-degrees);
			else if (dir == "left")
				obj->rotate(degrees);
			else
				obj->rotate(degrees);
		} else if (rotatePitch) {
			obj->rotatePitch(degrees);
		} else if (rotateRoll) {
			obj->rotateRoll(degrees);
		} else if (resetRotate) {
			obj->setDirection(1, 0, 0, 0);
		}

		obj->incrementMovementCounter();

		ManagedReference<SceneObject*> objParent = obj->getParent().get();
		if (objParent != nullptr)
			obj->teleport(obj->getPositionX(), obj->getPositionZ(), obj->getPositionY(), objParent->getObjectID());
		else
			obj->teleport(obj->getPositionX(), obj->getPositionZ(), obj->getPositionY());

		return SUCCESS;
	}

	bool isValidMoveable(CreatureObject* player, SceneObject* object, bool rotateYaw, bool rotatePitch, bool rotateRoll, bool resetRotate, bool enhancedRotate) const {
		EventPerkDataComponent* data = cast<EventPerkDataComponent*>(object->getDataObjectComponent()->get());

		if (data != nullptr) {
			EventPerkDeed* deed = data->getDeed();

			if (deed == nullptr)
				return false;

			ManagedReference<CreatureObject*> owner = deed->getOwner().get();

			if (owner == nullptr || owner != player) {
				player->sendSystemMessage("@player_structure:cant_manipulate"); // You can't manipulate that.
				return false;
			}

			if (enhancedRotate && !rotateYaw && !resetRotate) {
				player->sendSystemMessage("Event perks can only be rotated by yaw.");
				return false;
			}

			return true;
		}

		if (object->isPlayerCreature() || (object->isCreatureObject() && !object->isVendor())) {
			player->sendSystemMessage("@player_structure:cant_manipulate"); // You can't manipulate that.
			return false;
		}

		ManagedReference<SceneObject*> rootParent = player->getRootParent();
		BuildingObject* buildingObject = rootParent != nullptr ? (rootParent->isBuildingObject() ? cast<BuildingObject*>( rootParent.get()) : nullptr) : nullptr;

		if (buildingObject == nullptr) {
			player->sendSystemMessage("@player_structure:must_be_in_building"); // You must be in a building to do that.
			return false;
		}

		if (buildingObject->isGCWBase()) {
			player->sendSystemMessage("@player_structure:no_move_hq"); // You may not move or rotate objects inside a factional headquarters.
			return false;
		}

		if (!object->isVendor() && !buildingObject->isOnAdminList(player)) {
			player->sendSystemMessage("@player_structure:admin_move_only"); // You must be an admin to manipulate objects.
			return false;
		}

		ManagedReference<SceneObject*> objectRootParent = object->getRootParent();

		if (objectRootParent == nullptr || objectRootParent != rootParent) {
			player->sendSystemMessage("@player_structure:item_not_in_building"); // That object is not within the building.
			return false;
		}

		if (buildingObject->containsChildObject(object)) {
			player->sendSystemMessage("@player_structure:cant_move_item"); // You cannot move that object.
			return false;
		}

		if (enhancedRotate && object->isVendor() && !rotateYaw && !resetRotate) {
			player->sendSystemMessage("Vendors can only be rotated by yaw.");
			return false;
		}

		return true;
	}

};

#endif //ROTATEFURNITURECOMMAND_H_
