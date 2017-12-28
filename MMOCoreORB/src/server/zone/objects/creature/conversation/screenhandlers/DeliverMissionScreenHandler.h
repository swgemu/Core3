/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DELIVERMISSIONSCREENHANDLER_H_
#define DELIVERMISSIONSCREENHANDLER_H_

#include "ScreenHandler.h"
#include "engine/log/Logger.h"
#include "server/zone/objects/mission/DeliverMissionObjective.h"
#include "server/zone/objects/mission/MissionObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
namespace conversation {
class ConversationScreen;
}  // namespace conversation
}  // namespace creature
namespace mission {
class DeliverMissionObjective;
class MissionObject;
}  // namespace mission
}  // namespace objects
}  // namespace zone
}  // namespace server
namespace sys {
namespace io {
class ObjectInputStream;
class ObjectOutputStream;
}  // namespace io
namespace lang {
class String;
}  // namespace lang
}  // namespace sys

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace conversation {
namespace screenhandlers {

class DeliverMissionScreenHandler : public ScreenHandler, Logger {
protected:
	MissionObject* getRelevantMissionObject(CreatureObject* player, CreatureObject* npc);

	bool isTargetNpc(DeliverMissionObjective* objective, CreatureObject* npc);

	bool isDestinationNpc(DeliverMissionObjective* objective, CreatureObject* npc);

	void performPickupConversation(ConversationScreen* conversationScreen, MissionObject* mission);

	void performDeliverConversation(ConversationScreen* conversationScreen, MissionObject* mission);

public:
	static const String STARTSCREENHANDLERID;

	DeliverMissionScreenHandler() : ScreenHandler(), Logger("DeliverMissionScreenHandler") {}

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

#endif /* DELIVERMISSIONSCREENHANDLER_H_ */
