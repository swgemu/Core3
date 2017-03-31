/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ROTATEFURNITURECOMMAND_H_
#define ROTATEFURNITURECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/components/EventPerkDataComponent.h"

class RotateFurnitureCommand : public QueueCommand {
public:

	RotateFurnitureCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == NULL)
			return GENERALERROR;

		String dir;
		int degrees = 0;

		try {
			UnicodeTokenizer tokenizer(arguments.toString());
			tokenizer.getStringToken(dir);
			degrees = tokenizer.getIntToken();

			dir = dir.toLowerCase();

			if (dir != "left" && dir != "right")
				throw Exception();

		} catch (Exception& e) {
			creature->sendSystemMessage("@player_structure:formet_rotratefurniture_degrees"); //Format: /rotateFurniture <LEFT/RIGHT> <degrees>
			return INVALIDPARAMETERS;
		}

		if (degrees < 1 || degrees > 180) {
			creature->sendSystemMessage("@player_structure:rotate_params"); //The amount to rotate must be between 1 and 180.
			return INVALIDPARAMETERS;
		}

		ZoneServer* zoneServer = creature->getZoneServer();
		ManagedReference<SceneObject*> obj = zoneServer->getObject(target);

		if (obj == NULL || !obj->isTangibleObject() || obj->isPlayerCreature() || obj->isPet()) {
			creature->sendSystemMessage("@player_structure:rotate_what"); //What do you want to rotate?
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> rootParent = creature->getRootParent();

		BuildingObject* buildingObject = rootParent != NULL ? (rootParent->isBuildingObject() ? cast<BuildingObject*>( rootParent.get()) : NULL) : NULL;
		EventPerkDataComponent* data = cast<EventPerkDataComponent*>(obj->getDataObjectComponent()->get());

		if (data != NULL) {
			EventPerkDeed* deed = data->getDeed();

			if (deed == NULL) {
				return GENERALERROR;
			}

			ManagedReference<CreatureObject*> owner = deed->getOwner().get();

			if (owner != creature) {
				return GENERALERROR;
			}

		} else if (buildingObject == NULL) {
			creature->sendSystemMessage("@player_structure:must_be_in_building"); //You must be in a building to do that.
			return GENERALERROR;

		} else {
			if (obj->isVendor() && !obj->checkContainerPermission(creature, ContainerPermissions::MOVEVENDOR)) {
				return GENERALERROR;
			}

			if (!obj->isVendor() && !buildingObject->isOnAdminList(creature)) {
				creature->sendSystemMessage("@player_structure:must_be_admin"); //You must be a building admin to do that.
				return GENERALERROR;
			}

			if (obj->getRootParent() != buildingObject || buildingObject->containsChildObject(obj)) {
				creature->sendSystemMessage("@player_structure:rotate_what"); //What do you want to rotate?
				return GENERALERROR;
			}

			if (buildingObject->isGCWBase()) {
				creature->sendSystemMessage("@player_structure:no_move_hq"); // You may not move or rotate objects inside a factional headquarters.
				return GENERALERROR;
			}
		}

		if (dir == "right")
			obj->rotate(-degrees);
		else
			obj->rotate(degrees);

		obj->incrementMovementCounter();

		ManagedReference<SceneObject*> objParent = obj->getParent().get();
		if (objParent != NULL)
			obj->teleport(obj->getPositionX(), obj->getPositionZ(), obj->getPositionY(), objParent->getObjectID());
		else
			obj->teleport(obj->getPositionX(), obj->getPositionZ(), obj->getPositionY());

		return SUCCESS;
	}

};

#endif //ROTATEFURNITURECOMMAND_H_
