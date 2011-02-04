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

#include "Container.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"

void ContainerImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("Container");
}

void ContainerImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);
}

void ContainerImplementation::sendContainerObjectsTo(SceneObject* player) {
	SceneObjectImplementation::sendContainerObjectsTo(player);
}

bool ContainerImplementation::checkPermission(PlayerCreature* player) {
	if (!isASubChildOf(player)) {
		if (parent == NULL || !parent->isCellObject())
			return false;
		else {
			BuildingObject* building = (BuildingObject*) parent->getParent();

			if (!building->isOnAdminList(player))
				return false;
		}
	}

	return true;
}

void ContainerImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);

	if (checkPermission(player))
		menuResponse->addRadialMenuItem(50, 1, "@base_player:set_name"); //Rotate
}

int ContainerImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (selectedID != 50 || !checkPermission(player))
		return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);

	ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(player, SuiWindowType::OBJECT_NAME, 0x00);

	inputBox->setPromptTitle("@sui:set_name_title");
	inputBox->setPromptText("@sui:set_name_prompt");
	inputBox->setUsingObject(_this);
	inputBox->setMaxInputSize(255);

	inputBox->setDefaultInput(objectName.getCustomString().toString());

	player->addSuiBox(inputBox);
	player->sendMessage(inputBox->generateMessage());

	return 0;
}

int ContainerImplementation::canAddObject(SceneObject* object, int containmentType, String& errorDescription) {
	if ((object->isIntangibleObject() && containerType != 3)
			|| (containerType == 3 && !object->isIntangibleObject())) {
		errorDescription = "@container_error_message:container07";

		return TransferErrorCode::INVALIDTYPE;
	}

	if (containmentType == -1) {
		if (gameObjectType == WEARABLECONTAINER && object->getGameObjectType() == WEARABLECONTAINER) {
			errorDescription = "@container_error_message:container12";

			return TransferErrorCode::CANTNESTOBJECT;
		}
	}

	return TangibleObjectImplementation::canAddObject(object, containmentType, errorDescription);
}
