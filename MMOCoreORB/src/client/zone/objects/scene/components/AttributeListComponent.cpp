/*
 * ObjectMenuComponent.cpp
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#include "AttributeListComponent.h"

#include "zone/objects/creature/CreatureObject.h"
#include "zone/objects/scene/SceneObject.h"
#include "zone/packets/scene/AttributeListMessage.h"

void AttributeListComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* creature, SceneObject* object) const {
	object->fillAttributeList(alm, creature);
}
