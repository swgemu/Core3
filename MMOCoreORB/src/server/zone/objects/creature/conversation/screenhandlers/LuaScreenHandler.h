/*
 * LuaScreenHandler.h
 *
 *  Created on: 03/01/2012
 *      Author: victor
 */

#ifndef LUASCREENHANDLER_H_
#define LUASCREENHANDLER_H_

#include "ScreenHandler.h"
#include "engine/log/Logger.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace conversation {
namespace screenhandlers {

class LuaScreenHandler : public ScreenHandler, Logger, public Object {
protected:

public:
	LuaScreenHandler() : ScreenHandler(), Logger("LuaScreenHandler") {}

	ConversationScreen* handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen);

	bool toBinaryStream(ObjectOutputStream* stream) {
		return true;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		return true;
	}
};

} // namespace screenhandlers
} // namespace conversation
} // namespace creature
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::creature::conversation::screenhandlers;



#endif /* LUASCREENHANDLER_H_ */
