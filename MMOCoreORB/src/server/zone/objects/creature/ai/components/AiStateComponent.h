/*
 * AiStateComponent.h
 *
 *  Created on: May 6, 2012
 *      Author: da
 */

#ifndef AISTATECOMPONENT_H_
#define AISTATECOMPONENT_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/components/SceneObjectComponent.h"

namespace server {
namespace zone {
namespace objects {
namespace scene {
class SceneObject;
}
namespace creature {
class CreatureObject;
}
}
}
}

using namespace server::zone::objects::scene;
using namespace server::zone::objects::creature;

class AiStateComponent : public SceneObjectComponent {
public:
	virtual void notifyPositionUpdate(Observable* actor, QuadTreeEntry* entry) {}
	virtual void doAwarenessCheck(Observable* actor, Coordinate& start, uint64 time, CreatureObject* target) {}
	virtual void onEnter() {}
	virtual void onExit() {}
};

#endif /* AISTATECOMPONENT_H_ */
