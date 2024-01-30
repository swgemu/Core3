/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GAMBLINGEVENT_H_
#define GAMBLINGEVENT_H_

#include "server/zone/ZoneProcessServer.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace terminal {
namespace gambling {
class GamblingTerminal;
}
} // namespace terminal
} // namespace tangible
} // namespace objects
} // namespace zone
} // namespace server

namespace server {
namespace zone {
namespace managers {
namespace minigames {
namespace events {

class GamblingEvent : public Task {
	ManagedWeakReference<server::zone::objects::tangible::terminal::gambling::GamblingTerminal*> gamblingTerm;
	int gameCount;

public:
	GamblingEvent(server::zone::objects::tangible::terminal::gambling::GamblingTerminal* terminal, int counter);

	void run();
};

} // namespace events
} // namespace minigames
} // namespace managers
} // namespace zone
} // namespace server

using namespace server::zone::managers::minigames::events;

#endif /* GAMBLINGEVENT_H_ */
