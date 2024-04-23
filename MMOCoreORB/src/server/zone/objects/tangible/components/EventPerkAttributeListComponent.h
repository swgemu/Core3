/*
 * EventPerkAttributeListComponent.h
 *
 *  Created on: 9/20/2014
 *      Author: Klivian
 */

#ifndef EVENTPERKATTRIBUTELISTCOMPONENT_H_
#define EVENTPERKATTRIBUTELISTCOMPONENT_H_

#include "server/zone/objects/scene/components/AttributeListComponent.h"
#include "server/zone/objects/tangible/components/EventPerkDataComponent.h"
#include "server/zone/objects/tangible/deed/eventperk/EventPerkDeed.h"

class EventPerkAttributeListComponent : public AttributeListComponent {
public:
	/**
	 * Fills the Attributes
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 */
	void fillAttributeList(AttributeListMessage* alm, CreatureObject* player, SceneObject* sceneObject) const {
		if (player == nullptr || sceneObject == nullptr || !sceneObject->isTangibleObject())
			return;

		// Fill from parent
		AttributeListComponent::fillAttributeList(alm, player, sceneObject);

		EventPerkDataComponent* data = cast<EventPerkDataComponent*>(sceneObject->getDataObjectComponent()->get());

		if (data == nullptr) {
			error() << "Event Perk EventPerkDataComponent is nullptr, destroying EventPerk ID: " << sceneObject->getObjectID();

			Locker lock(sceneObject);
			sceneObject->destroyObjectFromWorld(true);
			sceneObject->destroyObjectFromDatabase(true);

			return;
		}

		EventPerkDeed* deed = data->getDeed();

		if (deed == nullptr) {
			error() << "Event Perk Deed is nullptr, destroying EventPerk ID: " << sceneObject->getObjectID();

			Locker lock(sceneObject);
			sceneObject->destroyObjectFromWorld(true);
			sceneObject->destroyObjectFromDatabase(true);

			return;
		}

		ManagedReference<CreatureObject*> owner = deed->getOwner().get();
		if (owner != nullptr) {
			alm->insertAttribute("owner", owner->getFirstName());
		}
	}
};

#endif /* EVENTPERKATTRIBUTELISTCOMPONENT_H_ */
