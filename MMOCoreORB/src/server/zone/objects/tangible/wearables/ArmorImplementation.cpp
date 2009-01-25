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

#include "../../../ZoneClientSession.h"
#include "../../player/Player.h"

#include "../../../packets.h"

#include "Armor.h"
#include "ArmorImplementation.h"

#include "../../../managers/player/PlayerManager.h"

#include "../../../objects/draftschematic/DraftSchematicValuesImplementation.h"

ArmorImplementation::ArmorImplementation(uint64 objid, uint32 tempCRC, const UnicodeString& n, const String& tempn, bool eqp)
		: ArmorServant(objid, tempCRC, n, tempn, eqp) {
	initialize();
}

ArmorImplementation::ArmorImplementation(CreatureObject* creature, uint32 tempCRC, const UnicodeString& n, const String& tempn, bool eqp)
		: ArmorServant(creature, tempCRC, n, tempn, eqp) {

	//objectCRC = String::hashCode(temp);
	customName = n;
	templateName = tempn;

	initialize();
}

void ArmorImplementation::parseItemAttributes() {
	String name = "armorType";
	armorType = itemAttributes->getIntAttribute(name);

	maxCondition = itemAttributes->getMaxCondition();
	conditionDamage = maxCondition - itemAttributes->getCurrentCondition();

	name = "rating";
	rating = itemAttributes->getIntAttribute(name);

	name = "sockets";
	sockets = itemAttributes->getIntAttribute(name);

	name = "skillMod0Type";
	skillMod0Type = itemAttributes->getIntAttribute(name);
	name = "skillMod0Value";
	skillMod0Value = itemAttributes->getIntAttribute(name);

	name = "skillMod1Type";
	skillMod1Type = itemAttributes->getIntAttribute(name);
	name = "skillMod1Value";
	skillMod1Value = itemAttributes->getIntAttribute(name);

	name = "skillMod2Type";
	skillMod2Type = itemAttributes->getIntAttribute(name);
	name = "skillMod2Value";
	skillMod2Value = itemAttributes->getIntAttribute(name);

	name = "socket0Type";
	socket0Type = itemAttributes->getIntAttribute(name);
	name = "socket0Value";
	socket0Value = itemAttributes->getIntAttribute(name);

	name = "socket1Type";
	socket1Type = itemAttributes->getIntAttribute(name);
	name = "socket1Value";
	socket1Value = itemAttributes->getIntAttribute(name);

	name = "socket2Type";
	socket2Type = itemAttributes->getIntAttribute(name);
	name = "socket2Value";
	socket2Value = itemAttributes->getIntAttribute(name);

	name = "socket3Type";
	socket3Type = itemAttributes->getIntAttribute(name);
	name = "socket3Value";
	socket3Value = itemAttributes->getIntAttribute(name);

	name = "healthEncumberence";
	healthEncumbrance = itemAttributes->getIntAttribute(name);
	name = "actionEncumberence";
	actionEncumbrance = itemAttributes->getIntAttribute(name);
	name = "mindEncumberence";
	mindEncumbrance = itemAttributes->getIntAttribute(name);

	name = "kinetic";
	kinetic = itemAttributes->getFloatAttribute(name);
	name = "energy";
	energy = itemAttributes->getFloatAttribute(name);
	name = "electricity";
	electricity = itemAttributes->getFloatAttribute(name);
	name = "stun";
	stun = itemAttributes->getFloatAttribute(name);
	name = "blast";
	blast = itemAttributes->getFloatAttribute(name);
	name = "heat";
	heat = itemAttributes->getFloatAttribute(name);
	name = "cold";
	cold = itemAttributes->getFloatAttribute(name);
	name = "acid";
	acid = itemAttributes->getFloatAttribute(name);
	name = "lightSaber";
	lightSaber = itemAttributes->getFloatAttribute(name);

	name = "kineticIsSpecial";
	kineticIsSpecial = itemAttributes->getBooleanAttribute(name);
	name = "energyIsSpecial";
	energyIsSpecial = itemAttributes->getBooleanAttribute(name);
	name = "electricityIsSpecial";
	electricityIsSpecial = itemAttributes->getBooleanAttribute(name);
	name = "stunIsSpecial";
	stunIsSpecial = itemAttributes->getBooleanAttribute(name);
	name = "blastIsSpecial";
	blastIsSpecial = itemAttributes->getBooleanAttribute(name);
	name = "heatIsSpecial";
	heatIsSpecial = itemAttributes->getBooleanAttribute(name);
	name = "coldIsSpecial";
	coldIsSpecial = itemAttributes->getBooleanAttribute(name);
	name = "acidIsSpecial";
	acidIsSpecial = itemAttributes->getBooleanAttribute(name);
	name = "lightSaberIsSpecial";
	lightSaberIsSpecial = itemAttributes->getBooleanAttribute(name);

	name = "sliced";
	sliced = itemAttributes->getBooleanAttribute(name);

}

void ArmorImplementation::initialize() {
	objectSubType = ARMOR;

	setRating(LIGHT);
	setConditionDamage(0);
	setCondition(35000, 35000);

	skillMod0Type = 0;
	skillMod0Value = 0;

	skillMod1Type = 0;
	skillMod1Value = 0;

	skillMod2Type = 0;
	skillMod2Value = 0;

	setSockets(1);

	firstCraftingUpdate = true;

	socket0Type = 0;
	socket0Value = 0;

	socket1Type = 0;
	socket1Value = 0;

	socket2Type = 0;
	socket2Value = 0;

	socket3Type = 0;
	socket3Value = 0;

	setHealthEncumbrance(100);
	setActionEncumbrance(100);
	setMindEncumbrance(100);

	setKinetic(10.0f);
	kineticIsSpecial = false;

	setEnergy(10.0f);
	energyIsSpecial = false;

	setElectricity(10.0f);
	electricityIsSpecial = false;

	setStun(0.0f);
	stunIsSpecial = false;

	setBlast(10.0f);
	blastIsSpecial = false;

	setHeat(10.0f);
	heatIsSpecial = false;

	setCold(10.0f);
	coldIsSpecial = false;

	setAcid(10.0f);
	acidIsSpecial = false;

	setLightSaber(0.0f);
	lightSaberIsSpecial = false;

	armorType = 0;

	slicable = true;

	customizationVariables.setVariable(3, 0);
	customizationVariables.setVariable(2, 0);
	customizationVariables.setVariable(1, 0);

	setArmorStyle();

	StringBuffer loggingname;
	loggingname << "Armor = 0x" << objectID;
	setLoggingName(loggingname.toString());

	setLogging(false);
	setGlobalLogging(true);
}

void ArmorImplementation::sendTo(Player* player, bool doClose) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);

	if (parent != NULL)
		link(client, parent);

	BaseMessage* tano3 = new TangibleObjectMessage3((TangibleObject*) _this);
	client->sendMessage(tano3);

	if (doClose)
		SceneObjectImplementation::close(client);

}

void ArmorImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	if (player->getInventoryItem(getObjectID()) != NULL) {
		omr->addRadialItem(0, 68, 3, "Change color");

		if (!isSliced() && player->getSlicingAbility() >= 3)
			omr->addRadialItem(0, 69, 3, "Slice");

		if (getConditionDamage() > 0)
			omr->addRadialItem(0, 70, 3, "Repair");
	}

	//TODO:Cell permission check
	if (_this->getParent() != NULL) {
		bool cellPermission = true;

		if (_this->getParent()->isCell() && cellPermission) {
			omr->addRadialItem(0, 10, 3, "Pickup");
		}
	}

	omr->finish();
	player->sendMessage(omr);
}

void ArmorImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;

	AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);

	addAttributes(alm);

	player->sendMessage(alm);

}

void ArmorImplementation::updateCraftingValues(DraftSchematic* draftSchematic){

	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	if (firstCraftingUpdate) {
		generateSockets(draftSchematic);
		addSpecialProtectionBasedOnType(draftSchematic);
	}

	setRating((int)craftingValues->getCurrentValue("armor_rating"));

	setHealthEncumbrance((int)craftingValues->getCurrentValue("armor_health_encumbrance"));
	setActionEncumbrance((int)craftingValues->getCurrentValue("armor_action_encumbrance"));
	setMindEncumbrance((int)craftingValues->getCurrentValue("armor_mind_encumbrance"));

	float base = craftingValues->getCurrentValue("armor_effectiveness");

	setCraftingKinetic(draftSchematic, base);
	setCraftingEnergy(draftSchematic, base);
	setCraftingElectrical(draftSchematic, base);
	setCraftingStun(draftSchematic, base);
	setCraftingBlast(draftSchematic, base);
	setCraftingHeat(draftSchematic, base);
	setCraftingCold(draftSchematic, base);
	setCraftingAcid(draftSchematic, base);
	setCraftingRestrain(draftSchematic, base);

	setCondition((int)craftingValues->getCurrentValue("armor_integrity"),
			(int)craftingValues->getCurrentValue("armor_integrity"));

	firstCraftingUpdate = false;
}

void ArmorImplementation::addSpecialProtectionBasedOnType(DraftSchematic* draftSchematic) {

	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	float base = craftingValues->getCurrentValue("armor_effectiveness");
	float value, min, max, currentValue;
	String title = "exp_resistance";
	String subtitle;
	//float min = craftingValues->getMinValue("armor_effectiveness");
	//float max = craftingValues->getMaxValue("armor_effectiveness");
	float currentPercentage = craftingValues->getCurrentPercentage("armor_effectiveness");
	float maxPercentage = craftingValues->getMaxPercentage("armor_effectiveness");
	int precision = craftingValues->getPrecision("armor_effectiveness");

	switch(armorStyle){
	case COMPOSITE:
		subtitle = "electricaleffectiveness";
		value = craftingValues->getCurrentValue(subtitle);
		min = 2;
		max = (value - min + (min * currentPercentage)) / currentPercentage;
		currentValue = (currentPercentage * (max - min)) + min;

craftingValues->toString();
		craftingValues->addExperimentalProperty(title, subtitle, min, max, precision, false);
		craftingValues->setMaxPercentage(subtitle, maxPercentage);
		craftingValues->setCurrentPercentage(subtitle, currentPercentage);
		craftingValues->setCurrentValue(subtitle, currentValue);
craftingValues->toString();
	}
}

void ArmorImplementation::generateSockets(DraftSchematic* draftSchematic) {

	String assemblySkill = draftSchematic->getAssemblySkill();
	// Get assembly points from skill

	Player* player = draftSchematic->getCrafter();

	if (player == NULL) {

		setSockets(0);

	} else {

		int sockets = int((player->getSkillMod(assemblySkill) / 10) / 3.0f)
				+ System::random(4) - System::random(4);

		if (sockets > 4)
			sockets = 4;
		if (sockets < 0)
			sockets = 0;

		setSockets(sockets);
	}
}

void ArmorImplementation::setCraftingKinetic(DraftSchematic* draftSchematic, float base) {

	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	float value = craftingValues->getCurrentValue("kineticeffectiveness");

	if (value == DraftSchematicValuesImplementation::VALUENOTFOUND && firstCraftingUpdate) {
		craftingValues->lockValue("kineticeffectiveness");
	}

	if (value == DraftSchematicValuesImplementation::VALUENOTFOUND) {
		if (isVunerableTo("kinetic"))
			setKinetic(0.0f);
		else
			setKinetic(base);
		if(firstCraftingUpdate)
			setKineticIsSpecial(false);
	} else {
		if (value + base > 80.0f)
			setKinetic(80.0f);
		else
			setKinetic(value + base);

		if(firstCraftingUpdate)
			setKineticIsSpecial(true);
	}
}

void ArmorImplementation::setCraftingEnergy(DraftSchematic* draftSchematic, float base) {

	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	float value = craftingValues->getCurrentValue("energyeffectiveness");

	if (value == DraftSchematicValuesImplementation::VALUENOTFOUND && firstCraftingUpdate) {
		craftingValues->lockValue("energyeffectiveness");
	}

	if (value == DraftSchematicValuesImplementation::VALUENOTFOUND) {
		if (isVunerableTo("energy"))
			setEnergy(0.0f);
		else
			setEnergy(base);
		if(firstCraftingUpdate)
			setEnergyIsSpecial(false);
	} else {
		if (value + base > 80.0f)
			setEnergy(80.0f);
		else
			setEnergy(value + base);
		if(firstCraftingUpdate)
			setEnergyIsSpecial(true);
	}
}

void ArmorImplementation::setCraftingElectrical(DraftSchematic* draftSchematic, float base) {

	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	float value = craftingValues->getCurrentValue("electricaleffectiveness");

	if (value == DraftSchematicValuesImplementation::VALUENOTFOUND && firstCraftingUpdate) {
		craftingValues->lockValue("electricaleffectiveness");
	}

	if (value == DraftSchematicValuesImplementation::VALUENOTFOUND) {
		if (isVunerableTo("energy"))
			setElectricity(0.0f);
		else
			setElectricity(base);
		if(firstCraftingUpdate)
			setElectricityIsSpecial(false);
	} else {
		if (value + base > 80.0f)
			setElectricity(80.0f);
		else
			setElectricity(value + base);

		if(firstCraftingUpdate)
			setElectricityIsSpecial(true);
	}
}

void ArmorImplementation::setCraftingStun(DraftSchematic* draftSchematic, float base) {

	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	float value = craftingValues->getCurrentValue("stuneffectiveness");

	if (value == DraftSchematicValuesImplementation::VALUENOTFOUND && firstCraftingUpdate) {
		craftingValues->lockValue("stuneffectiveness");
	}

	if (value == DraftSchematicValuesImplementation::VALUENOTFOUND) {
		if (isVunerableTo("stun"))
			setStun(0.0f);
		else
			setStun(base);
		if(firstCraftingUpdate)
			setStunIsSpecial(false);
	} else {
		if (value + base > 80.f)
			setStun(80.0f);
		else
			setStun(value + base);

		if(firstCraftingUpdate)
			setStunIsSpecial(true);
	}
}

void ArmorImplementation::setCraftingBlast(DraftSchematic* draftSchematic, float base) {

	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	float value = craftingValues->getCurrentValue("blasteffectiveness");

	if (value == DraftSchematicValuesImplementation::VALUENOTFOUND && firstCraftingUpdate) {
		craftingValues->lockValue("blasteffectiveness");
	}

	if (value == DraftSchematicValuesImplementation::VALUENOTFOUND) {
		if (isVunerableTo("blast"))
			setBlast(0.0f);
		else
			setBlast(base);
		if(firstCraftingUpdate)
			setBlastIsSpecial(false);
	} else {
		if (value + base > 80.0f)
			setBlast(80.0f);
		else
			setBlast(value + base);

		if(firstCraftingUpdate)
			setBlastIsSpecial(true);
	}
}

void ArmorImplementation::setCraftingHeat(DraftSchematic* draftSchematic, float base) {

	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	float value = craftingValues->getCurrentValue("heateffectiveness");

	if (value == DraftSchematicValuesImplementation::VALUENOTFOUND && firstCraftingUpdate) {
		craftingValues->lockValue("heateffectiveness");
	}

	if (value == DraftSchematicValuesImplementation::VALUENOTFOUND) {
		if (isVunerableTo("heat"))
			setHeat(0.0f);
		else
			setHeat(base);

		if(firstCraftingUpdate)
			setHeatIsSpecial(false);
	} else {
		if (value + base > 80.f)
			setHeat(80.0f);
		else
			setHeat(value + base);

		if(firstCraftingUpdate)
			setHeatIsSpecial(true);
	}
}

void ArmorImplementation::setCraftingCold(DraftSchematic* draftSchematic, float base) {

	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	float value = craftingValues->getCurrentValue("coldeffectiveness");

	if (value == DraftSchematicValuesImplementation::VALUENOTFOUND && firstCraftingUpdate) {
		craftingValues->lockValue("coldeffectiveness");
	}

	if (value == DraftSchematicValuesImplementation::VALUENOTFOUND) {
		if (isVunerableTo("cold"))
			setCold(0.0f);
		else
			setCold(base);
		if(firstCraftingUpdate)
			setColdIsSpecial(false);
	} else {
		if (value + base > 80.f)
			setCold(80.0f);
		else
			setCold(value + base);

		if(firstCraftingUpdate)
			setColdIsSpecial(true);
	}
}

void ArmorImplementation::setCraftingAcid(DraftSchematic* draftSchematic, float base) {

	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	float value = craftingValues->getCurrentValue("acideffectiveness");

	if (value == DraftSchematicValuesImplementation::VALUENOTFOUND && firstCraftingUpdate) {
		craftingValues->lockValue("acideffectiveness");
	}

	if (value == DraftSchematicValuesImplementation::VALUENOTFOUND) {
		if (isVunerableTo("acid"))
			setAcid(0.0f);
		else
			setAcid(base);
		if(firstCraftingUpdate)
			setAcidIsSpecial(false);
	} else {
		if (value + base > 80.f)
			setAcid(80.0f);
		else
			setAcid(value + base);

		if(firstCraftingUpdate)
			setAcidIsSpecial(true);
	}
}

void ArmorImplementation::setCraftingRestrain(DraftSchematic* draftSchematic, float base) {

	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	float value = craftingValues->getCurrentValue("restraineffectiveness");

	if (value == DraftSchematicValuesImplementation::VALUENOTFOUND && firstCraftingUpdate) {
		craftingValues->lockValue("restraineffectiveness");
	}

	if (value == DraftSchematicValuesImplementation::VALUENOTFOUND) {
		if (isVunerableTo("restrain"))
			setLightSaber(0.0f);
		else
			setLightSaber(base);
		if(firstCraftingUpdate)
			setLightSaberIsSpecial(false);
	} else {
		if (value + base > 80.f)
			setLightSaber(80.0f);
		else
			setLightSaber(value + base);

		if(firstCraftingUpdate)
			setLightSaberIsSpecial(true);
	}
}

bool ArmorImplementation::isVunerableTo(String damagetype) {


	switch(armorStyle) {
	case COMPOSITE:
		if(damagetype == "restrain" || damagetype == "stun")
			return true;
		else
			return false;
		break;
	case BONE:
		if(damagetype == "restrain" || damagetype == "kinetic" || damagetype == "blast" ||
				damagetype == "stun" || damagetype == "heat" || damagetype == "cold" || damagetype == "acid")
			return true;
		else
			return false;
		break;
	}
	return false;
}

void ArmorImplementation::decay(float decayRate) {
	TangibleObjectImplementation::decay(decayRate);

	if (getMaxCondition() > 0) {
		float ratio = ((float) getConditionDamage()) / ((float) getMaxCondition());

		if (ratio > 0.99) {
			onBroken();
		} else if (ratio > 0.75) {
			setKinetic(getKinetic() * (1 - decayRate));
			setEnergy(getEnergy()* (1 - decayRate));
			setElectricity(getElectricity() * (1 - decayRate));
			setStun(getStun() * (1 - decayRate));
			setBlast(getBlast() * (1 - decayRate));
			setHeat(getHeat() * (1 - decayRate));
			setCold(getCold() * (1 - decayRate));
			setAcid(getAcid() * (1 - decayRate));
			setLightSaber(getLightSaber() * (1 - decayRate));
		}
	}
}

void ArmorImplementation::onBroken() {
	setRating(0);
	setMaxCondition(1);
	setConditionDamage(1);

	//Is this needed?
	itemAttributes->setCondition(0, 1);

	setKinetic(0.0f);
	setKineticIsSpecial(false);
	setEnergy(0.0f);
	setEnergyIsSpecial(false);
	setElectricity(0.0f);
	setElectricityIsSpecial(false);
	setStun(0.0f);
	setStunIsSpecial(false);
	setBlast(0.0f);
	setBlastIsSpecial(false);
	setHeat(0.0f);
	setHeatIsSpecial(false);
	setCold(0.0f);
	setColdIsSpecial(false);
	setAcid(0.0f);
	setAcidIsSpecial(false);
	setLightSaber(0.0f);
	setLightSaberIsSpecial(false);

	//TODO: Is this needed?
	//BaseMessage* tano3 = new TangibleObjectMessage3(_this);
	//player->sendMessage(tano3);
}


void ArmorImplementation::setArmorStats(int modifier) {

	int maxLevel = 120;

	if (modifier > maxLevel){
		int diff = System::random(modifier - maxLevel);
		modifier = maxLevel;
		modifier += diff;
	}

	int luck = (System::random(100)) + (modifier / 4);

	if (System::random(1000) == 7)
		luck = luck * 10;

	if (System::random(10000) == 777)
		luck = luck * 25;

	if (System::random(100) == 6)
		luck = 0;

	int playerRoll = System::random(1000) * modifier * luck / 1000;
	if (playerRoll > 200000) {
		modifier = modifier + 100;
		luck = luck + 100;

		StringBuffer itemText;
		itemText << "\\#ffff00" << customName.toString() << " (Legendary)";
		customName = UnicodeString(itemText.toString());
	} else if (playerRoll > 55000) {
		modifier = modifier + 50;
		luck = luck + 50;

		StringBuffer itemText;
		itemText << "\\#ffff00" << customName.toString() << " (Exceptional)";
		customName = UnicodeString(itemText.toString());
	} else if (playerRoll > 12500) {
		modifier = modifier + 10;
		luck = luck + 20;

		StringBuffer itemText;
		itemText << "\\#ffff00" << customName.toString();
		customName = UnicodeString(itemText.toString());
	}

	maxCondition = 25000 + (luck * System::random(luck));
	setCondition(maxCondition, maxCondition);

	if ((luck * System::random(100)) > 2000) {
		setHealthEncumbrance(healthEncumbrance - (healthEncumbrance * luck / 357));
		setActionEncumbrance(actionEncumbrance - (actionEncumbrance * luck / 357));
		setMindEncumbrance(mindEncumbrance - (mindEncumbrance * luck / 357));
	}

	if ((luck * System::random(100)) > 2000) {
		float resistMod = (luck / 367.43f);

		setKinetic(kinetic + (kinetic * resistMod));
		setEnergy(energy + (energy * resistMod));
		setElectricity(electricity + (electricity * resistMod));
		setBlast(blast + (blast * resistMod));
		setHeat(heat + (heat * resistMod));
		setCold(cold + (cold * resistMod));
		setAcid(acid + (acid * resistMod));
	}

	/*if (playerRoll > 45000 && System::random(3) == 1) {
		skillMod0Type = System::random(28) + 1;
		skillMod0Value = luck / (System::random(3) + 9);
	}
	if (playerRoll > 75000 && System::random(2) == 1) {
		skillMod1Type = System::random(28) + 1;
		skillMod1Value = luck / (System::random(3) + 9);
	}
	if (playerRoll > 125000) {
		skillMod2Type = System::random(28) + 1;
		skillMod2Value = luck / (System::random(3) + 9);
	}*/

	if (playerRoll > 20000 && System::random(3) == 1) {
		setStun(stun + System::random(9) + 1);
		setStunIsSpecial(System::random(1));
	}

	if (System::random(1))
		setKineticIsSpecial(true);
	if (System::random(1))
		setEnergyIsSpecial(true);
	if (System::random(1))
		setElectricityIsSpecial(true);
	if (System::random(1))
		setBlastIsSpecial(true);
	if (System::random(1))
		setHeatIsSpecial(true);
	if (System::random(1))
		setColdIsSpecial(true);
	if (System::random(1))
		setAcidIsSpecial(true);

	if (kinetic > 87.0f)
		setKinetic(87.0f);

	if (energy > 87.0f)
		setEnergy(87.0f);

	if (electricity > 87.0f)
		setElectricity(87.0f);

	if (blast > 87.0f)
		setBlast(87.0f);

	if (heat > 87.0f)
		setHeat(87.0f);

	if (cold > 87.0f)
		setCold(87.0f);

	if (acid > 87.0f)
		setAcid(87.0f);

	if (healthEncumbrance < 0)
		setHealthEncumbrance(0);

	if (actionEncumbrance < 0)
		setActionEncumbrance(0);

	if (mindEncumbrance < 0)
		setMindEncumbrance(0);

	/*if (skillMod0Value > 25)
		skillMod0Value = 25;

	if (skillMod1Value > 25)
		skillMod1Value = 25;

	if (skillMod2Value > 25)
		skillMod2Value = 25;

	if (skillMod2Type == skillMod1Type || skillMod2Type == skillMod0Type) {
		skillMod2Type = 0;
		skillMod2Value = 0;
	}

	if (skillMod1Type == skillMod0Type || skillMod1Type == skillMod2Type) {
		skillMod1Type = 0;
		skillMod1Value = 0;
	}*/
}

void ArmorImplementation::setSocket(int index, int type, int value) {
	switch (index) {
	case 0:
		setSocket0Value(value);
		setSocket0Type(type);
		break;
	case 1:
		setSocket1Value(value);
		setSocket1Type(type);
		break;
	case 2:
		setSocket2Value(value);
		setSocket2Type(type);
		break;
	case 3:
		setSocket3Value(value);
		setSocket3Type(type);
		break;
	}
}

void ArmorImplementation::setSocketValue(int index, int value) {
	switch (index) {
	case 0:
		setSocket0Value(value);
		break;
	case 1:
		setSocket1Value(value);
		break;
	case 2:
		setSocket2Value(value);
		break;
	case 3:
		setSocket3Value(value);
		break;
	}
}

void ArmorImplementation::setSocketType(int index, int type) {
	switch (index) {
	case 0:
		setSocket0Type(type);
		break;
	case 1:
		setSocket1Type(type);
		break;
	case 2:
		setSocket2Type(type);
		break;
	case 3:
		setSocket3Type(type);
		break;
	}
}

int ArmorImplementation::getSocketType(int index) {
	switch (index) {
	case 0:
		return socket0Type;
		break;
	case 1:
		return socket1Type;
		break;
	case 2:
		return socket2Type;
		break;
	case 3:
		return socket3Type;
		break;
	}
	return -1;
}

int ArmorImplementation::getSocketValue(int index) {
	switch (index) {
	case 0:
		return socket0Value;
		break;
	case 1:
		return socket1Value;
		break;
	case 2:
		return socket2Value;
		break;
	case 3:
		return socket3Value;
		break;
	}
	return 0;
}

int ArmorImplementation::addSkillMod(int skillModType, int skillModValue) {

	if (skillModType == 0 || skillModValue == 0) {
		return -1;
	}

	int i = 0;

	for (; i < 4; i++) {
		if (getSocketType(i) == skillModType) {
			int modValue = getSocketValue(i);

			if (skillModValue <= modValue)
				return -2;
			else if (skillModValue > modValue){
				setSocketValue(i, skillModValue);
				updated = true;
				return -3;
			}
		}
	}

	if (sockets > 0)
		for (i = 0; i < 4; i++)
			if (getSocketValue(i) == 0) {
				setSocket(i, skillModType, skillModValue);
				updated = true;
				setSockets(sockets - 1);
				return i;
			}

	return -1;
}

void ArmorImplementation::addAttributes(AttributeListMessage* alm) {
	StringBuffer conditionStr;
	conditionStr << getCondition() << '/' << maxCondition;
	alm->insertAttribute("Condition", conditionStr);

	alm->insertAttribute("Volume", "1");

	if(sockets > 0)
		alm->insertAttribute("Sockets", sockets);

	if (skillMod0Type != 0)
		generateSkillMods(alm, skillMod0Type, skillMod0Value);

	if (skillMod1Type != 0)
		generateSkillMods(alm, skillMod1Type, skillMod1Value);

	if (skillMod2Type != 0)
		generateSkillMods(alm, skillMod2Type, skillMod2Value);

	if (socket0Type != 0)
		generateSkillMods(alm, socket0Type, socket0Value);

	if (socket1Type != 0)
		generateSkillMods(alm, socket1Type, socket1Value);

	if (socket2Type != 0)
		generateSkillMods(alm, socket2Type, socket2Value);

	if (socket3Type != 0)
		generateSkillMods(alm, socket3Type, socket3Value);

	//Armor Rating
	if (rating == LIGHT)
		alm->insertAttribute("armorrating", "Light");
	else if (rating == MEDIUM)
		alm->insertAttribute("armorrating", "Medium");
	else if (rating == HEAVY)
		alm->insertAttribute("armorrating", "Heavy");

	//Check for special protections
	if (kineticIsSpecial && kinetic >= 0.5) {
		StringBuffer txt;
		txt << round(kinetic) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_kinetic", txt.toString());
	}
	if (energyIsSpecial && energy >= 0.5) {
		StringBuffer txt;
		txt << round(energy) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_energy", txt.toString());
	}
	if (electricityIsSpecial && electricity >= 0.5) {
		StringBuffer txt;
		txt << round(electricity) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_electrical", txt.toString());
	}
	if (stunIsSpecial && stun >= 0.5) {
		StringBuffer txt;
		txt << round(stun) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_stun", txt.toString());
	}
	if (blastIsSpecial && blast >= 0.5) {
		StringBuffer txt;
		txt << round(blast) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_blast", txt.toString());
	}
	if (heatIsSpecial && heat >= 0.5) {
		StringBuffer txt;
		txt << round(heat) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_heat", txt.toString());
	}
	if (coldIsSpecial && cold >= 0.5) {
		StringBuffer txt;
		txt << round(cold) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_cold", txt.toString());
	}
	if (acidIsSpecial && acid >= 0.5) {
		StringBuffer txt;
		txt << round(acid) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_acid", txt.toString());
	}
	if (lightSaberIsSpecial && lightSaberIsSpecial >= 0.5) {
		StringBuffer txt;
		txt << round(lightSaber) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_restraint", txt.toString());
	}
	//Check for Effectiveness protections(Normal)
	if (!kineticIsSpecial && kinetic >= 0.5) {
		StringBuffer txt;
		txt << round(kinetic) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_kinetic", txt.toString());
	}
	if (!energyIsSpecial && energy >= 0.5) {
		StringBuffer txt;
		txt << round(energy) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_energy", txt.toString());
	}
	if (!electricityIsSpecial && electricity >= 0.5) {
		StringBuffer txt;
		txt << round(electricity) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_electrical", txt.toString());
	}
	if (!stunIsSpecial && stun >= 0.5) {
		StringBuffer txt;
		txt << round(stun) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_stun", txt.toString());
	}
	if (!blastIsSpecial && blast >= 0.5) {
		StringBuffer txt;
		txt << round(blast) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_blast", txt.toString());
	}
	if (!heatIsSpecial && heat >= 0.5) {
		StringBuffer txt;
		txt << round(heat) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_heat", txt.toString());
	}
	if (!coldIsSpecial && cold >= 0.5) {
		StringBuffer txt;
		txt << round(cold) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_cold", txt.toString());
	}
	if (!acidIsSpecial && acid >= 0.5) {
		StringBuffer txt;
		txt << round(acid) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_acid", txt.toString());
	}
	if (!lightSaberIsSpecial && lightSaber >= 0.5) {
		StringBuffer txt;
		txt << round(lightSaber) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_restraint", txt.toString());
	}

	//Vulnerabilities
	if (kinetic < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_kinetic", "-");

	if (energy < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_energy", "-");

	if (electricity < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_electrical", "-");

	if (stun < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_stun", "-");

	if (blast < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_blast", "-");

	if (heat < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_heat", "-");

	if (cold < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_cold", "-");

	if (acid < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_acid", "-");

	if (lightSaber < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_restraint", "-");

	//Encumbrances
	alm->insertAttribute("cat_armor_encumbrance.health", healthEncumbrance);

	alm->insertAttribute("cat_armor_encumbrance.action", actionEncumbrance);

	alm->insertAttribute("cat_armor_encumbrance.mind", mindEncumbrance);

	if (craftersName != "") {

		alm->insertAttribute("crafter", craftersName);
	}
	if (craftedSerial != "") {

		alm->insertAttribute("serial_number", craftedSerial);
	}


	if (sliced == 1)
		alm->insertAttribute("hacked", "");

}

//Event Handlers
/**
 * This event occurs following a successful encumbrance slice.
 * \param slicer The Player doing the slicing.
 * \param percentage The percentage increase.
 */
void ArmorImplementation::onEncumbranceSliced(Player* slicer, uint8 percentage) {
	StfParameter* params = new StfParameter();
	params->addDI(percentage);
	slicer->sendSystemMessage("slicing/slicing", "enc_mod", params); //You have successfully reduced the encumberance of the armor by %DI%!
	delete params;
}

/**
 * This event occurs following a successful effectiveness slice.
 * \param slicer The Player doing the slicing.
 * \param percentage The percentage increase.
 */
void ArmorImplementation::onEffectivenessSliced(Player* slicer, uint8 percentage) {
	StfParameter* params = new StfParameter();
	params->addDI(percentage);
	slicer->sendSystemMessage("slicing/slicing", "eff_mod", params); //You have successfully increased the base effectiveness of the armor by %DI%!
	delete params;
}

/**
 * This event occurs when a slicing attempt has gone awry.
 * \param slicer The player doing the slicing.
 */
void ArmorImplementation::onSlicingFailure(Player* slicer) {
	slicer->sendSystemMessage("slicing/slicing", "fail_armor"); //You've made a critical mistake modifying the armor's basic systems. The damage is extensive and while the armor still retains its previous effectiveness, no one will be able to modify it in the future.
	setSliced(true);
}

//Actions
/**
 * Slices the item.
 * \param slicer The player slicing the item.
 */
void ArmorImplementation::slice(Player* slicer) {
	uint8 sliceType = System::random(1);

	int sliceSkill = slicer->getSlicingAbility();
	uint8 min = 0;
	uint8 max = 0;

	//sliceType 0 = effectiveness
	//sliceType 1 = encumbrance

	//Cases fall through compounding upon each other.
	switch (sliceSkill) {
	case 5:
		min += (sliceType == 0) ? 6 : 5;
		max += (sliceType == 0) ? 5 : 5;
	case 4:
		min += (sliceType == 0) ? 0 : 10;
		max += (sliceType == 0) ? 10 : 10;
	case 3:
		min += (sliceType == 0) ? 5 : 5;
		max += (sliceType == 0) ? 20 : 30;
		break;
	default:
		return;
	}

	uint8 percentage = System::random(max - min) + min;

	try {
		wlock();

		switch (sliceType) {
		case 0:
			sliceEffectiveness(slicer, percentage);
			break;
		case 1:
			sliceEncumbrance(slicer, percentage);
			break;
		}

		generateAttributes(slicer);

		unlock();
	} catch (...) {
		unlock();
	}
}

/**
 * Slices the armor, decreasing encumbrance.
 * \param slicer The player doing the slicing.
 * \param percentage What percentage increase will take effect.
 */
void ArmorImplementation::sliceEncumbrance(Player* slicer, uint8 percentage){
	if (isSliced())
		return;

	setHealthEncumbrance(healthEncumbrance - (healthEncumbrance * percentage / 100));
	setActionEncumbrance(actionEncumbrance - (actionEncumbrance * percentage / 100));
	setMindEncumbrance(mindEncumbrance - (mindEncumbrance * percentage / 100));

	setSliced(true);
	updated = true;

	onEncumbranceSliced(slicer, percentage);
}

/**
 * Slices the armor, increasing effectiveness.
 * \param slicer The player doing the slicing.
 * \param percentage What percentage increase will take effect.
 */
void ArmorImplementation::sliceEffectiveness(Player* slicer, uint8 percentage){
	if (sliced)
		return;

	if (!kineticIsSpecial) {
		setKinetic(kinetic + (kinetic * percentage / 100));
		if (kinetic > 90.0f)
			setKinetic(90.0f);
	}

	if (!energyIsSpecial) {
		setEnergy(energy + (energy * percentage / 100));
		if (energy > 90.0f)
			setEnergy(90.0f);
	}
	if (!electricityIsSpecial) {
		setElectricity(electricity + (electricity * percentage / 100));
		if (electricity > 90.0f)
			setElectricity(90.0f);
	}
	if (!stunIsSpecial) {
		setStun(stun + (stun * percentage / 100));
		if (stun > 90.0f)
			setStun(90.0f);
	}
	if (!blastIsSpecial) {
		setBlast(blast + (blast * percentage / 100));
		if (blast > 90.0f)
			setBlast(90.0f);
	}
	if (!heatIsSpecial) {
		setHeat(heat + (heat * percentage / 100));
		if (heat > 90.0f)
			setHeat(90.0f);
	}
	if (!coldIsSpecial) {
		setCold(cold + (cold * percentage / 100));
		if (cold > 90.0f)
			setCold(90.0f);
	}
	if (!acidIsSpecial) {
		setAcid(acid + (acid * percentage / 100));
		if (acid > 90.0f)
			setAcid(90.0f);
	}
	if (!lightSaberIsSpecial) {
		setLightSaber(lightSaber + (lightSaber * percentage / 100));
		if (lightSaber > 90.0f)
			setLightSaber(90.0f);
	}

	setSliced(true);
	updated = true;

	onEffectivenessSliced(slicer, percentage);
}

