/*
 * ObjectMenuComponent.cpp
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#include "AttributeListComponent.h"

#include "client/zone/objects/creature/CreatureObject.h"
#include "client/zone/objects/scene/SceneObject.h"
#include "client/zone/packets/scene/AttributeListMessage.h"

void AttributeListComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* creature, SceneObject* object) const {
	object->fillAttributeList(alm, creature);
}
