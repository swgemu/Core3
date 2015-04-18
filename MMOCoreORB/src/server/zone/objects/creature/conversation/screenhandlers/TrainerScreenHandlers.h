/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TRAINERSCREENHANDLERS_H_
#define TRAINERSCREENHANDLERS_H_

#include "ScreenHandler.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace conversation {
namespace screenhandlers {

class TrainerInfoScreenHandler : public ScreenHandler {
public:
	TrainerInfoScreenHandler() : ScreenHandler() {}

	ConversationScreen* handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen);
};

class TrainerTrainableSkillsScreenHandler : public ScreenHandler {
	void getTrainableSkillsList(CreatureObject* conversingPlayer, Vector<String>* trainableSkillList, Skill* skill);
public:
	TrainerTrainableSkillsScreenHandler() : ScreenHandler() {}

	ConversationScreen* handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen);
};

class TrainerNextSkillsScreenHandler : public ScreenHandler {
	void getNextSkillsList(CreatureObject* conversingPlayer, Vector<String>* trainableSkillList, Skill* skill);
public:
	TrainerNextSkillsScreenHandler() : ScreenHandler() {}

	ConversationScreen* handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen);
};

class TrainerSkillInfoScreenHandler : public ScreenHandler {
public:
	TrainerSkillInfoScreenHandler() : ScreenHandler() {}

	ConversationScreen* handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen);
};

class TrainerCanLearnSkillScreenHandler : public ScreenHandler {
public:
	TrainerCanLearnSkillScreenHandler() : ScreenHandler() {}

	ConversationScreen* handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen);
};

class TrainerTrainSkillScreenHandler : public ScreenHandler {
public:
	TrainerTrainSkillScreenHandler() : ScreenHandler() {}

	ConversationScreen* handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen);
};

class TrainerNotEnoughCreditsScreenHandler : public ScreenHandler {
public:
	TrainerNotEnoughCreditsScreenHandler() : ScreenHandler() {}

	ConversationScreen* handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen);
};

class TrainerNotEnoughSkillPointsScreenHandler : public ScreenHandler {
public:
	TrainerNotEnoughSkillPointsScreenHandler() : ScreenHandler() {}

	ConversationScreen* handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen);
};

class TrainerTrainedMasterScreenHandler : public ScreenHandler {
public:
	TrainerTrainedMasterScreenHandler() : ScreenHandler() {}

	ConversationScreen* handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen);
};

/**
 * Class containing all screen handlers.
 */
class TrainerScreenHandlers {
public:
	static const String STARTSCREENHANDLERID;
	static const String INFOSCREENHANDLERID;
	static const String TRAINABLESKILLSSCREENHANDLERID;
	static const String NEXTSKILLSSCREENHANDLERID;
	static const String SKILLINFOSCREENHANDLERID;
	static const String CANLEARNSKILLSCREENHANDLERID;
	static const String TRAINSKILLSCREENHANDLERID;
	static const String NOTENOUGHCREDITSSCREENHANDLERID;
	static const String NOTENOUGHSKILLPOINTSSCREENHANDLERID;
	static const String NOTENOUGHXPSCREENHANDLERID;
	static const String TRAINEDMASTERSCREENHANDLERID;
	static const String ERRORSCREENHANDLERID;
	static const String NONEXISTINGSCREENHANDLERID;

	TrainerInfoScreenHandler infoScreenHandler;

	TrainerTrainableSkillsScreenHandler trainableSkillsScreenHandler;

	TrainerNextSkillsScreenHandler nextSkillsScreenHandler;

	TrainerSkillInfoScreenHandler skillInfoScreenHandler;

	TrainerCanLearnSkillScreenHandler canLearnSkillScreenHandler;

	TrainerTrainSkillScreenHandler trainSkillScreenHandler;

	TrainerNotEnoughCreditsScreenHandler notEnoughCreditsScreenHandler;

	TrainerNotEnoughSkillPointsScreenHandler notEnoughSkillPointsScreenHandler;

	TrainerTrainedMasterScreenHandler trainedMasterScreenHandler;

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

#endif /* TRAINERSCREENHANDLERS_H_ */
