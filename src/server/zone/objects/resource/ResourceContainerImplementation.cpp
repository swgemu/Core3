/*
Copyright (C) 2010 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 3 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/


#include "ResourceContainer.h"
#include "ResourceSpawn.h"
#include "server/zone/packets/resource/ResourceContainerObjectDeltaMessage3.h"
#include "server/zone/packets/resource/ResourceContainerObjectMessage3.h"
#include "server/zone/packets/resource/ResourceContainerObjectMessage6.h"
#include "server/zone/ZoneClientSession.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/player/PlayerCreature.h"

void ResourceContainerImplementation::fillAttributeList(AttributeListMessage* alm, PlayerCreature* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

	StringBuffer ssQuantity;
	ssQuantity << stackQuantity << "/" << ResourceContainer::MAXSIZE;

	alm->insertAttribute("resource_name", getSpawnName());
	alm->insertAttribute("resource_contents", ssQuantity);

	spawnObject->fillAttributeList(alm, object);
}

void ResourceContainerImplementation::sendBaselinesTo(SceneObject* player) {
	info("sending rnco baselines");

	BaseMessage* rnco3 = new ResourceContainerObjectMessage3(_this);
	player->sendMessage(rnco3);

	BaseMessage* rnco6 = new ResourceContainerObjectMessage6(_this);
	player->sendMessage(rnco6);
}

void ResourceContainerImplementation::setQuantity(int quantity, SceneObject* player) {
	Locker _locker(_this);

	stackQuantity = quantity;

	if (player == NULL)
		return;

	int newStackSize = 0;

	if (stackQuantity > ResourceContainer::MAXSIZE) {

		newStackSize = stackQuantity - ResourceContainer::MAXSIZE;
		stackQuantity = ResourceContainer::MAXSIZE;
	}

	if (newStackSize > 0) {

		// Add resource to inventory
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

		ResourceContainer* harvestedResource = spawnObject->createResource(newStackSize);
		harvestedResource->sendTo(player, true);
		inventory->addObject(harvestedResource, -1, true);
		harvestedResource->updateToDatabase();
	}

	ResourceContainerObjectDeltaMessage3* rcnod3 = new ResourceContainerObjectDeltaMessage3(_this);

	rcnod3->setQuantity(stackQuantity);
	rcnod3->close();

	player->sendMessage(rcnod3);
}

void ResourceContainerImplementation::split(PlayerCreature* playerCreature, int newStackSize) {
	ManagedReference<SceneObject*> inventory =
			playerCreature->getSlottedObject("inventory");

	ResourceContainer* newResource = spawnObject->createResource(newStackSize);

	if(newResource == NULL)
		return;

	newResource->sendTo(playerCreature, true);
	inventory->addObject(newResource, -1, true);
	newResource->updateToDatabase();

	setQuantity(getQuantity() - newStackSize, playerCreature);
}

void ResourceContainerImplementation::combine(PlayerCreature* player, ResourceContainer* fromContainer) {
	Locker _locker(_this);

	ManagedReference<SceneObject*> inventory =
			player->getSlottedObject("inventory");

	setQuantity(getQuantity() + fromContainer->getQuantity(), player);
	fromContainer->setQuantity(0);

	Locker _inventorylocker(inventory);
	inventory->removeObject(fromContainer, true);
	fromContainer->destroyObjectFromDatabase(true);
}

void ResourceContainerImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	TangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);

	spawnObject->decreaseContainerReferenceCount();
}
