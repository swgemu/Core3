/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef SETGODMODECOMMAND_H_
#define SETGODMODECOMMAND_H_

#include "server/zone/managers/objectcontroller/ObjectController.h"

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/tangible/TangibleObjectDeltaMessage3.h"
#include "server/zone/packets/player/PlayerObjectDeltaMessage6.h"

class SetGodModeCommand : public QueueCommand {
public:

	SetGodModeCommand(const String& name, ZoneProcessServer* server)
	: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		PermissionLevelList* permissionLevelList = PermissionLevelList::instance();
		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == NULL) {
			return GENERALERROR;
		}

		int ghostPermissionLevel = ghost->getAdminLevel();

		if (!creature->hasSkill("admin_base")) {
			return INSUFFICIENTPERMISSION;
		}

		ObjectController* controller = creature->getZoneServer()->getObjectController();
		controller->logAdminCommand(creature, this, target, arguments);

		String targetName;
		String param;

		try {
			UnicodeTokenizer args(arguments);
			args.getStringToken(targetName);
			args.getStringToken(param);
		} catch (Exception& e) {
			creature->sendSystemMessage("SYNTAX: /setGodMode <name> [admin level | on | off].");
			return INVALIDPARAMETERS;
		}

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();
		SkillManager* skillManager = server->getSkillManager();
		ManagedReference<CreatureObject*> targetPlayer = playerManager->getPlayer(targetName);

		if(targetPlayer == NULL)
			return GENERALERROR;

		Locker clocker(targetPlayer, creature);

		ManagedReference<PlayerObject*> targetGhost = targetPlayer->getPlayerObject();
		if(targetGhost != NULL) {
			int targetPermissionLevel = targetGhost->getAdminLevel();

			if(param == "on" && targetPermissionLevel > 0) {
				skillManager->addAbility(targetGhost, "admin");
				playerManager->updatePermissionName(targetPlayer, targetPermissionLevel);
			} else if(param == "off" && targetPermissionLevel > 0) {
				skillManager->removeAbility(targetGhost, "admin");
				playerManager->updatePermissionName(targetPlayer, targetPermissionLevel);
			} else  {
				if(ghostPermissionLevel < permissionLevelList->getLevelNumber("admin")) {
					creature->sendSystemMessage("Must have \"admin\" level permission to set permissions.");
					return INSUFFICIENTPERMISSION;
				}
				if(permissionLevelList->containsLevel(param)) {
					int permissionLevel = permissionLevelList->getLevelNumber(param);
					playerManager->updatePermissionLevel(targetPlayer, permissionLevel);
					creature->sendSystemMessage("You have set " + targetPlayer->getFirstName()
							+ "'s permission level to " + param);
				} else {
					creature->sendSystemMessage("Invalid permission level: " + param);
					error("Invalid parameter for setGodMode");
					return INVALIDPARAMETERS;
				}
			}
		}

		return SUCCESS;
	}

};

#endif //SETGODMODECOMMAND_H_
