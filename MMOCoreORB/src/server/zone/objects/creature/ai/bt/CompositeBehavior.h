/*
 * CompositeBehavior
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#ifndef COMPOSITEBEHAVIOR_H_
#define COMPOSITEBEHAVIOR_H_

#include "Behavior.h"
#include "engine/engine.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class CompositeBehavior : public Behavior{
public:
	Vector<Behavior*> children;
};

}
}
}
}
}
}
using namespace server::zone::objects::creature::ai::bt;
#endif /* COMPOSITEBEHAVIOR_H_ */
