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

#include "BlueFrogCreatureImplementation.h"
#include "BlueFrogCreature.h"

#include "../../player/professions/Profession.h"

#include "../../../managers/player/ProfessionManager.h"

#include "../../../objects.h"
#include "../../../packets.h"

#include "../../../../ServerCore.h"

#include "BlueFrogVector.h"

#include "../../../managers/item/ItemManager.h"

BlueFrogCreatureImplementation::BlueFrogCreatureImplementation(uint64 oid) : BlueFrogCreatureServant(oid) {
	setType(CreatureImplementation::TRAINER);

	optionsBitmask = 0x108;

	customName = UnicodeString("a Jawa Trader");
	templateName = "bluefrog";
	objectCRC = 1350586805;

	StringBuffer loggingname;
	loggingname << "BlueFrog = 0x" << oid;
	setLoggingName(loggingname.toString());
	setLockName(loggingname.toString());
	setLogging(false);
	setGlobalLogging(true);
}

BlueFrogCreatureImplementation::~BlueFrogCreatureImplementation() {
}

void BlueFrogCreatureImplementation::setBFType(int type) {
	switch (type) {
	case JAWA:
		customName = UnicodeString("Jawa Trader");
		objectCRC = 0x508051B5;
		break;
	case GUNGAN:
		customName = UnicodeString("Gungan Trader");
		objectCRC = 0xF1E56234;
		break;
	case MEDDROID:
		customName = UnicodeString("Medical Droid");
		objectCRC = 0x25CD1614;
		break;
	case BARTENDER:
		customName = UnicodeString("Bartender");
		objectCRC = 0x4B30B5E4;
		break;
	case EWOK:
		customName = UnicodeString("Ewok Trader");
		objectCRC = 0xC25E7435;
		break;
	case JEDI:
		customName = UnicodeString("Jedi Trader");
		objectCRC = 0x04340A7D;
		break;
	default:
		break;
	}
}

void BlueFrogCreatureImplementation::sendConversationStartTo(SceneObject* obj) {
	Player* player = (Player*)obj;

	StartNpcConversation* conv = new StartNpcConversation(player, objectID, "");
	player->sendMessage(conv);
	player->setLastNpcConvStr("blue_frog");

	sendMessage1(player);
}

void BlueFrogCreatureImplementation::sendMessage1(Player* player) {
	StringBuffer mes1;
	mes1 << "I have been sanctioned by the developers to give you certain goods and to train";
	mes1 << " you in certain skills and provide you with certain services that will help you test specific areas of development.";
	mes1 << endl << endl << "What do you need?";
	UnicodeString message = UnicodeString(mes1.toString());

	NpcConversationMessage* m1 = new NpcConversationMessage(player, message);
	player->sendMessage(m1);
	sendChoices1(player);
}
void BlueFrogCreatureImplementation::sendChoices1(Player* player) {
	StringList* slist = new StringList(player);
	UnicodeString option1 = UnicodeString("Which professions will you teach me?");
	//UnicodeString option2 = UnicodeString("I'd like to unlearn all my skills and start over.");
	UnicodeString option3 = UnicodeString("Which items can I get?");
	UnicodeString option4 = UnicodeString("I want to test wounds.");
	UnicodeString option5 = UnicodeString("I want to test states.");
	//UnicodeString option6 = UnicodeString("I want to earn some faction points.");

	slist->insertOption(option1);
	//slist->insertOption(option2);
	slist->insertOption(option3);
	slist->insertOption(option4);
	slist->insertOption(option5);
	//slist->insertOption(option6);

	player->setLastNpcConvMessStr("blue_frog_m1");
	player->sendMessage(slist);
}

void BlueFrogCreatureImplementation::sendSelectProfessionMessage(Player * player) {
	StringBuffer mes1;
	mes1 << "I can train you in the following professions...";
	UnicodeString message = UnicodeString(mes1.toString());

	NpcConversationMessage* m1 = new NpcConversationMessage(player, message);
	player->sendMessage(m1);

	sendProfessionChoices(player);
}

void BlueFrogCreatureImplementation::sendProfessionChoices(Player* player) {
	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();

	StringList* slist = new StringList(player);

	String messStr = player->getLastNpcConvMessStr();
	String group = messStr.subString(15, messStr.length());

	BlueFrogVector * bfVector = itemManager->getBFProfList(group);
	for (int i = 0; i < bfVector->size(); i++) {
		UnicodeString option = UnicodeString(bfVector->get(i));
		slist->insertOption(option);
	}

	UnicodeString restart = UnicodeString("Can we start over?");

	slist->insertOption(restart);

	player->sendMessage(slist);

	bfVector->finalize();
}

void BlueFrogCreatureImplementation::sendSelectItemMessage(Player * player) {
	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();

	SuiListBox* sui = new SuiListBox(player, SuiWindowType::BLUE_FROG_ITEM_REQUEST);
	sui->setPromptTitle("Blue Frog Items");
	sui->setPromptText("You can have any of the following item sets.");
	sui->setCancelButton(true);

	BlueFrogVector * bfVector = itemManager->getBFItemList();
	for (int i = 0; i < bfVector->size(); i++) {
		sui->addMenuItem(bfVector->get(i));
	}

	player->addSuiBox(sui);
	player->sendMessage(sui->generateMessage());
}

void BlueFrogCreatureImplementation::sendWoundTerminalMessage(Player * player) {
	SuiListBox* sui = new SuiListBox(player, SuiWindowType::WOUND_TERMINAL_REQUEST);
	sui->setPromptTitle("@wound_terminal:beta_terminal_wound");
	sui->setPromptText("Each selection will cause 500 wound damage.");
	sui->setCancelButton(true);

	sui->addMenuItem("@wound_terminal:inflict_wound_health");
	sui->addMenuItem("@wound_terminal:inflict_wound_strength");
	sui->addMenuItem("@wound_terminal:inflict_wound_constitution");
	sui->addMenuItem("@wound_terminal:inflict_wound_action");
	sui->addMenuItem("@wound_terminal:inflict_wound_quickness");
	sui->addMenuItem("@wound_terminal:inflict_wound_stamina");
	sui->addMenuItem("@wound_terminal:inflict_wound_mind");
	sui->addMenuItem("@wound_terminal:inflict_wound_focus");
	sui->addMenuItem("@wound_terminal:inflict_wound_willpower");

	player->addSuiBox(sui);
	player->sendMessage(sui->generateMessage());
}

void BlueFrogCreatureImplementation::sendStateTerminalMessage(Player * player) {
	SuiListBox* sui = new SuiListBox(player, SuiWindowType::STATE_TERMINAL_REQUEST);
	sui->setPromptTitle("State Terminal");
	sui->setPromptText("Each selection will cause a state.  Use curepacks or statepacks to heal them.");
	sui->setCancelButton(true);

	sui->addMenuItem("Test Fire State.");
	sui->addMenuItem("Test Disease State");
	sui->addMenuItem("Test Poison State");
	sui->addMenuItem("Test Dizzied State.");
	sui->addMenuItem("Test Blinded State");
	sui->addMenuItem("Test Intimidated State");
	sui->addMenuItem("Test Stunned State");

	player->addSuiBox(sui);
	player->sendMessage(sui->generateMessage());
}

void BlueFrogCreatureImplementation::sendFactionPointTerminalMessage(Player * player) {
	StringBuffer mes1;
	mes1 << "Which Faction would you like to earn points for?";
	UnicodeString message = UnicodeString(mes1.toString());

	NpcConversationMessage* m1 = new NpcConversationMessage(player, message);
	player->sendMessage(m1);

	UnicodeString option1 = UnicodeString("The Empire");
	UnicodeString option2 = UnicodeString("The Rebellion");
	UnicodeString restart = UnicodeString("I'd like to start over.");

	StringList* slist = new StringList(player);
	slist->insertOption(option1);
	slist->insertOption(option2);
	slist->insertOption(restart);

	player->sendMessage(slist);
}

void BlueFrogCreatureImplementation::selectConversationOption(int option, SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*)obj;

	if (player->getLastNpcConvStr() != "blue_frog")
		return;

	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();

	String lastMessage = player->getLastNpcConvMessStr();

	if (lastMessage == "blue_frog_m1") {
		switch(option) {
		case 0:
			player->setLastNpcConvMessStr("blue_frog_prof_root");
			sendSelectProfessionMessage(player);
			break;
	/*	case 1:
			dropSkills(player);
			player->sendSystemMessage("You have unlearned all your skills...");
			sendMessage1(player);
			break; */
		case 1:
			sendSelectItemMessage(player);
			sendMessage1(player);
			break;
		case 2:
			sendWoundTerminalMessage(player);
			sendMessage1(player);
			break;
		case 3:
			sendStateTerminalMessage(player);
			sendMessage1(player);
			break;
	/*	case 4:
			player->setLastNpcConvMessStr("blue_frog_fp");
			sendFactionPointTerminalMessage(player);
			break; */
		}
	} else if (lastMessage.indexOf("blue_frog_fp") != -1) {
		switch (option) {
		case 0:
			player->addFactionPoints("imperial", 500);
			player->subtractFactionPoints("rebel", 500);
			sendMessage1(player);
			break;
		case 1:
			player->addFactionPoints("rebel", 500);
			player->subtractFactionPoints("imperial", 500);
			sendMessage1(player);
			break;
		case 2:
			sendMessage1(player);
		}
	} else if (lastMessage.indexOf("blue_frog_prof") != -1) {
		String group = lastMessage.subString(15, lastMessage.length());
		BlueFrogVector* bfVector = itemManager->getBFProfList(group);

		if (option < bfVector->size()) {
			String key = bfVector->get(option);
			String prof = itemManager->getBFProf(key);

			if (prof.isEmpty()) {
				StringBuffer ss;
				ss << "blue_frog_prof_" << key;
				player->setLastNpcConvMessStr(ss.toString());

				sendSelectProfessionMessage(player);

				bfVector->finalize();
				return;
			}

			player->sendSystemMessage("Attempting to train you as a " + key + "...");

			if (trainProfession(player, prof)) {
				player->sendSystemMessage("You now are a " + key);
			} else {
				player->sendSystemMessage("You could not be trained as a " + key);
			}

			player->setLastNpcConvMessStr("blue_frog_prof_root");
			sendSelectProfessionMessage(player);
		} else {
			sendMessage1(player);
		}

		bfVector->finalize();
	}
}

bool BlueFrogCreatureImplementation::trainProfession(Player * player, String prof) {
	if (player->hasSkillBox(prof))
		return false;

	ProfessionManager * professionManager = server->getProfessionManager();
	SkillBox * skill = professionManager->getSkillBox(prof);

	if (skill == NULL)
		return false;

	bool ret = trainSkill(player, skill);

	player->sendTo(player);

	return ret;
}

bool BlueFrogCreatureImplementation::trainSkill(Player * player, SkillBox * skill) {

	for (int i = 0; i < skill->getRequiredSkillsSize(); i++) {
		SkillBox * sbox = skill->getRequiredSkill(i);

		if (!player->hasSkillBox(sbox->getName())) {

			if (!trainSkill(player, sbox))
				return false;
		}

	}

	bool res = player->trainSkillBox(skill->getName(), false);
	return res;
}

void BlueFrogCreatureImplementation::dropSkills(Player * player) {
	//TODO: Add ability to drop all skills
}
