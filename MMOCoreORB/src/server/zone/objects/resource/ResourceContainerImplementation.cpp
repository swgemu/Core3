/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/


#include "server/zone/objects/resource/ResourceContainer.h"
#include "server/zone/packets/resource/ResourceContainerObjectDeltaMessage3.h"
#include "server/zone/packets/resource/ResourceContainerObjectMessage3.h"
#include "server/zone/packets/resource/ResourceContainerObjectMessage6.h"
#include "server/zone/objects/creature/CreatureObject.h"

void ResourceContainerImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

	StringBuffer ssQuantity;
	ssQuantity << stackQuantity << "/" << ResourceContainer::MAXSIZE;

	alm->insertAttribute("resource_name", getSpawnName());
	alm->insertAttribute("resource_contents", ssQuantity);

	if (spawnObject != NULL)
		spawnObject->fillAttributeList(alm, object);
	else
		object->sendSystemMessage("error resource container has no spawn object");
}

void ResourceContainerImplementation::sendBaselinesTo(SceneObject* player) {
	debug("sending rnco baselines");

	BaseMessage* rnco3 = new ResourceContainerObjectMessage3(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(rnco3);

	BaseMessage* rnco6 = new ResourceContainerObjectMessage6(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(rnco6);
}

void ResourceContainerImplementation::setUseCount(uint32 newQuantity, bool notifyClient) {
	setQuantity(newQuantity, notifyClient);
}

void ResourceContainerImplementation::setQuantity(uint32 quantity, bool doNotify, bool ignoreMax) {
	Locker _locker(_this.getReferenceUnsafeStaticCast());
	ManagedReference<SceneObject*> parent = getParent().get();
	stackQuantity = quantity;

	if (stackQuantity < 1) {

		if (parent != NULL) {
			destroyObjectFromWorld(true);
		}

		destroyObjectFromDatabase(true);
		return;
	}

	int newStackSize = 0;

	if (!ignoreMax && stackQuantity > ResourceContainer::MAXSIZE) {

		newStackSize = stackQuantity - ResourceContainer::MAXSIZE;
		stackQuantity = ResourceContainer::MAXSIZE;
	}

	if (newStackSize > 0) {
		if (parent != NULL) {

			Locker locker(spawnObject);

			Reference<ResourceContainer*> harvestedResource = spawnObject->createResource(newStackSize);

			locker.release();

			Locker clocker(harvestedResource, _this.getReferenceUnsafeStaticCast());

			if (parent->transferObject(harvestedResource, -1, true)) {
				parent->broadcastObject(harvestedResource, true);
			} else {
				harvestedResource->destroyObjectFromDatabase(true);
			}
		}
	}

	if(!doNotify)
		return;

	ResourceContainerObjectDeltaMessage3* rcnod3 =
			new ResourceContainerObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast());

	rcnod3->updateQuantity();
	rcnod3->close();

	broadcastMessage(rcnod3, true);
}

void ResourceContainerImplementation::split(int newStackSize) {
	if (getQuantity() <= newStackSize)
		return;

	if(newStackSize > getQuantity())
		newStackSize = getQuantity();

	ManagedReference<SceneObject*> sceneParent = cast<SceneObject*>(parent.get().get());

	if (sceneParent == NULL)
		return;

	Locker locker(spawnObject);

	ManagedReference<ResourceContainer*> newResource = spawnObject->createResource(newStackSize);

	locker.release();

	if(newResource == NULL)
		return;

	Locker rlocker(newResource);

	if (newResource->getSpawnObject() == NULL) {
		newResource->destroyObjectFromDatabase(true);
		return;
	}

	if(sceneParent->transferObject(newResource, -1, true)) {
		sceneParent->broadcastObject(newResource, true);

		setQuantity(getQuantity() - newStackSize);
	} else {
		StringBuffer errorMessage;
		errorMessage << "Unable to split resource in container type: " << sceneParent->getGameObjectType() << " " << sceneParent->getDisplayedName();
		error(errorMessage.toString());

		newResource->destroyObjectFromDatabase(true);
	}
}

void ResourceContainerImplementation::split(int newStackSize, CreatureObject* player) {

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory == NULL)
		return;

	Locker locker(spawnObject);

	ManagedReference<ResourceContainer*> newResource = spawnObject->createResource(newStackSize);

	locker.release();

	if (newResource == NULL)
		return;

	Locker rlocker(newResource);

	if (newResource->getSpawnObject() == NULL) {
		newResource->destroyObjectFromDatabase(true);
		return;
	}

	if(inventory->transferObject(newResource, -1, true)) {
		newResource->sendTo(player, true);

		setQuantity(getQuantity() - newStackSize);
	} else {
		error("Unable to split resource to player: " + player->getFirstName());
		newResource->destroyObjectFromDatabase(true);
	}
}

void ResourceContainerImplementation::combine(ResourceContainer* fromContainer) {
	Locker _locker(_this.getReferenceUnsafeStaticCast());
	Locker clocker(fromContainer, _this.getReferenceUnsafeStaticCast());

	setQuantity(getQuantity() + fromContainer->getQuantity());
	fromContainer->setQuantity(0);

	fromContainer->destroyObjectFromWorld(true);
	fromContainer->destroyObjectFromDatabase(true);
}

void ResourceContainerImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	TangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);

	if (spawnObject != NULL)
		spawnObject->decreaseContainerReferenceCount();
}
