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

#ifndef TRANSFERSTRUCTURECOMMAND_H_
#define TRANSFERSTRUCTURECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/player/PlayerManager.h"

class TransferstructureCommand : public QueueCommand {
public:

	TransferstructureCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		if (!creature->isPlayerCreature())
			return INVALIDPARAMETERS;

		CreatureObject* player = (CreatureObject*) creature;

		PlayerObject* ghost = player->getPlayerObject();

		String targetName = arguments.toString();

		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(target);

		if (obj == NULL || !obj->isPlayerCreature()) {
			player->sendSystemMessage("@player_structure:no_transfer_target"); //You must specify a player with whom to transfer ownership.
			return GENERALERROR;
		}

		CreatureObject* targetPlayer = (CreatureObject*) obj.get();

		Locker _lock(targetPlayer, player);

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();


		//Get the building to be transfered.
		ManagedReference<SceneObject*> structobj = playerManager->getInRangeStructureWithAdminRights(player, target);

		if (structobj == NULL || !structobj->isStructureObject()) {
			player->sendSystemMessage("@player_structure:not_in_building"); //You must be inside your building to transfer it.
			return GENERALERROR;
		}

		StructureObject* structureObject = (StructureObject*) structobj.get();

		Locker _slock(structureObject);

		if (!structureObject->isOwnerOf(player)) {
			player->sendSystemMessage("@player_structure:not_owner"); //You are not the owner of this structure.
			return GENERALERROR;
		}

		if (targetPlayer == player) {
			player->sendSystemMessage("@player_structure:already_owner"); //You are already the owner.
			return GENERALERROR;
		}

		if (!targetPlayer->isInRange(player, 16) || targetPlayer->getRootParent() != player->getRootParent())
			return TOOFAR;

		int lotSize = structureObject->getLotSize();

		/*if (targetPlayer->getLotsRemaining() < lotSize) {
			StringIdChatParameter params("@player_structure:not_enough_lots");
			params.setDI(structureObject->getLotSize());
			player->sendSystemMessage(params);

			return GENERALERROR;
		}*/

		//TODO:
		//@player_structure:trail_no_transfer Trial accounts may not be involved in a property ownership transfer.
		//@player_structure:building_has_no_trade The object %TT may not be traded and must be put in your inventory or destroyed before the building can be transferred.
		//@player_structure:faction_base You cannot transfer your factional base access and allotment responsibility to anyone else.

		/**
		ManagedReference<Region*> region = (Region*) structureObject->getActiveRegion();

		if (region != NULL) {
			ManagedReference<CityHallObject*> cityHall = region->getCityHall();

			if (cityHall != NULL && cityHall->isBanned(targetPlayer->getObjectID())) {
				player->sendSystemMessage("@city/city:cant_transfer_to_city_banned"); //You cannot transfer ownership of a structure to someone who is banned from the city in which the structure resides.
				return GENERALERROR;
			}
		}
		*/

		if (structureObject->isOnBanList(targetPlayer)) {
			player->sendSystemMessage("@player_structure:no_banned_player"); //You cannot transfer ownership to a banned player
			return GENERALERROR;
		}

		structureObject->setOwnerObjectID(targetPlayer->getObjectID());
		//TODO: Do we need to manually update the permission lists too?

		if (ghost->getDeclaredResidence() == structureObject)
			ghost->setDeclaredResidence(NULL);

		//Update the cell permissions if the structure is private and a building.
		if (!structureObject->isPublicStructure() && structureObject->isBuildingObject()) {
			BuildingObject* buildingObject = (BuildingObject*) structureObject;

			buildingObject->updateCellPermissionsTo(targetPlayer);
			buildingObject->updateCellPermissionsTo(player);
		}

		//Transfer the lots.
		//targetPlayer->setLotsRemaining(targetPlayer->getLotsRemaining() - lotSize);
		//player->setLotsRemaining(player->getLotsRemaining() + lotSize);

		StringIdChatParameter params("@player_structure:ownership_transferred_in"); //%NT has transfered ownership of the structure to you
		params.setTT(player);
		targetPlayer->sendSystemMessage(params);

		params.setStringId("@player_structure:ownership_transferred_out"); //Ownership of the structure has been transferred to %NT.
		params.setTT(targetPlayer);
		player->sendSystemMessage(params);

		return SUCCESS;
	}

};

#endif //TRANSFERSTRUCTURECOMMAND_H_
