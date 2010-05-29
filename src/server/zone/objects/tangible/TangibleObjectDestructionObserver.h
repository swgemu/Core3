/*
 * SceneObjectDestructionObserver.h
 *
 *  Created on: 29/05/2010
 *      Author: victor
 */

#ifndef SCENEOBJECTDESTRUCTIONOBSERVER_H_
#define SCENEOBJECTDESTRUCTIONOBSERVER_H_

#include "server/zone/objects/scene/Observer.h"

class TangibleObjectDestructionObserver : public Observer {
public:
	virtual int notifyDestruction(TangibleObject* destructor, TangibleObject* destructedObject, int condition) = 0;
};


#endif /* SCENEOBJECTDESTRUCTIONOBSERVER_H_ */
