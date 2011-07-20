/*
 * TrainerCreatureImplementation.cpp
 *
 *  Created on: 26/05/2010
 *      Author: victor
 */

#include "TrainerCreature.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/StartNpcConversation.h"
#include "server/zone/packets/object/StringList.h"
#include "server/zone/packets/object/StopNpcConversation.h"
#include "server/zone/packets/object/NpcConversationMessage.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/creature/professions/SkillBox.h"
#include "server/chat/StringIdChatParameter.h"

void TrainerCreatureImplementation::sendConversationStartTo(SceneObject* obj) {
	if (!obj->isPlayerCreature() || profession == NULL)
		return;

	CreatureObject* player = (CreatureObject*) obj;
	PlayerObject* ghost = player->getPlayerObject();

	String stffile = "skill_teacher";

	StartNpcConversation* conv = new StartNpcConversation(player, getObjectID(), "");
	player->sendMessage(conv);
	ghost->setLastNpcConvStr(getObjectNameStringIdName());

	bool qual = true;

	SkillBox* sBox = profession->getNoviceBox();

	ghost->setLastNpcConvMessStr("");

	for (int i = 0; (qual == true) && (i < sBox->getRequiredSkillsSize()); i++) {
		String skillname;
		sBox->getRequiredSkill(skillname, i);

		if (!player->hasSkillBox(skillname)) {
			qual = false;
		}
	}

	if (!qual) {
		StringIdChatParameter params(stffile, "no_qualify");
		NpcConversationMessage* fail = new NpcConversationMessage(player, params);
		player->sendMessage(fail);

		ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::TEACH_DENY);

		suiBox->setPromptTitle("@skill_teacher:no_qualify_title");
		suiBox->setPromptText("@skill_teacher:no_qualify_prompt");

		for (int j = 0; j < sBox->getRequiredSkillsSize(); j++) {
			StringBuffer skillboxname;
			skillboxname << "@skl_n:" << sBox->getRequiredSkill(j)->getName();

			suiBox->addMenuItem(skillboxname.toString());
		}

		player->getPlayerObject()->addSuiBox(suiBox);
		player->sendMessage(suiBox->generateMessage());
		ghost->setConversatingCreature(NULL);
		player->sendMessage(new StringList(player));
		player->sendMessage(new StopNpcConversation(player, getObjectID()));

	} else if (qual) {
		sendInitialMessage(player);
	}

}


void TrainerCreatureImplementation::sendInitialMessage(CreatureObject* player) {
	String stffile = "skill_teacher";
	String stfname = getObjectNameStringIdName();

	StringIdChatParameter params(stffile, stfname);
	NpcConversationMessage* m1 = new NpcConversationMessage(player, params);
	player->sendMessage(m1);

	PlayerObject* ghost = player->getPlayerObject();

	ghost->setLastNpcConvMessStr("trainer_initial");
	sendInitialChoices(player);
}


void TrainerCreatureImplementation::sendInitialChoices(CreatureObject* player) {
	StringList* slist = new StringList(player);

	slist->insertOption("skill_teacher", "opt1_1");
	slist->insertOption("skill_teacher", "opt1_2");
	//slist->insertOption("skill_teacher", "opt1_3");
	//slist->insertOption("skill_teacher", "opt1_4");

	PlayerObject* ghost = player->getPlayerObject();
	ghost->setLastNpcConvMessStr("trainer_initial");

	player->sendMessage(slist);
}

void TrainerCreatureImplementation::sendSkillBoxes(CreatureObject* player, bool checkXp) {
	StringList* slist = new StringList(player);
	Vector<SkillBox*>* skillBoxes;
	String stffile = "skill_teacher";

	skillBoxes = profession->getSkillBoxes();

	String option;
	int known = 0;

	PlayerObject* ghost = player->getPlayerObject();
	ghost->clearLastNpcConvOptions();

	PlayerObject* playerObject = (PlayerObject*) player->getSlottedObject("ghost");

	for (int i = 0; i < skillBoxes->size(); i++) {
		SkillBox* skillBox = skillBoxes->get(i);
		bool qual = true;

		if (player->hasSkillBox(skillBox->getName())) {
			known++;
			qual = false;
		}

		if (checkXp && (skillBox->getSkillXpCost() > playerObject->getExperience(skillBox->getSkillXpType())))
			qual = false;

		for (int j = 0; (qual == true) && (j < skillBox->getRequiredSkillsSize()); j++) {
			String skillname;
			skillBox->getRequiredSkill(skillname, j);

			if (!player->hasSkillBox(skillname))
				qual = false;
		}

		if (qual) {
			slist->insertOption("skl_n", skillBox->getName());
			ghost->addLastNpcConvOptions(skillBox->getName());
		}
	}

	if (checkXp)
		ghost->setLastNpcConvMessStr("trainer_canlearn");
	else
		ghost->setLastNpcConvMessStr("trainer_nextskills");

	if (slist->getOptionCount() > 0)
		if (checkXp)
			option = "msg2_1";
		else
			option = "msg2_2";
	else if (known == skillBoxes->size())
		option = "msg3_1";
	else
		option = "error_empty_category";

	StringIdChatParameter params(stffile, option);
	NpcConversationMessage* m2 = new NpcConversationMessage(player, params);
	player->sendMessage(m2);

	slist->insertOption("skill_teacher", "back");
	ghost->addLastNpcConvOptions(String("back"));
	player->sendMessage(slist);
}

void TrainerCreatureImplementation::sendSkillBoxList(CreatureObject* player, bool checkLearned) {
	StringList* slist = new StringList(player);
	Vector<SkillBox*>* skillBoxes;

	String stffile = "skill_teacher";

	skillBoxes = profession->getSkillBoxes();

	PlayerObject* ghost = player->getPlayerObject();

	for (int i = 0; i < skillBoxes->size(); i++) {
		SkillBox *skillBox = skillBoxes->get(i);

		if (checkLearned && player->hasSkillBox(skillBox->getName()))
			continue;

		slist->insertOption("skl_n", skillBox->getName());
		ghost->addLastNpcConvOptions(skillBox->getName());
	}

	String option;
	if (checkLearned) {
		option = "msg2_3";
		ghost->setLastNpcConvMessStr("trainer_unlearned");
	} else {
		option = "msg2_4";
		ghost->setLastNpcConvMessStr("trainer_allskills");
	}

	StringIdChatParameter params(stffile, option);
	NpcConversationMessage* m3 = new NpcConversationMessage(player, params);
	slist->insertOption("skill_teacher", "back");
	ghost->addLastNpcConvOptions(String("back"));
	player->sendMessage(slist);
}

void TrainerCreatureImplementation::sendConfirmation(CreatureObject* player) {
	StringList* slist = new StringList(player);

	slist->insertOption("skill_teacher", "yes");
	slist->insertOption("skill_teacher", "no");

	player->sendMessage(slist);
}

void TrainerCreatureImplementation::selectConversationOption(int option, SceneObject* obj) {
	if (!obj->isPlayerCreature())
		return;

	CreatureObject* player = (CreatureObject*) obj;
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost->getLastNpcConvStr() != getObjectNameStringIdName())
		return;

	String stffile = "skill_teacher";

	Vector<SkillBox*>* skillBoxes;

	bool deleteSkills = false;
	skillBoxes = profession->getSkillBoxes();

	String choice;

	if (ghost->countLastNpcConvOptions() > 0) {
		if (ghost->getLastNpcConvMessStr() == "trainer_learn")
			choice = ghost->getLastNpcConvOption(0);
		else if (ghost->countLastNpcConvOptions() > (uint32)option)
			choice = ghost->getLastNpcConvOption(option);
	}

	ghost->clearLastNpcConvOptions();

	if (ghost->getLastNpcConvMessStr() == "trainer_initial" ||
			ghost->getLastNpcConvMessStr() == "jedi_trainer_initial") {
		switch (option) {
		case 0:
			sendSkillBoxes(player, true);
			break;
		case 1:
			sendSkillBoxes(player, false);
			break;
		case 2:
			sendSkillBoxList(player, true);
			break;
		case 3:
			sendSkillBoxList(player, false);
			break;
		default:
			break;
		};

	} else if (ghost->getLastNpcConvMessStr() == "trainer_canlearn") {
		if (choice == "back") {
			sendInitialMessage(player);
		} else {
			StringIdChatParameter params(stffile, "confirm");
			NpcConversationMessage* skillmsg = new NpcConversationMessage(player, params);
			ghost->setLastNpcConvMessStr("trainer_learn");
			ghost->addLastNpcConvOptions(choice);
			player->sendMessage(skillmsg);
			sendConfirmation(player);
		}
	} else if (ghost->getLastNpcConvMessStr() == "trainer_nextskills") {
		if (choice == "back") {
			sendInitialMessage(player);
		} else {
			StringIdChatParameter params("skl_d", choice);
			NpcConversationMessage* skillmsg = new NpcConversationMessage(player, params);
			player->sendMessage(skillmsg);
			sendSkillBoxes(player, false);
		}
	} else if (ghost->getLastNpcConvMessStr() == "trainer_unlearned") {
		if (choice == "back") {
			sendInitialMessage(player);
		} else {
			StringIdChatParameter params("skl_d", choice);
			NpcConversationMessage* skillmsg = new NpcConversationMessage(player, params);
			player->sendMessage(skillmsg);
			sendSkillBoxList(player, true);
		}
	} else if (ghost->getLastNpcConvMessStr() == "trainer_allskills") {
		if (choice == "back") {
			sendInitialMessage(player);
		} else {
			StringIdChatParameter params("skl_d", choice);
			NpcConversationMessage* skillmsg = new NpcConversationMessage(player, params);
			player->sendMessage(skillmsg);
			sendSkillBoxList(player, false);
		}
	} else if (ghost->getLastNpcConvMessStr() == "trainer_learn") {
		SkillBox* sBox = NULL;
		String optionmessage;
		int money, sp;

		switch (option) {
		case 0: {
			StringIdChatParameter params;
			params.setTO("skl_n", choice);

			for (int i = 0; i < skillBoxes->size(); i++) {
				if (skillBoxes->get(i)->getName() == choice) {
					sBox = skillBoxes->get(i);
					break;
				}
			}

			if (sBox != NULL) {
				money = sBox->getSkillMoneyRequired();
				sp = sBox->getSkillPointsRequired();

				PlayerObject* playerObject = (PlayerObject*) player->getSlottedObject("ghost");

				if (sBox->getSkillXpCost() > playerObject->getExperience(sBox->getSkillXpType())) {
					params.setStringId(stffile, "prose_train_failed");
					player->sendSystemMessage(params);
				} else if ((ghost->getSkillPoints() + sBox->getSkillPointsRequired()) > 250) {
					params.setDI(sp);
					if (ghost->getSkillPoints() != 250) {
						params.setStringId(stffile, "nsf_skill_points");
						player->sendSystemMessage(params);
					} else
						player->sendSystemMessage(stffile, "no_skill_points");
				} else if (!player->verifyCashCredits(money)) {
					params.setDI(money);
					params.setStringId(stffile, "prose_nsf");
					player->sendSystemMessage(params);
				} else {
					params.setDI(money);

					bool res = ProfessionManager::instance()->trainSkillBox(sBox, player, true);

					if (res == true) {
						playerObject->addExperience(sBox->getSkillXpType(), (-1) * sBox->getSkillXpCost(), true);
						player->substractCashCredits(money);
						params.setStringId(stffile, "prose_pay");
						player->sendSystemMessage(params);
						params.setStringId(stffile, "prose_skill_learned");
					}
				}
			}
			optionmessage = "msg_yes";
			break;
		}
		case 1: //no
			optionmessage = "msg_no";
			break;
		default:
			break;
		};

		StringIdChatParameter params(stffile, optionmessage);
		NpcConversationMessage* skillmsg = new NpcConversationMessage(player, params);
		player->sendMessage(skillmsg);
		sendInitialChoices(player);
	} else
		player->sendMessage(new StopNpcConversation(player, getObjectID()));

	if (deleteSkills)
		delete skillBoxes;
}


/*
void TrainerCreatureImplementation::getMapLocation(GetMapLocationsResponseMessage* gmlr) {
	uint8 type2 = 0;

	if (profession->getName() == "combat_brawler")
		type2 = 20;

	if (profession->getName() == "crafting_artisan")
		type2 = 21;

	if (profession->getName() == "outdoors_scout")
		type2 = 22;

	if (profession->getName() == "combat_marksman")
		type2 = 23;

	if (profession->getName() == "social_entertainer")
		type2 = 24;

	if (profession->getName() == "science_medic")
		type2 = 25;

	if (type2 == 0)
		return;

	float x = positionX;
	float y = positionY;

	gmlr->addMapLocation(objectID, customName, x, y, 19, type2, 0);
}
*/
