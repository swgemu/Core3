#include "ScavengerChestContainerComponent.h"
#include "server/zone/objects/tangible/Container.h"
#include "server/zone/objects/tangible/eventperk/ScavengerChest.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/components/EventPerkDataComponent.h"

bool ScavengerChestContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) {
	ContainerPermissions* permissions = sceneObject->getContainerPermissions();

	if(!sceneObject->isEventPerkItem())
		return false;

	ManagedReference<ScavengerChest*> chest = cast<ScavengerChest*>(sceneObject);

	if (chest == NULL)
		return false;

	Locker guard(chest);

	EventPerkDataComponent* gameData = cast<EventPerkDataComponent*>(chest->getDataObjectComponent()->get());

	if (gameData == NULL)
		return false;

	EventPerkDeed* deed = gameData->getDeed();

	if (deed == NULL)
		return false;

	ManagedReference<CreatureObject*> owner = deed->getOwner().get();

	if (permission == ContainerPermissions::MOVEIN) {
		if (creature == owner) {
			return true;
		} else {
			creature->sendSystemMessage("@event_perk:chest_can_not_add");
			return false;
		}
	} else if (permission == ContainerPermissions::MOVEOUT) {
		if (creature == owner) {
			return true;
		} else if (chest->isOnLootedList(creature->getObjectID())) {
			creature->sendSystemMessage("@event_perk:chest_only_one_item");
			return false;
		}

		chest->addtoLootedList(creature->getObjectID());
		return true;
	} else if ( permission == ContainerPermissions::OPEN  ) {
		return true;
	}

	return false;
}



