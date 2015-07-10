/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "TrainerScreenHandlers.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/objects/player/sessions/TrainerConversationSession.h"
#include "server/zone/Zone.h"

const String TrainerScreenHandlers::STARTSCREENHANDLERID = "convoscreenstart";
const String TrainerScreenHandlers::INFOSCREENHANDLERID = "convoscreentrainerinfo";
const String TrainerScreenHandlers::TRAINABLESKILLSSCREENHANDLERID = "convoscreentrainableskills";
const String TrainerScreenHandlers::NEXTSKILLSSCREENHANDLERID = "convoscreennextskills";
const String TrainerScreenHandlers::SKILLINFOSCREENHANDLERID = "convoscreenskillinfo";
const String TrainerScreenHandlers::CANLEARNSKILLSCREENHANDLERID = "convoscreencanlearnskill";
const String TrainerScreenHandlers::TRAINSKILLSCREENHANDLERID = "convoscreentrainskill";
const String TrainerScreenHandlers::NOTENOUGHCREDITSSCREENHANDLERID = "convoscreennotenoughcredits";
const String TrainerScreenHandlers::NOTENOUGHSKILLPOINTSSCREENHANDLERID = "convoscreennotenoughskillpoints";
const String TrainerScreenHandlers::NOTENOUGHXPSCREENHANDLERID = "convoscreennotenoughxp";
const String TrainerScreenHandlers::TRAINEDMASTERSCREENHANDLERID = "convoscreentrainedmaster";
const String TrainerScreenHandlers::ERRORSCREENHANDLERID = "convoscreenerror";
const String TrainerScreenHandlers::NONEXISTINGSCREENHANDLERID = "non-existing-screen";

ConversationScreen* TrainerInfoScreenHandler::handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen) {
	Reference<TrainerConversationSession*> session = conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION).castTo<TrainerConversationSession* >();
	if (session == NULL) {
		nextScreenId = TrainerScreenHandlers::ERRORSCREENHANDLERID;
		return NULL;
	}

	String masterSkill = conversationScreen->getOptionLink(0);

	session->setMasterSkill(masterSkill);

	ManagedReference<PlayerObject*> ghost = conversingPlayer->getPlayerObject();

	if (ghost == NULL)
		return NULL;

	// The following is for Jedi trainers.
	Vector3 npc(conversingNPC->getWorldPositionX(), conversingNPC->getWorldPositionY(), 0);
	Vector3 playerCoord = ghost->getTrainerCoordinates();
	Vector3 player(playerCoord.getX(), playerCoord.getY(), 0);

	if ((npc == player) && (ghost->getTrainerZoneName() == conversingNPC->getZone()->getZoneName())) {
		String jedi1 = "force_discipline_light_saber_master";
		String jedi2 = "force_discipline_defender_master";
		String jedi3 = "force_discipline_powers_master";
		String jedi4 = "force_discipline_enhancements_master";
		String jedi5 = "force_discipline_healing_master";

		session->addAdditionalMasterSkill(jedi1);
		session->addAdditionalMasterSkill(jedi2);
		session->addAdditionalMasterSkill(jedi3);
		session->addAdditionalMasterSkill(jedi4);
		session->addAdditionalMasterSkill(jedi5);
	}

	if (conversingPlayer->hasSkill(session->getMasterSkill())) {
		nextScreenId = TrainerScreenHandlers::TRAINEDMASTERSCREENHANDLERID;
		return NULL;
	} else {
		nextScreenId = TrainerScreenHandlers::STARTSCREENHANDLERID;
		return NULL;
	}

	return conversationScreen;
}

ConversationScreen* TrainerTrainableSkillsScreenHandler::handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen) {
	Vector<String> trainableSkills;
	Vector<Skill*> masterSkills;

	Reference<TrainerConversationSession*> session = conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION).castTo<TrainerConversationSession* >();
	if (session == NULL) {
		nextScreenId = TrainerScreenHandlers::ERRORSCREENHANDLERID;
		return NULL;
	}

	Skill* startingMasterSkill = SkillManager::instance()->getSkill(session->getMasterSkill());

	if (session->getAdditionalMasterSkillsCount() > 0) {
		for (int i = 0; i < session->getAdditionalMasterSkillsCount(); i++) {
			masterSkills.add(SkillManager::instance()->getSkill(session->getAdditionalMasterSkill(i)));
		}
	}

	PlayerObject* ghost = conversingPlayer->getPlayerObject();

	if (masterSkills.size() <= 0)
		masterSkills.add(startingMasterSkill);

	//Clear options since we will add new below.
	for (int i = 0; i < 5; ++i) {
		conversationScreen->removeOption(0);
	}

	//Get trainable skills
	for (int i = 0; i < masterSkills.size(); ++i) {
		getTrainableSkillsList(conversingPlayer, &trainableSkills, masterSkills.get(i));
	}

	session->clearTrainableSkills();

	if (trainableSkills.size() > 0) {
		//Fill in text.
		for (int i = 0; i < trainableSkills.size(); ++i) {
			conversationScreen->addOption("@skl_n:" + trainableSkills.get(i), TrainerScreenHandlers::CANLEARNSKILLSCREENHANDLERID);
			session->addTrainableSkill(trainableSkills.get(i));
		}
		conversationScreen->addOption("@skill_teacher:back", TrainerScreenHandlers::STARTSCREENHANDLERID);
	} else {
		//No skills to learn, change conversation screen.
		nextScreenId = TrainerScreenHandlers::NOTENOUGHXPSCREENHANDLERID;
		conversationScreen = NULL;
	}

	return conversationScreen;
}

void TrainerTrainableSkillsScreenHandler::getTrainableSkillsList(CreatureObject* conversingPlayer, Vector<String>* trainableSkillList, Skill* skill) {
	if (skill == NULL) {
		return;
	}

	if (conversingPlayer->hasSkill(skill->getSkillName())) {
		return;
	}

	if (SkillManager::instance()->fullfillsSkillPrerequisitesAndXp(skill->getSkillName(), conversingPlayer)) {
		if (!trainableSkillList->contains(skill->getSkillName())) {
			trainableSkillList->add(skill->getSkillName());
		}
	} else if (skill->getSkillName().indexOf("novice") < 0){
		//Check skills recursive but no longer down the tree than novice skill.
		Vector<String>* requiredSkills = skill->getSkillsRequired();
		for (int i = 0; i < requiredSkills->size(); ++i) {
			getTrainableSkillsList(conversingPlayer, trainableSkillList, SkillManager::instance()->getSkill(requiredSkills->get(i)));
		}
	}
}

ConversationScreen* TrainerNextSkillsScreenHandler::handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen) {
	Vector<String> nextSkills;
	Vector<Skill*> masterSkills;

	Reference<TrainerConversationSession*> session = conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION).castTo<TrainerConversationSession* >();
	if (session == NULL) {
		nextScreenId = TrainerScreenHandlers::ERRORSCREENHANDLERID;
		return NULL;
	}

	Skill* startingMasterSkill = SkillManager::instance()->getSkill(session->getMasterSkill());

	if (session->getAdditionalMasterSkillsCount() > 0) {
		for (int i = 0; i < session->getAdditionalMasterSkillsCount(); i++) {
			masterSkills.add(SkillManager::instance()->getSkill(session->getAdditionalMasterSkill(i)));
		}
	}

	if (masterSkills.size() <= 0)
		masterSkills.add(startingMasterSkill);

	//Clear options since we will add new below.
	for (int i = 0; i < 5; ++i) {
		conversationScreen->removeOption(0);
	}
	session->clearNextSkills();

	//Get next skills
	for (int i = 0; i < masterSkills.size(); ++i) {
		getNextSkillsList(conversingPlayer, &nextSkills, masterSkills.get(i));
	}

	if (nextSkills.size() > 0) {
		//Fill in text.
		for (int i = 0; i < nextSkills.size(); ++i) {
			conversationScreen->addOption("@skl_n:" + nextSkills.get(i), TrainerScreenHandlers::SKILLINFOSCREENHANDLERID);
			session->addNextSkill(nextSkills.get(i));
		}
		conversationScreen->addOption("@skill_teacher:back", TrainerScreenHandlers::STARTSCREENHANDLERID);
	} else {
		//No skills to learn, change conversation screen.
		nextScreenId = TrainerScreenHandlers::NOTENOUGHXPSCREENHANDLERID;
		conversationScreen = NULL;
	}

	return conversationScreen;
}

void TrainerNextSkillsScreenHandler::getNextSkillsList(CreatureObject* conversingPlayer, Vector<String>* nextSkillList, Skill* skill) {
	if (skill == NULL) {
		return;
	}

	if (conversingPlayer->hasSkill(skill->getSkillName())) {
		return;
	}

	if (SkillManager::instance()->fullfillsSkillPrerequisites(skill->getSkillName(), conversingPlayer)) {
		if (!nextSkillList->contains(skill->getSkillName())) {
			nextSkillList->add(skill->getSkillName());
		}
	} else if (skill->getSkillName().indexOf("novice") < 0){
		//Check skills recursive but no longer down the tree than novice skill.
		Vector<String>* requiredSkills = skill->getSkillsRequired();
		for (int i = 0; i < requiredSkills->size(); ++i) {
			getNextSkillsList(conversingPlayer, nextSkillList, SkillManager::instance()->getSkill(requiredSkills->get(i)));
		}
	}
}

ConversationScreen* TrainerSkillInfoScreenHandler::handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen) {
	//Get conversation session.
	Reference<TrainerConversationSession*> session = conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION).castTo<TrainerConversationSession* >();
	if (session == NULL) {
		nextScreenId = TrainerScreenHandlers::ERRORSCREENHANDLERID;
		return NULL;
	}

	//Check if the player selected a skill, back or end conversation.
	if (selectedOption < session->getNextSkillsCount()) {
		//Skill selected, get correct skill name from the session.
		StringIdChatParameter dialogText("@skl_d:" + session->getNextSkill(selectedOption));
		conversationScreen->setDialogText(dialogText);
	} else if (selectedOption == session->getNextSkillsCount()) {
		//Back selected.
		nextScreenId = TrainerScreenHandlers::INFOSCREENHANDLERID;
		conversationScreen = NULL;
	} else {
		//End conversation.
		nextScreenId = TrainerScreenHandlers::NONEXISTINGSCREENHANDLERID;
		conversationScreen = NULL;
	}

	return conversationScreen;
}

ConversationScreen* TrainerCanLearnSkillScreenHandler::handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen) {
	//Get conversation session.
	Reference<TrainerConversationSession*> session = conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION).castTo<TrainerConversationSession* >();
	if (session == NULL) {
		nextScreenId = TrainerScreenHandlers::ERRORSCREENHANDLERID;
		return NULL;
	}

	//Check if the player selected a skill, back or end conversation.
	if (selectedOption < session->getTrainableSkillsCount()) {
		//Skill selected.
		Skill* trainingSkill = SkillManager::instance()->getSkill(session->getTrainableSkills(selectedOption));
		if (trainingSkill != NULL) {
			StringIdChatParameter optionText("@skill_teacher:prose_cost");
			optionText.setDI(trainingSkill->getMoneyRequired());
			optionText.setTO("@skl_n:" + trainingSkill->getSkillName());
			conversationScreen->setDialogText(optionText);
			//Store selected skill in player session for next screen.
			session->setSelectedSkill(trainingSkill->getSkillName());
		} else {
			//Error.
			nextScreenId = TrainerScreenHandlers::ERRORSCREENHANDLERID;
			conversationScreen = NULL;
		}
	} else if (selectedOption == session->getTrainableSkillsCount()) {
		//Back selected.
		nextScreenId = TrainerScreenHandlers::INFOSCREENHANDLERID;
		conversationScreen = NULL;
	} else {
		//End conversation.
		nextScreenId = TrainerScreenHandlers::NONEXISTINGSCREENHANDLERID;
		conversationScreen = NULL;
	}

	return conversationScreen;
}

ConversationScreen* TrainerTrainSkillScreenHandler::handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen) {
	ManagedReference<PlayerObject* > ghost = conversingPlayer->getPlayerObject();

	//Skill previously stored in player session.
	Reference<TrainerConversationSession*> session = conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION).castTo<TrainerConversationSession* >();
	if (session == NULL) {
		nextScreenId = TrainerScreenHandlers::ERRORSCREENHANDLERID;
		return NULL;
	}
	Skill* skill = SkillManager::instance()->getSkill(session->getSelectedSkill());

	//Lock player
	Locker _lock(conversingPlayer);

	bool canLearnSkill = false;
	bool enoughCredits = false;
	bool playerLacksSkillPoints = false;

	//Verify that player can train skill.
	if (SkillManager::instance()->canLearnSkill(skill->getSkillName(), conversingPlayer, false)) {
		canLearnSkill = true;
	} else {
		//Check if the player lacks skill points.
		playerLacksSkillPoints = SkillManager::instance()->fullfillsSkillPrerequisitesAndXp(skill->getSkillName(), conversingPlayer);
	}
	// Verify that the player has enough credits.
	if (conversingPlayer->getCashCredits() + conversingPlayer->getBankCredits() >= skill->getMoneyRequired()) {
		enoughCredits = true;
	}

	if (canLearnSkill && enoughCredits) {
		//Train skill.

		//Withdraw money from player.
		int skillCost = skill->getMoneyRequired();
		if (skillCost <= conversingPlayer->getCashCredits()) {
			conversingPlayer->subtractCashCredits(skillCost);
		} else {
			skillCost -= conversingPlayer->getCashCredits();
			conversingPlayer->subtractCashCredits(conversingPlayer->getCashCredits());
			conversingPlayer->subtractBankCredits(skillCost);
		}

		//Award skill.
		SkillManager::instance()->awardSkill(skill->getSkillName(), conversingPlayer, true, false, false);

		//Send message to client
		StringIdChatParameter systemMessageCredits("@skill_teacher:prose_pay");
		systemMessageCredits.setDI(skill->getMoneyRequired());
		systemMessageCredits.setTO("@skl_n:" + skill->getSkillName());
		conversingPlayer->sendSystemMessage(systemMessageCredits);
		StringIdChatParameter systemMessageSkillLearned("@skill_teacher:prose_skill_learned");
		systemMessageSkillLearned.setTO("@skl_n:" + skill->getSkillName());
		conversingPlayer->sendSystemMessage(systemMessageSkillLearned);

		//Return correct conversation screen.
		if (skill->getSkillName() == session->getMasterSkill()) {
			//Mastered profession.
			nextScreenId = TrainerScreenHandlers::TRAINEDMASTERSCREENHANDLERID;
			conversationScreen = NULL;
		}

	} else {
		//Return screen depending on what failed.
		if (!enoughCredits) {
			nextScreenId = TrainerScreenHandlers::NOTENOUGHCREDITSSCREENHANDLERID;
			conversationScreen = NULL;
		} else if (playerLacksSkillPoints) {
			nextScreenId = TrainerScreenHandlers::NOTENOUGHSKILLPOINTSSCREENHANDLERID;
			conversationScreen = NULL;
		} else {
			nextScreenId = TrainerScreenHandlers::ERRORSCREENHANDLERID;
			conversationScreen = NULL;
		}
	}

	return conversationScreen;
}

ConversationScreen* TrainerNotEnoughCreditsScreenHandler::handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen) {
	//Skill previously stored in player session.
	Reference<TrainerConversationSession*> session = conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION).castTo<TrainerConversationSession* >();
	if (session == NULL) {
		nextScreenId = TrainerScreenHandlers::ERRORSCREENHANDLERID;
		return NULL;
	}
	Skill* skill = SkillManager::instance()->getSkill(session->getSelectedSkill());

	if (skill != NULL) {
		StringIdChatParameter* dialogText = conversationScreen->getDialogText();
		dialogText->setDI(skill->getMoneyRequired());
		dialogText->setTO("@skl_n:" + skill->getSkillName());
	} else {
		nextScreenId = TrainerScreenHandlers::ERRORSCREENHANDLERID;
		conversationScreen = NULL;
	}

	return conversationScreen;
}

ConversationScreen* TrainerNotEnoughSkillPointsScreenHandler::handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen) {
	//Skill previously stored in player session.
	Reference<TrainerConversationSession*> session = conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION).castTo<TrainerConversationSession* >();
	if (session == NULL) {
		nextScreenId = TrainerScreenHandlers::ERRORSCREENHANDLERID;
		return NULL;
	}

	Skill* skill = SkillManager::instance()->getSkill(session->getSelectedSkill());

	if (skill != NULL) {
		StringIdChatParameter* dialogText = conversationScreen->getDialogText();
		dialogText->setDI(skill->getSkillPointsRequired());
		dialogText->setTO("@skl_n:" + skill->getSkillName());
		conversationScreen->setDialogText(*dialogText);
	} else {
		nextScreenId = TrainerScreenHandlers::ERRORSCREENHANDLERID;
		conversationScreen = NULL;
	}

	return conversationScreen;
}

ConversationScreen* TrainerTrainedMasterScreenHandler::handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen) {
	String name;
	//Add a space between first and last name only if both names are used.
	if (conversingPlayer->getFirstName() != "" && conversingPlayer->getLastName() != "") {
		name = conversingPlayer->getFirstName() + " " + conversingPlayer->getLastName();
	} else {
		name = conversingPlayer->getFirstName() + conversingPlayer->getLastName();
	}
	StringIdChatParameter* dialogText = conversationScreen->getDialogText();
	dialogText->setTT(name);

	return conversationScreen;
}

