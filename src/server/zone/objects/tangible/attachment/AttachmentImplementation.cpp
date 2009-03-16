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

#include "../../../managers/item/ItemManager.h"

#include "../TangibleObject.h"

#include "../wearables/WearableSkillMods.h"

#include "engine/engine.h"

#include "AttachmentImplementation.h"

AttachmentImplementation::AttachmentImplementation(uint64 objID, int type) :
	AttachmentServant(objID, type) {

	attachmentType = type;
	objectID = objID;

	init();
}

AttachmentImplementation::~AttachmentImplementation()
{
}

void AttachmentImplementation::init() {

	objectType = SceneObjectImplementation::TANGIBLE;

	if (attachmentType == TangibleObjectImplementation::ARMORATTACHMENT) {
		objectCRC = 0xDF144F5C;
		objectSubType = TangibleObjectImplementation::ARMORATTACHMENT;
		setOptionsBitmask(TangibleObjectImplementation::OPTIONS_YELLOW);
		attachmentType = AttachmentImplementation::ARMORATTACHMENT;
		templateName = "socket_gem_armor";
	} else {
		objectCRC = 0xC0FCFE34;
		objectSubType = TangibleObjectImplementation::CLOTHINGATTACHMENT;
		setOptionsBitmask(TangibleObjectImplementation::OPTIONS_YELLOW);
		templateName = "socket_gem_clothing";
		attachmentType = AttachmentImplementation::CLOTHINGATTACHMENT;
	}

	templateTypeName = "item_n";

	maxmods = 3;

	persistent = false;
	updated = false;
	equipped = false;
}

void AttachmentImplementation::parseItemAttributes() {

	String name = "skillMods";
	parseSkillModAttributeString(itemAttributes->getStringAttribute(name));

	name = "skillModIndex";
	parseSkillModIndexString(itemAttributes->getStringAttribute(name));

}

void AttachmentImplementation::saveSkillModIndex() {

	StringBuffer index;

	for (int i = 0; i < skillModIndex.size(); ++i) {
		index << skillModIndex.get(i) << ";";
	}

	String name = "skillModIndex";
	String value = index.toString();
	itemAttributes->setStringAttribute(name, value);
}

void AttachmentImplementation::saveSkillModAttributes() {

	StringBuffer skills;

	for (int i = 0; i < skillModMap.size(); ++i) {
		skills << skillModMap.elementAt(i)->getKey() << "="
				<< skillModMap.elementAt(i)->getValue() << ";";
	}

	String name = "skillMods";
	String value = skills.toString();
	itemAttributes->setStringAttribute(name, value);
}

void AttachmentImplementation::parseSkillModAttributeString(String attribute) {

	String temp, type;

	StringTokenizer tokenizer(attribute);
	tokenizer.setDelimeter(";");

	while(tokenizer.hasMoreTokens()) {

		tokenizer.getStringToken(temp);

		StringTokenizer keyvaluepair(temp);
		keyvaluepair.setDelimeter("=");

		if (keyvaluepair.hasMoreTokens()) {
			keyvaluepair.getStringToken(type);
			int value = keyvaluepair.getIntToken();

			addSkillMod(type, value);
		}
	}
}

void AttachmentImplementation::parseSkillModIndexString(String attribute) {

	String name;

	StringTokenizer tokenizer(attribute);
	tokenizer.setDelimeter(";");

	skillModIndex.removeAll();

	while(tokenizer.hasMoreTokens()) {

		tokenizer.getStringToken(name);

		skillModIndex.add(name);
	}
}

void AttachmentImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;

	AttributeListMessage* alm = new AttributeListMessage(_this);
	addAttributes(alm);

	player->sendMessage(alm);
}


void AttachmentImplementation::addAttributes(AttributeListMessage* alm) {
	StringBuffer name;
	for(int i = 0; i < skillModMap.size(); ++i) {

		name << "cat_skill_mod_bonus.@stat_n:" << skillModMap.elementAt(i)->getKey();
		int value = skillModMap.elementAt(i)->getValue();

		alm->insertAttribute(name.toString(), value);

		name.removeAll();
	}
}

void AttachmentImplementation::addSkillMod(String skillModType, int skillModValue) {

	if (skillModMap.contains(skillModType)) {
		skillModMap.drop(skillModType);
	}

	skillModMap.put(skillModType, skillModValue);

	skillModIndex.add(skillModType);

	saveSkillModIndex();
	saveSkillModAttributes();
}

void AttachmentImplementation::generateSkillMods(Player* player, int creatureLevel) {

	int maxEffectiveLevel = 250;

	if (creatureLevel > maxEffectiveLevel)
		creatureLevel = maxEffectiveLevel;

	// Gives a max Value of 200 - If creature level i >= 250 this will equal 100
	int levelModifier = int(float(creatureLevel) / float(maxEffectiveLevel) * 100) * 2;

	// Gives a max Value of 500 - If creature level i >= 250 this will equal 100
	int luckskill = int(float(player->getSkillMod("luck") + player->getSkillMod("force_luck")) / 125.0f) * 100 * 2;

	int luckRoll = System::random(300);

	if (System::random(1000) == 7)
		luckRoll *=  2;

	if (System::random(50000) == 77)
		luckRoll *= 5;

	if (System::random(1000000) == 777)
		luckRoll *= 10;

	if (System::random(100) == 6)
		luckRoll = 0;

	int playerRoll = System::random(levelModifier + luckskill + luckRoll);

	/*for(int i = 0; i < 1000; i++) {
		levelModifier = System::random(250);
		luckRoll = System::random(300);
		int playerRoll = System::random(levelModifier + luckskill + luckRoll);

		if(playerRoll > 350)
			System::out << " Level: " << levelModifier << " Luck: " << luckRoll << " Got 3 Sockets" << endl;
		else if(playerRoll > 250)
				System::out << " Level: " << levelModifier << " Luck: " << luckRoll <<  " Got 2 Sockets" << endl;
	}*/

	// Max roll without luck mods Creature max is 500, luck max is 200
	// int maxPlayerRoll = 1000 * 250 * 2250 / 1000;

	maxmods = 1;

	if (playerRoll > 200) {
		maxmods = 2;
	} else if (playerRoll > 350) {
		maxmods = 3;
	}

	for(int i = 0; i < maxmods; ++i) {
		int randomLuck = System::random(int(luckRoll / 2)) + int(luckRoll / 2) + luckskill;
		addSkillMod(wearableSkillMods.getRandomAttachmentMod(attachmentType), getRandomModValue(randomLuck, creatureLevel));
	}
}

int AttachmentImplementation::getRandomModValue(int luck, int creatureLevel){

	int min, mod, result;

	if (luck > 280 && creatureLevel > 250){
		min = 9;
		mod = luck % 27;
	} else if (luck > 200 && creatureLevel > 125){
		min = 4;
		mod = luck % 19;
	} else if (luck > 110){
		min = 2;
		mod = luck % 7;
	} else if (luck > 45){
		min = 2;
		mod = luck % 4;
	} else if (luck > 15){
		min = 1;
		mod = luck % 2;
	}

	result = min + mod;
	if (mod == 0){
		result *= -1;
	}

	if(result > 25)
		result = 25;
	if(result < -25)
		result = -25;
	if(result == 0)
		result = -1;

	return result;
}

void AttachmentImplementation::remove(Player* player) {
	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();

	itemManager->deletePlayerItem(player, _this, false);

	player->removeInventoryItem(objectID);

	sendDestroyTo(player);
}
