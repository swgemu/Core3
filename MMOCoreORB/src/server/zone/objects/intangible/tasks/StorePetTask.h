/*
 * StorePetTask.h
 *
 *  Created on: Dec 11, 2013
 *      Author: TheAnswer
 */

#include "engine/engine.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
class AiAgent;
}

class CreatureObject;
} // namespace creature

} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::creature;
using namespace server::zone::objects::creature::ai;

class StorePetTask : public Task {
	WeakReference<CreatureObject*> play;
	WeakReference<AiAgent*> pt;

public:
	StorePetTask(CreatureObject* player, AiAgent* pet);

	void run();
};
