/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "GarageZoneComponent.h"
#include "GarageDataComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"

void GarageZoneComponent::notifyPositionUpdate(SceneObject* sceneObject, TreeEntry* entry) const {

	ManagedReference<SceneObject*> obj = cast<SceneObject*>(entry);

	if (obj == nullptr)
		return;

	if (obj->isVehicleObject()) {
		obj = obj->getSlottedObject("rider");

		if (obj == nullptr){
			return;
		}
	}

	if (!obj->isCreatureObject())
		return;

	CreatureObject* player = obj->asCreatureObject();

	if (player == nullptr)
		return;

	GarageDataComponent* data = cast<GarageDataComponent*>(sceneObject->getDataObjectComponent()->get());

	if (data == nullptr)
		return;

	uint64 objID = player->getObjectID();

	float deltaX = sceneObject->getPositionX() - player->getPositionX();
	float deltaY = sceneObject->getPositionY() - player->getPositionY();
	float rangeSq = deltaX * deltaX + deltaY * deltaY;

	if (rangeSq > 4096) { // 64^2
		if (data->hasNotifiedPlayer(objID))
		{
			data->removeNotifiedPlayer(objID);
		}
	} else {

		if (!data->hasNotifiedPlayer(objID) && player->isRidingMount()) {
			data->addNotifiedPlayer(objID);
			player->sendSystemMessage("@pet/pet_menu:garage_proximity"); //You have entered into the proximity of a vehicle garage.
		}
		else if (data->hasNotifiedPlayer(objID) && !player->isRidingMount())
		{
				data->removeNotifiedPlayer(objID);
		}
	}
}

void GarageZoneComponent::notifyDissapear(SceneObject* sceneObject, TreeEntry* entry) const {
	StructureZoneComponent::notifyDissapear(sceneObject, entry);

	ManagedReference<SceneObject*> obj = cast<SceneObject*>(entry);

	if (obj == nullptr)
		return;

	if (obj->isVehicleObject())
	{
		obj = obj->getSlottedObject("rider");
          	if (obj == nullptr){
          		return;
                }
	}

	if (!obj->isCreatureObject())
		return;

	CreatureObject* player = obj->asCreatureObject();

	if (player == nullptr)
		return;

	GarageDataComponent* data = cast<GarageDataComponent*>(sceneObject->getDataObjectComponent()->get());

	if (data == nullptr)
		return;

	uint64 objID = player->getObjectID();

	if (data->hasNotifiedPlayer(objID))
		data->removeNotifiedPlayer(objID);
}