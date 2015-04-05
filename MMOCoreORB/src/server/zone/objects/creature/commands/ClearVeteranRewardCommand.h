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

#ifndef CLEARVETERANREWARDCOMMAND_H_
#define CLEARVETERANREWARDCOMMAND_H_

#include "server/zone/ZoneProcessServer.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/login/account/Account.h"

class ClearVeteranRewardCommand : public QueueCommand {
public:

	ClearVeteranRewardCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* player, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(player))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(player))
			return INVALIDLOCOMOTION;

		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		if (ghost == NULL || !ghost->isPrivileged())
			return INSUFFICIENTPERMISSION;

		StringTokenizer tokenizer(arguments.toString());
		tokenizer.setDelimeter(" ");
		int milestone = tokenizer.getIntToken();
		if( milestone < 0 ){
			player->sendSystemMessage("SYNTAX: /clearVeteranReward player milestone");
			return INVALIDPARAMETERS;
		}

		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(target);
		if (obj == NULL || !obj->isPlayerCreature()) {
			player->sendSystemMessage("SYNTAX: /clearVeteranReward player milestone");
			return INVALIDPARAMETERS;
		}

		PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();
		if( playerManager == NULL )
			return GENERALERROR;

		CreatureObject* targetCreature = cast<CreatureObject*>( obj.get());
		PlayerObject* targetGhost = targetCreature->getPlayerObject();

		Locker clocker(targetCreature, player);

		String reward = targetGhost->getChosenVeteranReward( milestone );
		if( reward.isEmpty() ){
			player->sendSystemMessage("Player has not chosen a reward for that milestone");
			return GENERALERROR;
		}

		// Get account
		ManagedReference<Account*> account = playerManager->getAccount( targetGhost->getAccountID() );
		if( account == NULL ){
			player->sendSystemMessage("Error finding account");
			return GENERALERROR;
		}

		// Clear reward in all characters registered to the account
		CharacterList* characters = account->getCharacterList();
		for(int i = 0; i < characters->size(); ++i) {
			CharacterListEntry* entry = &characters->get(i);
			if(entry->getGalaxyID() == server->getZoneServer()->getGalaxyID()) {

				ManagedReference<CreatureObject*> altPlayer = playerManager->getPlayer(entry->getFirstName());
				if(altPlayer != NULL && altPlayer->getPlayerObject() != NULL) {
					Locker alocker(altPlayer, player);
					altPlayer->getPlayerObject()->clearVeteranReward(milestone);
					player->sendSystemMessage( altPlayer->getFirstName() + "'s " + String::valueOf(milestone) + "-day reward has been cleared" );
					alocker.release();
				}
			}
		}

		return SUCCESS;
	}

};

#endif //CLEARVETERANREWARDCOMMAND_H_
