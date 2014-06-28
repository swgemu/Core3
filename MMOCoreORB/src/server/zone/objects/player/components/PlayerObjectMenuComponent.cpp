/*
 Copyright (C) 2007-2011 <SWGEmu>

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

#include "PlayerObjectMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/managers/player/PlayerManager.h"

void PlayerObjectMenuComponent::fillObjectMenuResponse(
		SceneObject* sceneObject, ObjectMenuResponse* menuResponse,
		CreatureObject* player) {
	if (!sceneObject->isCreatureObject())
		return;

	CreatureObject* creature = cast<CreatureObject*>( sceneObject);
	GroupObject* group = creature->getGroup();

	if (group != NULL) {
		if (group->hasMember(player))
			menuResponse->addRadialMenuItem(51, 3, "@sui:teach");
	}

	if (creature->isPlayingMusic()) {
		if (!player->isListening())
			menuResponse->addRadialMenuItem(113, 3,
					"@radial_performance:listen");
		else
			menuResponse->addRadialMenuItem(115, 3,
					"@radial_performance:listen_stop");
	}

	if (creature->isDancing()) {
		if (!player->isWatching())
			menuResponse->addRadialMenuItem(114, 3, "@radial_performance:watch");
		else
			menuResponse->addRadialMenuItem(116, 3,
					"@radial_performance:watch_stop");
	}

	// Allow admins to grant divorce to married players
	if( creature->getPlayerObject() != NULL && creature->getPlayerObject()->isMarried() && player->getPlayerObject()->isPrivileged() ){
		menuResponse->addRadialMenuItem(117, 3, "@unity:mnu_divorce"); // "Divorce"
	}

}

int PlayerObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject,
		CreatureObject* player, byte selectedID) {
	CreatureObject* ownerPlayer = dynamic_cast<CreatureObject*> (sceneObject);
	PlayerObject* ghost = ownerPlayer->getPlayerObject();

	switch (selectedID) {
	case 113:
		player->executeObjectControllerAction(0x5855BB1B,
				sceneObject->getObjectID(), ""); // listen
		break;
	case 115:
		player->executeObjectControllerAction(0xC2E4D4D0,
				sceneObject->getObjectID(), ""); // stoplistening
		break;

	case 114:
		player->executeObjectControllerAction(0xEC93CA43,
				sceneObject->getObjectID(), ""); // watch
		break;

	case 116:
		player->executeObjectControllerAction(0x6651AD9A,
				sceneObject->getObjectID(), ""); // stopwatching
		break;

	case 51:
		player->executeObjectControllerAction(0x5041F83A,
				sceneObject->getObjectID(), ""); // teach
		break;

	case 117:
		if(player->getPlayerObject()->isPrivileged()) {
			Locker( ownerPlayer, player );
			PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();
			playerManager->grantDivorce( ownerPlayer );
		}
		break;

	}

	return 0;
}

