/*
 * SkillBuffObjectMenuComponent.cpp
 *
 *  Created on: 9/21/2013
 *      Author: Klivian
 */

#include <stddef.h>
#include <algorithm>

#include "SkillBuffObjectMenuComponent.h"
#include "engine/core/ManagedReference.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/buffs/Buff.h"
#include "server/zone/objects/creature/buffs/BuffType.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/tangible/components/TangibleObjectMenuComponent.h"
#include "system/lang/String.h"
#include "system/lang/ref/Reference.h"
#include "system/thread/Locker.h"
#include "system/util/VectorMap.h"
#include "templates/tangible/SkillBuffTemplate.h"

namespace server {
namespace zone {
namespace packets {
namespace object {
class ObjectMenuResponse;
}  // namespace object
}  // namespace packets
}  // namespace zone
}  // namespace server

void SkillBuffObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {

	if(!sceneObject->isTangibleObject())
		return;

	TangibleObject* tano = cast<TangibleObject*>(sceneObject);
	if(tano == NULL)
		return;

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

}

int SkillBuffObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {

	if (!sceneObject->isASubChildOf(player))
		return 0;

	if (selectedID != 20) {
		return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
	}

	if (player->isDead() || player->isIncapacitated())
		return 0;

	if(!sceneObject->isTangibleObject())
		return 0;

	ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(sceneObject);

	ManagedReference<SkillBuffTemplate*> skillBuff = cast<SkillBuffTemplate*>(sceneObject->getObjectTemplate());
	if (skillBuff == NULL) {
		error("No SkillBuffTemplate for: " + String::valueOf(sceneObject->getServerObjectCRC()));
		return 1;
	}

	unsigned int buffCRC = skillBuff->getBuffCRC();
	int duration = skillBuff->getDuration();
	VectorMap<String, float>* modifiers = skillBuff->getModifiers();

	// Check if buff of same type is already active
	if ( player->hasBuff(buffCRC) ) {
		player->sendSystemMessage("@skill_buff_n:already_have"); //You already have that skill modifier active.
		return 0;
	}

	// Build buff
	ManagedReference<Buff*> buff = new Buff(player, buffCRC, duration, BuffType::SKILL);

	Locker locker(buff);

	for (int i = 0; i < modifiers->size(); ++i) {
		String attribute = modifiers->elementAt(i).getKey();
		float value = modifiers->elementAt(i).getValue();
		buff->setSkillModifier(attribute, (int)value);
	}

	// Submit buff
	if (buff != NULL){
		player->addBuff(buff);
	}

	// Send message to player
	StringIdChatParameter stringId("skill_buff_d", "consume"); // You feel enhanced!
	player->sendSystemMessage(stringId);

	//Consume a charge from the item, destroy it if it reaches 0 charges remaining.
	tano->decreaseUseCount();

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
