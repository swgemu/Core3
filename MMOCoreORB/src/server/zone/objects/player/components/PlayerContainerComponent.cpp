/*
 * PlayerContainerComponent.cpp
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#include "PlayerContainerComponent.h"
#include "server/zone/objects/tangible/wearables/ArmorObject.h"
#include "server/zone/managers/player/PlayerManager.h"

int PlayerContainerComponent::canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) {
	CreatureObject* creo = dynamic_cast<CreatureObject*>(sceneObject);

	if (object->isTangibleObject() && containmentType == 4) {
		TangibleObject* wearable = (TangibleObject*) object;

		uint16 charMask = creo->getWearableMask();
		uint16 objMask = wearable->getPlayerUseMask();

		uint16 maskRes = ~objMask & charMask;

		if (maskRes != 0) {
			/*StringBuffer maskResol;
						maskResol << "returned maskRes :" << maskRes;
						info(maskResol.toString(), true);*/
			errorDescription = "You lack the necessary requirements to wear this object";

			return TransferErrorCode::PLAYERUSEMASKERROR;
		}
	}

	if (object->isArmorObject() && containmentType == 4) {
		PlayerManager* playerManager = sceneObject->getZoneServer()->getPlayerManager();

		if (!playerManager->checkEncumbrancies(dynamic_cast<PlayerCreature*>(sceneObject), (ArmorObject*) object)) {
			errorDescription = "You lack the necessary secondary stats to equip this item";

			return TransferErrorCode::NOTENOUGHENCUMBRANCE;
		}
	}

	return ContainerComponent::canAddObject(sceneObject, object, containmentType, errorDescription);
}
