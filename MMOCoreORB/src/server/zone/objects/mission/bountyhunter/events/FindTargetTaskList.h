/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FINDTARGETTASKLIST_H_
#define FINDTARGETTASKLIST_H_

#include "engine/core/Task.h"

namespace server {
namespace zone {
namespace objects {
namespace mission {
namespace bountyhunter {
namespace events {

class FindTargetTaskList : public Vector<Reference<Task* > > {

};

} // namespace events
} // namespace bountyhunter
} // namespace mission
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::mission::bountyhunter::events;

#endif /* FINDTARGETTASKLIST_H_ */
