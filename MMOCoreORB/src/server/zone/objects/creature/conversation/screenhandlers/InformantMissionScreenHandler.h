/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INFORMANTMISSIONSCREENHANDLER_H_
#define INFORMANTMISSIONSCREENHANDLER_H_

#include "ScreenHandler.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "engine/log/Logger.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace conversation {
namespace screenhandlers {

class InformantMissionScreenHandler : public ScreenHandler, Logger {
protected:
	MissionObject* getBountyMissionObject(CreatureObject* player);

public:
	static const String STARTSCREENHANDLERID;

	InformantMissionScreenHandler() : ScreenHandler(), Logger("InformantMissionScreenHandler") {}

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

#endif /* INFORMANTMISSIONSCREENHANDLER_H_ */
