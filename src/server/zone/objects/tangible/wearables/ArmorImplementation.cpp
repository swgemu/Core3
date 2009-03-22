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

ArmorImplementation::ArmorImplementation(uint64 objid, uint32 tempCRC,
		const UnicodeString& n, const String& tempn, bool eqp) :
	ArmorServant(objid, tempCRC, n, tempn, eqp) {
	init();
}

ArmorImplementation::ArmorImplementation(CreatureObject* creature,
		uint32 tempCRC, const UnicodeString& n, const String& tempn, bool eqp) :
	ArmorServant(creature, tempCRC, n, tempn, eqp) {

	//objectCRC = String::hashCode(temp);
	customName = n;
	stfName = tempn;

	init();
}

void ArmorImplementation::parseItemAttributes() {

	WearableImplementation::parseItemAttributes();

	String name = "rating";
	rating = itemAttributes->getIntAttribute(name);

	name = "armorPiece";
	armorPiece = itemAttributes->getIntAttribute(name);

	name = "armorStyle";
	armorStyle = itemAttributes->getIntAttribute(name);

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

	name = "sliced";
	sliced = itemAttributes->getBooleanAttribute(name);

	String temp;

	StringTokenizer specialtokenizer(itemAttributes->getStringAttribute("specialprotection"));
	specialtokenizer.setDelimeter(";");

	while(specialtokenizer.hasMoreTokens()) {
		specialtokenizer.getStringToken(temp);
		setSpecial(temp);
	}

	StringTokenizer vunerabilitytokenizer(itemAttributes->getStringAttribute("vunerability"));
	vunerabilitytokenizer.setDelimeter(";");

	while(vunerabilitytokenizer.hasMoreTokens()) {
		vunerabilitytokenizer.getStringToken(temp);
		setVunerable(temp);

	}
	wearableType = WearableImplementation::WEARABLEARMOR;
}

void ArmorImplementation::init() {
	objectSubType = ARMOR;

	setRating(LIGHT);
	setConditionDamage(0);
	setCondition(5000, 5000);

	setMaxSockets(0);

	firstCraftingUpdate = true;

	setHealthEncumbrance(100);
	setActionEncumbrance(100);
	setMindEncumbrance(100);

	setKinetic(0.0f);
	setEnergy(0.0f);
	setElectricity(0.0f);
	setStun(0.0f);
	setBlast(0.0f);
	setHeat(0.0f);
	setCold(0.0f);
	setAcid(0.0f);
	setLightSaber(0.0f);

	armorPiece = 0;

	slicable = true;

	customizationVariables.setVariable(3, 0);
	customizationVariables.setVariable(2, 0);
	customizationVariables.setVariable(1, 0);

	StringBuffer loggingname;
	loggingname << "Armor = 0x" << objectID;
	setLoggingName(loggingname.toString());

	setVunerable("restraineffectiveness");

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

void ArmorImplementation::sendRadialResponseTo(Player* player,
		ObjectMenuResponse* omr) {
	if (player->getInventoryItem(getObjectID()) != NULL) {

		if (!isSliced() && player->getSlicingAbility() >= 3)
			omr->addRadialParent(69, 3, "@slicing:slice");

		if (getConditionDamage() > 0)
			omr->addRadialParent(70, 3, "@sui:repair");
	}

	//TODO:Cell permission check
	if (_this->getParent() != NULL) {
		bool cellPermission = true;

		if (_this->getParent()->isCell() && cellPermission) {
			omr->addRadialParent(10, 3, "@ui_radial:item_pickup");
		}
	}

	omr->finish();
	player->sendMessage(omr);
}

void ArmorImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;

	AttributeListMessage* alm =
			new AttributeListMessage((TangibleObject*) _this);

	addAttributes(alm);

	player->sendMessage(alm);

}

void ArmorImplementation::updateCraftingValues(DraftSchematic* draftSchematic) {
	/*
	 * Incoming Values:					Ranges:
	 * sockets							All depend on type of armor
	 * hit_points
	 * armor_effectiveness
	 * armor_integrity
	 * armor_health_encumbrance
	 * armor_action_encumbrance
	 * armor_mind_encumbrance
	 * armor_rating
	 * armor_special_type
	 * armor_special_effectiveness
	 * armor_special_integrity
	 */
	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	if (firstCraftingUpdate) {
		generateSockets(draftSchematic);
		calculateSpecalProtection(draftSchematic);
	}

	setRating((int) craftingValues->getCurrentValue("armor_rating"));

	setHealthEncumbrance((int) craftingValues->getCurrentValue(
			"armor_health_encumbrance"));
	setActionEncumbrance((int) craftingValues->getCurrentValue(
			"armor_action_encumbrance"));
	setMindEncumbrance((int) craftingValues->getCurrentValue(
			"armor_mind_encumbrance"));

	float base = craftingValues->getCurrentValue("armor_effectiveness");

	setProtection(draftSchematic, "kineticeffectiveness", base);
	setProtection(draftSchematic, "energyeffectiveness", base);
	setProtection(draftSchematic, "electricaleffectiveness", base);
	setProtection(draftSchematic, "stuneffectiveness", base);
	setProtection(draftSchematic, "blasteffectiveness", base);
	setProtection(draftSchematic, "heateffectiveness", base);
	setProtection(draftSchematic, "coldeffectiveness", base);
	setProtection(draftSchematic, "acideffectiveness", base);
	setProtection(draftSchematic, "restraineffectiveness", base);

	setCondition((int) craftingValues->getCurrentValue("armor_integrity"),
			(int) craftingValues->getCurrentValue("armor_integrity"));

	firstCraftingUpdate = false;
}

void ArmorImplementation::calculateSpecalProtection(
		DraftSchematic* draftSchematic) {

	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	float base = craftingValues->getCurrentValue("armor_effectiveness");
	float value, min, max, currentValue;
	String title = "exp_resistance";
	String subtitle;
	//float min = craftingValues->getMinValue("armor_effectiveness");
	//float max = craftingValues->getMaxValue("armor_effectiveness");
	float currentPercentage = craftingValues->getCurrentPercentage(
			"armor_effectiveness");
	float maxPercentage = craftingValues->getMaxPercentage(
			"armor_effectiveness");
	int precision = craftingValues->getPrecision("armor_effectiveness");

	for (int i = 0; i < specialResistsVector.size(); ++i) {
		subtitle = specialResistsVector.get(i);

		value = craftingValues->getCurrentValue(subtitle);
		min = 2;
		max = (value - min + (min * currentPercentage)) / currentPercentage;
		currentValue = (currentPercentage * (max - min)) + min;

		craftingValues->addExperimentalProperty(title, subtitle, min, max,
				precision, false);
		craftingValues->setMaxPercentage(subtitle, maxPercentage);
		craftingValues->setCurrentPercentage(subtitle, currentPercentage);
		craftingValues->setCurrentValue(subtitle, currentValue);
	}
}

void ArmorImplementation::setProtection(DraftSchematic* draftSchematic,
		String type, float base) {

	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	float value = craftingValues->getCurrentValue(type);

	if (value == DraftSchematicValuesImplementation::VALUENOTFOUND
			&& firstCraftingUpdate) {
		craftingValues->lockValue(type);
	}

	if (value == DraftSchematicValuesImplementation::VALUENOTFOUND) {
		if (isVunerable(type))
			setProtectionValue(type, 0.0f);
		else
			setProtectionValue(type, base);
	} else {
		if (value + base > 80.0f)
			setProtectionValue(type, 80.0f);
		else
			setProtectionValue(type, value + base);
	}
}

void ArmorImplementation::setProtectionValue(String type, float value) {

	if (type == "kineticeffectiveness") {
		setKinetic(value);
	} else if (type == "energyeffectiveness") {
		setEnergy(value);
	} else if (type == "electricaleffectiveness") {
		setElectricity(value);
	} else if (type == "stuneffectiveness") {
		setStun(value);
	} else if (type == "blasteffectiveness") {
		setBlast(value);
	} else if (type == "heateffectiveness") {
		setHeat(value);
	} else if (type == "coldeffectiveness") {
		setCold(value);
	} else if (type == "acideffectiveness") {
		setAcid(value);
	} else if (type == "restraineffectiveness") {
		setLightSaber(value);
	}

}

void ArmorImplementation::decay(float decayRate) {
	TangibleObjectImplementation::decay(decayRate);

	if (getMaxCondition() > 0) {
		float ratio = ((float) getConditionDamage())
				/ ((float) getMaxCondition());

		if (ratio > 0.99) {
			onBroken();
		} else if (ratio > 0.75) {
			setKinetic(getKinetic() * (1 - decayRate));
			setEnergy(getEnergy() * (1 - decayRate));
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
	setEnergy(0.0f);
	setElectricity(0.0f);
	setStun(0.0f);
	setBlast(0.0f);
	setHeat(0.0f);
	setCold(0.0f);
	setAcid(0.0f);
	setLightSaber(0.0f);

	//TODO: Is this needed?
	//BaseMessage* tano3 = new TangibleObjectMessage3(_this);
	//player->sendMessage(tano3);
}

void ArmorImplementation::setArmorStats(int modifier) {

	int maxLevel = 120;

	if (modifier > maxLevel) {
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
		setHealthEncumbrance(healthEncumbrance - (healthEncumbrance * luck
				/ 357));
		setActionEncumbrance(actionEncumbrance - (actionEncumbrance * luck
				/ 357));
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
		if (System::random(1))
			specialResistsVector.add("stuneffectiveness");
	}

	if (System::random(1))
		specialResistsVector.add("kineticeffectiveness");
	if (System::random(1))
		specialResistsVector.add("energyeffectiveness");
	if (System::random(1))
		specialResistsVector.add("electricaleffectiveness");
	if (System::random(1))
		specialResistsVector.add("blasteffectiveness");
	if (System::random(1))
		specialResistsVector.add("heateffectiveness");
	if (System::random(1))
		specialResistsVector.add("coldeffectiveness");
	if (System::random(1))
		specialResistsVector.add("acideffectiveness");

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

}

void ArmorImplementation::addAttributes(AttributeListMessage* alm) {
	StringBuffer conditionStr;
	conditionStr << getCondition() << '/' << maxCondition;
	alm->insertAttribute("Condition", conditionStr);

	alm->insertAttribute("Volume", "1");

	if (sockets > 0)
		alm->insertAttribute("Sockets", socketsLeft());

	insertStatMods(alm);

	//Armor Rating
	if (rating == LIGHT)
		alm->insertAttribute("armorrating", "Light");
	else if (rating == MEDIUM)
		alm->insertAttribute("armorrating", "Medium");
	else if (rating == HEAVY)
		alm->insertAttribute("armorrating", "Heavy");

	//Check for special protections
	if (isSpecial("kineticeffectiveness") && kinetic >= 0.5) {
		StringBuffer txt;
		txt << round(kinetic) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_kinetic",
				txt.toString());
	}
	if (isSpecial("energyeffectiveness") && energy >= 0.5) {
		StringBuffer txt;
		txt << round(energy) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_energy",
				txt.toString());
	}
	if (isSpecial("electricityeffectiveness") && electricity >= 0.5) {
		StringBuffer txt;
		txt << round(electricity) << "%";
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_electrical",
				txt.toString());
	}
	if (isSpecial("stuneffectiveness") && stun >= 0.5) {
		StringBuffer txt;
		txt << round(stun) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_stun",
				txt.toString());
	}
	if (isSpecial("blasteffectiveness") && blast >= 0.5) {
		StringBuffer txt;
		txt << round(blast) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_blast",
				txt.toString());
	}
	if (isSpecial("heateffectiveness") && heat >= 0.5) {
		StringBuffer txt;
		txt << round(heat) << "%";
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_heat",
				txt.toString());
	}
	if (isSpecial("coldeffectiveness") && cold >= 0.5) {
		StringBuffer txt;
		txt << round(cold) << "%";
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_cold",
				txt.toString());
	}
	if (isSpecial("acideffectiveness") && acid >= 0.5) {
		StringBuffer txt;
		txt << round(acid) << "%";
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_elemental_acid",
				txt.toString());
	}
	if (isSpecial("restraineffectiveness") && lightSaber >= 0.5) {
		StringBuffer txt;
		txt << round(lightSaber) << "%";
		alm->insertAttribute(
				"cat_armor_special_protection.armor_eff_restraint",
				txt.toString());
	}
	//Check for Effectiveness protections(Normal)
	if (!isSpecial("kineticeffectiveness") && kinetic >= 0.5) {
		StringBuffer txt;
		txt << round(kinetic) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_kinetic",
				txt.toString());
	}
	if (!isSpecial("energyeffectiveness") && energy >= 0.5) {
		StringBuffer txt;
		txt << round(energy) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_energy",
				txt.toString());
	}
	if (!isSpecial("electricityeffectiveness") && electricity >= 0.5) {
		StringBuffer txt;
		txt << round(electricity) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_electrical",
				txt.toString());
	}
	if (!isSpecial("stuneffectiveness") && stun >= 0.5) {
		StringBuffer txt;
		txt << round(stun) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_stun",
				txt.toString());
	}
	if (!isSpecial("blasteffectiveness") && blast >= 0.5) {
		StringBuffer txt;
		txt << round(blast) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_blast",
				txt.toString());
	}
	if (!isSpecial("heateffectiveness") && heat >= 0.5) {
		StringBuffer txt;
		txt << round(heat) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_heat",
				txt.toString());
	}
	if (!isSpecial("coldeffectiveness") && cold >= 0.5) {
		StringBuffer txt;
		txt << round(cold) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_cold",
				txt.toString());
	}
	if (!isSpecial("acideffectiveness") && acid >= 0.5) {
		StringBuffer txt;
		txt << round(acid) << "%";
		alm->insertAttribute(
				"cat_armor_effectiveness.armor_eff_elemental_acid",
				txt.toString());
	}
	if (!isSpecial("restraineffectiveness") && lightSaber >= 0.5) {
		StringBuffer txt;
		txt << round(lightSaber) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_restraint",
				txt.toString());
	}

	//Vulnerabilities
	if (kinetic < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_kinetic", "-");

	if (energy < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_energy", "-");

	if (electricity < 0.5)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_electrical", "-");

	if (stun < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_stun", "-");

	if (blast < 0.5)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_blast", "-");

	if (heat < 0.5)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_heat", "-");

	if (cold < 0.5)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_cold", "-");

	if (acid < 0.5)
		alm->insertAttribute(
				"cat_armor_vulnerability.armor_eff_elemental_acid", "-");

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
void ArmorImplementation::onEffectivenessSliced(Player* slicer,
		uint8 percentage) {
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
void ArmorImplementation::sliceEncumbrance(Player* slicer, uint8 percentage) {
	if (isSliced())
		return;

	setHealthEncumbrance(healthEncumbrance - (healthEncumbrance * percentage
			/ 100));
	setActionEncumbrance(actionEncumbrance - (actionEncumbrance * percentage
			/ 100));
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
void ArmorImplementation::sliceEffectiveness(Player* slicer, uint8 percentage) {
	if (sliced)
		return;

	if (!isSpecial("kineticeffectiveness")) {
		setKinetic(kinetic + (kinetic * percentage / 100));
		if (kinetic > 90.0f)
			setKinetic(90.0f);
	}

	if (!isSpecial("energyeffectiveness")) {
		setEnergy(energy + (energy * percentage / 100));
		if (energy > 90.0f)
			setEnergy(90.0f);
	}
	if (!isSpecial("electricityeffectiveness")) {
		setElectricity(electricity + (electricity * percentage / 100));
		if (electricity > 90.0f)
			setElectricity(90.0f);
	}
	if (!isSpecial("stuneffectiveness")) {
		setStun(stun + (stun * percentage / 100));
		if (stun > 90.0f)
			setStun(90.0f);
	}
	if (!isSpecial("blasteffectiveness")) {
		setBlast(blast + (blast * percentage / 100));
		if (blast > 90.0f)
			setBlast(90.0f);
	}
	if (!isSpecial("heateffectiveness")) {
		setHeat(heat + (heat * percentage / 100));
		if (heat > 90.0f)
			setHeat(90.0f);
	}
	if (!isSpecial("coldeffectiveness")) {
		setCold(cold + (cold * percentage / 100));
		if (cold > 90.0f)
			setCold(90.0f);
	}
	if (!isSpecial("acideffectiveness")) {
		setAcid(acid + (acid * percentage / 100));
		if (acid > 90.0f)
			setAcid(90.0f);
	}
	if (!isSpecial("restraineffectiveness")) {
		setLightSaber(lightSaber + (lightSaber * percentage / 100));
		if (lightSaber > 90.0f)
			setLightSaber(90.0f);
	}

	setSliced(true);
	updated = true;

	onEffectivenessSliced(slicer, percentage);
}

void ArmorImplementation::onEquip(Player* player) {

	WearableImplementation::onEquip(player);

	player->setArmorEncumbrance(_this, false);

}
void ArmorImplementation::onUnequip(Player* player) {

	WearableImplementation::onUnequip(player);

	player->unsetArmorEncumbrance(_this);
}
