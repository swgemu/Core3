/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SCREENHANDLER_H_
#define SCREENHANDLER_H_

#include "server/zone/objects/creature/conversation/ConversationScreen.h"
#include "server/zone/objects/creature/CreatureObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace conversation {
namespace screenhandlers {

class ScreenHandler {
protected:
	String nextScreenId;
public:
	ScreenHandler() {}
	~ScreenHandler() {}

	String getNextScreenId() {
		return nextScreenId;
	}

	virtual ConversationScreen* handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen) = 0;
};

} // namespace screenhandlers
} // namespace conversation
} // namespace creature
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::creature::conversation::screenhandlers;

#endif /* SCREENHANDLER_H_ */
