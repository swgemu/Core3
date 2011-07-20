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
#include "server/zone/objects/creature/CreatureObject.h"

void ResourceContainerImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
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

void ResourceContainerImplementation::setUseCount(uint32 newQuantity, bool notifyClient) {
	setQuantity(newQuantity, notifyClient);
}

void ResourceContainerImplementation::setQuantity(uint32 quantity, bool doNotify) {
	Locker _locker(_this);

	stackQuantity = quantity;

	if(stackQuantity < 1) {

		if(parent != NULL) {
			parent->broadcastDestroy(_this, true);
			parent->removeObject(_this, true);
			setParent(NULL);
		}

		destroyObjectFromDatabase(true);
		return;
	}

	int newStackSize = 0;

	if (stackQuantity > ResourceContainer::MAXSIZE) {

		newStackSize = stackQuantity - ResourceContainer::MAXSIZE;
		stackQuantity = ResourceContainer::MAXSIZE;
	}

	if(!doNotify)
		return;

	if (newStackSize > 0) {
		if (parent != NULL) {

			ResourceContainer* harvestedResource = spawnObject->createResource(newStackSize);

			parent->addObject(harvestedResource, -1, true);
			parent->broadcastObject(harvestedResource, true);
			harvestedResource->updateToDatabase();
		}
	}

	ResourceContainerObjectDeltaMessage3* rcnod3 =
			new ResourceContainerObjectDeltaMessage3(_this);

	rcnod3->setQuantity(stackQuantity);
	rcnod3->close();

	broadcastMessage(rcnod3, true);
}

void ResourceContainerImplementation::split(int newStackSize) {

	ManagedReference<ResourceContainer*> newResource = spawnObject->createResource(newStackSize);

	if(parent == NULL || newResource == NULL || newResource->getSpawnObject() == NULL)
		return;

	parent->addObject(newResource, -1, true);
	parent->broadcastObject(newResource, true);

	setQuantity(getQuantity() - newStackSize);

   	newResource->updateToDatabase();
   	updateToDatabase();
}

void ResourceContainerImplementation::split(int newStackSize, CreatureObject* player) {
	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	ManagedReference<ResourceContainer*> newResource = spawnObject->createResource(newStackSize);

	if (newResource == NULL || newResource->getSpawnObject() == NULL)
		return;

	newResource->sendTo(player, true);
	inventory->addObject(newResource, -1, true);

	setQuantity(getQuantity() - newStackSize);

   	newResource->updateToDatabase();
   	updateToDatabase();
}

void ResourceContainerImplementation::combine(ResourceContainer* fromContainer) {
	Locker _locker(_this);

	ManagedReference<SceneObject*> parent =
			fromContainer->getParent();

	setQuantity(getQuantity() + fromContainer->getQuantity());
	fromContainer->setQuantity(0);

	if(parent != NULL) {
		Locker _parentlocker(parent);
		parent->removeObject(fromContainer, true);
	}

	fromContainer->destroyObjectFromDatabase(true);
}

void ResourceContainerImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	TangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);

	spawnObject->decreaseContainerReferenceCount();
}
