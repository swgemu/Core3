/*
 * ContainmentTeam.h
 *
 *  Created on: Oct 9, 2020
 *      Author: loshult
 */

#ifndef CONTAINMENTTEAM_H_
#define CONTAINMENTTEAM_H_

#include "server/zone/objects/creature/ai/AiAgent.h"

namespace server {
namespace zone {
namespace managers {
namespace gcw {
namespace tasks {

class ContainmentTeam : public Vector<WeakReference<AiAgent*>> {
public:
	/**
	 * Constructor.
	 */
	ContainmentTeam() : Vector<WeakReference<AiAgent*>>() {}

	/**
	 * Destructor.
	 */
	~ContainmentTeam() {}
};

} // namespace tasks
} // namespace gcw
} // namespace managers
} // namespace zone
} // namespace server

using namespace server::zone::managers::gcw::tasks;

#endif /* CONTAINMENTTEAM_H_ */