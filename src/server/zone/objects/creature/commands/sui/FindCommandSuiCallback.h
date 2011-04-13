/*
 * FindCommandSuiCallback.h
 *
 *  Created on: Nov 3, 2010
 *      Author: crush
 */

#ifndef FINDCOMMANDSUICALLBACK_H_
#define FINDCOMMANDSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
	class PlayerCreature;

	namespace sui {
		class SuiBox;
	}
}
}
}
}

using namespace server::zone::objects::player;
using namespace server::zone::objects::player::sui;

class FindCommandSuiCallback : public SuiCallback {
public:
	FindCommandSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(PlayerCreature* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args);
};

#endif /* FINDCOMMANDSUICALLBACK_H_ */
