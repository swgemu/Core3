#include "ChecksSpace.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"

// full template specializations need to go in cpp so they don't get
// defined multiple times.

using namespace server::zone::objects::ship::ai::btspace::leafspace;

template<> bool CheckDestination::check(ShipAiAgent* agent) const {
	return agent->setDestination() > checkVar;
}
