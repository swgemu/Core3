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
				}
			}
		}
	}
}


namespace server {
namespace zone {
namespace managers {
namespace minigames {
namespace events {

class GamblingEvent : public Task {
	Reference<server::zone::objects::tangible::terminal::gambling::GamblingTerminal*> gamblingTerminal;
	int gameCount;

public:
	GamblingEvent(server::zone::objects::tangible::terminal::gambling::GamblingTerminal* gamblingTerm, int counter);

	void run();

};

}
}
}
}
}

using namespace server::zone::managers::minigames::events;

#endif /* GAMBLINGSLOTEVENT_H_ */
