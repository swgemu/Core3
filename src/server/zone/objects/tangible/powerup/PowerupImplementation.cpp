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

#include "../../../managers/item/ItemManager.h"

#include "../TangibleObject.h"

#include "engine/engine.h"

#include "PowerupImplementation.h"

#include "../../../packets.h"

PowerupImplementation::PowerupImplementation(uint64 objID, uint32 tempCRC, const UnicodeString& n, const String& tempn)
		: PowerupServant(objID, WEAPONPOWERUP) {
	objectCRC = tempCRC;
	objectID = objID;

	customName = n;
	templateName = tempn;
	templateTypeName = "weapon_name";

	init();
}

PowerupImplementation::PowerupImplementation(uint64 objID)
		: PowerupServant(objID, WEAPONPOWERUP) {
	templateTypeName = "weapon_name";

	init();
}

PowerupImplementation::~PowerupImplementation() {

}

void PowerupImplementation::init() {

	objectType = SceneObjectImplementation::TANGIBLE;
	objectSubType = TangibleObjectImplementation::WEAPONPOWERUP;

	conditionDamage = 0;
	maxCondition = 100;

	equipped = false;
	persistent = false;
	updated = false;

}

void PowerupImplementation::setPowerupStats(int modifier) {

	int maxLevel = 120;

	if (modifier > maxLevel){
		int diff = System::random(modifier - maxLevel);
		modifier = maxLevel;
		modifier += diff;
	}

	setPowerupUses(100);

	setPowerupType(System::random(1) + 1);
	setPowerupSubType(System::random(5) + 1);

	if (type == MELEE) {
		setPowerup0Type(System::random(3) + 1);
		setPowerup1Type(System::random(3) + 1);
		setPowerup2Type(System::random(3) + 1);
	} else {
		if (subType == BARREL || subType == STOCK)
			setPowerup0Type(System::random(2) + 1);
		else
			setPowerup0Type(System::random(3) + 1);

		if (subType == COUPLER || subType == SCOPE) {
			setPowerup1Type(System::random(2) + 1);
			setPowerup2Type(System::random(2) + 1);
		} else {
			setPowerup1Type(System::random(3) + 1);
			setPowerup2Type(System::random(3) + 1);
		}
	}

	setPowerup0Value(((float)System::random(modifier) + modifier) / 4.7f);
	setPowerup1Value(((float)System::random(modifier) + modifier) / 5.7f);
	setPowerup2Value(((float)System::random(modifier) + modifier) / 6.3f);

	if (powerup2Type == powerup1Type) {
		setPowerup2Type(0);
		setPowerup2Value(0);
	}

	if (type == RANGED && subType == MUZZLE && powerup0Type == 3 && powerup1Type == 2) {
			powerup1Type = 0;
			powerup1Value = 0;
	}

	if (powerup0Value > 33.34)
		setPowerup0Value(33.34);

	if (powerup1Value > 16.67)
		setPowerup1Value(16.67);

	if (powerup2Value > 8.34)
		setPowerup2Value(8.34);

	if (type == MELEE) {
		objectCRC = 0x520273B1;
		templateName = "powerup_weapon_melee";
	}
	else if (type == RANGED)
		switch (subType) {
		case BARREL:
			objectCRC = 0x82E7596;
			templateName = "powerup_weapon_ranged_barrel";
			break;
		case COUPLER:
			objectCRC = 0x60B89822;
			templateName = "powerup_weapon_ranged_power";
			break;
		case GRIP:
			objectCRC = 0x4E39F9EB;
			templateName = "powerup_weapon_ranged_grip";
			break;
		case MUZZLE:
			objectCRC = 0x212273E9;
			templateName = "powerup_weapon_ranged_muzzle";
			break;
		case SCOPE:
			objectCRC = 0xE0019303;
			templateName = "powerup_weapon_ranged_scope";
			break;
		case STOCK:
			objectCRC = 0xA343A929;
			templateName = "powerup_weapon_ranged_stock";
			break;
		default:
			objectCRC = 0x6195F9A8;
			templateName = "powerup_weapon_ranged";
			break;
		}
	else {
		objectCRC = 0x6195F9A8;
		templateName = "powerup_weapon_ranged";
	}

	generateName();
}

void PowerupImplementation::generateName() {
	StringBuffer powerupName;

	switch (type) {
	case MELEE :
		switch (powerup0Type) {
		case 1:
			powerupName << "Balancing Melee Powerup";
			break;
		case 2:
			powerupName << "Barbing Melee Powerup";
			break;
		case 3:
			powerupName << "Compensating Melee Powerup";
			break;
		case 4:
			powerupName << "Extending Melee Powerup";
			break;
		}
		switch (powerup1Type) {
		case 1:
			powerupName << " of Control-Enhancement";
			break;
		case 2:
			powerupName << " of Accuracy";
			break;
		case 3:
			powerupName << " of Precision";
			break;
		case 4:
			powerupName << " of Wounding";
			break;
		}
		break;
	case RANGED :
		switch (subType) {
		case BARREL :
			switch (powerup0Type) {
			case 1:
				powerupName << "Ported Barrel";
				break;
			case 2:
				powerupName << "Smooth Barrel";
				break;
			case 3:
				powerupName << "Taper-Bored Barrel";
				break;
			}
			switch (powerup1Type) {
			case 1:
				powerupName << " of Alignment";
				break;
			case 2:
				powerupName << " of Concentration";
				break;
			case 3:
				powerupName << " of Condensing";
				break;
			case 4:
				powerupName << " of Dampening";
				break;
			}
			break;
		case COUPLER :
			switch (powerup0Type) {
			case 1:
				powerupName << "Hot-Wired Coupler";
				break;
			case 2:
				powerupName << "Quick-Charge Coupler";
				break;
			case 3:
				powerupName << "Short-Circuited Coupler";
				break;
			case 4:
				powerupName << "Tweaked Coupler";
				break;
			}
			switch (powerup1Type) {
			case 1:
				powerupName << " of Compensation";
				break;
			case 2:
				powerupName << " of Overpowering";
				break;
			case 3:
				powerupName << " of Searing";
				break;
			}
			break;
		case GRIP :
			switch (powerup0Type) {
			case 1:
				powerupName << "Ergonomic Grip";
				break;
			case 2:
				powerupName << "Fitted Grip";
				break;
			case 3:
				powerupName << "Hair-Triggered Grip";
				break;
			case 4:
				powerupName << "Lightening Grip";
				break;
			}
			switch (powerup1Type) {
			case 1:
				powerupName << " of Recoil-Deadening";
				break;
			case 2:
				powerupName << " of Aiming";
				break;
			case 3:
				powerupName << " of Reckoning";
				break;
			case 4:
				powerupName << " of Steadying";
				break;
			}
			break;
		case MUZZLE :
			switch (powerup0Type) {
			case 1:
				powerupName << "Muffled Muzzle";
				break;
			case 2:
				powerupName << "Polished Muzzle";
				break;
			case 3:
				powerupName << "Scattering Muzzle";
				break;
			case 4:
				powerupName << "Tuned Muzzle";
				break;
			}
			switch (powerup1Type) {
			case 1:
				powerupName << " of Flaring";
				break;
			case 2:
				powerupName << " of Focusing";
				break;
			case 3:
				powerupName << " of Braking";
				break;
			case 4:
				powerupName << " of Sighting";
				break;
			}
			break;
		case SCOPE :
			switch (powerup0Type) {
			case 1:
				powerupName << "Calibrated Scope";
				break;
			case 2:
				powerupName << "Powered Scope";
				break;
			case 3:
				powerupName << "Precision Scope";
				break;
			case 4:
				powerupName << "Ranged Scope";
				break;
			}
			switch (powerup1Type) {
			case 1:
				powerupName << " of Targetting";
				break;
			case 2:
				powerupName << " of Pin-Pointing";
				break;
			case 3:
				powerupName << " of Tracking";
				break;
			}
			break;
		case STOCK :
			switch (powerup0Type) {
			case 1:
				powerupName << "Anti-Jitter Stock";
				break;
			case 2:
				powerupName << "Balanced Stock";
				break;
			case 3:
				powerupName << "Reactive Stock";
				break;
			}
			switch (powerup1Type) {
			case 1:
				powerupName << " of Dissipation";
				break;
			case 2:
				powerupName << " of Accuracy";
				break;
			case 3:
				powerupName << " of Cushioning";
				break;
			case 4:
				powerupName << " of Loading";
				break;
			}
			break;
		}
		break;
	case MINE :
		break;
	case THROWN :
		break;
	}

	customName = UnicodeString(powerupName.toString());
}

void PowerupImplementation::updateCraftingValues(DraftSchematic* draftSchematic){
	/*
	 * Incoming Values:				Range:
	 * effect						1-100
	 * hitpoints					1000-1000
	 */
	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	int hitPoints = (int)craftingValues->getCurrentValue("hitpoints");
	setPowerupUses(hitPoints);

	int effect = (int)craftingValues->getCurrentValue("effect");
	setPowerupStats(effect);
}

void PowerupImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;

	AttributeListMessage* alm = new AttributeListMessage((Weapon*) _this);
	addAttributes(alm);

	player->sendMessage(alm);
}

void PowerupImplementation::apply(Weapon* weapon) {

	if (weapon == NULL)
		return;

	switch (type) {
	case MELEE :
		switch (powerup0Type) {
		case 1:
			weapon->powerupHealthAttackCost(powerup0Value);
			break;
		case 2:
			weapon->powerupPointBlankAccuracy(powerup0Value);
			break;
		case 3:
			weapon->powerupMindAttackCost(powerup0Value);
			break;
		case 4:
			weapon->powerupIdealRange(powerup0Value);
			break;
		}
		switch (powerup1Type) {
		case 1:
			weapon->powerupAttackSpeed(powerup1Value);
			break;
		case 2:
			weapon->powerupIdealAccuracy(powerup1Value);
			break;
		case 3:
			weapon->powerupMinDamage(powerup1Value);
			break;
		case 4:
			weapon->powerupWoundsRatio(powerup1Value);
			break;
		}
		switch (powerup2Type) {
		case 1:
			weapon->powerupAttackSpeed(powerup2Value);
			break;
		case 2:
			weapon->powerupIdealAccuracy(powerup2Value);
			break;
		case 3:
			weapon->powerupMinDamage(powerup2Value);
			break;
		case 4:
			weapon->powerupWoundsRatio(powerup2Value);
			break;
		}
		break;	case RANGED :
		switch (subType) {
		case BARREL :
			switch (powerup0Type) {
			case 1:
				weapon->powerupHealthAttackCost(powerup0Value);
				break;
			case 2:
				weapon->powerupPointBlankAccuracy(powerup0Value);
				break;
			case 3:
				weapon->powerupWoundsRatio(powerup0Value);
				break;
			}
			switch (powerup1Type) {
			case 1:
				weapon->powerupIdealAccuracy(powerup1Value);
				break;
			case 2:
				weapon->powerupMaxDamage(powerup1Value);
				break;
			case 3:
				weapon->powerupIdealRange(powerup1Value);
				break;
			case 4:
				weapon->powerupMindAttackCost(powerup1Value);
			break;
			}
			switch (powerup2Type) {
			case 1:
				weapon->powerupIdealAccuracy(powerup2Value);
				break;
			case 2:
				weapon->powerupMaxDamage(powerup2Value);
				break;
			case 3:
				weapon->powerupIdealAccuracy(powerup2Value);
				break;
			case 4:
				weapon->powerupMindAttackCost(powerup2Value);
			break;
			}
		break;
		case COUPLER :
			switch (powerup0Type) {
			case 1:
				weapon->powerupMaxDamage(powerup0Value);
				break;
			case 2:
				weapon->powerupAttackSpeed(powerup0Value);
				break;
			case 3:
				weapon->powerupMinDamage(powerup0Value);
				break;
			case 4:
				weapon->powerupActionAttackCost(powerup0Value);
				break;
			}
			switch (powerup1Type) {
			case 1:
				weapon->powerupMindAttackCost(powerup1Value);
				break;
			case 2:
				weapon->powerupIdealRange(powerup1Value);
				break;
			case 3:
				weapon->powerupPointBlankAccuracy(powerup1Value);
				break;
			}
			switch (powerup2Type) {
			case 1:
				weapon->powerupMindAttackCost(powerup2Value);
				break;
			case 2:
				weapon->powerupIdealRange(powerup2Value);
				break;
			case 3:
				weapon->powerupPointBlankAccuracy(powerup2Value);
				break;
			}
		break;
		case GRIP :
			switch (powerup0Type) {
			case 1:
				weapon->powerupIdealRange(powerup0Value);
				break;
			case 2:
				weapon->powerupIdealAccuracy(powerup0Value);
				break;
			case 3:
				weapon->powerupAttackSpeed(powerup0Value);
				break;
			case 4:
				weapon->powerupMindAttackCost(powerup0Value);
				break;
			}
			switch (powerup1Type) {
			case 1:
				weapon->powerupHealthAttackCost(powerup1Value);
				break;
			case 2:
				weapon->powerupMinDamage(powerup1Value);
				break;
			case 3:
				weapon->powerupWoundsRatio(powerup1Value);
				break;
			case 4:
				weapon->powerupMaxRangeAccuracy(powerup1Value);
				break;
			}
			switch (powerup2Type) {
			case 1:
				weapon->powerupHealthAttackCost(powerup2Value);
				break;
			case 2:
				weapon->powerupMinDamage(powerup2Value);
				break;
			case 3:
				weapon->powerupWoundsRatio(powerup2Value);
				break;
			case 4:
				weapon->powerupMaxRangeAccuracy(powerup2Value);
				break;
			}
		break;
		case MUZZLE :
			switch (powerup0Type) {
			case 1:
				weapon->powerupMindAttackCost(powerup0Value);
				break;
			case 2:
				weapon->powerupWoundsRatio(powerup0Value);
				break;
			case 3:
				weapon->powerupMaxRangeAccuracy(powerup0Value);
				break;
			case 4:
				weapon->powerupMaxDamage(powerup0Value);
				break;
			}
			switch (powerup1Type) {
			case 1:
				weapon->powerupPointBlankAccuracy(powerup1Value);
				break;
			case 2:
				weapon->powerupMaxRangeAccuracy(powerup1Value);
				break;
			case 3:
				weapon->powerupMaxRangeAccuracy(powerup1Value);
				break;
			case 4:
				weapon->powerupMinDamage(powerup1Value);
				break;
			}
			switch (powerup2Type) {
			case 1:
				weapon->powerupPointBlankAccuracy(powerup2Value);
				break;
			case 2:
				weapon->powerupMaxRangeAccuracy(powerup2Value);
				break;
			case 3:
				weapon->powerupMaxRangeAccuracy(powerup2Value);
				break;
			case 4:
				weapon->powerupMinDamage(powerup2Value);
				break;
			}
			break;
		case SCOPE :
			switch (powerup0Type) {
			case 1:
				weapon->powerupMaxRangeAccuracy(powerup0Value);
				break;
			case 2:
				weapon->powerupMindAttackCost(powerup0Value);
				break;
			case 3:
				weapon->powerupMinDamage(powerup0Value);
				break;
			case 4:
				weapon->powerupIdealAccuracy(powerup0Value);
				break;
			}
			switch (powerup1Type) {
			case 1:
				weapon->powerupAttackSpeed(powerup1Value);
				break;
			case 2:
				weapon->powerupWoundsRatio(powerup1Value);
				break;
			case 3:
				weapon->powerupActionAttackCost(powerup1Value);
				break;
			}
			switch (powerup2Type) {
			case 1:
				weapon->powerupAttackSpeed(powerup2Value);
				break;
			case 2:
				weapon->powerupWoundsRatio(powerup2Value);
				break;
			case 3:
				weapon->powerupActionAttackCost(powerup2Value);
				break;
			}
		break;
		case STOCK :
			switch (powerup0Type) {
			case 1:
				weapon->powerupMaxRangeAccuracy(powerup0Value);
				break;
			case 2:
				weapon->powerupIdealAccuracy(powerup0Value);
				break;
			case 3:
				weapon->powerupHealthAttackCost(powerup0Value);
				break;
			}
			switch (powerup1Type) {
			case 1:
				weapon->powerupMaxDamage(powerup1Value);
				break;
			case 2:
				weapon->powerupIdealAccuracy(powerup1Value);
				break;
			case 3:
				weapon->powerupActionAttackCost(powerup1Value);
				break;
			case 4:
				weapon->powerupAttackSpeed(powerup1Value);
				break;
			}
			switch (powerup2Type) {
			case 1:
				weapon->powerupMaxDamage(powerup2Value);
				break;
			case 2:
				weapon->powerupIdealAccuracy(powerup2Value);
				break;
			case 3:
				weapon->powerupActionAttackCost(powerup2Value);
				break;
			case 4:
				weapon->powerupAttackSpeed(powerup2Value);
				break;
			}
		break;
		}
	}
	weapon->setPowerupUses(uses);
	weapon->setUpdated(true);

}

void PowerupImplementation::parseItemAttributes() {

	maxCondition = itemAttributes->getMaxCondition();
	conditionDamage = maxCondition - itemAttributes->getCurrentCondition();

	String name = "type";
	type = itemAttributes->getIntAttribute(name);

	name = "subType";
	subType = itemAttributes->getIntAttribute(name);

	name = "powerup0Type";
	powerup0Type = itemAttributes->getIntAttribute(name);
	name = "powerup1Type";
	powerup1Type = itemAttributes->getIntAttribute(name);
	name = "powerup2Type";
	powerup2Type = itemAttributes->getIntAttribute(name);

	name = "powerup0Value";
	powerup0Value = itemAttributes->getFloatAttribute(name);
	name = "powerup1Value";
	powerup1Value = itemAttributes->getFloatAttribute(name);
	name = "powerup2Value";
	powerup2Value = itemAttributes->getFloatAttribute(name);

	name = "uses";
	uses = itemAttributes->getIntAttribute(name);

}

void PowerupImplementation::remove(Player* player) {
	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();

	itemManager->deletePlayerItem(player, _this, false);

	player->removeInventoryItem(objectID);

	BaseMessage* msg = new SceneObjectDestroyMessage(objectID);
	player->sendMessage(msg);

}

void PowerupImplementation::addAttributes(AttributeListMessage* alm) {
	StringBuffer val0;
	StringBuffer val1;
	StringBuffer val2;

	val0 << "+" << powerup0Value << "%";
	val1 << "+" << powerup1Value << "%";
	val2 << "+" << powerup2Value << "%";

	switch (type) {
	case MELEE :
		switch (powerup0Type) {
		case 1:
			alm->insertAttribute("cat_pup.pup_wpn_attack_cost_health", val0.toString());
			break;
		case 2:
			alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_zero", val0.toString());
			break;
		case 3:
			alm->insertAttribute("cat_pup.pup_wpn_attack_cost_mind", val0.toString());
			break;
		case 4:
			alm->insertAttribute("cat_pup.pup_wpn_range_mid", val0.toString());
			break;
		}
		switch (powerup1Type) {
		case 1:
			alm->insertAttribute("cat_pup.pup_wpn_attack_speed", val1.toString());
			break;
		case 2:
			alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_mid", val1.toString());
			break;
		case 3:
			alm->insertAttribute("cat_pup.pup_wpn_damage_min", val1.toString());
			break;
		case 4:
			alm->insertAttribute("cat_pup.pup_wpn_wound_chance", val1.toString());
			break;
		}
		switch (powerup2Type) {
		case 1:
			alm->insertAttribute("cat_pup.pup_wpn_attack_speed", val2.toString());
			break;
		case 2:
			alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_mid", val2.toString());
			break;
		case 3:
			alm->insertAttribute("cat_pup.pup_wpn_damage_min", val2.toString());
			break;
		case 4:
			alm->insertAttribute("cat_pup.pup_wpn_wound_chance", val2.toString());
			break;
		}
		break;
	case RANGED :
		switch (subType) {
		case BARREL :
			switch (powerup0Type) {
			case 1:
				alm->insertAttribute("cat_pup.pup_wpn_attack_cost_health", val0.toString());
				break;
			case 2:
				alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_zero", val0.toString());
				break;
			case 3:
				alm->insertAttribute("cat_pup.pup_wpn_wound_chance", val0.toString());
				break;
			}
			switch (powerup1Type) {
			case 1:
				alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_mid", val1.toString());
				break;
			case 2:
				alm->insertAttribute("cat_pup.pup_wpn_damage_max", val1.toString());
				break;
			case 3:
				alm->insertAttribute("cat_pup.pup_wpn_range_mid", val1.toString());
				break;
			case 4:
				alm->insertAttribute("cat_pup.pup_wpn_attack_cost_mind", val1.toString());
			break;
			}
			switch (powerup2Type) {
			case 1:
				alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_mid", val2.toString());
				break;
			case 2:
				alm->insertAttribute("cat_pup.pup_wpn_damage_max", val2.toString());
				break;
			case 3:
				alm->insertAttribute("cat_pup.pup_wpn_range_mid", val2.toString());
				break;
			case 4:
				alm->insertAttribute("cat_pup.pup_wpn_attack_cost_mind", val2.toString());
			break;
			}
		break;
		case COUPLER :
			switch (powerup0Type) {
			case 1:
				alm->insertAttribute("cat_pup.pup_wpn_damage_max", val0.toString());
				break;
			case 2:
				alm->insertAttribute("cat_pup.pup_wpn_attack_speed", val0.toString());
				break;
			case 3:
				alm->insertAttribute("cat_pup.pup_wpn_damage_min", val0.toString());
				break;
			case 4:
				alm->insertAttribute("cat_pup.pup_wpn_attack_cost_action", val0.toString());
				break;
			}
			switch (powerup1Type) {
			case 1:
				alm->insertAttribute("cat_pup.pup_wpn_attack_cost_mind", val1.toString());
				break;
			case 2:
				alm->insertAttribute("cat_pup.pup_wpn_range_mid", val1.toString());
				break;
			case 3:
				alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_zero", val1.toString());
				break;
			}
			switch (powerup2Type) {
			case 1:
				alm->insertAttribute("cat_pup.pup_wpn_attack_cost_mind", val2.toString());
				break;
			case 2:
				alm->insertAttribute("cat_pup.pup_wpn_range_mid", val2.toString());
				break;
			case 3:
				alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_zero", val2.toString());
				break;
			}
		break;
		case GRIP :
			switch (powerup0Type) {
			case 1:
				alm->insertAttribute("cat_pup.pup_wpn_range_mid", val0.toString());
				break;
			case 2:
				alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_mid", val0.toString());
				break;
			case 3:
				alm->insertAttribute("cat_pup.pup_wpn_attack_speed", val0.toString());
				break;
			case 4:
				alm->insertAttribute("cat_pup.pup_wpn_attack_cost_mind", val0.toString());
				break;
			}
			switch (powerup1Type) {
			case 1:
				alm->insertAttribute("cat_pup.pup_wpn_attack_cost_health", val1.toString());
				break;
			case 2:
				alm->insertAttribute("cat_pup.pup_wpn_damage_min", val1.toString());
				break;
			case 3:
				alm->insertAttribute("cat_pup.pup_wpn_wound_chance", val1.toString());
				break;
			case 4:
				alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_max", val1.toString());
				break;
			}
			switch (powerup2Type) {
			case 1:
				alm->insertAttribute("cat_pup.pup_wpn_attack_cost_health", val2.toString());
				break;
			case 2:
				alm->insertAttribute("cat_pup.pup_wpn_damage_min", val2.toString());
				break;
			case 3:
				alm->insertAttribute("cat_pup.pup_wpn_wound_chance", val2.toString());
				break;
			case 4:
				alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_max", val2.toString());
				break;
			}
		break;
		case MUZZLE :
			switch (powerup0Type) {
			case 1:
				alm->insertAttribute("cat_pup.pup_wpn_attack_cost_mind", val0.toString());
				break;
			case 2:
				alm->insertAttribute("cat_pup.pup_wpn_wound_chance", val0.toString());
				break;
			case 3:
				alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_max", val0.toString());
				break;
			case 4:
				alm->insertAttribute("cat_pup.pup_wpn_damage_max", val0.toString());
				break;
			}
			switch (powerup1Type) {
			case 1:
				alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_zero", val1.toString());
				break;
			case 2:
				alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_max", val1.toString());
				break;
			case 3:
				alm->insertAttribute("cat_pup.pup_wpn_attack_cost_health", val1.toString());
				break;
			case 4:
				alm->insertAttribute("cat_pup.pup_wpn_damage_min", val1.toString());
				break;
			}
			switch (powerup2Type) {
			case 1:
				alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_zero", val2.toString());
				break;
			case 2:
				alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_max", val2.toString());
				break;
			case 3:
				alm->insertAttribute("cat_pup.pup_wpn_attack_cost_health", val2.toString());
				break;
			case 4:
				alm->insertAttribute("cat_pup.pup_wpn_damage_min", val2.toString());
				break;
			}
			break;
		case SCOPE :
			switch (powerup0Type) {
			case 1:
				alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_max", val0.toString());
				break;
			case 2:
				alm->insertAttribute("cat_pup.pup_wpn_attack_cost_mind", val0.toString());
				break;
			case 3:
				alm->insertAttribute("cat_pup.pup_wpn_damage_min", val0.toString());
				break;
			case 4:
				alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_mid", val0.toString());
				break;
			}
			switch (powerup1Type) {
			case 1:
				alm->insertAttribute("cat_pup.pup_wpn_attack_speed", val1.toString());
				break;
			case 2:
				alm->insertAttribute("cat_pup.pup_wpn_wound_chance", val1.toString());
				break;
			case 3:
				alm->insertAttribute("cat_pup.pup_wpn_attack_cost_action", val1.toString());
				break;
			}
			switch (powerup2Type) {
			case 1:
				alm->insertAttribute("cat_pup.pup_wpn_attack_speed", val2.toString());
				break;
			case 2:
				alm->insertAttribute("cat_pup.pup_wpn_wound_chance", val2.toString());
				break;
			case 3:
				alm->insertAttribute("cat_pup.pup_wpn_attack_cost_action", val2.toString());
				break;
			}
		break;
		case STOCK :
			switch (powerup0Type) {
			case 1:
				alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_max", val0.toString());
				break;
			case 2:
				alm->insertAttribute("cat_pup.pup_wpn_range_mid", val0.toString());
				break;
			case 3:
				alm->insertAttribute("cat_pup.pup_wpn_attack_cost_health", val0.toString());
				break;
			}
			switch (powerup1Type) {
			case 1:
				alm->insertAttribute("cat_pup.pup_wpn_damage_max", val1.toString());
				break;
			case 2:
				alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_mid", val1.toString());
				break;
			case 3:
				alm->insertAttribute("cat_pup.pup_wpn_attack_cost_action", val1.toString());
				break;
			case 4:
				alm->insertAttribute("cat_pup.pup_wpn_attack_speed", val1.toString());
				break;
			}
			switch (powerup2Type) {
			case 1:
				alm->insertAttribute("cat_pup.pup_wpn_damage_max", val2.toString());
				break;
			case 2:
				alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_mid", val2.toString());
				break;
			case 3:
				alm->insertAttribute("cat_pup.pup_wpn_attack_cost_action", val2.toString());
				break;
			case 4:
				alm->insertAttribute("cat_pup.pup_wpn_attack_speed", val2.toString());
				break;
			}
		break;
		}
	}
}
