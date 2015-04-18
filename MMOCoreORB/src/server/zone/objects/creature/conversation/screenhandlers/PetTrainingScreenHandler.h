/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PETTRAININGSCREENHANDLER_H_
#define PETTRAININGSCREENHANDLER_H_

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

class PetTrainingScreenHandler : public ScreenHandler, Logger {

public:
	static const String STARTSCREENHANDLERID;
	static const String PETCOMMANDREPAIR;
	static const String PETFORMATION1COMMAND;
	static const String PETFORMATION2COMMAND;
	static const String PETGUARDCOMMAND;
	static const String PETATTACKCOMMAND;
	static const String PETFRIENDCOMMAND;
	static const String PETTRANSFERCOMMAND;
	static const String PETCLEARPOINTSCOMMAND;
	static const String PETGETPOINTSCOMMAND;
	static const String PETPATROLCOMMAND;
	static const String PETSTAYCOMMAND;
	static const String PETFOLLOWCOMMAND;
	static const String PETFOLLOWOTHERCOMMAND;
	static const String PETGROUPCOMMAND;
	static const String PETRELEASECOMMAND;

	PetTrainingScreenHandler() : ScreenHandler(), Logger("PetTrainingScreenHandler") {}

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

#endif /* PETTRAININGSCREENHANDLER_H_ */
