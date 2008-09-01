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

#include "TrainerCreatureImplementation.h"
#include "TrainerCreature.h"

#include "../CreatureImplementation.h"
#include "../../player/Player.h"

#include "../../player/professions/Profession.h"

#include "../../../managers/player/ProfessionManager.h"

#include "../../../packets.h"

#include "../../../../ServerCore.h"

TrainerCreatureImplementation::TrainerCreatureImplementation(uint64 oid, Profession* prof) : TrainerCreatureServant(oid) {
	profession = prof;
	setType(CreatureImplementation::TRAINER);

	creatureBitmask = 0x108;
	pvpStatusBitmask = 0;

	stringstream loggingname;
	loggingname << "Trainer = 0x" << oid;
	setLoggingName(loggingname.str());
	
	setLogging(false);
	setGlobalLogging(true);
}

TrainerCreatureImplementation::~TrainerCreatureImplementation() {
}

bool TrainerCreatureImplementation::train(SkillBox* skillBox, Player* player) {
	return player->trainSkillBox(skillBox->getName());
}

void TrainerCreatureImplementation::sendConversationStartTo(SceneObject* obj) {
	Player* player = (Player*)obj;
	
	StartNpcConversation* conv = new StartNpcConversation(player, objectID, "");
	player->sendMessage(conv);
	
	unicode mes1 = "Please select the box you want to learn";
	NpcConversationMessage* m1 = new NpcConversationMessage(player, mes1);
	player->sendMessage(m1);
	
	sendSkillBoxes(player);
}

void TrainerCreatureImplementation::sendSkillBoxes(Player* player) {
	StringList* slist = new StringList(player);
	Vector<SkillBox*>* skillBoxes = profession->getSkillBoxes();
	
	for (int i = 0; i < skillBoxes->size(); i++) {
		SkillBox* skillBox = skillBoxes->get(i);
		slist->insertOption("skl_n", skillBox->getName());
	}
	
	player->sendMessage(slist);
}

void TrainerCreatureImplementation::selectConversationOption(int option, SceneObject* obj) {
	if (!obj->isPlayer())
		return;
		
	Player* player = (Player*)obj;
	
	Vector<SkillBox*>* skillBoxes = profession->getSkillBoxes();
	
	SkillBox* sBox = skillBoxes->get(option);
	if (sBox == NULL)
		return;
		
	stringstream test;
	test << "Trying to train " << sBox->getName();
	player->sendSystemMessage(test.str());
	
	if (train(sBox, player))
		player->sendSystemMessage("SkillBox trained");
	else
		player->sendSystemMessage("You lack the requisites to train this SkillBox");
		
	sendSkillBoxes(player);
}
