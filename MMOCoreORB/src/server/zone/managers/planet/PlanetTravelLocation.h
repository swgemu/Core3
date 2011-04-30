/*
 * PlanetTravelLocation.h
 *
 *  Created on: Apr 30, 2011
 *      Author: crush
 */

#ifndef PLANETTRAVELLOCATION_H_
#define PLANETTRAVELLOCATION_H_

#include "engine/engine.h"

using namespace server::zone::objects::creature;
using namespace server::zone::objects::scene;

class CreatureObject;
class SceneObject;

class PlanetTravelLocation : public Object {
	ManagedReference<CreatureObject*> shuttleCreature;
	ManagedReference<SceneObject*> shuttlePort;

public:
	PlanetTravelLocation(CreatureObject* shuttle, SceneObject* port) {
		shuttleCreature = shuttle;
		shuttlePort = port;
	}

	PlanetTravelLocation(const PlanetTravelLocation& ptl) :
			Object() {
	}

	PlanetTravelLocation& operator= (const PlanetTravelLocation& ptl) {
		if (this == &ptl)
			return *this;

		return *this;
	}
};


#endif /* PLANETTRAVELLOCATION_H_ */
