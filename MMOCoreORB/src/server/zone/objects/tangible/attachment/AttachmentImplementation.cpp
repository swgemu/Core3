/*
 * AttachmentImplementation.cpp
 *
 *  Created on: Mar 10, 2011
 *      Author: polonel
 */

#include "Attachment.h"
#include "server/zone/objects/tangible/wearables/WearableSkillModMap.h"
#include "server/zone/objects/tangible/wearables/WearableSkillMods.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"

void AttachmentImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("AttachmentObject");

}

void AttachmentImplementation::initializeMembers() {
	if (gameObjectType == SceneObject::CLOTHINGATTACHMENT) {
		setOptionsBitmask(32, true);
		attachmentType = CLOTHINGTYPE;

	} else if (gameObjectType == SceneObject::ARMORATTACHMENT) {
		setOptionsBitmask(32, true);
		attachmentType = ARMORTYPE;

	}

}

void AttachmentImplementation::fillAttributeList(AttributeListMessage* msg, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(msg, object);

	StringBuffer name;
	for(int i = 0; i < skillModMap.size(); ++i) {

		name << "cat_skill_mod_bonus.@stat_n:" << skillModMap.elementAt(i).getKey();
		int value = skillModMap.elementAt(i).getValue();

		msg->insertAttribute(name.toString(), value);

		name.deleteAll();
	}

}

void AttachmentImplementation::parseSkillModAttributeString(String& attr) {
	String temp, type;
	StringTokenizer tokenizer(attr);
	tokenizer.setDelimeter(";");

	while (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(temp);

		StringTokenizer keyValuePair(temp);
		keyValuePair.setDelimeter("=");

		if (keyValuePair.hasMoreTokens()) {
			keyValuePair.getStringToken(type);
			int value = keyValuePair.getIntToken();

			addSkillMod(type, value);
		}
	}
}

void AttachmentImplementation::addSkillMod(const String& skillModType, int skillModValue) {
	if (skillModMap.contains(skillModType))
		skillModMap.drop(skillModType);

	skillModMap.put(skillModType, skillModValue);

}

bool AttachmentImplementation::removeAttachment(CreatureObject* player) {
	SceneObject* container = parent;

	if (container == NULL)
		return 0;

	if (!container->isContainerObject())
		return 0;

	Locker _locker(container);

	if (container->hasObjectInContainer(getObjectID())) {
		container->removeObject(_this, true);

		return 1;
	}

	return 0;

}

void AttachmentImplementation::generateSkillMods() {

	int creatureLevel = System::random(250); // TODO: handle this by lootdrop

	int maxEffectiveLevel = 250;

	if (creatureLevel > maxEffectiveLevel)
		creatureLevel = maxEffectiveLevel;

	// Gives a max Value of 200 - If creature level i >= 250 this will equal 100
	int levelModifier = int(float(creatureLevel) / float(maxEffectiveLevel) * 100) * 2;

	//TODO: get this to pull from the player SkillMod Values for Luck.
	// Gives a max Value of 500 - If creature level i >= 250 this will equal 100
	//int luckskill = int(float(player->getSkillMod("luck") + player->getSkillMod("force_luck")) / 125.0f) * 100 * 2;
	int luckskill = 0;

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

	maxModifiers = 1;

	if (playerRoll > 200) {
		maxModifiers = 2;
	} else if (playerRoll > 350) {
		maxModifiers = 3;
	}

	for(int i = 0; i < maxModifiers; ++i) {
		int randomLuck = System::random(int(luckRoll / 2)) + int(luckRoll / 2) + luckskill;
		addSkillMod(WearableSkillMods::getRandomAttachmentMod(attachmentType), getRandomModValue(randomLuck, creatureLevel));
	}

}

int AttachmentImplementation::getRandomModValue(int luck, int creatureLevel) {

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

String AttachmentImplementation::getSkillModName(int idx) {
	return skillModMap.elementAt(idx).getKey();
}

int AttachmentImplementation::getSkillModValue(int idx) {
	return skillModMap.elementAt(idx).getValue();
}
