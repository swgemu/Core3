/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TRANSFERSTRUCTURECOMMAND_H_
#define TRANSFERSTRUCTURECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/templates/tangible/SharedStructureObjectTemplate.h"

class TransferstructureCommand : public QueueCommand {
public:

	TransferstructureCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		ManagedReference<SceneObject*> obj = playerManager->getInRangeStructureWithAdminRights(creature);

		if (obj == NULL || !obj->isStructureObject()) {
			creature->sendSystemMessage("@player_structure:command_no_building"); //You must be in a building or near an installation to use that command.
			return INVALIDPARAMETERS;
		}

		StructureObject* structure = cast<StructureObject*>( obj.get());

		if (!structure->isOwnerOf(creature)) {
			creature->sendSystemMessage("@player_structure:not_owner"); //You are not the owner of this structure.
			return GENERALERROR;
		}

		if ((structure->isGCWBase()) || structure->isTurret() || structure->isMinefield()) {
			creature->sendSystemMessage("@player_structure:faction_base"); // You cannot transfer your factional base access and allotment responsibility to anyone else.
			return INVALIDTARGET;
		}

		if (structure->isBuildingObject() && creature->getRootParent() != structure) {
			creature->sendSystemMessage("@player_structure:not_in_building"); //You must be inside your building to transfer it.
			return GENERALERROR;
		}

		if (structure->isBuildingObject() && creature->getRootParent() != structure) {

			BuildingObject* building = cast<BuildingObject*>(structure);

			for (int i = 1; i < building->getTotalCellNumber(); ++i) {
				ManagedReference<CellObject*> cell = building->getCell(i);

				if(cell == NULL)
					continue;

				for(int j = 0; j < cell->getContainerObjectsSize(); ++j) {
					ManagedReference<SceneObject*> obj = cell->getContainerObject(j);

					if(obj == NULL)
						continue;

					if(obj->isNoTrade() || obj->containsNoTradeObjectRecursive()) {
						StringIdChatParameter param("@player_structure:building_has_notrade"); // The object %TT may not be traded and must be put in your inventory or destroyed before the building can be transferred.
						param.setTT(obj->getDisplayedName());
						creature->sendSystemMessage(param);
						return GENERALERROR;
					}
				}
			}
		}

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);

		if (targetObject == NULL || !targetObject->isCreatureObject() || !targetObject->isPlayerCreature()) {
			creature->sendSystemMessage("@player_structure:no_transfer_target"); //You must specify a player with whom to transfer ownership.
			return INVALIDTARGET;
		}

		if (targetObject == creature) {
			creature->sendSystemMessage("@player_structure:already_owner"); //You are already the owner.
			return GENERALERROR;
		}

		CreatureObject* targetCreature = cast<CreatureObject*>( targetObject.get());

		if (structure->isOnBanList(targetCreature)) {
			creature->sendSystemMessage("@player_structure:no_banned_player"); //You cannot transfer ownership to a banend player.
			return GENERALERROR;
		}

		Reference<SharedStructureObjectTemplate*> tmpl = cast<SharedStructureObjectTemplate*>(obj->getObjectTemplate());

		PlayerObject* ghost = targetCreature->getPlayerObject();

		String& abilityRequired = tmpl->getAbilityRequired();

		if (abilityRequired != "" && !ghost->hasAbility(abilityRequired)) {
			StringIdChatParameter params("@player_structure:not_able_to_own"); //%NT is not able to own this structure.
			params.setTT(targetCreature);
			creature->sendSystemMessage(params);
			return GENERALERROR;
		}

		return doTransferStructure(creature, targetCreature, structure);

	}

	// pre: creature, targetCreature, and structure are not locked
	// bForceTransfer = whether or not to force the transfer. This means do the transfer even if the target is offline or out of range, or if the old owner is NULL
	static int doTransferStructure(CreatureObject* creature, CreatureObject* targetCreature, StructureObject* structure, bool bForceTransfer = false){
		if (targetCreature == NULL || structure == NULL)
			return GENERALERROR;

		ManagedReference<PlayerObject*> targetGhost = targetCreature->getPlayerObject();
		if (targetGhost == NULL)
			return GENERALERROR;

		ManagedReference<PlayerObject*> ghost = NULL;

		if (creature != NULL) {
			ghost = creature->getPlayerObject().get();
		}

		if (!bForceTransfer && (creature == NULL || ghost == NULL)) {
			return GENERALERROR;
		}

		//Ensure that they are within at least 16m of the transferrer.
		if (!bForceTransfer && (!targetCreature->isInRange(creature, 16.f) || !targetGhost->isOnline()) ) {
			StringIdChatParameter params("@cmd_err:target_range_prose"); //Your target is too far away to %TO.
			params.setTO("Transfer Structure");
			creature->sendSystemMessage(params);
			return TOOFAR;
		}

		int lotSize = structure->getLotSize();

		if (!targetGhost->hasLotsRemaining(lotSize)) {
			if ( !bForceTransfer) {
				System::out << "lotsize: " << lotSize << endl;
				StringIdChatParameter params("@player_structure:not_able_to_own"); //%NT is not able to own this structure.
				params.setTT(targetCreature);
				creature->sendSystemMessage(params);
			} else {

				// send message to the person trying to do the guild transfer
			}

			return GENERALERROR;
		}

		//TODO:
		//@player_structure:trail_no_transfer Trial accounts may not be involved in a property ownership transfer.

		ManagedReference<CityRegion*> region = structure->getCityRegion();

		if (region != NULL && ghost != NULL) {
			Locker locker(region);

			if (region->isBanned(targetCreature->getObjectID())) {
				creature->sendSystemMessage("@city/city:cant_transfer_to_city_banned"); //You cannot transfer ownership of a structure to someone who is banned from the city in which the structure resides.
				return GENERALERROR;
			}

			if (region->isZoningEnabled() && !region->hasZoningRights(targetCreature->getObjectID())) {
				targetCreature->sendSystemMessage("@player_structure:no_rights"); //You don't have the right to place that structure in this city. The mayor or one of the city milita must grant you zoning rights first.

				return GENERALERROR;
			}

			if (ghost->getDeclaredResidence() == structure->getObjectID()) {
				CityManager* cityManager = creature->getZoneServer()->getCityManager();
				cityManager->unregisterCitizen(region, creature);
			}

			locker.release();
		}

		if (ghost != NULL) {
			Locker lock(creature);

			if (ghost->getDeclaredResidence() == structure->getObjectID()) {
				ghost->setDeclaredResidence(NULL);
			}

			ghost->removeOwnedStructure(structure);

			lock.release();
		}

		Locker targetLock(targetCreature);

		targetGhost->addOwnedStructure(structure);

		Locker clocker(structure, targetCreature);

		//Setup permissions.
		structure->revokeAllPermissions(targetCreature->getObjectID());
		structure->grantPermission("ADMIN", targetCreature->getObjectID());

		structure->setOwner(targetCreature->getObjectID());

		if (creature != NULL)
			structure->revokePermission("ADMIN", creature->getObjectID());

		//Update the cell permissions if the structure is private and a building.
		if (!structure->isPublicStructure() && structure->isBuildingObject()) {
			BuildingObject* buildingObject = cast<BuildingObject*>( structure);

			buildingObject->updateCellPermissionsTo(targetCreature);

			if (creature != NULL)
				buildingObject->updateCellPermissionsTo(creature);
		}

		if (creature != NULL && !bForceTransfer) {
			StringIdChatParameter params("@player_structure:ownership_transferred_in"); //%TT has transfered ownership of the structure to you
			params.setTT(creature->getFirstName());
			targetCreature->sendSystemMessage(params);

			params.setStringId("@player_structure:ownership_transferred_out"); //Ownership of the structure has been transferred to %NT.
			params.setTT(targetCreature->getFirstName());
			creature->sendSystemMessage(params);
		}

		return SUCCESS;
	}

};

#endif //TRANSFERSTRUCTURECOMMAND_H_
