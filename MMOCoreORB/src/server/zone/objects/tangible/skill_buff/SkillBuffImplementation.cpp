/*
 * SkillBuffImplementation.cpp
 *
 *  Created on: 20/09/2013
 *      Author: Klivian
 */

#include "SkillBuff.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/creature/buffs/Buff.h"
#include "server/zone/templates/tangible/SkillBuffTemplate.h"

void SkillBuffImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	SkillBuffTemplate* skillbuff = dynamic_cast<SkillBuffTemplate*>(templateData);

	if (skillbuff == NULL)
		return;

	duration = skillbuff->getDuration();

	modifiers = *skillbuff->getModifiers();
	buffName = skillbuff->getBuffName();
	buffCRC = buffName.hashCode();

	setUseCount(skillbuff->getQuantity(), true);
}

int SkillBuffImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (!isASubChildOf(player))
		return 0;

	if (selectedID != 20) {
		return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);
	}

	// Check if player is dead or incap'd
	if (player->isDead() || player->isIncapacitated())
		return 0;

	// Check if buff of same type is already active
	if ( player->hasBuff(buffCRC) ) {
		player->sendSystemMessage("@skill_buff_n:already_have"); //You already have that skill modifier active.
		return 0;
	}

	// Build buff
	ManagedReference<Buff*> buff = new Buff(player, buffCRC, duration, BuffType::SKILL);
	for (int i = 0; i < modifiers.size(); ++i) {
		String attribute = modifiers.elementAt(i).getKey();
		float value = modifiers.elementAt(i).getValue();
		buff->setSkillModifier(attribute, (int)value);
	}

	// Submit buff
	if (buff != NULL){
		player->addBuff(buff);
	}

	// Send message to player
	StringIdChatParameter stringId("skill_buff_d", "consume"); // You feel enhanced!
	stringId.setTT(getObjectID());
	player->sendSystemMessage(stringId);

	//Consume a charge from the item, destroy it if it reaches 0 charges remaining.
	decreaseUseCount();

	return 0;
}

void SkillBuffImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player) {

	if (maxCondition > 0) {
		StringBuffer cond;
		cond << (maxCondition-(int)conditionDamage) << "/" << maxCondition;

		alm->insertAttribute("condition", cond);
	}

	alm->insertAttribute("volume", volume);

	if (useCount > 0){
			alm->insertAttribute("quantity", useCount);
	}

	if (!craftersName.isEmpty()){
		alm->insertAttribute("crafter", craftersName);
	}

	if (!objectSerial.isEmpty()){
		alm->insertAttribute("serial_number", objectSerial);
	}

	for (int i = 0; i < modifiers.size(); ++i) {
		VectorMapEntry<String, float>* entry = &modifiers.elementAt(i);
		alm->insertAttribute("skill", "@stat_n:" + entry->getKey());
	}

	StringBuffer durationstring;
	int minutes = (int) floor(duration / 60.0f);
	int seconds = duration % 60;

	if (minutes > 0){
		durationstring << minutes << "m ";
	}

	durationstring << seconds << "s";

	alm->insertAttribute("duration", durationstring.toString());

}
