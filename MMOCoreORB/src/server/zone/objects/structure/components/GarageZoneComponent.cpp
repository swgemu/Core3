/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "GarageZoneComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"

void GarageZoneComponent::notifyPositionUpdate(SceneObject* sceneObject, QuadTreeEntry* entry) {
	ManagedReference<SceneObject*> obj = cast<SceneObject*>(entry);

	if (obj == NULL || !obj->isPlayerCreature())
		return;

	CreatureObject* player = obj->asCreatureObject();

	float deltaX = sceneObject->getPositionX() - obj->getPositionX();
	float deltaY = sceneObject->getPositionY() - obj->getPositionY();
	float rangeSq = deltaX * deltaX + deltaY * deltaY;

	if (rangeSq > 4096) { // 64^2
		if (notifiedPlayers.contains(obj))
			notifiedPlayers.drop(obj);

	} else {
		ManagedReference<SceneObject*> rootParent = obj->getRootParent().get();

		if (rootParent == NULL || !rootParent->isVehicleObject())
			return;

		if (!notifiedPlayers.contains(obj)) {
			notifiedPlayers.put(obj);

			player->sendSystemMessage("@pet/pet_menu:garage_proximity"); //You have entered into the proximity of a vehicle garage.
		}
	}
}

void GarageZoneComponent::notifyDissapear(SceneObject* sceneObject, QuadTreeEntry* entry) {
	StructureZoneComponent::notifyDissapear(sceneObject, entry);

	ManagedReference<SceneObject*> obj = cast<SceneObject*>(entry);

	if (obj == NULL || !obj->isPlayerCreature())
		return;

	if (notifiedPlayers.contains(obj))
		notifiedPlayers.drop(obj);
}
