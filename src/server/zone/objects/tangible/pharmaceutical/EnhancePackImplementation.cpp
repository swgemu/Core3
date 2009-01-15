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

#include "EnhancePack.h"
#include "EnhancePackImplementation.h"

#include "../../../objects.h"

EnhancePackImplementation::EnhancePackImplementation(uint64 oid, uint32 tempCRC, const UnicodeString& n, const String& tempn)
		: EnhancePackServant(oid, tempCRC, n, tempn, ENHANCEPACK) {
	initialize();
}
EnhancePackImplementation::EnhancePackImplementation(CreatureObject* creature, uint32 tempCRC, const UnicodeString& n, const String& tempn)
		: EnhancePackServant(creature, tempCRC, n, tempn, ENHANCEPACK) {

	customName = n;
	templateName = tempn;

	initialize();
}

int EnhancePackImplementation::useObject(Player* player) {
	if (player->getSkillMod("healing_ability") < medicineUseRequired) {
		player->sendSystemMessage("error_message", "insufficient_skill"); //You lack the skill to use this item.
		return 0;
	}

	uint32 actionCRC = 0xEEE029CF; //healenhance
	player->queueHeal((TangibleObject*)_this, actionCRC, CreatureAttribute::getName(attribute));

	return 0;
}

uint32 EnhancePackImplementation::getBuffCRC() {
	switch (attribute) {
	case CreatureAttribute::ACTION:
		return BuffCRC::MEDICAL_ENHANCE_ACTION;
		break;
	case CreatureAttribute::CONSTITUTION:
		return BuffCRC::MEDICAL_ENHANCE_CONSTITUTION;
		break;
	case CreatureAttribute::STRENGTH:
		return BuffCRC::MEDICAL_ENHANCE_STRENGTH;
		break;
	case CreatureAttribute::QUICKNESS:
		return BuffCRC::MEDICAL_ENHANCE_QUICKNESS;
		break;
	case CreatureAttribute::STAMINA:
		return BuffCRC::MEDICAL_ENHANCE_STAMINA;
		break;
	case CreatureAttribute::HEALTH:
	default:
		return BuffCRC::MEDICAL_ENHANCE_HEALTH;
		break;
	}
}

void EnhancePackImplementation::initialize() {
	setEffectiveness(0.0f);
	setDuration(0.0f);
	setAttribute(CreatureAttribute::UNKNOWN);
}

void EnhancePackImplementation::parseItemAttributes() {
	PharmaceuticalImplementation::parseItemAttributes();

	String attr = "effectiveness";
	setEffectiveness(itemAttributes->getFloatAttribute(attr));
	attr = "duration";
	setDuration(itemAttributes->getFloatAttribute(attr));
	attr = "attribute";
	setAttribute(itemAttributes->getIntAttribute(attr));
}

void EnhancePackImplementation::addAttributes(AttributeListMessage* alm) {
	PharmaceuticalImplementation::addHeaderAttributes(alm);

	String attributeName = CreatureAttribute::getName(attribute);

	StringBuffer eff;
	eff << "examine_enhance_" << attributeName;
	alm->insertAttribute(String(eff.toString()), effectiveness);

	StringBuffer dur;
	dur << "examine_duration_" << attributeName;
	alm->insertAttribute(String(dur.toString()), duration);

	PharmaceuticalImplementation::addFooterAttributes(alm);
}

void EnhancePackImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;
	AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);

	addAttributes(alm);

	player->sendMessage(alm);
}
