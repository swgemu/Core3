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
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"
#include "server/zone/templates/tangible/ContainerTemplate.h"

void ContainerImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("Container");

}

void ContainerImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	ContainerTemplate* containerTemplate = dynamic_cast<ContainerTemplate*>(templateData);

	if (containerTemplate == NULL)
		return;

	locked = containerTemplate->getLocked();

}

/*void ContainerImplementation::sendContainerObjectsTo(SceneObject* player) {
	if (!locked)
		SceneObjectImplementation::sendContainerObjectsTo(player);
}*/

bool ContainerImplementation::checkPermission(CreatureObject* player) {
	if (!isASubChildOf(player)) {
		if (parent == NULL || !parent->isCellObject())
			return false;
		else {

			BuildingObject* building = (BuildingObject*) parent->getParent();

			if (!building->isOnAdminList(player->getFirstName()))
				return false;
		}
	}

	if (locked)
		return false;

	return true;
}

void ContainerImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);

	if (checkPermission(player))
		menuResponse->addRadialMenuItem(50, 3, "@base_player:set_name"); //Set Name

	if (isSliceable() && isContainerLocked() && player->hasSkill("combat_smuggler_novice"))
		menuResponse->addRadialMenuItem(69, 3, "@slicing/slicing:slice"); // Slice
}

int ContainerImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID == 50 && checkPermission(player)) {
		ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(player, SuiWindowType::OBJECT_NAME, 0x00);

		inputBox->setPromptTitle("@sui:set_name_title");
		inputBox->setPromptText("@sui:set_name_prompt");
		inputBox->setUsingObject(_this);
		inputBox->setMaxInputSize(255);

		inputBox->setDefaultInput(objectName.getCustomString().toString());

		player->getPlayerObject()->addSuiBox(inputBox);
		player->sendMessage(inputBox->generateMessage());

		return 0;

	} else if (selectedID == 69) {
		ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::SLICING);
		ManagedReference<SlicingSession*> session = dynamic_cast<SlicingSession*>(facade.get());

		if (session != NULL) {
			player->sendSystemMessage("@slicing/slicing:already_slicing");
			return 0;
		}

		//Create Session
		session = new SlicingSession(player);
		session->initalizeSlicingMenu(player, _this);

		return 0;

	} else
		return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);
}

int ContainerImplementation::canAddObject(SceneObject* object, int containmentType, String& errorDescription) {
//	if (locked)
	//	return TransferErrorCode::CONTAINERLOCKED;

	if ((object->isIntangibleObject() && getContainerType() != 3)
			|| (getContainerType() == 3 && !object->isIntangibleObject())) {
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
