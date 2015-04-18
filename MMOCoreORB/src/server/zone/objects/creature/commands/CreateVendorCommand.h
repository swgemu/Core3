/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATEVENDORCOMMAND_H_
#define CREATEVENDORCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/sessions/vendor/CreateVendorSession.h"

class CreateVendorCommand : public QueueCommand {
public:

	CreateVendorCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(creature);
		ManagedReference<SceneObject*> parent = player->getRootParent();

		if (player->containsActiveSession(SessionFacadeType::CREATEVENDOR)) {
			player->sendSystemMessage("@player_structure:already_creating");
			return GENERALERROR;
		}

		if (parent == NULL || !parent->isBuildingObject()) {
			player->sendSystemMessage("@player_structure:must_be_in_building");
			return GENERALERROR;
		}

		ManagedReference<BuildingObject*> building = cast<BuildingObject*>( parent.get());

		if (!building->isOnAdminList(player) &&
				!building->isOnPermissionList("VENDOR", player)) {
			player->sendSystemMessage("@player_structure:drop_npc_vendor_perm"); // You don't have vendor permissions
			return GENERALERROR;
		}

		if (!building->isPublicStructure()) {
			player->sendSystemMessage("@player_structure:vendor_public_only");
			return GENERALERROR;
		}

		//Create Session
		ManagedReference<CreateVendorSession*> session = new CreateVendorSession(player);
		session->initializeSession();

		return SUCCESS;
	}

};

#endif //CREATEVENDORCOMMAND_H_

