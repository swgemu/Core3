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

#ifndef EQUIPPEDITEMS_H_
#define EQUIPPEDITEMS_H_

#include "../tangible/wearables/Wearable.h"
#include "../tangible/wearables/Armor.h"
#include "../tangible/weapons/Weapon.h"
#include "../tangible/instrument/Instrument.h"

// This could be moved to wearable or armor
static const char* enhancements[] =
{
	"no_enhancement", "melee_defense", "ranged_defense", "stun_defense",
	"dizzy_defense", "blind_defense", "knockdown_defense", "intimidate_defense",
	"pistol_speed",	"carbine_speed", "rifle_speed", "unarmed_speed",
	"onehandmelee_speed", "twohandmelee_speed", "polearm_speed", "pistol_accuracy",
	"carbine_accuracy",	"rifle_accuracy", "unarmed_accuracy", "onehandmelee_accuracy",
	"twohandmelee_accuracy", "polearm_accuracy", "dodge", "block",
	"counterattack", "resistance_bleeding",	"resistance_disease", "resistance_fire",
	"resistance_poison", "slope_move", "heavyweapon_speed", "heavyweapon_accuracy"
};

// This could be move to instrument
static const char* instrumentSkills[] =
{
		"no_instrument",
		"social_musician_novice", // Traz
		"social_entertainer_novice", // Slitherhorn
		"social_entertainer_music_03", // Fanfar
		"social_musician_knowledge_03", // Flutedroopy?
		"social_entertainer_music_04", // Kloohorn
		"social_entertainer_music_01", // Fizz
		"social_musician_knowledge_02", // Bandfill
		"social_musician_knowledge_04", // Omnibox
		"social_musician_master", // Nalargon
		"social_entertainer_master"  // Mandoviol
};

class EquippedItems {
protected:
	Player* player;
	Wearable* clothingLocations[15];
	Weapon* weapon;
	Instrument* instrument;

	int armorEquipped;

	int totalHealthEncumbrance;
	int totalActionEncumbrance;
	int totalMindEncumbrance;

	static const int MALE = 0x01;
	static const int FEMALE = 0x02;
	static const int NEUTRAL = 0x1000;
	static const int IMPERIAL = 0x2000;
	static const int REBEL = 0x4000;
	static const int COVERT = 0x8000;

	// Areas covered
	static const uint16 CHEST = 0x0001;
	static const uint16 HANDS = 0x0002;
	static const uint16 LEFT_FOREARM = 0x0004;
	static const uint16 LEFT_UPPERARM = 0x0008;
	static const uint16 RIGHT_FOREARM = 0x0010;
	static const uint16 RIGHT_UPPERARM = 0x0020;
	static const uint16 ARMS = 0x003C;
	static const uint16 LEGS = 0x0040;
	static const uint16 FEET = 0x0080;
	static const uint16 HEAD = 0x0100;
	static const uint16 BELT = 0x0200;  // special case as a belt can go over most clothing
	static const uint16 SHIRT = 0x0400;  // special case as a shirt can go under most clothing.
	static const uint16 PACK = 0x0800;
	static const uint16 BANDOLIER = 0x1000;
	static const uint16 PSG = 0x2000;	// Personal shield generator
	static const uint16 EYES = 0x4000;

public:
	EquippedItems(Player* plyr) {
		player = plyr;
		for (int i = 0; i < 15; i++)
			clothingLocations[i] = NULL;

		weapon = NULL;
		instrument = NULL;
		armorEquipped = 0;

		totalHealthEncumbrance = totalActionEncumbrance = totalMindEncumbrance = 0;
	}

	void equipItem (TangibleObject* item) {
		if (item->isArmor() || item->isClothing() || item->isWearableContainer())
			changeWearable((Wearable*)item);
//		else if (item->isWeapon() || item->isInstrument())
//			changeWeapon(item);
	}

	bool changeWearable (Wearable* item, bool forced = false){
		if (item->isEquipped())
			return unequipClothing(item);
		else
			return equipClothing(item, forced);
	}
/*
	bool changeWeapon (TangibleObject* item ) {
		if (item->isEquipped())
			return unequipWeapon(item);
		else
			return equipWeapon(item);
	}
*/
	bool equipClothing (Wearable* item, bool forced = false) {
		uint16 locations;

		if(!checkPermissions(item)) { // Can player equip item
			return false;
		}

		switch (item->getObjectSubType()) {
		case TangibleObjectImplementation::VEST:
		case TangibleObjectImplementation::JACKET:
		case TangibleObjectImplementation::CAPE:
			locations = CHEST;
			break;

		case TangibleObjectImplementation::BANDOLIER:
			locations = BANDOLIER;
			break;

		case TangibleObjectImplementation::ROBE:
			locations = CHEST + ARMS + LEGS;

		case TangibleObjectImplementation::CLOAK:
			locations = CHEST + ARMS + HEAD;
			break;

		case TangibleObjectImplementation::DRESS:
		case TangibleObjectImplementation::BODYSUIT:
			locations = SHIRT + ARMS + LEGS + CHEST;
			break;

		case TangibleObjectImplementation::SHIRT:
			locations = SHIRT;
			break;

		case TangibleObjectImplementation::BELT:
			locations = BELT;
			break;

		case TangibleObjectImplementation::FOOTWEAR:
			locations = FEET;
			break;

		case TangibleObjectImplementation::HANDWEAR:
			locations = HANDS;
			break;

		case TangibleObjectImplementation::EYEWEAR:
			locations = EYES;
			break;

		case TangibleObjectImplementation::HEADWEAR:
			locations = HEAD;
			break;

		case TangibleObjectImplementation::PANTS:
			locations = LEGS;
			break;

		case TangibleObjectImplementation::WEARABLECONTAINER:
			locations = PACK; // TODO: Add pack contents to inventory on unequip.
			break;

		case TangibleObjectImplementation::ARMOR:
		case TangibleObjectImplementation::BODYARMOR:
		case TangibleObjectImplementation::MISCARMOR:
		case TangibleObjectImplementation::LEGARMOR:
		case TangibleObjectImplementation::ARMARMOR:
		case TangibleObjectImplementation::HANDARMOR:
		case TangibleObjectImplementation::FOOTARMOR:
			// TODO: Special cases for Wookie, Ithorian etc armour
			Armor* armor = (Armor*)item;
			locations = getArmorLocations(armor);

			if (!checkEncumbrance(armor, clothingLocations[armor->getArmorType()]) && !forced) {
				player->sendSystemMessage("You don't have enough pool points to do that!");
				return false;
			}
			armorEquipped++;
			break;

		case TangibleObjectImplementation::SHIELDGENERATOR:
			locations = PSG;
			break;

		default:
			System::out << "Unknown clothing type " << item->getObjectSubType() << endl;
			break;
		}

		int currentLocation = 1; // Chest
		for (int i = 0; i < 15; i++) {
			if (locations & currentLocation) { // new item occupies the current location
				if ((clothingLocations[i] != NULL) && (item != clothingLocations[i]))
					// This location already has another item equipped
					unequipClothing(i); // So unequip it
				clothingLocations[i] = item;  // Equip the new item
			}
			currentLocation <<= 1;
		}
		addEnhancements(item);
		addEncumbrance(item, forced);

		player->equipItem((TangibleObject*) item);

		return true;
	}

	bool unequipClothing (Wearable* item) {
		bool equipped = false;

		for (int i = 0; i < 15; i++)
			if (clothingLocations[i] == item) {
				clothingLocations[i] = NULL;
				equipped = true;
			}

		if (!equipped)
			return false;

		removeEnhancements(item);
		removeEncumbrance(item);
		player->unequipItem((TangibleObject*)item);

		if (item->isArmor())
			armorEquipped--;

		return true;
	}

	void unequipClothing (uint16 location) {
		Wearable* item = clothingLocations[location];
		if (item == NULL)
			return;
		unequipClothing(item);
	}

/*
	bool equipWeapon(TangibleObject* item) {
		if (!checkCertification(item))
			return false;

		if (weapon != NULL)
			unequipWeapon(weapon);
		else if (instrument != NULL)
			unequipWeapon(instrument);

		if (item->isWeapon()) {
			weapon = (Weapon*)item;
			setWeaponSkillMods(weapon);
			player->setWeaponAccuracy(weapon);
			player->setWeapon(weapon);
		} else {
			instrument = (Instrument*)item;
			player->setWeaponAccuracy(NULL);
			player->setWeapon(NULL);
		}

		player->equipItem(item);

		return true;
	}

	bool unequipWeapon(TangibleObject* item) {
		if (player->isPlayingMusic())
			player->stopPlayingMusic();

		if (item->isWeapon()) {
			weapon = NULL;
			unsetWeaponSkillMods((Weapon*)item);
			player->setWeaponAccuracy(NULL);
		} else {
			instrument = NULL;
		}

		player->unequipItem(item);

		return true;
	}
*/
	Wearable* getClothing (int location) {
		return clothingLocations[location];
	}

	Armor* getArmor (int location) {
		if (location > 14 || location < 0) {
			System::out << "Illegal clothing location " << location << endl;
			return NULL;
		}
		if (clothingLocations[location] == NULL || !clothingLocations[location]->isArmor()) {
			return NULL;
		} else {
			return (Armor*)clothingLocations[location];
		}
	}
/*
	Weapon* getWeapon () {
		return weapon;
	}

	Instrument* getInstrument () {
		return instrument;
	}
*/
	int getArmorLocations(Armor* armor) {
		int locations;

		// Add extra locations covered for Wookie etc. and optional mini-suits
		switch (armor->getObjectCRC()) {

		// Wookie armours
		// TODO: Find out about protection for hands
		case 0xE11CC6F9:  // Kashyykian Hunting Chest
		case 0x9F9C111B:  // Kashyykian Black Mountain chest
		case 0x8BA52D06:  // Kashyykian Ceremonial chest
			locations = CHEST + HEAD  + LEFT_UPPERARM  + RIGHT_UPPERARM;
			break;
		case 0xF198491B:  // Kashyykian Hunting leggings
		case 0x2BAFC7:   // Kashyykian Black Mountain leggings
		case 0x894B355B:  // Kashyykian Ceremonial leggings
			locations = LEGS + FEET;
			break;

		default:
			locations = 0x1 << (armor->getArmorType() - 1);
			if (locations == HEAD)
				locations += EYES;
			break;
		}

		return locations;
	}
/*
	void setWeaponSkillMods(Weapon* weapon) {
		setItemSkillMod(weapon->getSkillMod0Type(), weapon->getSkillMod0Value());
		setItemSkillMod(weapon->getSkillMod1Type(), weapon->getSkillMod1Value());
		setItemSkillMod(weapon->getSkillMod2Type(), weapon->getSkillMod2Value());
	}

	void unsetWeaponSkillMods(Weapon* weapon) {
		setItemSkillMod(weapon->getSkillMod0Type(), -weapon->getSkillMod0Value());
		setItemSkillMod(weapon->getSkillMod1Type(), -weapon->getSkillMod1Value());
		setItemSkillMod(weapon->getSkillMod2Type(), -weapon->getSkillMod2Value());
	}
*/
	bool checkEncumbrance(Armor* item, Wearable* originalitem) {
		int strength = player->getStrength();
		int constitution = player->getConstitution();
		int quickness = player->getQuickness();
		int stamina = player->getStamina();
		int focus = player->getFocus();
		int willpower = player->getWillpower();

		if (originalitem != NULL && originalitem->isArmor()) {
			Armor* originalArmor = (Armor*)originalitem;
			strength += originalArmor->getHealthEncumbrance();
			constitution += originalArmor->getHealthEncumbrance();
			quickness += originalArmor->getActionEncumbrance();
			stamina += originalArmor->getActionEncumbrance();
			focus += originalArmor->getMindEncumbrance();
			willpower += originalArmor->getMindEncumbrance();
		}

		int healthEncumb = item->getHealthEncumbrance();
		int actionEncumb = item->getActionEncumbrance();
		int mindEncumb = item->getMindEncumbrance();

		if (healthEncumb >= strength || healthEncumb >= constitution ||
			actionEncumb >= quickness || actionEncumb >= stamina ||
			mindEncumb >= focus || mindEncumb >= willpower)
			return false;
		else
			return true;
	}

	bool checkPermissions(Wearable* item) {
		uint16 maskRes = ~(item->getPlayerUseMask()) & player->getCharacterMask();

		if (maskRes == 0) {
			return true;
		} else if (maskRes == COVERT) {
			player->sendSystemMessage("You can not use this item while on leave.");
			return false;
		} else if (maskRes & (COVERT | REBEL | IMPERIAL | NEUTRAL)) {
			player->sendSystemMessage("You are not the proper faction to use this item.");
			return false;
		} else if (maskRes & 0x0FFC) {
			player->sendSystemMessage("Your species can not use this item.");
			return false;
		} else if (maskRes & (MALE | FEMALE)) {
			player->sendSystemMessage("This item is not appropriate for your gender.");
			return false;
		}

		//should never get here
		player->sendSystemMessage("There was an error, while trying to equip this item.");
		return false;
	}

	bool checkCertification(TangibleObject* item) {

		if (item->isInstrument()) {
			int instrument = ((Instrument*)item)->getInstrumentType();

			String skillBox;
			// Needs to be refactored
			skillBox = instrumentSkills[instrument];
			if (!player->getSkillBoxesSize() || !player->hasSkillBox(skillBox)) {
				player->sendSystemMessage("You do not have sufficient abilities to equip " + item->getName().toString() + ".");
				return false;
			}

			if (player->isPlayingMusic())
				player->stopPlayingMusic();

			return true;

		} else if (item->isWeapon()) {
			if (player->checkCertification(((Weapon*)item)->getCert())) {
				((Weapon*)item)->setCertified(true);
			} else {
				player->sendSystemMessage("You are not certified to use this weapon. Damage will be reduced.");
				((Weapon*)item)->setCertified(false);
			}
			return true;
		}
		return true;
	}

	void addEnhancements(Wearable* item) {
		// TODO: CAs need to be added
		if (!item->isArmor())
			return;

		Armor* armoritem = (Armor*)item;

		setItemSkillMod(armoritem->getSkillMod0Type(), armoritem->getSkillMod0Value());
		setItemSkillMod(armoritem->getSkillMod1Type(), armoritem->getSkillMod1Value());
		setItemSkillMod(armoritem->getSkillMod2Type(), armoritem->getSkillMod2Value());

		setItemSkillMod(armoritem->getSocket0Type(), armoritem->getSocket0Value());
		setItemSkillMod(armoritem->getSocket1Type(), armoritem->getSocket1Value());
		setItemSkillMod(armoritem->getSocket2Type(), armoritem->getSocket2Value());
		setItemSkillMod(armoritem->getSocket3Type(), armoritem->getSocket3Value());

	}

	void removeEnhancements(Wearable* item) {
		// TODO: CAs need to be added
		if (!item->isArmor())
			return;

		Armor* armoritem = (Armor*)item;

		setItemSkillMod(armoritem->getSkillMod0Type(), -armoritem->getSkillMod0Value());
		setItemSkillMod(armoritem->getSkillMod1Type(), -armoritem->getSkillMod1Value());
		setItemSkillMod(armoritem->getSkillMod2Type(), -armoritem->getSkillMod2Value());

		setItemSkillMod(armoritem->getSocket0Type(), -armoritem->getSocket0Value());
		setItemSkillMod(armoritem->getSocket1Type(), -armoritem->getSocket1Value());
		setItemSkillMod(armoritem->getSocket2Type(), -armoritem->getSocket2Value());
		setItemSkillMod(armoritem->getSocket3Type(), -armoritem->getSocket3Value());
	}

	void setItemSkillMod(int type, int value) {
		if (type == 0)
			return;

		String enhanceName = enhancements[type];
		player->addSkillModBonus(enhanceName, value, true);
	}

	void removeEncumbrance(Wearable* item) {
		if (!item->isArmor())
			return;
		Armor* armor = (Armor*)item;

		totalHealthEncumbrance -= armor->getHealthEncumbrance();
		totalActionEncumbrance -= armor->getActionEncumbrance();
		totalMindEncumbrance -= armor->getMindEncumbrance();

		player->unsetArmorEncumbrance(armor);
	}

	void addEncumbrance(Wearable* item, bool forced) {
		if (!item->isArmor())
			return;

		Armor* armor = (Armor*)item;

		totalHealthEncumbrance += armor->getHealthEncumbrance();
		totalActionEncumbrance += armor->getActionEncumbrance();
		totalMindEncumbrance += armor->getMindEncumbrance();

		player->setArmorEncumbrance(armor, forced);
	}

	int getHealthEncumbrance() {
		return totalHealthEncumbrance;
	}

	int getActionEncumbrance() {
		return totalActionEncumbrance;
	}

	int getMindEncumbrance() {
		return totalMindEncumbrance;
	}

	bool hasArmorEquipped() {
		if (armorEquipped > 0)
			return true;
		else
			return false;
	}

};

#endif /* EQUIPPEDITEMS_H_ */
