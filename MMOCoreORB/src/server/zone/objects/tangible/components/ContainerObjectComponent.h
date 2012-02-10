/*
 * ContainerObjectComponent.h
 *
 *  Created on: 07/02/2012
 *      Author: victor
 */

#ifndef CONTAINEROBJECTCOMPONENT_H_
#define CONTAINEROBJECTCOMPONENT_H_

#include "server/zone/objects/scene/components/ContainerComponent.h"

class ContainerObjectComponent : public ContainerComponent {
public:
	bool checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission);
};


#endif /* CONTAINEROBJECTCOMPONENT_H_ */
