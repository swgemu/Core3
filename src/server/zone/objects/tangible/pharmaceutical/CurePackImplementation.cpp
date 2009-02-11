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

#include "CurePack.h"
#include "CurePackImplementation.h"

#include "../../../objects.h"

CurePackImplementation::CurePackImplementation(uint64 oid, uint32 tempCRC, const UnicodeString& n, const String& tempn)
		: CurePackServant(oid, tempCRC, n, tempn, CUREPACK) {
	initialize();
}
CurePackImplementation::CurePackImplementation(CreatureObject* creature, uint32 tempCRC, const UnicodeString& n, const String& tempn)
		: CurePackServant(creature, tempCRC, n, tempn, CUREPACK) {

	customName = n;
	templateName = tempn;

	initialize();
}

int CurePackImplementation::useObject(Player* player) {
	if (player->getSkillMod("healing_ability") < medicineUseRequired) {
		player->sendSystemMessage("error_message", "insufficient_skill"); //You lack the skill to use this item.
		return 0;
	}

	uint32 actionCRC = 0;

	switch (state) {
	case CreatureState::POISONED:
		actionCRC = 0x1754A3E5; //curepoison
		break;
	case CreatureState::DISEASED:
		actionCRC = 0xE994DE9C; //curedisease
		break;
	case CreatureState::ONFIRE:
	default:
		actionCRC = 0xDF49EA58; //extinguishfire
		break;
	}

	player->queueHeal((TangibleObject*)_this, actionCRC, String(""));

	return 0;
}

void CurePackImplementation::initialize() {
	setEffectiveness(0.0f);
	setArea(0.0f);
	setState(CreatureState::INVALID);
}

void CurePackImplementation::parseItemAttributes() {
	PharmaceuticalImplementation::parseItemAttributes();

	String attr = "effectiveness";
	setEffectiveness(itemAttributes->getFloatAttribute(attr));

	attr = "state";
	setState(itemAttributes->getUnsignedLongAttribute(attr));

	attr = "area";
	setArea(itemAttributes->getFloatAttribute(attr));
}

void CurePackImplementation::addAttributes(AttributeListMessage* alm) {
	PharmaceuticalImplementation::addHeaderAttributes(alm);

	StringBuffer eff;
	eff << "@obj_attr_n:dot_type_" << CreatureState::getSpecialName(state);
	alm->insertAttribute("examine_dot_cure", eff.toString());

	alm->insertAttribute("examine_dot_cure_power", effectiveness);

	if (isArea()) {
		alm->insertAttribute("examine_heal_area", getPrecision(area, 0));
	}

	PharmaceuticalImplementation::addFooterAttributes(alm);
}

void CurePackImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;
	AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);

	addAttributes(alm);

	player->sendMessage(alm);
}
