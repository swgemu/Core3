/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "TrainerScreenHandlers.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/objects/player/sessions/TrainerConversationSession.h"

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
	TrainerConversationSession* session = cast<TrainerConversationSession* >(conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION));
	if (session == NULL) {
		nextScreenId = TrainerScreenHandlers::ERRORSCREENHANDLERID;
		return NULL;
	}

	String masterSkill = conversationScreen->getOptionLink(0);
	session->setMasterSkill(masterSkill);

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

	TrainerConversationSession* session = cast<TrainerConversationSession* >(conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION));
	if (session == NULL) {
		nextScreenId = TrainerScreenHandlers::ERRORSCREENHANDLERID;
		return NULL;
	}

	Skill* startingMasterSkill = SkillManager::instance()->getSkill(session->getMasterSkill());

	//Clear options since we will add new below.
	for (int i = 0; i < 5; ++i) {
		conversationScreen->removeOption(0);
	}

	//Get trainable skills
	getTrainableSkillsList(conversingPlayer, &trainableSkills, startingMasterSkill);
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

	TrainerConversationSession* session = cast<TrainerConversationSession* >(conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION));
	if (session == NULL) {
		nextScreenId = TrainerScreenHandlers::ERRORSCREENHANDLERID;
		return NULL;
	}

	Skill* startingMasterSkill = SkillManager::instance()->getSkill(session->getMasterSkill());

	//Clear options since we will add new below.
	for (int i = 0; i < 5; ++i) {
		conversationScreen->removeOption(0);
	}
	session->clearNextSkills();

	//Get next skills
	getNextSkillsList(conversingPlayer, &nextSkills, startingMasterSkill);

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
	TrainerConversationSession* session = cast<TrainerConversationSession* >(conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION));
	if (session == NULL) {
		nextScreenId = TrainerScreenHandlers::ERRORSCREENHANDLERID;
		return NULL;
	}

	Skill* startingMasterSkill = SkillManager::instance()->getSkill(session->getMasterSkill());

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
	TrainerConversationSession* session = cast<TrainerConversationSession* >(conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION));
	if (session == NULL) {
		nextScreenId = TrainerScreenHandlers::ERRORSCREENHANDLERID;
		return NULL;
	}

	Skill* startingMasterSkill = SkillManager::instance()->getSkill(session->getMasterSkill());

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
	TrainerConversationSession* session = cast<TrainerConversationSession* >(conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION));
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
			conversingPlayer->substractCashCredits(skillCost);
		} else {
			skillCost -= conversingPlayer->getCashCredits();
			conversingPlayer->substractCashCredits(conversingPlayer->getCashCredits());
			conversingPlayer->substractBankCredits(skillCost);
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
	TrainerConversationSession* session = cast<TrainerConversationSession* >(conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION));
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
	TrainerConversationSession* session = cast<TrainerConversationSession* >(conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION));
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

