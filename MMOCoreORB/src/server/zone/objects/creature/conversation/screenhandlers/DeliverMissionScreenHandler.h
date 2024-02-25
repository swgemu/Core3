/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DELIVERMISSIONSCREENHANDLER_H_
#define DELIVERMISSIONSCREENHANDLER_H_

#include "ScreenHandler.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/objects/mission/DeliverMissionObjective.h"
#include "engine/log/Logger.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace conversation {
namespace screenhandlers {

class DeliverMissionScreenHandler : public ScreenHandler, Logger {
protected:
	MissionObject* getRelevantMissionObject(CreatureObject* player, SceneObject* npc);

	bool isTargetNpc(DeliverMissionObjective* objective, SceneObject* npc);

	bool isDestinationNpc(DeliverMissionObjective* objective, SceneObject* npc);

	void performPickupConversation(ConversationScreen* conversationScreen, MissionObject* mission);

	void performDeliverConversation(ConversationScreen* conversationScreen, MissionObject* mission);

public:
	static const String STARTSCREENHANDLERID;

	DeliverMissionScreenHandler() : ScreenHandler(), Logger("DeliverMissionScreenHandler") {}

	ConversationScreen* handleScreen(CreatureObject* conversingPlayer, SceneObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen);

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
