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

#include "RangedStimPack.h"
#include "RangedStimPackImplementation.h"

#include "../../../objects.h"

RangedStimPackImplementation::RangedStimPackImplementation(uint64 oid, uint32 tempCRC, const UnicodeString& n, const String& tempn)
		: RangedStimPackServant(oid, tempCRC, n, tempn) {
	init();
}
RangedStimPackImplementation::RangedStimPackImplementation(CreatureObject* creature, uint32 tempCRC, const UnicodeString& n, const String& tempn)
		: RangedStimPackServant(creature, tempCRC, n, tempn) {
	customName = n;
	templateName = tempn;

	init();
}

int RangedStimPackImplementation::useObject(Player* player) {
	if (player->getSkillMod("combat_healing_ability") < medicineUseRequired) {
		player->sendSystemMessage("error_message", "insufficient_skill"); //You lack the skill to use this item.
		return 0;
	}

	if (!player->canTreatInjuries()) {
		player->sendSystemMessage("healing_response", "healing_must_wait"); //You must wait before you can do that.
		return 0;
	}

	StringBuffer cmd;
	cmd << "/healdamage "<< getObjectID();
	ExecuteConsoleCommand* msg =  new ExecuteConsoleCommand(cmd.toString());

	player->sendMessage(msg);

	return 0;
}

void RangedStimPackImplementation::updateCraftingValues(DraftSchematic* draftSchematic) {
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
}

void RangedStimPackImplementation::init() {
	setMedpackType(RANGEDSTIMPACK);
	setEffectiveness(0.0f);
	setRange(10.0f);
	setArea(0.0f);

	switch(objectCRC) {
	case 0xF44F43F:
		rangeMod = 1.0;
		break;
	case 0xD4535CA8:
		rangeMod = 0.8;
		break;
	case 0x9D5E3B25:
		rangeMod = 0.6;
		break;
	case 0x66BD1031:
		rangeMod = 0.4;
		break;
	case 0x2FB077BC:
		rangeMod = 0.3;
		break;
	case 0x5D62E08E:
		rangeMod = 0.6;
		break;
	case 0x86754819:
		rangeMod = 0.4;
		break;
	case 0xCF782F94:
		rangeMod = 0.3;
		break;
	}
}

void RangedStimPackImplementation::parseItemAttributes() {
	PharmaceuticalImplementation::parseItemAttributes();

	String attr = "effectiveness";
	setEffectiveness(itemAttributes->getFloatAttribute(attr));

	attr = "range";
	setRange(itemAttributes->getFloatAttribute(attr));

	attr = "area";
	setArea(itemAttributes->getFloatAttribute(attr));

}

void RangedStimPackImplementation::addAttributes(AttributeListMessage* alm) {
	PharmaceuticalImplementation::addHeaderAttributes(alm);

	String attr = "examine_heal_damage_health";
	alm->insertAttribute(attr, getPrecision(effectiveness, 0));
	attr = "examine_heal_damage_action";
	alm->insertAttribute(attr, getPrecision(effectiveness, 0));

	attr = "examine_heal_range";
	alm->insertAttribute(attr, getPrecision(range, 0));
	if (isArea()) {
		attr = "examine_heal_area";
		alm->insertAttribute(attr, getPrecision(area, 0));
	}
	attr = "combat_healing_ability";
	alm->insertAttribute(attr, getMedicineUseRequired());

}

void RangedStimPackImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;
	AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);

	addAttributes(alm);

	player->sendMessage(alm);
}

uint32 RangedStimPackImplementation::calculatePower(CreatureObject* healer, CreatureObject* patient, bool applyBattleFatigue) {
	float power = getEffectiveness();

	if (applyBattleFatigue)
		power -= power * patient->calculateBFRatio();

	float modSkill = (float) healer->getSkillMod("combat_medic_effectiveness");

	return (int) round((100.0f + modSkill) / 100.0f * power);
}
