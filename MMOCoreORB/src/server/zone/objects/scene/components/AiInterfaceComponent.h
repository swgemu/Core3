/*
 * AiInterfaceComponent.h
 *
 *  Created on: Feb 15, 2012
 *      Author: da
 */

#ifndef AIINTERFACECOMPONENT_H_
#define AIINTERFACECOMPONENT_H_

#include "engine/engine.h"
#include "SceneObjectComponent.h"

namespace server {
namespace zone {
namespace objects {
namespace scene {
class SceneObject;
}
}
}
}

using namespace server::zone::objects::scene;

class AiInterfaceComponent : public SceneObjectComponent {
public:
	virtual void notifyPositionUpdate(SceneObject* scno, QuadTreeEntry* entry) {}
	virtual void doAwarenessCheck(SceneObject* scno, Coordinate& start, uint64 time, CreatureObject* target) {}
};

#endif /* AIINTERFACECOMPONENT_H_ */
