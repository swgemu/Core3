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
