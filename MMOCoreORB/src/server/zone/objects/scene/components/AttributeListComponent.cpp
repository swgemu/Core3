/*
 * ObjectMenuComponent.cpp
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#include "AttributeListComponent.h"

#include "server/zone/objects/scene/SceneObject.h"

void AttributeListComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* creature, SceneObject* object) const {
	object->fillAttributeList(alm, creature);
}
