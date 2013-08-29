/*
 * BehaviourTreeList.h
 *
 *  Created on: Aug 24, 2013
 *      Author: swgemu
 */

#ifndef BEHAVIORTREELIST_H_
#define BEHAVIORTREELIST_H_

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class BehaviorTreeList: public ArrayQueue<Behavior*> {

};

}
}
}
}
}
}

using namespace server::zone::objects::creature::ai::bt;

#endif /* BEHAVIORTREELIST_H_ */