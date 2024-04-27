/*
 * EventPerkActorContainerComponent.cpp
 *
 * Created on: 2024-04-26
 * By: Hakry
 */

#include "EventPerkActorContainerComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/components/EventPerkDataComponent.h"
#include "server/zone/objects/player/PlayerObject.h"

bool EventPerkActorContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const {
	// sceneObject->info(true) << "EventPerkActorContainerComponent::checkContainerPermission -- for object: " << sceneObject->getDisplayedName();

	if (sceneObject == nullptr || creature == nullptr) {
		return false;
	}

	auto zoneServer = sceneObject->getZoneServer();

	if (zoneServer == nullptr) {
		return false;
	}

	const ContainerPermissions* permissions = sceneObject->getContainerPermissions();

	if (permissions == nullptr) {
		return false;
	}

	uint64 parentID = permissions->getOwnerID();
	auto parentPerk = zoneServer->getObject(parentID);

	if (parentPerk == nullptr) {
		return false;
	}

	auto data = parentPerk->getDataObjectComponent()->get();

	if (data == nullptr || !data->isEventPerkData()) {
		return false;
	}

	auto perkData = cast<EventPerkDataComponent*>(data);

	if (perkData == nullptr) {
		return false;
	}

	auto deed = perkData->getDeed();

	if (deed == nullptr) {
		return false;
	}

	auto ghost = creature->getPlayerObject();

	if (ghost == nullptr || !ghost->isPrivileged()) {
		return false;
	}

	return true;
}