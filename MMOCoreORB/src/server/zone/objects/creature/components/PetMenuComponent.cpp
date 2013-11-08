
#include "PetMenuComponent.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/intangible/PetControlDevice.h"

void PetMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	if (!sceneObject->isPet())
		return;

	AiAgent* pet = cast<AiAgent*>(sceneObject);

	if (!player->getPlayerObject()->isPrivileged() && pet->getLinkedCreature() != player)
		return;

	menuResponse->addRadialMenuItem(59, 3, "@pet/pet_menu:menu_store"); // Store
}

int PetMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (!sceneObject->isPet())
		return 0;

	AiAgent* pet = cast<AiAgent*>(sceneObject);

	if (!player->getPlayerObject()->isPrivileged() && pet->getLinkedCreature() != player)
		return 0;

	ManagedReference<PetControlDevice*> petControlDevice = pet->getControlDevice().get().castTo<PetControlDevice*>();

	if (petControlDevice == NULL)
		return 0;

	if (selectedID == 59) {
		petControlDevice->storeObject(player);

		return 0;
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
