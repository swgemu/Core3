/*
 * VendorContainerComponent.cpp
 *
 *  Created on: 08/02/2012
 *      Author: victor
 */

#include "VendorContainerComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"

bool VendorContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const {

	if (!sceneObject->isVendor())
		return false;

	DataObjectComponentReference* data = sceneObject->getDataObjectComponent();
	if(data == nullptr || data->get() == nullptr || !data->get()->isVendorData())
		return false;

	VendorDataComponent* vendorData = cast<VendorDataComponent*>(data->get());
	if(vendorData == nullptr)
		return false;

	if (vendorData->getOwnerId() != creature->getObjectID()) {
		creature->sendSystemMessage("Only the vendor owner can do that.");
		return false;
	}

	if (vendorData->isInitialized()) {
		creature->sendSystemMessage("@player_structure:cant_move");
		return false;
	}

	return true;
}
