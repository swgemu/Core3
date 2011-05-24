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

#include "TangibleObjectMenuComponent.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

void TangibleObjectMenuComponentImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	ObjectMenuComponentImplementation::fillObjectMenuResponse(menuResponse, player);

	uint32 gameObjectType = sceneObject->getGameObjectType();

	if (!sceneObject->isTangibleObject())
		return;

	TangibleObject* tano = (TangibleObject*) sceneObject.get();

	// Figure out what the object is and if its able to be Sliced.
	if(!tano->isSliceable())
		return;
	else { // Check to see if the player has the correct skill level
		if ((gameObjectType == SceneObject::PLAYERLOOTCRATE || sceneObject->isContainerObject()) && !player->hasSkillBox("combat_smuggler_novice"))
			return;
		else if (sceneObject->isMissionTerminal() && !player->hasSkillBox("combat_smuggler_slicing_01"))
			return;
		else if (sceneObject->isWeaponObject() && !player->hasSkillBox("combat_smuggler_slicing_02"))
			return;
		else if (sceneObject->isArmorObject() && !player->hasSkillBox("combat_smuggler_slicing_03"))
			return;

		menuResponse->addRadialMenuItem(69, 3, "@slicing/slicing:slice"); // Slice

	}
}

int TangibleObjectMenuComponentImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (!sceneObject->isTangibleObject())
		return 0;

	TangibleObject* tano = (TangibleObject*) sceneObject.get();


	if (selectedID == 69) { // Slice [PlayerLootCrate]
		if (player->containsActiveSession(SessionFacadeType::SLICING)) {
			player->sendSystemMessage("@slicing/slicing:already_slicing");
			return 0;
		}

		//Create Session
		ManagedReference<SlicingSession*> session = new SlicingSession(player);
		session->initalizeSlicingMenu(player, tano);

		return 0;
	} else
		return ObjectMenuComponentImplementation::handleObjectMenuSelect(player, selectedID);

}

