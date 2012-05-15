/*
 * FactoryObjectMenuComponent.h
 *
 *  Created on: Feb 27, 2012
 *      Author: xyborn
 */

#ifndef FACTORYOBJECTMENUCOMPONENT_H_
#define FACTORYOBJECTMENUCOMPONENT_H_

#include "engine/engine.h"
#include "server/zone/objects/installation/components/InstallationObjectMenuComponent.h"

class FactoryObjectMenuComponent : public InstallationObjectMenuComponent {
public:
	void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* creature);
	int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID);
};


#endif /* FACTORYOBJECTMENUCOMPONENT_H_ */
