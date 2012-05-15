/*
 * InstallationObjectMenuComponent.h
 *
 *  Created on: Feb 27, 2012
 *      Author: xyborn
 */

#ifndef INSTALLATIONOBJECTMENUCOMPONENT_H_
#define INSTALLATIONOBJECTMENUCOMPONENT_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"

class InstallationObjectMenuComponent : public ObjectMenuComponent {
public:
	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* creature);
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID);
};

#endif /* INSTALLATIONOBJECTMENUCOMPONENT_H_ */
