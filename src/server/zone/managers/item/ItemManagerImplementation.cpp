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
				
		while (res->next())	{
			createPlayerObject(player, res);
		}
		
		loadDefaultPlayerDatapadItems(player);
		
		delete res;
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
}

TangibleObject* ItemManagerImplementation::getPlayerItem(Player* player, uint64 objectid) {
	TangibleObject* tano = NULL;
	
	SceneObject* item = player->getPlayerItem(objectid);
	
	if (item != NULL && item->isTangible())
		return (TangibleObject*) item;

	try {
		stringstream query;
		query << "select * from `character_items` where `item_id` = " << objectid;
	
		ResultSet* res = ServerDatabase::instance()->executeQuery(query);
				
		while (res->next())	{
			tano = createPlayerObject(player, res);
		}
		
		delete res;

	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
	
	return tano;
}

TangibleObject* ItemManagerImplementation::createPlayerObject(Player* player, ResultSet* result) {
	uint64 objectid = result->getUnsignedLong(0);

	int objecttype = result->getInt(4);
	uint32 objectcrc = result->getUnsignedInt(3);  
	
	unicode objectname(result->getString(2));
	char* objecttemp = result->getString(5); // template_name
	
	string appearance = result->getString(10);
	BinaryData cust(appearance);
	string custStr;
	cust.decode(custStr);

	TangibleObjectImplementation* item = NULL;
	
	bool equipped = result->getBoolean(7);
	
	if (result->getBoolean(8) != 0) // deleted
		return NULL;
	
	string attributes = result->getString(9);
	
	if (objecttype & TangibleObjectImplementation::WEAPON || objecttype & TangibleObjectImplementation::LIGHTSABER) {	
		switch (objecttype) {
		case TangibleObjectImplementation::MELEEWEAPON:
			item = new UnarmedMeleeWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::ONEHANDMELEEWEAPON:
			item = new OneHandedMeleeWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::TWOHANDMELEEWEAPON:
			item = new TwoHandedMeleeWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::POLEARM:
			item = new PolearmMeleeWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::PISTOL:
			item = new PistolRangedWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::CARBINE:
			item = new CarbineRangedWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::RIFLE:
			item = new RifleRangedWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::ONEHANDSABER:
			item = new OneHandedJediWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::TWOHANDSABER:
			item = new TwoHandedJediWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::POLEARMSABER:
			item = new PolearmJediWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::SPECIALHEAVYWEAPON:
			item = new SpecialHeavyRangedWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::HEAVYWEAPON:
			item = new HeavyRangedWeaponImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		}
		
	} else if (objecttype & TangibleObjectImplementation::CLOTHING) {
		
		item = new WearableImplementation(objectid, objectcrc, objectname, objecttemp, equipped);

	} else if (objecttype & TangibleObjectImplementation::ARMOR) {
	
		item = new ArmorImplementation(objectid, objectcrc, objectname, objecttemp, equipped);

	} else if (objecttype & TangibleObjectImplementation::MISC) {
		
		switch (objecttype) {
		case TangibleObjectImplementation::TRAVELTICKET:
			
			item = new TicketImplementation(objectid, objectcrc, objectname, objecttemp);
			
			break;
		case TangibleObjectImplementation::INSTRUMENT:
			
			item = new InstrumentImplementation(objectid, objectcrc, objectname, objecttemp, equipped);
			
			break;
		case TangibleObjectImplementation::CLOTHINGATTACHMENT:
			
			item = new AttachmentImplementation(objectid, AttachmentImplementation::CLOTHING);

			break;
		case TangibleObjectImplementation::ARMORATTACHMENT:

			item = new AttachmentImplementation(objectid, AttachmentImplementation::ARMOR);
			
			break;
		}
	} else if (objecttype & TangibleObjectImplementation::SURVEYTOOL) {
	
		item = new SurveyToolImplementation(objectid, objectcrc, objectname, objecttemp, player);

	} else if (objecttype & TangibleObjectImplementation::WEAPONPOWERUP) {

		item = new PowerupImplementation(objectid, objectcrc, objectname, objecttemp);
	
	} else if (objecttype & TangibleObjectImplementation::RESOURCECONTAINER) {
		switch (objecttype) {
		case TangibleObjectImplementation::ENERGYGAS:
		case TangibleObjectImplementation::ENERGYLIQUID:
		case TangibleObjectImplementation::ENERGYRADIOACTIVE:
		case TangibleObjectImplementation::ENERGYSOLID:
		case TangibleObjectImplementation::INORGANICCHEMICAL:
		case TangibleObjectImplementation::INORGANICGAS:
		case TangibleObjectImplementation::INORGANICMINERAL:
		case TangibleObjectImplementation::WATER:
		case TangibleObjectImplementation::ORGANICFOOD:
		case TangibleObjectImplementation::ORGANICHIDE:
		case TangibleObjectImplementation::ORGANICSTRUCTURAL:
			item = new ResourceContainerImplementation(objectid, objectcrc, objectname, objecttemp, player);

			break;
		}
	}
	
	if (item == NULL)
		return NULL;
	
	item->setAttributes(attributes);
	item->parseItemAttributes();
	
	item->setCustomizationString(custStr);
	
	
	item->setPersistent(true);
	
	TangibleObject* tano = (TangibleObject*) item->deploy();
	
	player->addInventoryItem(tano);
	
	if (equipped && tano->isWeapon()) {
		player->setWeapon((Weapon*) tano);
		player->setWeaponSkillMods((Weapon*) tano);
	}
	
	if (equipped && tano->isArmor()) {
		tano->setEquipped(false);
		player->changeArmor(tano->getObjectID(), true);
	}
	
	return tano;
}

void ItemManagerImplementation::loadDefaultPlayerItems(Player* player) {
	Weapon* weapon;
	WeaponImplementation* weaoImpl;
	
	string certification;


	if (player->getRaceFileName().find("wookie") !=string::npos) {
		
		// Wookie clothing
		WearableImplementation* hoodImpl = new WearableImplementation(player, 0xF504D4EC, unicode("Wookie Hood"), "wke_hood_s02", true);
		player->addInventoryItem(hoodImpl->deploy());

		WearableImplementation* skirtImpl = new WearableImplementation(player, 0x756D77B0, unicode("Wookie Skirt"), "wke_skirt_s02", true);
		player->addInventoryItem(skirtImpl->deploy());
		
		WearableImplementation* shirtImpl = new WearableImplementation(player, 0x7D7652BA, unicode("Wookie Shirt"), "wke_shirt_s02", true);
		player->addInventoryItem(shirtImpl->deploy());

		
		// Wookie armor
		ArmorImplementation	* chestImpl = new ArmorImplementation(player, 0xE11CC6F9, unicode("Kasshyykian Hunting Armor Chestplate"), "armor_kashyyykian_hunting_chest_plate", false);
		chestImpl->setType(ArmorImplementation::CHEST);
		player->addInventoryItem(chestImpl->deploy());

		ArmorImplementation* pantsImpl = new ArmorImplementation(player, 0xF198491B, unicode("Kasshyykian Hunting Armor Leggings"), "armor_kashyyykian_hunting_leggings", false);
		pantsImpl->setType(ArmorImplementation::LEG);
		player->addInventoryItem(pantsImpl->deploy());

		ArmorImplementation* bracerlImpl = new ArmorImplementation(player, 0x7EBC9404, unicode("Kasshyykian Hunting Armor Bracer"), "armor_kashyyykian_hunting_bracer_l", false);
		bracerlImpl->setType(ArmorImplementation::BRACERL);
		player->addInventoryItem(bracerlImpl->deploy());

		ArmorImplementation* bracerrImpl = new ArmorImplementation(player, 0xE69D197, unicode("Kasshyykian Hunting Armor Bracer"), "armor_kashyyykian_hunting_bracer_r", false);
		bracerrImpl->setType(ArmorImplementation::BRACERR);
		player->addInventoryItem(bracerrImpl->deploy());

		weaoImpl = new RifleRangedWeaponImplementation(player, "object/weapon/ranged/rifle/shared_rifle_bowcaster.iff", unicode("Bowcaster"), "bowcaster", false);
		weaoImpl->setDamageType(WeaponImplementation::ENERGY);
		weaoImpl->setArmorPiercing(WeaponImplementation::HEAVY);
		player->addInventoryItem(weaoImpl->deploy());

	} else if (player->getRaceFileName().find("ithorian") !=string::npos) {
		
		// clothes
		WearableImplementation* shirtImpl = new WearableImplementation(player, 0xA141D2A4, unicode("Ithorian Shirt"), "ith_shirt_s02", true);
		player->addInventoryItem(shirtImpl->deploy());

		WearableImplementation* pantsImpl = new WearableImplementation(player, 0x9849E919, unicode("Sexah Pants"), "ith_pants_s02", true);
		player->addInventoryItem(pantsImpl->deploy());

		WearableImplementation* vestImpl = new WearableImplementation(player, 0xB8CF50D5, unicode("Sexah Vest"), "ith_vest_s02", true);
		player->addInventoryItem(vestImpl->deploy());


		// armors
		ArmorImplementation	* chestImpl = new ArmorImplementation(player, 0x169D55D8, unicode("Ithorian Sentinel Armor Chestplate"), "ith_armor_s03_chest_plate", false);
		chestImpl->setType(ArmorImplementation::CHEST);
		player->addInventoryItem(chestImpl->deploy());

		ArmorImplementation* helmetImpl = new ArmorImplementation(player, 0x24E0753F, unicode("Ithorian Sentinel Armor Helmet"), "ith_armor_s03_helmet", false);
		helmetImpl->setType(ArmorImplementation::HEAD);
		player->addInventoryItem(helmetImpl->deploy());

		ArmorImplementation* bootsImpl = new ArmorImplementation(player, 0xECE5898D, unicode("Ithorian Sentinel Armor Boots"), "ith_armor_s03_boots", false);
		bootsImpl->setType(ArmorImplementation::FOOT);
		player->addInventoryItem(bootsImpl->deploy());

		ArmorImplementation* glovesImpl = new ArmorImplementation(player, 0x92209437, unicode("Ithorian Sentinel Armor Gloves"), "ith_armor_s03_gloves", false);
		glovesImpl->setType(ArmorImplementation::HAND);
		player->addInventoryItem(glovesImpl->deploy());
	
		ArmorImplementation* pants2Impl = new ArmorImplementation(player, 0x2F35FD70, unicode("Ithorian Sentinel Armor Leggings"), "ith_armor_s03_leggings", false);
		pants2Impl->setType(ArmorImplementation::LEG);
		player->addInventoryItem(pants2Impl->deploy());

		ArmorImplementation* biceplImpl = new ArmorImplementation(player, 0x877F6265, unicode("Ithorian Sentinel Armor Bicep"), "ith_armor_s03_bicep_l", false);
		biceplImpl->setType(ArmorImplementation::BICEPL);
		player->addInventoryItem(biceplImpl->deploy());

		ArmorImplementation* biceprImpl = new ArmorImplementation(player, 0xF7AA27F6, unicode("Ithorian Sentinel Armor Bicep"), "ith_armor_s03_bicep_r", false);
		biceprImpl->setType(ArmorImplementation::BICEPR);
		player->addInventoryItem(biceprImpl->deploy());

		ArmorImplementation* bracerlImpl = new ArmorImplementation(player, 0xA011206F, unicode("Ithorian Sentinel Armor Bracer"), "ith_armor_s03_bracer_l", false);
		bracerlImpl->setType(ArmorImplementation::BRACERL);
		player->addInventoryItem(bracerlImpl->deploy());

		ArmorImplementation* bracerrImpl = new ArmorImplementation(player, 0xD0C465FC, unicode("Ithorian Sentinel Armor Bracer"), "ith_armor_s03_bracer_r", false);
		bracerrImpl->setType(ArmorImplementation::BRACERR);
		player->addInventoryItem(bracerrImpl->deploy());

	} else {
		
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
		chestImpl->setType(ArmorImplementation::CHEST);
		player->addInventoryItem(chestImpl->deploy());

		ArmorImplementation* helmetImpl = new ArmorImplementation(player, 0x9AF51EAA, unicode("Composite Helmet"), "armor_composite_helmet", false);
		helmetImpl->setType(ArmorImplementation::HEAD);
		player->addInventoryItem(helmetImpl->deploy());

		ArmorImplementation* bootsImpl = new ArmorImplementation(player, 0xDB91E9DB, unicode("Composite Boots"), "armor_composite_boots", false);
		bootsImpl->setType(ArmorImplementation::FOOT);
		player->addInventoryItem(bootsImpl->deploy());

		ArmorImplementation* glovesImpl = new ArmorImplementation(player, 0x2C35FFA2, unicode("Composite Gloves"), "armor_composite_gloves", false);
		glovesImpl->setType(ArmorImplementation::HAND);
		player->addInventoryItem(glovesImpl->deploy());
	
		ArmorImplementation* pants2Impl = new ArmorImplementation(player, 0xC294C432, unicode("Composite Leggings"), "armor_composite_pants", false);
		pants2Impl->setType(ArmorImplementation::LEG);
		player->addInventoryItem(pants2Impl->deploy());

		ArmorImplementation* biceplImpl = new ArmorImplementation(player, 0x13A4DA11, unicode("Composite Bicep"), "armor_composite_bicep_l", false);
		biceplImpl->setType(ArmorImplementation::BICEPL);
		player->addInventoryItem(biceplImpl->deploy());

		ArmorImplementation* biceprImpl = new ArmorImplementation(player, 0x63719F82, unicode("Composite Bicep"), "armor_composite_bicep_r", false);
		biceprImpl->setType(ArmorImplementation::BICEPR);
		player->addInventoryItem(biceprImpl->deploy());

		ArmorImplementation* bracerlImpl = new ArmorImplementation(player, 0x4DB0192D, unicode("Composite Bracer"), "armor_composite_bracer_l", false);
		bracerlImpl->setType(ArmorImplementation::BRACERL);
		player->addInventoryItem(bracerlImpl->deploy());

		ArmorImplementation* bracerrImpl = new ArmorImplementation(player, 0x3D655CBE, unicode("Composite Bracer"), "armor_composite_bracer_r", false);
		bracerrImpl->setType(ArmorImplementation::BRACERR);
		player->addInventoryItem(bracerrImpl->deploy());

	}
	
	// weapons

	//weaoImpl = new PolearmJediWeaponImplementation(player, "object/weapon/melee/polearm/crafted_saber/shared_sword_lightsaber_polearm_s2_gen4.iff", 
	//deployItemFor(player, weaoImpl, "Weapon");

	weaoImpl = new OneHandedMeleeWeaponImplementation(player, "object/weapon/melee/baton/shared_baton_gaderiffi.iff", unicode("Teh Pwn"), "baton_gaderiffi", false);
	weaoImpl->setDamageType(WeaponImplementation::KINETIC);
	weaoImpl->setArmorPiercing(WeaponImplementation::NONE);
	certification = "cert_baton_gaderiffi";
	weaoImpl->setCert(certification);
	player->addInventoryItem(weaoImpl->deploy());

	weaoImpl = new UnarmedMeleeWeaponImplementation(player, "object/weapon/melee/special/shared_vibroknuckler.iff",	unicode("Sticker"), "vibroknuckler", false);
	certification = "cert_vibroknuckler";
	weaoImpl->setCert(certification);
	player->addInventoryItem(weaoImpl->deploy());

	weaoImpl = new RifleRangedWeaponImplementation(player, "object/weapon/ranged/rifle/shared_rifle_t21.iff", unicode("Teh Pwn"), "rifle_t21", false);
	weaoImpl->setDamageType(WeaponImplementation::ENERGY);
	weaoImpl->setArmorPiercing(WeaponImplementation::HEAVY);
	certification = "cert_rifle_t21";
	weaoImpl->setCert(certification);
	player->addInventoryItem(weaoImpl->deploy());

	weaoImpl = new PistolRangedWeaponImplementation(player, "object/weapon/ranged/pistol/shared_pistol_cdef.iff", unicode("Teh Pwn Pistol"), "pistol_cdef", false);
	weaoImpl->setDamageType(WeaponImplementation::ENERGY);
	weaoImpl->setArmorPiercing(WeaponImplementation::NONE);
	player->addInventoryItem(weaoImpl->deploy());

	weaoImpl = new CarbineRangedWeaponImplementation(player, "object/weapon/ranged/carbine/shared_carbine_cdef.iff", unicode("Teh Pwn Carbine"), "carbine_cdef", false);
	weaoImpl->setDamageType(WeaponImplementation::ENERGY);
	weaoImpl->setArmorPiercing(WeaponImplementation::NONE);
	player->addInventoryItem(weaoImpl->deploy());

	weaoImpl = new PolearmMeleeWeaponImplementation(player, "object/weapon/melee/polearm/shared_lance_vibrolance.iff", unicode("Teh Pwn Lance"), "lance_vibrolance", false);
	weaoImpl->setDamageType(WeaponImplementation::ELECTRICITY);
	weaoImpl->setArmorPiercing(WeaponImplementation::LIGHT);
	certification = "cert_lance_vibrolance";
	weaoImpl->setCert(certification);
	player->addInventoryItem(weaoImpl->deploy());

	weaoImpl = new TwoHandedMeleeWeaponImplementation(player, "object/weapon/melee/2h_sword/shared_2h_sword_maul.iff", unicode("Teh Pwn Battle Hammer"), "2h_sword_battleaxe", false);
	weaoImpl->setDamageType(WeaponImplementation::BLAST);
	weaoImpl->setArmorPiercing(WeaponImplementation::MEDIUM);
	certification = "cert_sword_2h_maul";
	weaoImpl->setCert(certification);
	player->addInventoryItem(weaoImpl->deploy());

	// Survey tools
	SurveyToolImplementation* minSurvImpl = new SurveyToolImplementation(player, 0xAA9AB32C, unicode("Mineral Survey Tool"), "survey_tool_mineral");
	player->addInventoryItem(minSurvImpl->deploy());
	
	SurveyToolImplementation* solSurvImpl = new SurveyToolImplementation(player, 0x8B95C48D, unicode("Solar Survey Tool"), "survey_tool_solar");
	player->addInventoryItem(solSurvImpl->deploy());
		
	SurveyToolImplementation* chemSurvImpl = new SurveyToolImplementation(player, 0x85A7C02A, unicode("Chemical Survey Tool"), "survey_tool_chemical");
	player->addInventoryItem(chemSurvImpl->deploy());
			
	SurveyToolImplementation* floSurvImpl = new SurveyToolImplementation(player, 0x4F38AD50, unicode("Flora Survey Tool"), "survey_tool_flora");
	player->addInventoryItem(floSurvImpl->deploy());
	
	SurveyToolImplementation* gasSurvImpl = new SurveyToolImplementation(player, 0x3F1F6443, unicode("Gas Survey Tool"), "survey_tool_gas");
	player->addInventoryItem(gasSurvImpl->deploy());
	
	//SurveyToolImplementation* geoSurvImpl = new SurveyToolImplementation(player, 0xAA9AB32C, unicode("Geothermal Survey Tool"), "survey_tool_geothermal");
	//player->addInventoryItem(geoSurvImpl->deploy());

	SurveyToolImplementation* watSurvImpl = new SurveyToolImplementation(player, 0x81AE2438, unicode("Water Survey Tool"), "survey_tool_water");
	player->addInventoryItem(watSurvImpl->deploy());
	
	SurveyToolImplementation* windSurvImpl = new SurveyToolImplementation(player, 0x21C39BD0, unicode("Wind Survey Tool"), "survey_tool_wind");
	player->addInventoryItem(windSurvImpl->deploy());
	
	// crafting tools
	CraftingToolImplementation* clothingTool = new CraftingToolImplementation(player, 0x2CED1748,	unicode("Clothing and Armor Crafting Tool"), "clothing_tool");
	player->addInventoryItem(clothingTool->deploy());
 
	CraftingToolImplementation* foodTool = new CraftingToolImplementation(player, 0xA9D9972F,	unicode("Food and Chemical Crafting Tool"), "food_tool");
	player->addInventoryItem(foodTool->deploy());
 
	CraftingToolImplementation* genericTool = new CraftingToolImplementation(player, 0x3EE5146D,	unicode("Generic Crafting Tool"), "generic_tool");
	player->addInventoryItem(genericTool->deploy());
 
	CraftingToolImplementation* lightsaberTool = new CraftingToolImplementation(player, 0x2CF24272,	unicode("Lightsaber Crafting Tool"), "jedi_tool");
	player->addInventoryItem(lightsaberTool->deploy());
 
	CraftingToolImplementation* starshipTool = new CraftingToolImplementation(player, 0xAD0E3DB0,	unicode("Starship Crafting Tool"), "space_tool");
	player->addInventoryItem(starshipTool->deploy());
 
	CraftingToolImplementation* structureTool = new CraftingToolImplementation(player, 0xFEDA0435,	unicode("Structure and Furniture Crafting Tool"), "structure_tool");
	player->addInventoryItem(structureTool->deploy());
 
	CraftingToolImplementation* weaponTool = new CraftingToolImplementation(player, 0x64F6D031,	unicode("Weapon Droid and General Item Crafting Tool"), "weapon_tool");
	player->addInventoryItem(weaponTool->deploy());
	
	//Slitherhorn
	InstrumentImplementation* instruImpl = new InstrumentImplementation(player, 0xD2A2E607, unicode("The Pwn Slitherhorn"), "obj_slitherhorn", InstrumentImplementation::SLITHERHORN);
	player->addInventoryItem(instruImpl->deploy());

	 //Fizz
	 //instrument = new Instrument(player, 0xBC38A9B, unicode("The Pwn Fizz"), "obj_fizzz", Instrument::FIZZ);
	 //player->addInventoryItem(instrument);
	 
	 //Fanfar
	 //instrument = new Instrument(player, 0x78A47467, unicode("The Pwn Fanfar"), "obj_fanfar", Instrument::FANFAR);
	 //player->addInventoryItem(instrument);
	 
	 //Kloohorn
	 //instrument = new Instrument(player, 0xFDFBC3BC, unicode("The Pwn Kloohorn"), "obj_kloo_horn", Instrument::KLOOHORN);
	 //player->addInventoryItem(instrument);
	 
	 //Mandoviol
	 //instrument = new Instrument(player, 0x6A58CECB, unicode("The Pwn Mandoviol"), "obj_mandoviol", Instrument::MANDOVIOL);
	 //player->addInventoryItem(instrument);
	 
	 //Traz
	 //instrument = new Instrument(player, 0x179316A2, unicode("The Pwn Traz"), "obj_traz", Instrument::TRAZ);
	 //player->addInventoryItem(instrument);
	 
	 //Bandfill
	 //instrument = new Instrument(player, 0x31FE6B97, unicode("The Pwn Bandfill"), "obj_bandfill", Instrument::BANDFILL);
	 //player->addInventoryItem(instrument);
	 
	 //Flutedroopy
	 //instrument = new Instrument(player, 0x46B975A6, unicode("The Pwn Flutedroopy"), "obj_growdi_flute", Instrument::FLUTEDROOPY);
	 //player->addInventoryItem(instrument);
	 
	 //Can't equip these, have you drop them in the world.
	 //Omnibox
	 //instrument = new Instrument(player, 0x77D28DF3, unicode("The Pwn Omnibox"), "obj_ommni_box", Instrument::OMNIBOX);
	 //player->addInventoryItem(instrument);
	 
	 //Nalargon
	 //instrument = new Instrument(player, 0x8FC48010, unicode("The Pwn Nalargon"), "obj_nalargon", Instrument::NALARGON);
	 //player->addInventoryItem(instrument);

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
			createPlayerItem(player, item);
		} else if (item->isUpdated()) {
			savePlayerItem(player, item);
		}
	}
}

void ItemManagerImplementation::createPlayerItem(Player* player, TangibleObject* item) {
	try {
		string appearance;
		string itemApp;
		item->getCustomizationString(itemApp);
		BinaryData cust(itemApp);
		cust.encode(appearance);
		
		stringstream query;
		query << "INSERT INTO `character_items` "
			  << "(`item_id`,`character_id`,`name`,`template_crc`,`template_type`,`template_name`,`equipped`,`attributes`,`appearance`)"
			  << " VALUES(" << item->getObjectID() << "," << player->getCharacterID() 
			  << ",'\\" << item->getName().c_str() << "'," 
			  << item->getObjectCRC() << "," << item->getObjectSubType() << ",'" << item->getTemplateName() << "',"
			  << item->isEquipped() << ",'" << item->getAttributes() 
			  << "','" << appearance.substr(0, appearance.size() - 1) << "')";

		ServerDatabase::instance()->executeStatement(query);
		
		item->setPersistent(true);
		
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
}

void ItemManagerImplementation::savePlayerItem(Player* player, TangibleObject* item) {
	
	try {
		string apperance = "";
		string itemApp;
		item->getCustomizationString(itemApp);
		BinaryData cust(itemApp);
		cust.encode(apperance);
		
		stringstream query;
		query << "update `character_items` set equipped = " << item->isEquipped();
		query << ", character_id = " << player->getCharacterID() << " ";
		query << ", attributes = '" << item->getAttributes() << "' ";
		query << ", appearance = '" << apperance.substr(0, apperance.size() - 1) << "' ";
		query << "where item_id = " << item->getObjectID();
		
		ServerDatabase::instance()->executeStatement(query);
		
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
}

void ItemManagerImplementation::deletePlayerItem(Player* player, TangibleObject* item, bool notify) {
	try {	
		stringstream query;
		query << "update `character_items` set deleted = " << 1 << " where item_id = " << item->getObjectID();
	
		ServerDatabase::instance()->executeStatement(query);

		stringstream playertxt;
		if (notify)
			playertxt << "You have destroyed " << item->getName().c_str() << ".";

		player->sendSystemMessage(playertxt.str());
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
			if (res->getInt(4) == WeaponImplementation::WEAPON) {
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
			if (res->getInt(4) == WeaponImplementation::WEAPON) {
				txt << "ObjID: " << res->getUnsignedLong(0) << " Name: " << res->getString(2) 
					<< "\\#ffffff MinDmg: " << res->getFloat(11) << " MaxDmg: " << res->getFloat(12) 
					<< " Spd: " << res->getFloat(13) << " Strength: " << res->getInt(58) 
					<< " Potency: " << res->getInt(60) << "\n";
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
			if (res->getInt(4) == WeaponImplementation::WEAPON) {
				txt << "ObjID: " << res->getUnsignedLong(0) << " Name: " << res->getString(2) 
					<< "\\#ffffff MinDmg: " << res->getFloat(11) << " MaxDmg: " << res->getFloat(12) 
					<< " Spd: " << res->getFloat(13) << "\n";
			} else if (res->getInt(4) == ArmorImplementation::ARMOR) {
				txt << "ObjID: " << res->getUnsignedLong(0) << " Name: " << res->getString(2) 
				<< "\\#ffffff Resists: " << res->getFloat(31) << " " << res->getFloat(33) << " " 
				<< res->getFloat(35) << " " << res->getFloat(36) << " " << res->getFloat(39) << " " 
				<< res->getFloat(41) << " " << res->getFloat(43) << " " << res->getFloat(45) << " " 
				<< res->getFloat(47) << "\n";
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
