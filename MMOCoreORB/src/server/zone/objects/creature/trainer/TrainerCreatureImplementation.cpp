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


#include "../../player/professions/Profession.h"

#include "../../../managers/player/ProfessionManager.h"

#include "../../../objects.h"
#include "../../../packets.h"

#include "../../../../ServerCore.h"

TrainerCreatureImplementation::TrainerCreatureImplementation(uint64 oid, Profession* prof) : TrainerCreatureServant(oid) {
	profession = prof;
	setType(CreatureImplementation::TRAINER);

	creatureBitmask = 0x108;
	pvpStatusBitmask = 0;

	StringBuffer loggingname;
	loggingname << "Trainer = 0x" << oid;
	setLoggingName(loggingname.toString());

	setLogging(false);
	setGlobalLogging(true);
}

TrainerCreatureImplementation::~TrainerCreatureImplementation() {
}

bool TrainerCreatureImplementation::train(SkillBox* skillBox, Player* player) {
	return player->trainSkillBox(skillBox->getName());
}

void TrainerCreatureImplementation::sendConversationStartTo(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*)obj;

	StartNpcConversation* conv = new StartNpcConversation(player, objectID, "");
	player->sendMessage(conv);
	player->setLastNpcConvStr(getSpeciesName());

	bool qual = true;

	SkillBox* sBox = profession->getNoviceBox();

	player->setLastNpcConvMessStr("");

	for (int i = 0; (qual == true) && (i < sBox->getRequiredSkillsSize()); i++) {
		String skillname;
		sBox->getRequiredSkill(skillname, i);
		if(!player->hasSkillBox(skillname))
			qual = false;
	}

	if (!qual) {
		NpcConversationMessage *fail = new NpcConversationMessage(player, "skill_teacher", "no_qualify");
		player->sendMessage(fail);
		SuiListBox* suiBox = new SuiListBox(player, SuiWindowType::DENY_TRAINING_LIST);
		suiBox->setPromptTitle("@skill_teacher:no_qualify_title");
		suiBox->setPromptText("@skill_teacher:no_qualify_prompt");
		for (int j = 0; j < sBox->getRequiredSkillsSize(); j++) {
			StringBuffer skillboxname;
			skillboxname << "@skl_n:" << sBox->getRequiredSkill(j)->getName();

			suiBox->addMenuItem(skillboxname.toString());
		}

		player->addSuiBox(suiBox);
		player->sendMessage(suiBox->generateMessage());
		player->setConversatingCreature(NULL);
		player->sendMessage(new StringList(player));
		player->sendMessage(new StopNpcConversation(player, getObjectID()));

	} else if (qual) {
		sendInitialMessage(player);
	}
}

void TrainerCreatureImplementation::sendInitialMessage(Player* player) {
	NpcConversationMessage* m1 = new NpcConversationMessage(player, "skill_teacher", getSpeciesName());
	player->sendMessage(m1);

	player->setLastNpcConvMessStr("trainer_initial");
	sendInitialChoices(player);
}

void TrainerCreatureImplementation::sendInitialChoices(Player* player) {
	StringList* slist = new StringList(player);

	slist->insertOption("skill_teacher", "opt1_1");
	slist->insertOption("skill_teacher", "opt1_2");
	//slist->insertOption("skill_teacher", "opt1_3");
	//slist->insertOption("skill_teacher", "opt1_4");

	player->setLastNpcConvMessStr("trainer_initial");

	player->sendMessage(slist);
}

void TrainerCreatureImplementation::sendSkillBoxes(Player* player, bool checkXp) {
	StringList* slist = new StringList(player);
	Vector<SkillBox*>* skillBoxes = profession->getSkillBoxes();
	String option;
	int known = 0;

	player->clearLastNpcConvOptions();

	for (int i = 0; i < skillBoxes->size(); i++) {
		SkillBox* skillBox = skillBoxes->get(i);
		bool qual = true;

		if (player->hasSkillBox(skillBox->getName())) {
			known++;
			qual = false;
		}

		if (checkXp && (skillBox->getSkillXpCost() > player->getXp(skillBox->getSkillXpType())))
			qual = false;

		for (int j = 0; (qual == true) && (j < skillBox->getRequiredSkillsSize()); j++) {
			String skillname;
			skillBox->getRequiredSkill(skillname, j);

			if (!player->hasSkillBox(skillname))
				qual = false;
		}

		if (qual) {
			slist->insertOption("skl_n", skillBox->getName());
			player->addLastNpcConvOptions(skillBox->getName());
		}
	}

	if (checkXp)
		player->setLastNpcConvMessStr("trainer_canlearn");
	else
		player->setLastNpcConvMessStr("trainer_nextskills");

	if (slist->getOptionCount() > 0)
		if (checkXp)
			option = "msg2_1";
		else
			option = "msg2_2";
	else if (known == skillBoxes->size())
		option = "msg3_1";
	else
		option = "error_empty_category";

	NpcConversationMessage* m2 = new NpcConversationMessage(player, "skill_teacher", option);
	player->sendMessage(m2);

	slist->insertOption("skill_teacher","back");
	player->addLastNpcConvOptions(String("back"));
	player->sendMessage(slist);
}

void TrainerCreatureImplementation::sendSkillBoxList(Player* player, bool checkLearned) {
	StringList* slist = new StringList(player);
	Vector<SkillBox*>* skillBoxes = profession->getSkillBoxes();

	for (int i = 0; i < skillBoxes->size(); i++) {
		SkillBox *skillBox = skillBoxes->get(i);
		if (checkLearned && player->hasSkillBox(skillBox->getName()))
			continue;
		slist->insertOption("skl_n", skillBox->getName());
		player->addLastNpcConvOptions(skillBox->getName());
	}

	String option;
	if (checkLearned) {
		option = "msg2_3";
		player->setLastNpcConvMessStr("trainer_unlearned");
	} else {
		option = "msg2_4";
		player->setLastNpcConvMessStr("trainer_allskills");
	}

	NpcConversationMessage* m3 = new NpcConversationMessage(player, "skill_teacher", option);
	slist->insertOption("skill_teacher","back");
	player->addLastNpcConvOptions(String("back"));
	player->sendMessage(slist);
}

void TrainerCreatureImplementation::sendConfirmation(Player* player) {
	StringList* slist = new StringList(player);

	slist->insertOption("skill_teacher", "yes");
	slist->insertOption("skill_teacher", "no");

	player->sendMessage(slist);
}

void TrainerCreatureImplementation::selectConversationOption(int option, SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*)obj;

	if (player->getLastNpcConvStr() != getSpeciesName())
		return;

	Vector<SkillBox*>* skillBoxes = profession->getSkillBoxes();

	String choice;
	if (player->countLastNpcConvOptions() > 0) {
		if (player->getLastNpcConvMessStr() == "trainer_learn")
			choice = player->getLastNpcConvOption(0);
		else
			choice = player->getLastNpcConvOption(option);
	}
	player->clearLastNpcConvOptions();

	if (player->getLastNpcConvMessStr() == "trainer_initial") {
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

	} else if (player->getLastNpcConvMessStr() == "trainer_canlearn") {
		if (choice == "back") {
			sendInitialMessage(player);
		} else {
			NpcConversationMessage* skillmsg = new NpcConversationMessage(player, "skill_teacher", "confirm");
			player->setLastNpcConvMessStr("trainer_learn");
			player->addLastNpcConvOptions(choice);
			player->sendMessage(skillmsg);
			sendConfirmation(player);
		}
	} else if (player->getLastNpcConvMessStr() == "trainer_nextskills") {
		if (choice == "back") {
			sendInitialMessage(player);
		} else {
			NpcConversationMessage* skillmsg = new NpcConversationMessage(player, "skl_d", choice);
			player->sendMessage(skillmsg);
			sendSkillBoxes(player, false);
		}
	} else if (player->getLastNpcConvMessStr() == "trainer_unlearned") {
		if (choice == "back") {
			sendInitialMessage(player);
		} else {
			NpcConversationMessage* skillmsg = new NpcConversationMessage(player, "skl_d", choice);
			player->sendMessage(skillmsg);
			sendSkillBoxList(player, true);
		}
	} else if (player->getLastNpcConvMessStr() == "trainer_allskills") {
		if (choice == "back") {
			sendInitialMessage(player);
		} else {
			NpcConversationMessage* skillmsg = new NpcConversationMessage(player, "skl_d", choice);
			player->sendMessage(skillmsg);
			sendSkillBoxList(player, false);
		}
	} else if (player->getLastNpcConvMessStr() == "trainer_learn") {
		SkillBox* sBox;
		String optionmessage;
		StfParameter* params = new StfParameter();
		int money, sp;

		switch (option) {
		case 0: //yes
			params->addTO("skl_n", choice);
			for (int i = 0; i < skillBoxes->size(); i++) {
				if (skillBoxes->get(i)->getName() == choice) {
					sBox = skillBoxes->get(i);
					break;
				}
			}

			if (sBox->getSkillXpCost() > player->getXp(sBox->getSkillXpType())) {
				player->sendSystemMessage("skill_teacher", "prose_train_failed", params);
			} else if ((player->getSkillPoints() + sBox->getSkillPointsRequired()) > 250) {
				sp = sBox->getSkillPointsRequired();
				params->addDI(sp);
				if (player->getSkillPoints() != 250)
					player->sendSystemMessage("skill_teacher", "nsf_skill_points", params);
				else
					player->sendSystemMessage("skill_teacher", "no_skill_points");
			} else if (!verifyCashCredits((uint32)money)) {
				player->sendSystemMessage("skill_teacher", "prose_nsf", params);
			} else {
				money = sBox->getSkillMoneyRequired();
				params->addDI(money);
				train(sBox, player);
				player->addXp(sBox->getSkillXpType(), (-1)*sBox->getSkillXpCost(), true);
				player->subtractCashCredits((uint32)money);
				player->sendSystemMessage("skill_teacher", "prose_pay", params);
				player->sendSystemMessage("skill_teacher", "prose_skill_learned", params);
			}
			optionmessage = "msg_yes";
			break;
		case 1: //no
			optionmessage = "msg_no";
			break;
		default:
			break;
		};

		delete params;
		NpcConversationMessage* skillmsg = new NpcConversationMessage(player, "skill_teacher", optionmessage);
		player->sendMessage(skillmsg);
		sendInitialChoices(player);
	} else
		player->sendMessage(new StopNpcConversation(player, getObjectID()));
}
