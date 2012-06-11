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

#ifndef SETGODMODECOMMAND_H_
#define SETGODMODECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/tangible/TangibleObjectDeltaMessage3.h"
#include "server/zone/packets/player/PlayerObjectDeltaMessage6.h"


class SetGodModeCommand : public QueueCommand {
public:

	SetGodModeCommand(const String& name, ZoneProcessServer* server)
	: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		PermissionLevelList* permissionLevelList = PermissionLevelList::instance();
		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == NULL) {
			return INSUFFICIENTPERMISSION;
		}

		int ghostPermissionLevel = ghost->getAdminLevel();

		if (!creature->hasSkill("admin_base")) {
			return INSUFFICIENTPERMISSION;
		}

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
			if(param == "on" && targetGhost->getAdminLevel() > 0) {
				skillManager->addAbility(targetGhost, "admin");
				playerManager->updatePermissionName(targetPlayer, targetPermissionLevel);
			} else if(param == "off" && targetGhost->getAdminLevel() > 0) {
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
