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
#include "../tangible/weapons/WeaponImplementation.h"
#include "../tangible/instrument/Instrument.h"

#include "engine/engine.h"

// This could be moved to wearable or armor
/*static const char* enhancements[] =
{
	"no_enhancement", "melee_defense", "ranged_defense", "stun_defense",
	"dizzy_defense", "blind_defense", "knockdown_defense", "intimidate_defense",
	"pistol_speed",	"carbine_speed", "rifle_speed", "unarmed_speed",
	"onehandmelee_speed", "twohandmelee_speed", "polearm_speed", "pistol_accuracy",
	"carbine_accuracy",	"rifle_accuracy", "unarmed_accuracy", "onehandmelee_accuracy",
	"twohandmelee_accuracy", "polearm_accuracy", "dodge", "block",
	"counterattack", "resistance_bleeding",	"resistance_disease", "resistance_fire",
	"resistance_poison", "slope_move", "heavyweapon_speed", "heavyweapon_accuracy"
};*/

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
	Vector<ManagedReference<Wearable> > clothingLocations;
	//Wearable* clothingLocations[15];
	ManagedReference<Weapon> weapon;
	ManagedReference<Instrument> instrument;

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
	static const uint16 PSG = 0x2000;	// Personal shield generator - uses belt slot
	static const uint16 EYES = 0x4000;

public:
	EquippedItems(Player* plyr) {
		player = plyr;
		for (int i = 0; i < 15; i++)
			clothingLocations.add(NULL);

		weapon = NULL;
		instrument = NULL;
		armorEquipped = 0;

		totalHealthEncumbrance = totalActionEncumbrance = totalMindEncumbrance = 0;
	}

	const static char* getInstrumentSkill(int idx) {
		if (idx > 10)
			throw ArrayIndexOutOfBoundsException(idx);

		return instrumentSkills[idx];
	}

	/*const static char* getEnhancement(int idx) {
		if (idx > 31)
			throw ArrayIndexOutOfBoundsException(idx);

		return enhancements[idx];
	}*/

	void equipItem (TangibleObject* item) {
		if (item->isArmor() || item->isClothing() || item->isWearableContainer())
			changeWearable((Wearable*)item);
		else if (item->isWeapon() || item->isInstrument())
			changeWeapon(item);
	}

	bool changeWearable (Wearable* item, bool forced = false){
		if (item->isEquipped())
			return unequipClothing(item);
		else
			return equipClothing(item, forced);
	}

	bool changeWeapon (TangibleObject* item ) {
		if (item->isEquipped())
			return unequipWeapon(item);
		else
			return equipWeapon(item);
	}

	bool equipClothing (Wearable* item, bool forced = false) {
		uint16 locations;
		int locationIndex;
		Armor* armor;

		if(!checkPermissions(item)) { // Can player equip item
			return false;
		}

		switch (item->getObjectSubType()) {

		case TangibleObjectImplementation::WOOKIEGARB:
			locations = getWookieWearLocations(item);
			break;

		case TangibleObjectImplementation::VEST:
		case TangibleObjectImplementation::CAPE:
			locations = CHEST;
			break;
		case TangibleObjectImplementation::JACKET:
			locations = CHEST + ARMS;
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
		case TangibleObjectImplementation::SKIRT:
			locations = LEGS;
			break;

		case TangibleObjectImplementation::WEARABLECONTAINER:
			locations = PACK; //
			break;

		case TangibleObjectImplementation::ARMOR:
		case TangibleObjectImplementation::BODYARMOR:
		case TangibleObjectImplementation::HEADARMOR:
		case TangibleObjectImplementation::MISCARMOR:
		case TangibleObjectImplementation::LEGARMOR:
		case TangibleObjectImplementation::ARMARMOR:
		case TangibleObjectImplementation::HANDARMOR:
		case TangibleObjectImplementation::FOOTARMOR:
			armor = (Armor*)item;
			locations = getArmorLocations(armor);

			locationIndex = getLocationOfArmor(armor);

			if(locationIndex == -1)
				return false;

			if (!checkEncumbrance(armor, clothingLocations.get(locationIndex)) && !forced) {
				player->sendSystemMessage("You don't have enough pool points to do that!");
				return false;
			}
			armorEquipped++;
			break;

		case TangibleObjectImplementation::SHIELDGENERATOR:
			locations = PSG + BELT;
			break;

		default:
			locations = SHIRT + ARMS + LEGS + CHEST;
			//System::out << "Unknown clothing type " << item->getObjectSubType() << endl;
			break;
		}

		int currentLocation = 1; // Chest
		for (int i = 0; i < 15; i++) {
			if (locations & currentLocation) { // new item occupies the current location
				if ((clothingLocations.get(i) != NULL) && (item != clothingLocations.get(i)))
					// This location already has another item equipped
					unequipClothing(i); // So unequip it
				clothingLocations.setElementAt(i, item);  // Equip the new item
			}
			currentLocation <<= 1;
		}

		if (locations != 0) {

			item->onEquip(player);

			calculateCurrentEncumbrance();

			player->equipItem((TangibleObject*) item);

			return true;
		} else
			return false;
	}

	int getLocationOfArmor(Armor* armor) {
		int type = armor->getArmorPiece();

		type -= 256;
		if(type < 0 || type > 14)
			type = -1;

		return type;
	}

	bool unequipClothing (Wearable* it) {
		ManagedReference<Wearable> item = it;

		bool equipped = false;

		for (int i = 0; i < 15; i++)
			if (clothingLocations.get(i) == item) {
				clothingLocations.setElementAt(i, NULL);
				equipped = true;
			}

		if (!equipped) {
			return false;
		}

		it->onUnequip(player);

		calculateCurrentEncumbrance();

		player->unequipItem((TangibleObject*)item);

		if (item->isArmor())
			armorEquipped--;

		return true;
	}

	void unequipClothing (uint16 location) {
		Wearable* item = clothingLocations.get(location);
		if (item == NULL)
			return;
		unequipClothing(item);
	}

	void calculateCurrentEncumbrance() {

		totalHealthEncumbrance = 0;
		totalActionEncumbrance = 0;
		totalMindEncumbrance = 0;

		Wearable* item;

		for (int i = 0; i < 15; i++) {
			item = (Wearable*)clothingLocations.get(i);

			if(item != NULL) {
				totalHealthEncumbrance += item->getHealthEncumbrance();
				totalActionEncumbrance += item->getActionEncumbrance();
				totalMindEncumbrance += item->getMindEncumbrance();
			}
		}
	}

	bool equipWeapon(TangibleObject* item) {
		if (!checkCertification(item))
			return false;

		if (weapon != NULL)
			unequipWeapon(weapon);
		else if (instrument != NULL)
			unequipWeapon(instrument);

		if (item->isWeapon()) {
			if (!checkPermissions(item) && !item->isEquipped())
				return false;
			weapon = (Weapon*)item;
			//setWeaponSkillMods(weapon);
			player->setWeaponAccuracy(weapon);
			player->setWeapon(weapon);

			uint32 aimMod = 0;

			if (weapon->isRanged()) {
				aimMod = player->getSkillMod("aim");

				switch (weapon->getType()) {
				case WeaponImplementation::RIFLE:
					aimMod += player->getSkillMod("rifle_aim");
					break;
				case WeaponImplementation::PISTOL:
					aimMod += player->getSkillMod("pistol_aim");
					break;
				case WeaponImplementation::CARBINE:
					aimMod += player->getSkillMod("carbine_aim");
					break;
				}
			}

			player->setAimMod(aimMod);

			if (player->isInCover() && (weapon->getType() != WeaponImplementation::RIFLE)) {
				player->clearState(CreatureState::COVER);
			}

			weapon->onEquip(player);
		} else {
			instrument = (Instrument*)item;
			player->setWeaponAccuracy(NULL);
			player->setWeapon(NULL);
		}

		player->equipItem(item);

		return true;
	}

	bool unequipWeapon(TangibleObject* it) {
		ManagedReference<TangibleObject> item = it;

		if (player->isPlayingMusic())
			player->stopPlayingMusic();

		if (item->isWeapon()) {
			item->onUnequip(player);
			weapon = NULL;
			//unsetWeaponSkillMods((Weapon*)item.get());
			player->setWeaponAccuracy(NULL);
			player->setAimMod(0);
		} else {
			instrument = NULL;
		}

		player->unequipItem(item);

		return true;
	}

	Wearable* getClothing (int location) {
		return clothingLocations.get(location);
	}

	Armor* getArmor (int location) {
		if (location > 14 || location < 0) {
			System::out << "Illegal clothing location " << location << endl;
			return NULL;
		}
		if (clothingLocations.get(location) == NULL || !clothingLocations.get(location)->isArmor()) {
			return NULL;
		} else {
			return (Armor*)clothingLocations.get(location).get();
		}
	}

	Weapon* getWeapon () {
		return weapon;
	}

	Instrument* getInstrument () {
		return instrument;
	}

	// This needs to be redesigned
	int getWookieWearLocations(Wearable* item) {
		int locations = 0;

		switch (item->getObjectCRC()) {

		case 0x3A8B7EDB:
		case 0xE19CD64C:
		case 0xA891B1C1:
		case 0x53729AD5:
			locations = HANDS;
			break;

		case 0x8895F73:
		case 0xF504D4EC:
		case 0xBC09B361:
		case 0x2E137C7B:
			locations = HEAD;
			break;

		case 0x4D2E3347:
		case 0x8A12762E:
		case 0x10ECD9BF:
			locations = CHEST + SHIRT + ARMS + LEGS;
			break;

		case 0xA661FA2D:
		case 0x7D7652BA:
		case 0x347B3537:
		case 0xCF981E23:
			locations = CHEST + SHIRT;
			break;

		case 0x481D5BDD:
		case 0x930AF34A:
			locations = CHEST;
			break;

		case 0xAE7ADF27:
		case 0x756D77B0:
		case 0x3C60103D:
		case 0xC7833B29:
			locations = LEGS;
			break;
		}
		return locations;
	}

	int getArmorLocations(Armor* armor) {
		int locations;

		//System::out << "Adding armor location " << armor->getArmorType() << endl;
		// Add extra locations covered for Wookie
		switch (armor->getObjectCRC()) {

		// Wookie armours
		case 0xE11CC6F9:  // Kashyykian Hunting Chest
		case 0x9F9C111B:  // Kashyykian Black Mountain chest
		case 0x8BA52D06:  // Kashyykian Ceremonial chest
			locations = CHEST + HEAD  + LEFT_UPPERARM  + RIGHT_UPPERARM + HANDS;
			break;
		case 0xF198491B:  // Kashyykian Hunting leggings
		case 0x2BAFC7:   // Kashyykian Black Mountain leggings
		case 0x894B355B:  // Kashyykian Ceremonial leggings
			locations = LEGS + FEET;
			break;

		default:
			locations = 0x1 << (armor->getArmorPiece());
			if (locations == HEAD)
				locations += EYES;
			break;
		}

		return locations;
	}

	/*void setWeaponSkillMods(Weapon* weapon) {
		setItemSkillMod(weapon->getSkillMod0Type(), weapon->getSkillMod0Value());
		setItemSkillMod(weapon->getSkillMod1Type(), weapon->getSkillMod1Value());
		setItemSkillMod(weapon->getSkillMod2Type(), weapon->getSkillMod2Value());
	}

	void unsetWeaponSkillMods(Weapon* weapon) {
		setItemSkillMod(weapon->getSkillMod0Type(), -weapon->getSkillMod0Value());
		setItemSkillMod(weapon->getSkillMod1Type(), -weapon->getSkillMod1Value());
		setItemSkillMod(weapon->getSkillMod2Type(), -weapon->getSkillMod2Value());
	}*/

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

	bool checkPermissions(TangibleObject* item) {
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

			// Needs to be refactored
			String skillBox = getInstrumentSkill(instrument);

			if (!player->getSkillBoxesSize() || !player->hasSkillBox(skillBox)) {
				player->sendSystemMessage("You do not have sufficient abilities to equip " + item->getCustomName().toString() + ".");
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

	/*void setItemSkillMod(int type, int value) {
		if (type == 0)
			return;

		String enhanceName = getEnhancement(type);
		player->addSkillModBonus(enhanceName, value, true);
	}*/

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
