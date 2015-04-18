/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef BOUNTYHUNTERTEFREMOVALTASKMAP_H_
#define BOUNTYHUNTERTEFREMOVALTASKMAP_H_

#include "engine/core/Task.h"

#include "system/util/SynchronizedVectorMap.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {

class BountyHunterTefRemovalTaskMap : public SynchronizedVectorMap<uint64, Reference<Task*> > {

};

}
}
}
}
}

using namespace server::zone::objects::player::events;

#endif /* BOUNTYHUNTERTEFREMOVALTASKMAP_H_ */
