/*
 * WearableContainerObjectImplementation.cpp
 *
 *  Created on: Oct 27, 2012
 *      Author: loshult
 */

#include "WearableContainerObject.h"
#include "server/zone/templates/tangible/ContainerTemplate.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/AiAgent.h"

void WearableContainerObjectImplementation::initializeTransientMembers() {
	WearableObjectImplementation::initializeTransientMembers();

	setLoggingName("WearableContainerObject");

}

void WearableContainerObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	WearableObjectImplementation::loadTemplateData(templateData);

	containerObjects.setDelayedLoadOperationMode();

	ContainerTemplate* containerTemplate = dynamic_cast<ContainerTemplate*>(templateData);

	if (containerTemplate == NULL)
		return;
}

void WearableContainerObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	WearableObjectImplementation::fillObjectMenuResponse(menuResponse, player);

	if (checkContainerPermission(player, ContainerPermissions::MOVECONTAINER && getParent().get() != NULL &&
			getParent().get()->checkContainerPermission(player, ContainerPermissions::MOVEOUT))) {
		menuResponse->addRadialMenuItem(50, 3, "@base_player:set_name"); //Set Name
	}
}

int WearableContainerObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID == 50) {
		if (checkContainerPermission(player, ContainerPermissions::MOVECONTAINER && getParent().get() != NULL &&
				getParent().get()->checkContainerPermission(player, ContainerPermissions::MOVEOUT))) {

			ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(player, SuiWindowType::OBJECT_NAME, 0x00);

			inputBox->setPromptTitle("@sui:set_name_title");
			inputBox->setPromptText("@sui:set_name_prompt");
			inputBox->setUsingObject(_this.get());
			inputBox->setMaxInputSize(255);

			inputBox->setDefaultInput(getCustomObjectName().toString());

			player->getPlayerObject()->addSuiBox(inputBox);
			player->sendMessage(inputBox->generateMessage());

			return 0;
		}
	}

	return WearableObjectImplementation::handleObjectMenuSelect(player, selectedID);
}

int WearableContainerObjectImplementation::canAddObject(SceneObject* object, int containmentType, String& errorDescription) {
	if ((object->isIntangibleObject() && getContainerType() != 3)
			|| (getContainerType() == 3 && !object->isIntangibleObject())) {
		errorDescription = "@container_error_message:container07";

		return TransferErrorCode::INVALIDTYPE;
	}

	if (containmentType == -1) {
		if ((gameObjectType == SceneObjectType::WEARABLECONTAINER && object->getGameObjectType() == SceneObjectType::WEARABLECONTAINER)) {
			errorDescription = "@container_error_message:container12";

			return TransferErrorCode::CANTNESTOBJECT;
		}

		if (object->isContainerObject() && getArrangementDescriptorSize() == 0) {
			errorDescription = "@container_error_message:container12";

			return TransferErrorCode::CANTNESTOBJECT;
		}

		ManagedReference<SceneObject*> myParent = getParent();
		ManagedReference<SceneObject*> otherParent = object->getParent();

		if (myParent != NULL && otherParent != NULL) {
			if (otherParent->isCreatureObject()) {
				AiAgent* ai = dynamic_cast<AiAgent*>(otherParent.get());

				if (ai != NULL) {
					SceneObject* creatureInventory = ai->getSlottedObject("inventory");

					if (creatureInventory != NULL) {
						uint64 lootOwnerID = creatureInventory->getContainerPermissions()->getOwnerID();

						if (lootOwnerID != myParent->getObjectID()) {
							errorDescription = "@group:no_loot_permission";

							return TransferErrorCode::NOLOOTPERMISSION;
						}
					}

				}
			}
		}
	}

	return WearableObjectImplementation::canAddObject(object, containmentType, errorDescription);
}

