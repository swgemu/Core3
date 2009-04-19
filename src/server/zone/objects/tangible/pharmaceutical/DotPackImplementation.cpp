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

#include "DotPack.h"
#include "DotPackImplementation.h"

#include "../../creature/CreatureAttribute.h"
#include "../../creature/CreatureState.h"

#include "../../../objects.h"

DotPackImplementation::DotPackImplementation(uint64 oid, uint32 tempCRC, const UnicodeString& n, const String& tempn)
		: DotPackServant(oid, tempCRC, n, tempn, 0) {
	init();
}
DotPackImplementation::DotPackImplementation(CreatureObject* creature, uint32 tempCRC, const UnicodeString& n, const String& tempn)
		: DotPackServant(creature, tempCRC, n, tempn, 0) {

	customName = n;
	stfName = tempn;

	init();
}

int DotPackImplementation::useObject(Player* player) {
	if (player->getSkillMod("combat_healing_ability") < medicineUseRequired) {
		player->sendSystemMessage("error_message", "insufficient_skill"); //You lack the skill to use this item.
		return 0;
	}

	//uint32 actionCRC = 0xE08596DB; //poison
	if (medpackType == POISONDELIVERYUNIT) {
		player->queueThrow((TangibleObject*)_this, 0xE08596DB);
	}
	else if (medpackType == DISEASEDELIVERYUNIT) {
		player->queueThrow((TangibleObject*)_this, 0xAF5E4D90);
	}
	return 0;
}

void DotPackImplementation::updateCraftingValues(DraftSchematic* draftSchematic) {
	String name;

	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();
	//craftingValues->toString();

	name = "effectiveness";
	effectiveness = craftingValues->getCurrentValue("power");
	itemAttributes->setFloatAttribute(name, effectiveness);

	name = "medicineUseRequired";
	medicineUseRequired = (int)craftingValues->getCurrentValue("medicineUseRequired");
	itemAttributes->setIntAttribute(name, medicineUseRequired);

	name = "usesRemaining";
	setUsesRemaining((int)(floor(craftingValues->getCurrentValue("charges") + .5f)));
	itemAttributes->setFloatAttribute(name, usesRemaining);

	name = "range";
	effectiveness = craftingValues->getCurrentValue("range");
	itemAttributes->setFloatAttribute(name, range);

	name = "area";
	effectiveness = craftingValues->getCurrentValue("area");
	itemAttributes->setFloatAttribute(name, area);

	name = "potency";
	potency = craftingValues->getCurrentValue("potency");
	itemAttributes->setFloatAttribute(name, potency);

	name = "duration";
	duration = (int)craftingValues->getCurrentValue("duration");
	itemAttributes->setIntAttribute(name, duration);
}

void DotPackImplementation::init() {
	setEffectiveness(0.0f);
	setArea(0);

	setEffectiveness(0.0f);
	setRange(18.0f);
	setPotency(65.0f);
	setPool(CreatureAttribute::HEALTH);
	setDuration(120);
	rangeMod = 1.0;
	if ((stfName.indexOf("poison") != -1))
		setMedpackType(POISONDELIVERYUNIT);
	else if (stfName.indexOf("disease") != -1)
		setMedpackType(DISEASEDELIVERYUNIT);

	if ((stfName.indexOf("area") != -1))
		setArea(8.0f);
	else
		setArea(0.0f);

	if ((stfName.indexOf("_a.iff") != -1))
		rangeMod = 1.0;
	else if ((stfName.indexOf("_b.iff") != -1))
		rangeMod = 0.6;
	else if ((stfName.indexOf("_c.iff") != -1))
		rangeMod = 0.3;

	if ((stfName.indexOf("health") != -1))
		setPool(CreatureAttribute::HEALTH);
	else if ((stfName.indexOf("strength") != -1))
		setPool(CreatureAttribute::STRENGTH);
	else if ((stfName.indexOf("constitution") != -1))
		setPool(CreatureAttribute::CONSTITUTION);
	else if ((stfName.indexOf("action") != -1))
		setPool(CreatureAttribute::ACTION);
	else if ((stfName.indexOf("quickness") != -1))
		setPool(CreatureAttribute::QUICKNESS);
	else if ((stfName.indexOf("stamina") != -1))
		setPool(CreatureAttribute::STAMINA);
	else if ((stfName.indexOf("mind") != -1))
		setPool(CreatureAttribute::MIND);
	else if ((stfName.indexOf("focus") != -1))
		setPool(CreatureAttribute::FOCUS);
	else if ((stfName.indexOf("willpower") != -1))
		setPool(CreatureAttribute::WILLPOWER);
}

void DotPackImplementation::parseItemAttributes() {
	PharmaceuticalImplementation::parseItemAttributes();

		String attr = "effectiveness";
		setEffectiveness(itemAttributes->getFloatAttribute(attr));

		attr = "range";
		setRange(itemAttributes->getFloatAttribute(attr));

		attr = "area";
		setArea(itemAttributes->getFloatAttribute(attr));

		attr = "potency";
		setPotency(itemAttributes->getFloatAttribute(attr));

		attr = "duration";
		setDuration(itemAttributes->getIntAttribute(attr));

}

void DotPackImplementation::addAttributes(AttributeListMessage* alm) {
	PharmaceuticalImplementation::addHeaderAttributes(alm);

	String attr = "examine_dot_attribute";
	alm->insertAttribute(attr, CreatureAttribute::getName(pool,true));

	attr = "examine_dot_apply_power";
	alm->insertAttribute(attr, getPrecision(effectiveness, 0));

	attr = "examine_dot_apply";
	if (isPoisonDeliveryUnit())
		alm->insertAttribute(attr, "Poison");
	else if (isDiseaseDeliveryUnit())
		alm->insertAttribute(attr, "Diseased");

	attr = "examine_dot_potency";
	alm->insertAttribute(attr, getPrecision(potency, 0));

	attr = "examine_heal_range";
	alm->insertAttribute(attr, getPrecision(range, 0));

	if (isArea()) {
		attr = "examine_heal_area";
		alm->insertAttribute(attr, getPrecision(area, 0));
	}

	attr = "duration";
	alm->insertAttribute(attr, getPrecision(duration, 0));

	attr = "combat_healing_ability";
	alm->insertAttribute("healing_ability", getMedicineUseRequired());
}

void DotPackImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;
	AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);
	addAttributes(alm);

	player->sendMessage(alm);
}
