/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETPERMISSIONCOMMAND_H_
#define SETPERMISSIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetpermissionCommand : public QueueCommand {
public:
	SetpermissionCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->checkCooldownRecovery("set_permission")) {
			creature->sendSystemMessage("@healing_response:healing_must_wait"); //You must wait before you can do that.
			return GENERALERROR;
		}

		creature->updateCooldownTimer("set_permission", defaultTime * 1000);

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		if (playerManager == nullptr)
			return GENERALERROR;

		uint64 targetid = creature->getTargetID();
		ManagedReference<SceneObject*> obj = playerManager->getInRangeStructureWithAdminRights(creature, targetid);

		if (obj == nullptr || !obj->isStructureObject()) {
			creature->sendSystemMessage("@player_structure:no_building"); // You must be in a building, be near an installation, or have one targeted to do that.
			return INVALIDTARGET;
		}

		StructureObject* structure = cast<StructureObject*>(obj.get());

		if (structure->isCivicStructure()) {
			creature->sendSystemMessage("You cannot modify permissions on civic structures.");
			return INVALIDTARGET;
		}

		if (structure->isGCWBase()) {
			return INVALIDTARGET;
		}

		String listName, targetName;

		try {
			UnicodeTokenizer tokenizer(arguments);
			tokenizer.getStringToken(listName);
			tokenizer.getStringToken(targetName);
		} catch (Exception& e) {
			creature->sendSystemMessage("@player_structure:format_setpermission_type_player"); // Format: /setPermission <type> <player>
			return INVALIDPARAMETERS;
		}

		UnicodeString args = targetName + " " + listName + " toggle";
		creature->executeObjectControllerAction(0x896713F2, obj->getObjectID(), args); // PermissionListModify

		return SUCCESS;
	}
};

#endif // SETPERMISSIONCOMMAND_H_
