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

#include "../../../objects/draftschematic/DraftSchematicValuesImplementation.h"

#include "WeaponImplementation.h"

WeaponImplementation::WeaponImplementation(uint64 objid, uint32 tempCRC, const UnicodeString& n, const String& tempn, bool eqp, int tp, int cat)
		: WeaponSkillModMap(), WeaponServant(objid, tempCRC, n, tempn, WEAPON) {
	type = tp;
	setCategory(cat);

	equipped = eqp;

	init();
}

WeaponImplementation::WeaponImplementation(CreatureObject* creature, const String& temp, const UnicodeString& n, const String& tempn, bool eqp, int tp, int cat)
		: WeaponSkillModMap(), WeaponServant(creature->getNewItemID(), WEAPON) {
	objectCRC = temp.hashCode();

	customName = n;

	type = tp;
	setCategory(cat);

	stfName = tempn;

	if ((equipped = eqp))
		setParent(creature, 0x04);
	else
		setParent(creature->getInventory(), 0xFFFFFFFF);

	init();
}

void WeaponImplementation::init() {
	stfFile = "weapon_name";
	cert = "";
	certified = true;

	unknownByte = 0;

	usesRemaining = -1;

	setMaxCondition(750);
	setConditionDamage(0);

	setDamageType(KINETIC);
	setMinDamage(50);
	setMaxDamage(100);

	setAttackSpeed(1.0f);

	setHealthAttackCost(15);
	setActionAttackCost(10);
	setMindAttackCost(5);
	setForceCost(0);

	setPointBlankRange(0);
	setPointBlankAccuracy(0);

	setIdealRange(2);
	setIdealAccuracy(15);

	setMaxRange(5);
	setMaxRangeAccuracy(0);

	setArea(0.0f);

	setWoundsRatio(10);

	setArmorPiercing(NONE);

	powerupUses = 0;

	bonusMinDamage = 0;
	bonusMaxDamage = 0;
	bonusAttackSpeed = 0;
	bonusHealthAttackCost = 0;
	bonusActionAttackCost = 0;
	bonusMindAttackCost = 0;
	bonusPointBlankRange = 0;
	bonusPointBlankAccuracy = 0;
	bonusIdealRange = 0;
	bonusIdealAccuracy = 0;
	bonusMaxRange = 0;
	bonusMaxRangeAccuracy = 0;
	bonusWoundsRatio = 0;

	slicable = true;

	StringBuffer loggingname;
	loggingname << "Weapon = 0x" << objectID;
	setLoggingName(loggingname.toString());
	setXpType();

	setLogging(false);
	setGlobalLogging(true);
}

void WeaponImplementation::parseItemAttributes() {

	maxCondition = itemAttributes->getMaxCondition();
	conditionDamage = maxCondition - itemAttributes->getCurrentCondition();

	String name = "type";
	type = itemAttributes->getIntAttribute(name);

	name = "category";
	category = itemAttributes->getIntAttribute(name);

	name = "usesRemaining";
	usesRemaining = itemAttributes->getIntAttribute(name);

	name = "damageType";
	damageType = itemAttributes->getIntAttribute(name);

	name = "attackSpeed";
	attackSpeed = itemAttributes->getFloatAttribute(name);

	name = "healthCost";
	healthAttackCost = itemAttributes->getIntAttribute(name);
	name = "actionCost";
	actionAttackCost = itemAttributes->getIntAttribute(name);
	name = "mindCost";
	mindAttackCost = itemAttributes->getIntAttribute(name);
	name = "forceCost";
	forceCost = itemAttributes->getIntAttribute(name);

	name = "minDamage";
	minDamage = itemAttributes->getFloatAttribute(name);
	name = "maxDamage";
	maxDamage = itemAttributes->getFloatAttribute(name);

	name = "pointBlankRange";
	pointBlankRange = itemAttributes->getIntAttribute(name);
	name = "pointBlankAccuracy";
	pointBlankAccuracy = itemAttributes->getIntAttribute(name);

	name = "idealRange";
	idealRange = itemAttributes->getIntAttribute(name);
	name = "idealAccuracy";
	idealAccuracy = itemAttributes->getIntAttribute(name);

	name = "maxRange";
	maxRange = itemAttributes->getIntAttribute(name);
	name = "maxRangeAccuracy";
	maxRangeAccuracy = itemAttributes->getIntAttribute(name);

	name = "woundsRatio";
	woundsRatio = itemAttributes->getFloatAttribute(name);

	name = "powerupUses";
	powerupUses = itemAttributes->getIntAttribute(name);

	name = "bonusAttackSpeed";
	bonusAttackSpeed = itemAttributes->getFloatAttribute(name);

	name = "bonusHealthAttackCost";
	bonusHealthAttackCost = itemAttributes->getIntAttribute(name);
	name = "bonusActionAttackCost";
	bonusActionAttackCost = itemAttributes->getIntAttribute(name);
	name = "bonusMindAttackCost";
	bonusMindAttackCost = itemAttributes->getIntAttribute(name);

	name = "bonusMinDamage";
	bonusMinDamage = itemAttributes->getFloatAttribute(name);
	name = "bonusMaxDamage";
	bonusMaxDamage = itemAttributes->getFloatAttribute(name);

	name = "bonusPointBlankRange";
	bonusPointBlankRange = itemAttributes->getIntAttribute(name);
	name = "bonusPointBlankAccuracy";
	bonusPointBlankAccuracy = itemAttributes->getIntAttribute(name);

	name = "bonusIdealRange";
	bonusIdealRange = itemAttributes->getIntAttribute(name);
	name = "bonusIdealAccuracy";
	bonusIdealAccuracy = itemAttributes->getIntAttribute(name);

	name = "bonusMaxRange";
	bonusMaxRange = itemAttributes->getIntAttribute(name);

	name = "bonusMaxRangeAccuracy";
	bonusMaxRangeAccuracy = itemAttributes->getIntAttribute(name);

	name = "bonusWoundsRatio";
	bonusWoundsRatio = itemAttributes->getFloatAttribute(name);

	name = "cert";
	cert = itemAttributes->getStringAttribute(name);

	name = "sliced";
	sliced = itemAttributes->getBooleanAttribute(name);

	name = "area";
	area = itemAttributes->getFloatAttribute(name);

	name = "armorPiercing";
	int type = itemAttributes->getIntAttribute(name);
	if (type != 0)
		armorPiercing = type;
	else
		armorPiercing = 0;

	name = "skillMods";
	makeSkillModMap(itemAttributes->getStringAttribute(name));

	name = "dots";
	makeDotMap(itemAttributes->getStringAttribute(name));
}

void WeaponImplementation::saveSkillModMap() {

	String name, value;

	name = "skillMods";
	value = getSkillModString();
	itemAttributes->setStringAttribute(name, value);
}

void WeaponImplementation::saveDotMap() {

	String name, value;

	name = "dots";
	value = getDotString();
	itemAttributes->setStringAttribute(name, value);
}

void WeaponImplementation::updateCraftingValues(DraftSchematic* draftSchematic){
		/*
		 * Incoming Values:					Ranges:
		 * mindamage						Differs between weapons
		 * maxdamage
		 * attackspeed
		 * woundchance
		 * roundsused
		 * hitpoints
		 * zerorangemod
		 * maxrange
		 * maxrangemod
		 * midrange
		 * midrangemod
		 * charges
		 * attackhealthcost
		 * attackactioncost
		 * attackmindcost
		 */
			DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

			float value = 0.f;
			_this->setMinDamage(craftingValues->getCurrentValue("mindamage"));
			_this->setMaxDamage(craftingValues->getCurrentValue("maxdamage"));

			_this->setAttackSpeed(craftingValues->getCurrentValue("attackspeed"));
			_this->setHealthAttackCost((int)craftingValues->getCurrentValue("attackhealthcost"));
			_this->setActionAttackCost((int)craftingValues->getCurrentValue("attackactioncost"));
			_this->setMindAttackCost((int)craftingValues->getCurrentValue("attackmindcost"));
			//_this->setDamageType((int)craftingValues->getCurrentValue("damagetype"));
			//_this->setArmorPiercing((int)craftingValues->getCurrentValue("armorpiercing"));

			value = craftingValues->getCurrentValue("woundchance");
			if(value != DraftSchematicValuesImplementation::VALUENOTFOUND)
				_this->setWoundsRatio(value);

			//value = craftingValues->getCurrentValue("roundsused");
			//if(value != DraftSchematicValuesImplementation::VALUENOTFOUND)
				//_this->set_______(value);

			value = craftingValues->getCurrentValue("zerorangemod");
			if(value != DraftSchematicValuesImplementation::VALUENOTFOUND)
				_this->setPointBlankAccuracy((int)value);

			value = craftingValues->getCurrentValue("maxrange");
			if(value != DraftSchematicValuesImplementation::VALUENOTFOUND)
				_this->setMaxRange((int)value);

			value = craftingValues->getCurrentValue("maxrangemod");
			if(value != DraftSchematicValuesImplementation::VALUENOTFOUND)
				_this->setMaxRangeAccuracy((int)value);

			value = craftingValues->getCurrentValue("midrange");
			if(value != DraftSchematicValuesImplementation::VALUENOTFOUND)
				_this->setIdealRange((int)value);

			value = craftingValues->getCurrentValue("midrangemod");
			if(value != DraftSchematicValuesImplementation::VALUENOTFOUND)
				_this->setIdealAccuracy((int)value);

			value = craftingValues->getCurrentValue("charges");
			if(value != DraftSchematicValuesImplementation::VALUENOTFOUND)
				_this->setUsesRemaining((int)value);

			value = craftingValues->getCurrentValue("hitpoints");
			if(value != DraftSchematicValuesImplementation::VALUENOTFOUND)
				_this->setMaxCondition((int)value);

			_this->setConditionDamage(0);

	}

void WeaponImplementation::sendTo(Player* player, bool doClose) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);

	if (parent != NULL)
		link(client, parent);

	BaseMessage* weao3 = new WeaponObjectMessage3((Weapon*) _this);
	client->sendMessage(weao3);

	/*Message* weao6 = new WeaponObjectMessage6(this);
	client->sendMessage(weao6);*/

	if (doClose)
		SceneObjectImplementation::close(client);
}

void WeaponImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	if (player->getInventoryItem(getObjectID()) != NULL) {

		if (!isSliced() && player->getSlicingAbility() >= 2)
			omr->addRadialParent(69, 3, "@slicing:slice");

		if (getConditionDamage() > 0)
			omr->addRadialParent(70, 3, "@sui:repair");

		if (hasPowerup())
			omr->addRadialParent(71, 3, "@powerup:mnu_remove_powerup");
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

void WeaponImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;

	AttributeListMessage* alm = new AttributeListMessage((Weapon*) _this);

	if (player->checkCertification(cert))
		alm->insertAttribute("weapon_cert_status", "Yes");
	else
		alm->insertAttribute("weapon_cert_status", "No");

	addAttributes(alm);
	player->sendMessage(alm);
}

void WeaponImplementation::generateDotAttributes(AttributeListMessage* alm) {
	if (getDotCount() > 0) {
		StringBuffer key;
		StringBuffer duration;
		StringBuffer potency;
		for (int i = 0; i < getDotCount(); ++i) {
			Dot* dot = dotVector.get(i);

			key.deleteAll();
			key << "cat_wpn_dot_0" << i << ".wpn_dot_type";

			switch (dot->getType()) {
			case CreatureState::BLEEDING:
				alm->insertAttribute(key.toString(), "Bleed");
				break;
			case CreatureState::DISEASED:
				alm->insertAttribute(key.toString(), "Disease");
				break;
			case CreatureState::ONFIRE:
				alm->insertAttribute(key.toString(), "Fire");
				break;
			case CreatureState::POISONED:
				alm->insertAttribute(key.toString(), "Poison");
				break;
			}

			key.deleteAll();
			key << "cat_wpn_dot_0" << i << ".wpn_dot_attrib";

			switch (dot->getAttribute()) {
			case CreatureAttribute::HEALTH:
				alm->insertAttribute(key.toString(), "Health");
				break;
			case CreatureAttribute::STRENGTH:
				alm->insertAttribute(key.toString(), "Strength");
				break;
			case CreatureAttribute::CONSTITUTION:
				alm->insertAttribute(key.toString(), "Constitution");
				break;
			case CreatureAttribute::ACTION:
				alm->insertAttribute(key.toString(), "Action");
				break;
			case CreatureAttribute::QUICKNESS:
				alm->insertAttribute(key.toString(), "Quickness");
				break;
			case CreatureAttribute::STAMINA:
				alm->insertAttribute(key.toString(), "Stamina");
				break;
			case CreatureAttribute::MIND:
				alm->insertAttribute(key.toString(), "Mind");
				break;
			case CreatureAttribute::FOCUS:
				alm->insertAttribute(key.toString(), "Focus");
				break;
			case CreatureAttribute::WILLPOWER:
				alm->insertAttribute(key.toString(), "Willpower");
				break;
			}

			key.deleteAll();
			key << "cat_wpn_dot_0" << i << ".wpn_dot_strength";
			alm->insertAttribute(key.toString(), dot->getStrength());

			key.deleteAll();
			key << "cat_wpn_dot_0" << i << ".wpn_dot_duration";
			duration.deleteAll();
			duration << dot->getDuration() << "s";
			alm->insertAttribute(key.toString(), duration);

			key.deleteAll();
			key << "cat_wpn_dot_0" << i << ".wpn_dot_potency";
			potency.deleteAll();
			potency << dot->getPotency() << "%";
			alm->insertAttribute(key.toString(), potency);

			key.deleteAll();
			key << "cat_wpn_dot_0" << i << ".wpn_dot_uses";
			alm->insertAttribute(key.toString(), dot->getUses());
		}
	}
}

void WeaponImplementation::decay(float decayRate) {
	TangibleObjectImplementation::decay(decayRate);

	if (getMaxCondition() > 0) {
		float ratio = ((float) getConditionDamage()) / ((float) getMaxCondition());

		if (ratio > 0.99f) {
			onBroken();
		} else if (ratio > 0.75f) {
			setMaxDamage(getBaseMaxDamage() * (1 - decayRate));
			setMinDamage(getBaseMinDamage() * (1 - decayRate));

			setAttackSpeed(getBaseAttackSpeed() * (1 + decayRate));
		}
	}
}

void WeaponImplementation::onBroken() {
	setMaxCondition(1);
	setConditionDamage(1);
	setMaxDamage(1);
	setMinDamage(1);
}

void WeaponImplementation::setWeaponStats(int modifier){
	wlock();

	int maxLevel = 120;
	/*
	 * the maximum value for skill mods generated for a weapon
	 */
	maxValue = 25;
	/*
	 * the maximum number of dots generated for a weapon
	 */
	maxDots = 3;

	if (modifier > maxLevel){
		int diff = System::random(modifier - maxLevel);
		modifier = maxLevel;
		modifier += diff;
	}

	int luck = (System::random(100)) + (modifier/4);

	if (System::random(1000) == 7)
		luck = luck * 2;

	if (System::random(50000) == 77)
		luck = luck * 5;

	if (System::random(1000000) == 777)
		luck = luck * 10;

	if (System::random(100) == 6)
		luck = 0;

	modifier = modifier + System::random(10);

	int playerRoll = System::random(1000) * modifier * luck / 1000;

	if (playerRoll > 170000) {
		modifier = modifier + 150;
		luck = luck + 170;
		setMaxDamage(maxDamage * 3);

		StringBuffer itemText;
		itemText << "\\#ffff00" << customName.toString() << " (Legendary)";
		customName = UnicodeString(itemText.toString());
	} else if (playerRoll > 60000) {
		modifier = modifier + 100;
		luck = luck + 120;
		setMaxDamage(maxDamage * 1.5);

		StringBuffer itemText;
		itemText << "\\#ffff00" << customName.toString() << " (Exceptional)";
		customName = UnicodeString(itemText.toString());
	} else if (playerRoll > 11000) {
		modifier = modifier + 35;
		luck = luck + 65;

		StringBuffer itemText;
		itemText << "\\#ffff00" << customName.toString();
		customName = UnicodeString(itemText.toString());
	}

	if (luck * System::random(100) > 1500) {
		setMinDamage(minDamage + (minDamage * luck / 149.93f));
		setMaxDamage(maxDamage + (maxDamage * luck / 150.11f));
	}

	if (luck * System::random(100) > 1750) {
		setAttackSpeed(attackSpeed - (attackSpeed * luck / 377.69f));
	}

	if (luck * System::random(100) > 1750) {
		setHealthAttackCost(healthAttackCost - (healthAttackCost * luck / 359));
		setActionAttackCost(actionAttackCost - (actionAttackCost * luck / 359));
		setMindAttackCost(mindAttackCost - (mindAttackCost * luck / 359));
	}

	if (luck * System::random(100) > 1750)
		setWoundsRatio(woundsRatio + (woundsRatio * luck / 173));

	if (playerRoll > 12000 && System::random(3) == 1) {
		putSkillMod(System::random(30) + 1, (luck / (System::random(3) +10)));
	}
	if (playerRoll > 20000 && System::random(2) == 1) {
		putSkillMod(System::random(30) + 1, (luck / (System::random(3) + 10)));
	}
	if (playerRoll > 30000) {
		putSkillMod(System::random(30) + 1, (luck / (System::random(3) + 10)));
	}

	if (playerRoll > 13000 && System::random(1) == 1)	{
		if (objectCRC != 0xE24F970E) {
			Dot* dot = new Dot();
			switch (System::random(3)) {
			case 0:
				dot->setType(CreatureState::BLEEDING);
				dot->setAttribute(System::random(2) * 3);
				break;
			case 1:
				dot->setType(CreatureState::DISEASED);
				dot->setAttribute(System::random(8));
				break;
			case 2:
				dot->setType(CreatureState::ONFIRE);
				dot->setAttribute(System::random(2) * 3);
				break;
			case 3:
				dot->setType(CreatureState::POISONED);
				dot->setAttribute(System::random(2) * 3);
				break;
			default:
				dot->setType(CreatureState::BLEEDING);
				dot->setAttribute(System::random(2) *3);
				break;
			}
			dot->setStrength((modifier / 3) + (luck / 2));
			dot->setDuration(((luck * 4) + modifier) / 7);
			dot->setPotency(System::random(luck / 3) + (luck / 5));
			dot->setUses((modifier + luck) * 11);
			addDot(dot);
		}

		if (playerRoll > 13000 && System::random(2) == 1)	{
			Dot* dot = new Dot();
			switch (System::random(3)) {
			case 0:
				dot->setType(CreatureState::BLEEDING);
				dot->setAttribute(System::random(2) * 3);
				break;
			case 1:
				dot->setType(CreatureState::DISEASED);
				dot->setAttribute(System::random(8));
				break;
			case 2:
				dot->setType(CreatureState::ONFIRE);
				dot->setAttribute(System::random(2) * 3);
				break;
			case 3:
				dot->setType(CreatureState::POISONED);
				dot->setAttribute(System::random(2) * 3);
				break;
			default:
				dot->setType(CreatureState::BLEEDING);
				dot->setAttribute(System::random(2) *3);
				break;
			}
			dot->setStrength((modifier / 3) + (luck / 2));
			dot->setDuration(((luck * 4) + modifier) / 7);
			dot->setPotency(System::random(luck / 3) + (luck / 5));
			dot->setUses((modifier + luck) * 11);
			addDot(dot);

			if (playerRoll > 13000 && System::random(4) == 1)	{
				switch (System::random(3)) {
				case 0:
					dot->setType(CreatureState::BLEEDING);
					dot->setAttribute(System::random(2) * 3);
					break;
				case 1:
					dot->setType(CreatureState::DISEASED);
					dot->setAttribute(System::random(8));
					break;
				case 2:
					dot->setType(CreatureState::ONFIRE);
					dot->setAttribute(System::random(2) * 3);
					break;
				case 3:
					dot->setType(CreatureState::POISONED);
					dot->setAttribute(System::random(2) * 3);
					break;
				default:
					dot->setType(CreatureState::BLEEDING);
					dot->setAttribute(System::random(2) *3);
					break;
				}
				dot->setStrength((modifier / 3) + (luck / 2));
				dot->setDuration(((luck * 4) + modifier) / 7);
				dot->setPotency(System::random(luck / 3) + (luck / 5));
				dot->setUses((modifier + luck) * 11);
				addDot(dot);

			}
		}
	}

	if (attackSpeed < 1)
		setAttackSpeed(1.0f);

	if (healthAttackCost < 0)
		setHealthAttackCost(0);

	if (actionAttackCost < 0)
		setActionAttackCost(0);

	if (mindAttackCost < 0)
		setMindAttackCost(0);

	if (objectSubType == TangibleObjectImplementation::HEAVYWEAPON) {
		if (maxDamage > 5000)
			setMaxDamage(4500 + System::random(500));
	}

	else if (objectSubType == TangibleObjectImplementation::SPECIALHEAVYWEAPON) {
		if (maxDamage > 1100)
			setMaxDamage(1050 + System::random(50));
	}

	else if (objectSubType == TangibleObjectImplementation::MELEEWEAPON && maxDamage > 575)
		setMaxDamage(500 + System::random(250));

	else if (maxDamage > 800)
		setMaxDamage(700 + System::random(350));

	//helps randomize the dot strength
	if (getDotCount() > 0){
		Dot* dot = dotVector.get(0);
		if (dot->getStrength() > 225) {
			dot->setStrength(100 + System::random(200));

		} else if (dot->getStrength() > 150) {
			dot->setStrength(100 + System::random(100));

		} else if (dot->getStrength() > 75) {
			dot->setStrength(50 + System::random(75));

		} else { dot->setStrength(1 + System::random(50));

		}
	}

	if (minDamage > maxDamage)
		setMinDamage(round(0.8 * maxDamage));

	equipped = false;

	persistent = false;
	updated = true;

	saveSkillModMap();

	unlock();
}

void WeaponImplementation::generatePowerup(AttributeListMessage* alm) {

	if (powerupUses != 0) {
		alm->insertAttribute("cat_pup.pup_uses", powerupUses);

		if (bonusMinDamage != 0) {
			StringBuffer txt;
			txt << "+" << round(bonusMinDamage);
			alm->insertAttribute("cat_pup.pup_wpn_damage_min", txt.toString());
		}
		if (bonusMaxDamage != 0) {
			StringBuffer txt;
			txt << "+" << round(bonusMaxDamage);
			alm->insertAttribute("cat_pup.pup_wpn_damage_max", txt.toString());
		}
		if (bonusAttackSpeed != 0) {

			float spd = bonusAttackSpeed;

			StringBuffer spdtxt;

			spdtxt << round(10 * spd)/10;

			if ((int(round(spd * 10)) % 10) == 0)
				spdtxt << ".0";

			StringBuffer txt;
			txt << round(10*bonusAttackSpeed)/10;
			alm->insertAttribute("cat_pup.pup_wpn_attack_speed", spdtxt.toString());
		}
		if (bonusHealthAttackCost != 0)
			alm->insertAttribute("cat_pup.pup_wpn_attack_cost_health", bonusHealthAttackCost);

		if (bonusActionAttackCost != 0)
			alm->insertAttribute("cat_pup.pup_wpn_attack_cost_action", bonusActionAttackCost);

		if (bonusMindAttackCost != 0)
			alm->insertAttribute("cat_pup.pup_wpn_attack_cost_mind", bonusMindAttackCost);

		if (bonusPointBlankAccuracy != 0) {
			StringBuffer txt;
			txt << "+" << bonusPointBlankAccuracy;
			alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_zero", txt.toString());
		}
		if (bonusIdealRange != 0)
			alm->insertAttribute("cat_pup.pup_wpn_range_mid", bonusIdealRange);

		if (bonusIdealAccuracy != 0) {
			StringBuffer txt;
			txt << "+" << bonusIdealAccuracy;
			alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_mid", txt.toString());
		}
		if (bonusMaxRangeAccuracy != 0) {
			StringBuffer txt;
			txt << "+" << bonusMaxRangeAccuracy;
			alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_max", txt.toString());
		}
		if (bonusWoundsRatio != 0) {
			StringBuffer txt;

			float wnd = round(10 * bonusWoundsRatio) / 10.0f;
			txt << "+" << wnd << "%";

			alm->insertAttribute("cat_pup.pup_wpn_wound_chance", txt.toString());
		}
	}
}

void WeaponImplementation::powerupMinDamage(float powerupValue) {
	setBonusMinDamage(minDamage * powerupValue / 100.0f);

	if (getMinDamage() > getMaxDamage())
		setBonusMinDamage(getMaxDamage() - minDamage - 1);
}

void WeaponImplementation::powerupMaxDamage(float powerupValue) {
	setBonusMaxDamage(maxDamage * powerupValue / 100.0f);
}

void WeaponImplementation::powerupHealthAttackCost(float powerupValue) {
	setBonusHealthAttackCost(int(-healthAttackCost * powerupValue / 100.0f));
}

void WeaponImplementation::powerupActionAttackCost(float powerupValue) {
	setBonusActionAttackCost(int(-actionAttackCost * powerupValue / 100.0f));
}

void WeaponImplementation::powerupMindAttackCost(float powerupValue) {
	setBonusMindAttackCost(int(-mindAttackCost * powerupValue / 100.0f));
}

void WeaponImplementation::powerupWoundsRatio(float powerupValue) {
	setBonusWoundsRatio(woundsRatio * powerupValue / 100.0f);
}

void WeaponImplementation::powerupAttackSpeed(float powerupValue) {
	setBonusAttackSpeed(-attackSpeed * powerupValue / 100.0f);
}

void WeaponImplementation::powerupPointBlankAccuracy(float powerupValue) {
	if (pointBlankAccuracy < 0)
		setBonusPointBlankAccuracy(int((float)-pointBlankAccuracy * powerupValue / 100.0f));
	else
		setBonusPointBlankAccuracy(int((float)pointBlankAccuracy * powerupValue / 100.0f));
}

void WeaponImplementation::powerupIdealRange(float powerupValue) {
	int idealRang = int((float)-idealRange * powerupValue / 100.0f);

	setBonusIdealRange(idealRang);
}

void WeaponImplementation::powerupIdealAccuracy(float powerupValue) {
	if (idealAccuracy < 0)
		setBonusIdealAccuracy(int((float)-idealAccuracy * powerupValue / 100.0f));
	else
		setBonusIdealAccuracy(int((float)idealAccuracy * powerupValue / 100.0f));
}

void WeaponImplementation::powerupMaxRangeAccuracy(float powerupValue) {
	if (maxRangeAccuracy < 0)
		setBonusMaxRangeAccuracy(int((float)-maxRangeAccuracy * powerupValue / 100.0f));
	else
		setBonusMaxRangeAccuracy(int((float)maxRangeAccuracy * powerupValue / 100.0f));
}

void WeaponImplementation::removePowerup(Player* player, bool notify) {
	setPowerupUses(0);

	setBonusMinDamage(0);
	setBonusMaxDamage(0);
	setBonusAttackSpeed(0);
	setBonusHealthAttackCost(0);
	setBonusActionAttackCost(0);
	setBonusMindAttackCost(0);
	setBonusPointBlankRange(0);
	setBonusPointBlankAccuracy(0);
	setBonusIdealRange(0);
	setBonusIdealAccuracy(0);
	setBonusMaxRange(0);
	setBonusMaxRangeAccuracy(0);
	setBonusWoundsRatio(0);

	if (notify) {
		StringBuffer txt;
		txt << "The powerup on your " << customName.toString() << " has expired.";
		player->sendSystemMessage(txt.toString());
	}

	generateAttributes(player);
}

void WeaponImplementation::addAttributes(AttributeListMessage* alm) {

	StringBuffer cond;
	cond << (maxCondition-conditionDamage) << "/" << maxCondition;

	alm->insertAttribute("condition", cond);

	alm->insertAttribute("volume", "1");

	if (usesRemaining > 0)
		alm->insertAttribute("count", usesRemaining);

	int key = 0;
	int value = 0;
	for (int i = 0; i < innateSkillModMap.size(); ++i) {
		key = innateSkillModMap.elementAt(i)->getKey();
		value = innateSkillModMap.elementAt(i)->getValue();

		generateSkillMods(alm, key, value);
	}

	String ap;

	switch (armorPiercing) {
	case NONE:
		ap = "None";
		break;
	case LIGHT:
		ap = "Light";
		break;
	case MEDIUM:
		ap = "Medium";
		break;
	case HEAVY:
		ap = "Heavy";
		break;
	default:
		ap = "Unknown";
		break;
	}

	alm->insertAttribute("wpn_armor_pierce_rating", ap);

	float speed = round(10 * getAttackSpeed()) / 10;

	StringBuffer spdtxt;

	spdtxt << speed;

	if ((int(round(speed * 10)) % 10) == 0)
		spdtxt << ".0";

	alm->insertAttribute("wpn_attack_speed", spdtxt.toString());

	if (area != 0.0f)
		alm->insertAttribute("area", getPrecision(area, 0));

	//Damage Information
	StringBuffer dmgtxt;

	switch (damageType) {
	case KINETIC:
		dmgtxt << "Kinetic";
		break;
	case ENERGY:
		dmgtxt << "Energy";
		break;
	case ELECTRICITY:
		dmgtxt << "Electricity";
		break;
	case STUN:
		dmgtxt << "Stun";
		break;
	case BLAST:
		dmgtxt << "Blast";
		break;
	case HEAT:
		dmgtxt << "Heat";
		break;
	case COLD:
		dmgtxt << "Cold";
		break;
	case ACID:
		dmgtxt << "Acid";
		break;
	case LIGHTSABER:
		dmgtxt << "Lightsaber";
		break;
	}

	alm->insertAttribute("damage.wpn_damage_type", dmgtxt);

	float minDmg = round(getMinDamage());
	float maxDmg = round(getMaxDamage());

	alm->insertAttribute("damage.wpn_damage_min", minDmg);

	alm->insertAttribute("damage.wpn_damage_max", maxDmg);

	StringBuffer woundsratio;

	float wnd = round(10 * getWoundsRatio()) / 10.0f;

	woundsratio << wnd << "%";

	alm->insertAttribute("damage.wpn_wound_chance", woundsratio);

	//Accuracy Modifiers
	StringBuffer pblank;
	if (getPointBlankAccuracy() >= 0)
		pblank << "+";

	pblank << getPointBlankAccuracy() << " @ " << getPointBlankRange() << "m";
	alm->insertAttribute("cat_wpn_rangemods.wpn_range_zero", pblank);

	StringBuffer ideal;
	if (getIdealAccuracy() >= 0)
		ideal << "+";

	ideal << getIdealAccuracy() << " @ " << getIdealRange() << "m";
	alm->insertAttribute("cat_wpn_rangemods.wpn_range_mid", ideal);

	StringBuffer maxrange;
	if (getMaxRangeAccuracy() >= 0)
		maxrange << "+";

	maxrange << getMaxRangeAccuracy() << " @ " << getMaxRange() << "m";
	alm->insertAttribute("cat_wpn_rangemods.wpn_range_max", maxrange);

	//Special Attack Costs
	alm->insertAttribute("cat_wpn_attack_cost.health", getHealthAttackCost());

	alm->insertAttribute("cat_wpn_attack_cost.action", getActionAttackCost());

	alm->insertAttribute("cat_wpn_attack_cost.mind", getMindAttackCost());

	// TODO: Find right string to display force cost
	if (getForceCost() > 0)
		alm->insertAttribute("force_cost", getForceCost());

	if (getDotCount() > 0)
		generateDotAttributes(alm);

	if (sliced == 1)
		alm->insertAttribute("hacked1", "");

	generatePowerup(alm);

}

void WeaponImplementation::setXpType() {
	switch (getType()) {
	case UNARMED:
		xpType = "combat_meleespecialize_unarmed";
		break;
	case ONEHANDED:
		xpType = "combat_meleespecialize_onehand";
		break;
	case TWOHANDED:
		xpType = "combat_meleespecialize_twohand";
		break;
	case POLEARM:
		xpType = "combat_meleespecialize_polearm";
		break;
	case PISTOL:
		xpType = "combat_rangedspecialize_pistol";
		break;
	case CARBINE:
		xpType = "combat_rangedspecialize_carbine";
		break;
	case RIFLE:
		xpType = "combat_rangedspecialize_rifle";
		break;
	case TRAP:
		xpType = "trapping";
		break;
	case ONEHANDSABER:
	case TWOHANDSABER:
	case POLEARMSABER:
		xpType = "jedi_general";
		break;
	case RIFLEBEAM:
	case RIFLEFLAMETHROWER:
	case RIFLELIGHTNING:
	case RIFLEACIDBEAM:
	case HEAVYACIDBEAM:
	case HEAVYLIGHTNINGBEAM:
	case HEAVYPARTICLEBEAM:
	case HEAVYROCKETLAUNCHER:
	case HEAVYLAUNCHER:
		xpType = "combat_rangedspecialize_heavy";
		break;
	case GRENADE:
		xpType = "combat_general";
		break;
	default:
		if (getDamageType() == FORCE || isJedi())
			xpType = "jedi_general";
		else
			xpType = "combat_meleespecialize_unarmed";
		return;
	};
}

void WeaponImplementation::createTestDot(int type) {
	Dot* dot = new Dot();
	switch(type) {
	case 1:
		type = CreatureState::BLEEDING;
		break;
	case 2:
		type = CreatureState::ONFIRE;
		break;
	case 3:
		type = CreatureState::POISONED;
		break;
	case 4:
		type = CreatureState::DISEASED;
		break;
	default:
		type = CreatureState::BLEEDING;
		break;
	}

	int attr = 0;
	int pool = System::random(3);
	switch (pool) {
	case 0:
		attr = CreatureAttribute::ACTION;
		break;
	case 1:
		attr = CreatureAttribute::MIND;
		break;
	default:
		attr = CreatureAttribute::HEALTH;
		break;
	}

	dot->setType(type);
	dot->setAttribute(attr);
	dot->setUses(System::random(1000));
	dot->setPotency(100);
	dot->setStrength(System::random(100));
	dot->setDuration(System::random(60));
	addDot(dot);
}

void WeaponImplementation::setInnateMods(Player* player) {
	for (int i = 0; i < innateSkillModMap.size(); ++i) {
		int skillModType = innateSkillModMap.elementAt(i)->getKey();
		int skillModValue = innateSkillModMap.elementAt(i)->getValue();

		if (skillModType == 0)
			return;

		String enhanceName = weaponSkillMods.getEnhancement(skillModType);
		player->addSkillModBonus(enhanceName, skillModValue, true);
	}
}

void WeaponImplementation::unsetInnateMods(Player* player) {
	for (int i = 0; i < innateSkillModMap.size(); ++i) {
		int skillModType = innateSkillModMap.elementAt(i)->getKey();
		int skillModValue = innateSkillModMap.elementAt(i)->getValue();

		if (skillModType == 0)
			return;

		String enhanceName = weaponSkillMods.getEnhancement(skillModType);
		player->addSkillModBonus(enhanceName, -skillModValue, true);
	}
}


//Event Handlers
/*
 * This function gets called from EquippedItems.h in equipWeapon()
 */
void WeaponImplementation::onEquip(Player* player) {
	setInnateMods(player);
}

/*
 * This function gets called from EquippedItems.h in unEquipWeapon()
 */
void WeaponImplementation::onUnequip(Player* player) {
	unsetInnateMods(player);
}

/**
 * This event occurs following a successful damage slice.
 * \param slicer The Player doing the slicing.
 * \param percentage The percentage increase.
 */
void WeaponImplementation::onDamageSliced(Player* slicer, uint8 percentage) {
	StfParameter* params = new StfParameter();
	params->addDI(percentage);
	slicer->sendSystemMessage("slicing/slicing", "dam_mod", params); //You have successfully increased the damage range of the weapon by %DI%!
	delete params;
}

/**
 * This event occurs following a successful speed slice.
 * \param slicer The Player doing the slicing.
 * \param percentage The percentage increase.
 */
void WeaponImplementation::onSpeedSliced(Player* slicer, uint8 percentage) {
	StfParameter* params = new StfParameter();
	params->addDI(percentage);
	slicer->sendSystemMessage("slicing/slicing", "spd_mod", params); //You have successfully increased the attack speed of the weapon by %DI%!
	delete params;
}

/**
 * This event occurs when a slicing attempt has gone awry.
 * \param slicer The player doing the slicing.
 */
void WeaponImplementation::onSlicingFailure(Player* slicer) {
	slicer->sendSystemMessage("slicing/slicing", "fail_weapon"); //You've made a critical mistake modifying the weapon's basic systems. The damage is extensive and while the weapon still retains its previous effectiveness, no one will be able to modify it in the future.
	setSliced(true);
}


//Actions
/**
 * Slices the item.
 * \param slicer The player slicing the item.
 */
void WeaponImplementation::slice(Player* slicer) {
	int sliceSkill = slicer->getSlicingAbility();
	uint8 min = 0;
	uint8 max = 0;

	switch (sliceSkill) {
	case 5:
		min += 5;
		max += 5;
	case 4:
		min += 5;
		max += 5;
	case 3:
	case 2:
		min += 10;
		max += 25;
		break;
	default:
		return;
	}

	uint8 percentage = System::random(max - min) + min;

	try {
		wlock();

		removePowerup(slicer, false);

		switch (System::random(1)) {
		case 0:
			sliceDamage(slicer, percentage);
			break;
		case 1:
			sliceSpeed(slicer, percentage);
			break;
		}

		generateAttributes(slicer);

		unlock();
	} catch (...) {
		unlock();
	}
}

/**
 * Slices the weapon, increasing damage.
 * \param slicer The player doing the slicing.
 * \param percentage What percentage increase will take effect.
 */
void WeaponImplementation::sliceDamage(Player* slicer, uint8 percentage){
	if (isSliced())
		return;

	setMinDamage((minDamage * percentage / 100) + minDamage);
	setMaxDamage((maxDamage * percentage / 100) + maxDamage);

	setSliced(true);
	updated = true;

	onDamageSliced(slicer, percentage);
}

/**
 * Slices the weapon, increasing speed.
 * \param slicer The player doing the slicing.
 * \param percentage What percentage increase will take effect.
 */
void WeaponImplementation::sliceSpeed(Player* slicer, uint8 percentage){
	if (isSliced())
		return;

	setAttackSpeed(attackSpeed - (attackSpeed * percentage / 100));

	if (attackSpeed < 1)
		setAttackSpeed(1.0f);

	setSliced(true);
	updated = true;

	onSpeedSliced(slicer, percentage);
}
