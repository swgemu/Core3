/*
 * AiDefaultComponent.h
 *
 *  Created on: Feb 15, 2012
 *      Author: da
 */

#ifndef AIDEFAULTCOMPONENT_H_
#define AIDEFAULTCOMPONENT_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/components/AiInterfaceComponent.h"

namespace server {
namespace zone {
namespace objects {
namespace scene {
class SceneObject;
}
namespace creature {
class CreatureObject;
class AiAgent;
}
}
}
}

using namespace server::zone::objects::scene;
using namespace server::zone::objects::creature;

class AiDefaultComponent : public AiInterfaceComponent {
};

#endif /* AIDEFAULTCOMPONENT_H_ */
