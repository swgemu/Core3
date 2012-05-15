/*
 * VendorContainerComponent.cpp
 *
 *  Created on: 08/02/2012
 *      Author: victor
 */

#include "VendorContainerComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/vendor/VendorCreature.h"
#include "server/zone/objects/tangible/terminal/vendor/VendorTerminal.h"
#include "server/zone/objects/auction/Vendor.h"

bool VendorContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) {
	if (permission == ContainerPermissions::MOVECONTAINER) {
		if (sceneObject->isVendor()) {
			Vendor* vendor = NULL;

			if (sceneObject->isCreatureObject()) {
				VendorCreature* vendorCreature = dynamic_cast<VendorCreature*>(sceneObject);
				vendor = vendorCreature->getVendor();
			} else if (sceneObject->isTerminal()) {
				VendorTerminal* vendorTerminal = dynamic_cast<VendorTerminal*>(sceneObject);
				vendor = vendorTerminal->getVendor();
			}

			if (vendor == NULL)
				return false;

			if (vendor->getOwnerID() != creature->getObjectID()) {
				creature->sendSystemMessage("Only the vendor owner can do that.");
				return false;
			}

			if (vendor->isInitialized()) {
				creature->sendSystemMessage("@player_structure:cant_move");
				return false;
			}
		}
	}

	return ContainerComponent::checkContainerPermission(sceneObject, creature, permission);
}
