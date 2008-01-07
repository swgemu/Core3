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

#include "system/lang.h"

#include "../../objects.h"

#include "../../Zone.h"
#include "../../ZoneServer.h"

#include "ItemManagerImplementation.h"

ItemManagerImplementation::ItemManagerImplementation(ZoneServer* serv) :
	ItemManagerServant() {
	server = serv;

	nextStaticItemID = 0x90000000;
}

void ItemManagerImplementation::loadStaticWorldObjects() {

}

void ItemManagerImplementation::loadPlayerItems(Player* player) {
	try {
		stringstream query;
		query << "select * from `character_items` where `character_id` = " << player->getCharacterID();
	
		ResultSet* res = ServerDatabase::instance()->executeQuery(query);
		
		/*if (res->size() == 0) {
			delete res;
			
			loadDefaultPlayerItems(player);
			loadDefaultPlayerDatapadItems(player);
			
			return;
		}*/
		
		while (res->next())	{
			createPlayerObject(player, res);
		}
		
		loadDefaultPlayerDatapadItems(player);
		
		delete res;
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
}

void ItemManagerImplementation::createPlayerObject(Player* player, ResultSet* result) {
	uint64 objectid = result->getUnsignedLong(0);

	int objecttype = result->getInt(4);
	uint32 objectcrc = result->getUnsignedInt(3);  
	
	unicode objectname(result->getString(2));
	char* objecttemp = result->getString(5);

	TangibleObjectImplementation* item = NULL;

	bool equipped = result->getBoolean(6);
	if (result->getBoolean(7)==0)	// if NOT deleted
	{
	switch (objecttype) {
	case TangibleObjectImplementation::ROBE:
		item = new WearableImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
		break;
	case TangibleObjectImplementation::WEAPON:
		int weapontype = result->getInt(8);
		
		switch (weapontype) {
		case WeaponImplementation::UNARMED:
			item = new UnarmedMeleeWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case WeaponImplementation::ONEHANDED:
			item = new OneHandedMeleeWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case WeaponImplementation::TWOHANDED:
			item = new TwoHandedMeleeWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case WeaponImplementation::POLEARM:
			item = new PolearmMeleeWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case WeaponImplementation::PISTOL:
			item = new PistolRangedWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case WeaponImplementation::CARBINE:
			item = new CarbineRangedWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case WeaponImplementation::RIFLE:
			item = new RifleRangedWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case WeaponImplementation::ONEHANDSABER:
			item = new OneHandedJediWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case WeaponImplementation::TWOHANDSABER:
			item = new TwoHandedJediWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case WeaponImplementation::POLEARMSABER:
			item = new PolearmJediWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		}
		
		WeaponImplementation* weaponitem = (WeaponImplementation*) item;
		weaponitem->setCategory(result->getInt(9));
		weaponitem->setDamageType(result->getInt(10));
		weaponitem->setMinDamage(result->getFloat(11));
		weaponitem->setMaxDamage(result->getFloat(12));
		weaponitem->setAttackSpeed(result->getFloat(13));
		weaponitem->setHealthAttackCost(result->getInt(14));
		weaponitem->setActionAttackCost(result->getInt(15));
		weaponitem->setMindAttackCost(result->getInt(16));
		weaponitem->setPointBlankAccuracy(result->getInt(17));
		weaponitem->setPointBlankRange(result->getInt(18));
		weaponitem->setIdealRange(result->getInt(19));
		weaponitem->setIdealAccuracy(result->getInt(20));
		weaponitem->setMaxRange(result->getInt(21));
		weaponitem->setMaxRangeAccuracy(result->getInt(22));
		weaponitem->setWoundsRatio(result->getInt(23));
		weaponitem->setArmorPiercing(result->getInt(24));
		weaponitem->setConditionDamage(result->getInt(25));
		weaponitem->setMaxCondition(result->getInt(26));
		weaponitem->setDot0Type(result->getInt(48));
		weaponitem->setDot0Attribute(result->getInt(49));
		weaponitem->setDot0Strength(result->getInt(50));
		weaponitem->setDot0Duration(result->getInt(51));
		weaponitem->setDot0Potency(result->getInt(52));
		weaponitem->setDot0Uses(result->getInt(53));
		weaponitem->setDot1Type(result->getInt(54));
		weaponitem->setDot1Attribute(result->getInt(55));
		weaponitem->setDot1Strength(result->getInt(56));
		weaponitem->setDot1Duration(result->getInt(57));
		weaponitem->setDot1Potency(result->getInt(58));
		weaponitem->setDot1Uses(result->getInt(59));
		weaponitem->setDot2Type(result->getInt(60));
		weaponitem->setDot2Attribute(result->getInt(61));
		weaponitem->setDot2Strength(result->getInt(62));
		weaponitem->setDot2Duration(result->getInt(63));
		weaponitem->setDot2Potency(result->getInt(64));
		weaponitem->setDot2Uses(result->getInt(65));
		weaponitem->setSliced(result->getBoolean(66));		
		break;
	case TangibleObjectImplementation::CLOTH:
		item = new WearableImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
		break;
	case TangibleObjectImplementation::ARMOR:
		item = new ArmorImplementation(objectid, objectcrc, objectname, objecttemp, equipped);

		ArmorImplementation* armoritem = (ArmorImplementation*) item;
		armoritem->setRating(result->getInt(24));
		//((ArmorImplementation*)item)->setCondition(result->getInt(25));
		armoritem->setMaxCondition(result->getInt(26));
		armoritem->setHealthEncumbrance(result->getInt(27));
		armoritem->setActionEncumbrance(result->getInt(28));
		armoritem->setMindEncumbrance(result->getInt(29));	 	
		armoritem->setKinetic(result->getFloat(30));
		armoritem->setKineticIsSpecial(result->getBoolean(31));
		armoritem->setEnergy(result->getFloat(32));
		armoritem->setEnergyIsSpecial(result->getBoolean(33));
		armoritem->setElectricity(result->getFloat(34));
		armoritem->setElectricityIsSpecial(result->getBoolean(35));
		armoritem->setStun(result->getFloat(36));
		armoritem->setStunIsSpecial(result->getBoolean(37));
		armoritem->setBlast(result->getFloat(38));
		armoritem->setBlastIsSpecial(result->getBoolean(39));
		armoritem->setHeat(result->getFloat(40));
		armoritem->setHeatIsSpecial(result->getBoolean(41));
		armoritem->setCold(result->getFloat(42));
		armoritem->setColdIsSpecial(result->getBoolean(43));
		armoritem->setAcid(result->getFloat(44));
		armoritem->setAcidIsSpecial(result->getBoolean(45));
		armoritem->setLightSaber(result->getFloat(46));
		armoritem->setLightSaberIsSpecial(result->getBoolean(47));		
		break;
	case TangibleObjectImplementation::TICKET:
		break;
	case TangibleObjectImplementation::TERMINAL:
		break;
	case TangibleObjectImplementation::INSTRUMENT:
		break;
	default:
		item = new TangibleObjectImplementation(objectid, objectname, objecttemp, objectcrc, equipped);
		break;
	}
	
	if (item == NULL)
		return;
	
	item->setPersistent(true);
	
	TangibleObject* tano = (TangibleObject*) item->deploy();
	
	player->addInventoryItem(tano);
	
	if (equipped && tano->isWeapon())
		player->setWeapon((Weapon*) tano);
	}
}

void ItemManagerImplementation::loadDefaultPlayerItems(Player* player) {
	// clothes
	WearableImplementation* shirtImpl = new WearableImplementation(player, 0x0E08CD84, unicode("Sexah Shirt"), "shirt_s16", true);
	player->addInventoryItem(shirtImpl->deploy());

	WearableImplementation* pantsImpl = new WearableImplementation(player, 0x1D2E8B9A, unicode("Sexah Pants"), "pants_s21", true);
	player->addInventoryItem(pantsImpl->deploy());

	WearableImplementation* shoesImpl = new WearableImplementation(player, 0x08878496, unicode("Sexah Shoes"), "shoes_s02", true);
	player->addInventoryItem(shoesImpl->deploy());

	WearableImplementation* vestImpl = new WearableImplementation(player, 0x717D3696, unicode("Sexah Vest"), "vest_s09", true);
	player->addInventoryItem(vestImpl->deploy());

	// armors
	ArmorImplementation	* chestImpl = new ArmorImplementation(player, 0x7B476F26, unicode("Composite Chestplate"), "armor_composite_chestplate", false);
	player->addInventoryItem(chestImpl->deploy());

	ArmorImplementation* helmetImpl = new ArmorImplementation(player, 0x9AF51EAA, unicode("Composite Helmet"), "armor_composite_helmet", false);
	player->addInventoryItem(helmetImpl->deploy());

	ArmorImplementation* bootsImpl = new ArmorImplementation(player, 0xDB91E9DB, unicode("Composite Boots"), "armor_composite_boots", false);
	player->addInventoryItem(bootsImpl->deploy());

	ArmorImplementation* glovesImpl = new ArmorImplementation(player, 0x2C35FFA2, unicode("Composite Gloves"), "armor_composite_gloves", false);
	player->addInventoryItem(glovesImpl->deploy());

	// weapons
	Weapon* weapon;
	WeaponImplementation* weaoImpl;

	/*weaoImpl = new PolearmJediWeaponImplementation(player, "object/weapon/melee/polearm/crafted_saber/shared_sword_lightsaber_polearm_s2_gen4.iff", 
	deployItemFor(player, weaoImpl, "Weapon");*/

	weaoImpl = new OneHandedMeleeWeaponImplementation(player, "object/weapon/melee/baton/shared_baton_gaderiffi.iff", unicode("Teh Pwn"), "baton_gaderiffi", false);
	player->addInventoryItem(weaoImpl->deploy());

	/*weapon = new Weapon(this, "object/weapon/melee/baton/base/shared_baton_stun.iff", 
	 unicode("Oru's little baby"), "baton_stun", false);
	 inventory->addObject(weapon);*/

	weaoImpl = new UnarmedMeleeWeaponImplementation(player, "object/weapon/melee/special/shared_vibroknuckler.iff",	unicode("Sticker"), "vibroknuckler", false);
	player->addInventoryItem(weaoImpl->deploy());

	weaoImpl = new RifleRangedWeaponImplementation(player, "object/weapon/ranged/rifle/shared_rifle_t21.iff", unicode("Teh Pwn"), "rifle_t21", false);
	player->addInventoryItem(weaoImpl->deploy());

	weaoImpl = new PistolRangedWeaponImplementation(player, "object/weapon/ranged/pistol/shared_pistol_cdef.iff", unicode("Teh Pwn Pistol"), "pistol_cdef", false);
	player->addInventoryItem(weaoImpl->deploy());

	weaoImpl = new CarbineRangedWeaponImplementation(player, "object/weapon/ranged/carbine/shared_carbine_cdef.iff", unicode("Teh Pwn Carbine"), "carbine_cdef", false);
	player->addInventoryItem(weaoImpl->deploy());

	weaoImpl = new PolearmMeleeWeaponImplementation(player, "object/weapon/melee/polearm/shared_lance_vibrolance.iff", unicode("Teh Pwn Lance"), "lance_vibrolance", false);
	player->addInventoryItem(weaoImpl->deploy());

	weaoImpl = new TwoHandedMeleeWeaponImplementation(player, "object/weapon/melee/2h_sword/shared_2h_sword_maul.iff", unicode("Teh Pwn Battle Hammer"), "2h_sword_battleaxe", false);
	player->addInventoryItem(weaoImpl->deploy());
	

	//Slitherhorn
	InstrumentImplementation* instruImpl = new InstrumentImplementation(player, 0xD2A2E607, unicode("The Pwn Slitherhorn"), "obj_slitherhorn", InstrumentImplementation::SLITHERHORN);
	player->addInventoryItem(instruImpl->deploy());

	/*
	 //Fizz
	 instrument = new Instrument(player, 0xBC38A9B, unicode("The Pwn Fizz"), "obj_fizzz", Instrument::FIZZ);
	 player->addInventoryItem(instrument);
	 
	 //Fanfar
	 instrument = new Instrument(player, 0x78A47467, unicode("The Pwn Fanfar"), "obj_fanfar", Instrument::FANFAR);
	 player->addInventoryItem(instrument);
	 
	 //Kloohorn
	 instrument = new Instrument(player, 0xFDFBC3BC, unicode("The Pwn Kloohorn"), "obj_kloo_horn", Instrument::KLOOHORN);
	 player->addInventoryItem(instrument);
	 
	 //Mandoviol
	 instrument = new Instrument(player, 0x6A58CECB, unicode("The Pwn Mandoviol"), "obj_mandoviol", Instrument::MANDOVIOL);
	 player->addInventoryItem(instrument);
	 
	 //Traz
	 instrument = new Instrument(player, 0x179316A2, unicode("The Pwn Traz"), "obj_traz", Instrument::TRAZ);
	 player->addInventoryItem(instrument);
	 
	 //Bandfill
	 instrument = new Instrument(player, 0x31FE6B97, unicode("The Pwn Bandfill"), "obj_bandfill", Instrument::BANDFILL);
	 player->addInventoryItem(instrument);
	 
	 //Flutedroopy
	 instrument = new Instrument(player, 0x46B975A6, unicode("The Pwn Flutedroopy"), "obj_growdi_flute", Instrument::FLUTEDROOPY);
	 player->addInventoryItem(instrument);
	 
	 //Can't equip these, have you drop them in the world.
	 //Omnibox
	 instrument = new Instrument(player, 0x77D28DF3, unicode("The Pwn Omnibox"), "obj_ommni_box", Instrument::OMNIBOX);
	 player->addInventoryItem(instrument);
	 
	 //Nalargon
	 instrument = new Instrument(player, 0x8FC48010, unicode("The Pwn Nalargon"), "obj_nalargon", Instrument::NALARGON);
	 player->addInventoryItem(instrument);
	 */
}

void ItemManagerImplementation::loadDefaultPlayerDatapadItems(Player* player) {
	// SWOOP
	MountCreatureImplementation* swoopImpl = new MountCreatureImplementation(player, "speederbike_swoop", "monster_name",
			String::hashCode("object/intangible/vehicle/shared_speederbike_swoop_pcd.iff"), 0xAF6D9F4F, player->getNewItemID());
	MountCreature* swoop = (MountCreature*) swoopImpl->deploy();
	swoop->addToDatapad();

	// flash speeder	
	MountCreatureImplementation* flashImpl = new MountCreatureImplementation(player, "speederbike_flash", "monster_name", String::hashCode("object/intangible/vehicle/shared_speederbike_flash_pcd.iff"), 
			0x4E3534, player->getNewItemID());
	MountCreature* flash = (MountCreature*) flashImpl->deploy();
	flash->addToDatapad();

	// landspeeder
	MountCreatureImplementation* landImpl = new MountCreatureImplementation(player, "landspeeder_x31", "monster_name",
		String::hashCode("object/intangible/vehicle/shared_landspeeder_x31_pcd.iff"), 0x273A9C02, player->getNewItemID());
	MountCreature* land = (MountCreature*) landImpl->deploy();
	land->addToDatapad();

	// xp 38 doesnt work
	/*MountCreatureImplementation* land2Impl = new MountCreatureImplementation(player, "landspeeder_xp38", "monster_name", 
	 String::hashCode("object/intangible/vehicle/shared_vehicle_pcd_base.iff"), 0x3F6E7BA7, player->getNewItemID());
	 stringstream Land2;
	 Land2 << "Mount" << land2Impl->getObjectID();
	 MountCreature* land2 = (MountCreature*) ObjectRequestBroker::instance()->deploy(Land2.str(), land2Impl);
	 land2->addToDatapad();*/

	// x34
	MountCreatureImplementation* land3Impl = new MountCreatureImplementation(player, "landspeeder_x34", "monster_name",
		String::hashCode("object/intangible/vehicle/shared_landspeeder_x34_pcd.iff"), 0x4EC3780C, player->getNewItemID());
	MountCreature* land3 = (MountCreature*) land3Impl->deploy();
	land3->addToDatapad();

	// av21
	MountCreatureImplementation* land4Impl = new MountCreatureImplementation(player, "landspeeder_av21", "monster_name",
		String::hashCode("object/intangible/vehicle/shared_landspeeder_av21_pcd.iff"), 0xA965DDBA, player->getNewItemID());
	MountCreature* land4 = (MountCreature*) land4Impl->deploy();
	land4->addToDatapad();

	// speederbike
	MountCreatureImplementation* speedImpl = new MountCreatureImplementation(player, "speederbike", "monster_name",
		String::hashCode("object/intangible/vehicle/shared_speederbike_pcd.iff"), 0x729517EF, player->getNewItemID());
	MountCreature* speed = (MountCreature*) speedImpl->deploy();
	speed->addToDatapad();

	// jetpack
	/*MountCreatureImplementation* jetImpl = new MountCreatureImplementation(player, "jetpack", "monster_name", 
	 String::hashCode("object/intangible/vehicle/shared_jetpack_pcd.iff"), 0x60250B32, player->getNewItemID());
	 jetImpl->setInstantMount(true);
	 stringstream Jet;
	 Jet << "Mount" << jetImpl->getObjectID();
	 MountCreature* jet = (MountCreature*) ObjectRequestBroker::instance()->deploy(Jet.str(), jetImpl);
	 jet->addToDatapad();*/	
}

void ItemManagerImplementation::unloadPlayerItems(Player* player) {
	Inventory* inventory = player->getInventory();

	for (int i = 0; i < inventory->objectsSize(); ++i) {
		TangibleObject* item = (TangibleObject*) inventory->getObject(i);
		
		if (!item->isPersistent()) {
			if (item->isWeapon())
				createPlayerWeapon(player, (Weapon*) item);
			else if (item->isArmor())
				createPlayerArmor(player, (Armor*) item);
			else 
				createPlayerItem(player, item);
		} else if (item->isUpdated()) {
			savePlayerItem(player, item);
		}
	}
}

void ItemManagerImplementation::createPlayerItem(Player* player, TangibleObject* item) {
	try {
		stringstream query;
		query << "INSERT INTO `character_items` "
			  << "(`item_id`,`character_id`,`name`,`template_crc`,`template_type`,`template_name`,`equipped`)"
			  << " VALUES(" << item->getObjectID() << "," << player->getCharacterID() 
			  << ",'" << item->getName().c_str() << "'," 
			  << item->getObjectCRC() << "," << item->getObjectSubType() << ",'" << item->getTemplateName() << "',"
			  << item->isEquipped() << ")";
	
		ServerDatabase::instance()->executeStatement(query);
		
		item->setPersistent(true);
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
}

void ItemManagerImplementation::savePlayerItem(Player* player, TangibleObject* item) {
	try {
		stringstream query;
		query << "update `character_items` set equipped = " << item->isEquipped();
		query << ", character_id = " << player->getCharacterID() << " ";

		if (item->isWeapon()) {
			query << ", condition_damage = " << ((Weapon*) item)->getConditionDamage();
			query << ", max_condition = " << ((Weapon*) item)->getMaxCondition();
			
			query << ", min_damage = " << ((Weapon*) item)->getMinDamage();
			query << ", max_damage = " << ((Weapon*) item)->getMaxDamage();
			
			query << ", attack_speed = " << ((Weapon*) item)->getAttackSpeed();
			
			query << ", sliced = " << ((Weapon*) item)->isSliced();
				
			query << ", dot0_uses = " << ((Weapon*) item)->getDot0Uses();
			query << ", dot1_uses = " << ((Weapon*) item)->getDot1Uses();
			query << ", dot2_uses = " << ((Weapon*) item)->getDot2Uses() << " ";
		}

		query << "where item_id = " << item->getObjectID();
		
		ServerDatabase::instance()->executeStatement(query);
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
}

void ItemManagerImplementation::createPlayerWeapon(Player* player, Weapon* item) {
	try { 
		stringstream query;
		query << "INSERT INTO `character_items` "
			  << "(`item_id`,`character_id`,`name`,`template_crc`,`template_type`,`template_name`,`equipped`,`weapon_type`,`category`,`damage_type`,`min_damage`,`max_damage`,`attack_speed`,`health_attack_cost`,`action_attack_cost`,`mind_attack_cost`,`point_blank_accuracy`,`point_blank_range`,`ideal_range`,`ideal_accuracy`,`max_range`,`max_range_accuracy`,`wounds_ratio`,`armor_piercing`,`condition_damage`,`max_condition`,`dot0_type`,`dot0_attribute`,`dot0_strength`,`dot0_duration`,`dot0_potency`,`dot0_uses`,`dot1_type`,`dot1_attribute`,`dot1_strength`,`dot1_duration`,`dot1_potency`,`dot1_uses`,`dot2_type`,`dot2_attribute`,`dot2_strength`,`dot2_duration`,`dot2_potency`,`dot2_uses`,`sliced`)"
			  << " VALUES(" << item->getObjectID() << "," << player->getCharacterID() 
			  << ",'\\" << item->getName().c_str() << "'," 
			  << item->getObjectCRC() << "," << item->getObjectSubType() << ",'" << item->getTemplateName() << "',"  
			  << item->isEquipped() << "," << item->getType() << "," << item->getCategory() << "," << item->getDamageType() << "," 
			  << item->getMinDamage() << "," << item->getMaxDamage() << "," << item->getAttackSpeed() << "," << item->getHealthAttackCost() << ","
			  << item->getActionAttackCost() << "," << item->getMindAttackCost() << "," << item->getPointBlankAccuracy() <<  ","  
			  << item->getPointBlankRange() << "," << item->getIdealRange() << "," << item->getIdealAccuracy() << "," 
			  << item->getMaxRange() << "," << item->getMaxRangeAccuracy() << "," << item->getWoundsRatio() << "," 
			  << item->getArmorPiercing() << "," << item->getConditionDamage() << "," << item->getMaxCondition() << "," 
			  << item->getDot0Type() << "," << item->getDot0Attribute() << "," 
			  << item->getDot0Strength() << "," << item->getDot0Duration() << "," << item->getDot0Potency() << "," 
			  << item->getDot0Uses() << "," << item->getDot1Type() << "," << item->getDot1Attribute() << "," 
			  << item->getDot1Strength() << "," << item->getDot1Duration() << "," << item->getDot1Potency() << "," 
			  << item->getDot1Uses() << "," << item->getDot2Type() << "," << item->getDot2Attribute() << "," 
			  << item->getDot2Strength() << "," << item->getDot2Duration() << "," << item->getDot2Potency() << "," 
			  << item->getDot2Uses() << "," << item->isSliced() << ")";
		
		ServerDatabase::instance()->executeStatement(query);
		
		item->setPersistent(true);
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
}

void ItemManagerImplementation::createPlayerArmor(Player* player, Armor* item) {
	try {
		stringstream query;
		query << "INSERT INTO `character_items` "
			  << "(`item_id`,`character_id`,`name`,`template_crc`,`template_type`,`template_name`,`equipped`,`category`,`armor_piercing`,`max_condition`,`health_encumb`,`action_encumb`,`mind_encumb`,`kinetic`,`kinetic_special`,`energy`,`energy_special`,`electricity`,`electricity_special`,`stun`,`stun_special`,`blast`,`blast_special`,`heat`,`heat_special`,`cold`,`cold_special`,`acid`,`acid_special`,`lightsaber`,`lightsaber_special`)"
			  << " VALUES(" << item->getObjectID() << "," << player->getCharacterID() 
			  << ",'\\" << item->getName().c_str() << "'," 
			  << item->getObjectCRC() << "," << item->getObjectSubType() << ",'" << item->getTemplateName() << "',"  
			  << item->isEquipped() << "," << item->getRating() << "," << 0 << "," 
			  << item->getMaxCondition() << "," << item->getHealthEncumbrance() << "," << item->getActionEncumbrance() << "," 
			  << item->getMindEncumbrance() << "," << item->getKinetic() << "," << item->isKineticSpecial() <<  ","  
			  << item->getEnergy() << "," << item->isEnergySpecial() << "," << item->getElectricity() << "," 
			  << item->isElectricitySpecial() << "," << item->getStun() << "," << item->isStunSpecial() << "," 
			  << item->getBlast() << "," << item->isBlastSpecial() << "," << item->getHeat() << "," << item->isHeatSpecial() << "," 
			  << item->getCold() << "," << item->isColdSpecial() << "," << item->getAcid() << "," << item->isAcidSpecial() << "," 
			  << item->getLightSaber() << "," << item->isLightSaberSpecial() << ")";
		
		ServerDatabase::instance()->executeStatement(query);
		
		item->setPersistent(true);
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
}

void ItemManagerImplementation::deletePlayerItem(Player* player, TangibleObject* item) {
	try {	
		stringstream query;
		query << "update `character_items` set deleted = " << 1 << " where item_id = " << item->getObjectID();
	
		ServerDatabase::instance()->executeStatement(query);

		player->sendSystemMessage("Item deleted.");
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
}

void ItemManagerImplementation::showDbStats(Player* player) {
	stringstream txt;
	txt << "Database Statistics\n";
	
	try {
		stringstream query;
		query << "select * from `character_items`";
		
		ResultSet* res = ServerDatabase::instance()->executeQuery(query);
		
		txt << res->size() << " total items in the database\n";
		
		delete res;
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
	
	try {
		stringstream query;
		query << "select * from `character_items` where `character_id` = " << player->getCharacterID() << " and `deleted` = 1";
		
		ResultSet* res = ServerDatabase::instance()->executeQuery(query);
		
		txt << res->size() << " deleted items in the database.\n";
		
		delete res;
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
	
	try {
		stringstream query;
		query << "select * from `character_items` where `character_id` = " << player->getCharacterID() << " and `template_type` = 2";
		
		ResultSet* res = ServerDatabase::instance()->executeQuery(query);
		
		txt << res->size() << " Weapon Items, ";
		
		delete res;
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
	
	try {
		stringstream query;
		query << "select * from `character_items` where `character_id` = " << player->getCharacterID() << " and `template_type` = 3";
		
		ResultSet* res = ServerDatabase::instance()->executeQuery(query);
		
		txt << res->size() << " Clothing Items, ";
		
		delete res;
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
	
	try {
		stringstream query;
		query << "select * from `character_items` where `character_id` = " << player->getCharacterID() << " and `template_type` = 4";
		
		ResultSet* res = ServerDatabase::instance()->executeQuery(query);
		
		txt << res->size() << " Armor Items.\n";
		
		delete res;
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
	
	try {
		stringstream query;
		query << "SELECT * FROM `character_items` WHERE `deleted` = 0 ORDER BY `max_damage` DESC LIMIT 10";
		
		ResultSet* res = ServerDatabase::instance()->executeQuery(query);
		
		txt << "Top 10 Weapons by Max Damage\n";
		
		while (res->next()) {
			if (res->getInt(4) == 2) {
				txt << "ObjID: " << res->getUnsignedLong(0) << " Name: " << res->getString(2) 
					<< "\\#ffffff MinDmg: " << res->getFloat(11) << " MaxDmg: " << res->getFloat(12) 
					<< " Spd: " << res->getFloat(13) << "\n";
			}
		}
		
		delete res;
		
		player->sendSystemMessage(txt.str());
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
	
	try {
		stringstream query;
		query << "SELECT * FROM `character_items` WHERE `deleted` = 0 ORDER BY `dot1_strength` DESC LIMIT 10";
		
		ResultSet* res = ServerDatabase::instance()->executeQuery(query);
		
		txt << "Top 10 Weapons by DOT Strength\n";
		
		while (res->next()) {
			if (res->getInt(4) == 2) {
				txt << "ObjID: " << res->getUnsignedLong(0) << " Name: " << res->getString(2) 
					<< "\\#ffffff MinDmg: " << res->getFloat(11) << " MaxDmg: " << res->getFloat(12) 
					<< " Spd: " << res->getFloat(13) << " Strength: " << res->getInt(57) 
					<< " Potency: " << res->getInt(59) << "\n";
			}
		}
		
		delete res;
		
		player->sendSystemMessage(txt.str());
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
	
	player->sendSystemMessage(txt.str());
}

void ItemManagerImplementation::showDbDeleted(Player* player) {
	try {
		stringstream query;
		query << "select * from `character_items` where `character_id` = " << player->getCharacterID() << " and `deleted` = 1";
		
		ResultSet* res = ServerDatabase::instance()->executeQuery(query);
		
		stringstream txt;
		
		while (res->next()) {
			if (res->getInt(4) == 2) {
				txt << "ObjID: " << res->getUnsignedLong(0) << " Name: " << res->getString(2) 
					<< "\\#ffffff MinDmg: " << res->getFloat(11) << " MaxDmg: " << res->getFloat(12) 
					<< " Spd: " << res->getFloat(13) << "\n";
			} else if (res->getInt(4) == 4) {
				txt << "ObjID: " << res->getUnsignedLong(0) << " Name: " << res->getString(2) 
				<< "\\#ffffff Resists: " << res->getFloat(30) << " " << res->getFloat(32) << " " 
				<< res->getFloat(34) << " " << res->getFloat(36) << " " << res->getFloat(38) << " " 
				<< res->getFloat(40) << " " << res->getFloat(42) << " " << res->getFloat(44) << " " 
				<< res->getFloat(46) << "\n";
			} else {
				txt << "ObjID: " << res->getUnsignedLong(0) << " Name: " << res->getString(2) << "\\#ffffff \n";
			}
		}
		
		player->sendSystemMessage(txt.str());
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}						
}

void ItemManagerImplementation::purgeDbDeleted(Player* player) {
	try {
		stringstream query;
		query << "DELETE FROM `character_items` WHERE `deleted` = 1";
		
		ServerDatabase::instance()->executeStatement(query);

		player->sendSystemMessage("Deleted items purged.");
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
}
