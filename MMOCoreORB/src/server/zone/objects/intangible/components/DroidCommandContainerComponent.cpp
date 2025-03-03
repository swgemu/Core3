/*
 * DroidCommandContainerComponent.cpp
 *
 * Created: 2025-03-04
 * By: Hakry
 *
 *
*/

#include "server/zone/objects/intangible/components/DroidCommandContainerComponent.h"
#include "server/zone/objects/creature/ai/DroidObject.h"

bool DroidCommandContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const {
	if (sceneObject == nullptr || creature == nullptr) {
		return false;
	}

	if (permission != ContainerPermissions::MOVECONTAINER) {
		return false;
	}

	creature->info(true) << "Checking with DroidCommandContainerComponent Perm: " << permission;

	//auto droid = sceneObject->getParentRecursively(SceneObjectType::DROIDCREATURE).castTo<DroidObject*>();

	//if (droid == nullptr || droid->getLinkedCreature() != creature) {
	//	return false;
	//}

	return true;
}