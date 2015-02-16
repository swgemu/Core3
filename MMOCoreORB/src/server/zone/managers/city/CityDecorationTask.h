/*
 * CityDecorationTask.h
 *
 *  Created on: Aug 26, 2013
 *      Author: root
 */

#ifndef CITYDECORATIONTASK_H_
#define CITYDECORATIONTASK_H_

#include "engine/engine.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/scene/SceneObject.h"

class CityDecorationTask : public Task {
	ManagedReference<CreatureObject*> mayor;
	ManagedReference<SceneObject*> obj;
	byte option;

public:
	static const byte PLACE;
	static const byte REMOVE;

	CityDecorationTask(CreatureObject* creature, SceneObject* object, byte function);

	void run();

	void placeDecoration();

	void removeDecoration();
};

#endif /* CITYDECORATIONTASK_H_ */
