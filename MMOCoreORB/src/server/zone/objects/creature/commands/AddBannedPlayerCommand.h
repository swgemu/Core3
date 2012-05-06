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

#ifndef ADDBANNEDPLAYERCOMMAND_H_
#define ADDBANNEDPLAYERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"

class AddBannedPlayerCommand: public QueueCommand {
public:

	AddBannedPlayerCommand(const String& name, ZoneProcessServer* server) :
		QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target,
			const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<PlayerObject*> adminGhost = creature->getPlayerObject();

		if (adminGhost == NULL || !adminGhost->isPrivileged())
			return INSUFFICIENTPERMISSION;

		ManagedReference<CreatureObject*> targetCreature = NULL;
		ManagedReference<PlayerObject*> ghost = NULL;
		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		StringTokenizer args(arguments.toString());

		if (args.hasMoreTokens()) {
			String character;
			args.getStringToken(character);

			targetCreature = playerManager->getPlayer(character);

		} else {

			targetCreature = cast<CreatureObject*> (
					server->getZoneServer()->getObject(target));

		}

		if (targetCreature == NULL || !targetCreature->isPlayerCreature())
			return INVALIDTARGET;

		ghost = targetCreature->getPlayerObject();

		if (ghost == NULL) {
			creature->sendSystemMessage("Player Ghost not found");
			return SUCCESS;
		}

		int duration;

		if (args.hasMoreTokens()) {
			duration = args.getIntToken();
		} else {
			creature->sendSystemMessage("Usage: /AddBannedPlayer <player name> <reason>");
			return GENERALERROR;
		}

		StringBuffer banReason;

		while (args.hasMoreTokens()) {
			String reason;
			args.getStringToken(reason);
			banReason << reason << " ";
		}

		if(banReason.toString().isEmpty()) {
			creature->sendSystemMessage("Usage: /AddBannedPlayer <player name> <reason>");			return GENERALERROR;
		}

		ManagedReference<Account*> account = playerManager->getAccount(ghost->getAccountID());

		String reason = banReason.toString();
		playerManager->banCharacter(adminGhost, account, targetCreature->getFirstName(), duration, reason);
		creature->sendSystemMessage(targetCreature->getFirstName() + " is banned");

		return SUCCESS;
	}

};

#endif //ADDBANNEDPLAYERCOMMAND_H_
