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

#include "../player/PlayerManager.h"

#include "ItemManagerImplementation.h"

ItemManagerImplementation * ItemManagerImplementation::instance = NULL;

ItemManagerImplementation::ItemManagerImplementation(ZoneServer* serv) :
	ItemManagerServant(), Lua() {
	server = serv;

	nextStaticItemID = 0x90000000;
	
	Lua::init();
	registerFunctions();
	registerGlobals();
	runFile("scripts/professions/main.lua");
	instance = this;
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
	SceneObject* item = NULL;
	
	if (player != NULL)
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

TangibleObjectImplementation* ItemManagerImplementation::createPlayerObjectTemplate(int objecttype, uint64 objectid, uint32 objectcrc, unicode objectname, char* objecttemp, bool equipped) {
	
	TangibleObjectImplementation* item = NULL;
	
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
		item->setObjectSubType(objecttype);
		
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
		case TangibleObjectImplementation::CRAFTINGSTATION:

			item = new CraftingStationImplementation(objectid, objectcrc, objectname, objecttemp);
					
			break;
			
		default:

			item = new TangibleObjectImplementation(objectid, objectname, objecttemp, objectcrc, objecttype);
							
			break;
		}
	} else if ( objecttype & TangibleObjectImplementation::RESOURCECONTAINER ) {
				
		item = new ResourceContainerImplementation(objectid, objectcrc, objectname, objecttemp);
			
	} else if (objecttype & TangibleObjectImplementation::TOOL) {
		switch (objecttype) {
		case TangibleObjectImplementation::CRAFTINGTOOL:
			item = new CraftingToolImplementation(objectid, objectcrc, objectname, objecttemp);
			break;
		case TangibleObjectImplementation::SURVEYTOOL:
			item = new SurveyToolImplementation(objectid, objectcrc, objectname, objecttemp);
			break;
		case TangibleObjectImplementation::REPAIRTOOL:
		case TangibleObjectImplementation::CAMPKIT:
		case TangibleObjectImplementation::SHIPCOMPONENTREPAIRITEM:
			break;
		}
	} else if (objecttype & TangibleObjectImplementation::WEAPONPOWERUP) {

		item = new PowerupImplementation(objectid, objectcrc, objectname, objecttemp);
	} 
	
	return item;
}

TangibleObject* ItemManagerImplementation::createPlayerObject(Player* player, ResultSet* result) {
	uint64 objectid = result->getUnsignedLong(0);

	int objecttype = result->getInt(4);
	uint32 objectcrc = result->getUnsignedInt(3);  
	
	string objectname = result->getString(2);
	char* objecttemp = result->getString(5); // template_name
	
	string appearance = result->getString(10);
	BinaryData cust(appearance);
	string custStr;
	cust.decode(custStr);

	bool equipped = result->getBoolean(7);
	
	if (result->getBoolean(8) != 0) // deleted
		return NULL;
	
	string attributes = result->getString(9);
	
	TangibleObjectImplementation* item = createPlayerObjectTemplate(objecttype, objectid, objectcrc, unicode(objectname), objecttemp, equipped);

	if (item == NULL) {
		cout << "NULL ITEM" << endl;
		return NULL;
	}
		
	
	item->setAttributes(attributes);
	item->parseItemAttributes();
	
	item->setCustomizationString(custStr);
	
	
	item->setPersistent(true);
	
	TangibleObject* tano = (TangibleObject*) item->deploy();
	
	if (player != NULL) 
		player->addInventoryItem(tano);
	
	return tano;
}

void ItemManagerImplementation::registerFunctions() {
	lua_register(getLuaState(), "AddPlayerItem", addPlayerItem);
	lua_register(getLuaState(), "RunProfessionFile", runProfessionFile);
}

void ItemManagerImplementation::registerGlobals() {
	//Object Types
	setGlobalInt("HAIR", TangibleObjectImplementation::HAIR);
	setGlobalInt("TERMINAL", TangibleObjectImplementation::TERMINAL);
	setGlobalInt("TICKETCOLLECTOR", TangibleObjectImplementation::TICKETCOLLECTOR);
	setGlobalInt("LAIR", TangibleObjectImplementation::LAIR);
	setGlobalInt("HOLOCRON", TangibleObjectImplementation::HOLOCRON);
	setGlobalInt("SHIPCOMPONENT", TangibleObjectImplementation::SHIPCOMPONENT);
	setGlobalInt("ARMOR", TangibleObjectImplementation::ARMOR);
	setGlobalInt("BODYARMOR", TangibleObjectImplementation::BODYARMOR);
	setGlobalInt("HEADARMOR", TangibleObjectImplementation::HEADARMOR);
	setGlobalInt("MISCARMOR", TangibleObjectImplementation::MISCARMOR);
	setGlobalInt("LEGARMOR", TangibleObjectImplementation::LEGARMOR);
	setGlobalInt("ARMARMOR", TangibleObjectImplementation::ARMARMOR);
	setGlobalInt("HANDARMOR", TangibleObjectImplementation::HANDARMOR);
	setGlobalInt("FOOTARMOR", TangibleObjectImplementation::FOOTARMOR);
	setGlobalInt("SHIELDGENERATOR", TangibleObjectImplementation::SHIELDGENERATOR);
	setGlobalInt("DATA", TangibleObjectImplementation::DATA);
	setGlobalInt("DRAFTSCHEMATIC", TangibleObjectImplementation::DRAFTSCHEMATIC);
	setGlobalInt("MANUFACTURINGSCHEMATIC", TangibleObjectImplementation::MANUFACTURINGSCHEMATIC);
	setGlobalInt("MISSIONOBJECT", TangibleObjectImplementation::MISSIONOBJECT);
	setGlobalInt("TOKEN", TangibleObjectImplementation::TOKEN);
	setGlobalInt("WAYPOINT", TangibleObjectImplementation::WAYPOINT);
	setGlobalInt("DATA2", TangibleObjectImplementation::DATA2);
	setGlobalInt("PETCONTROLDEVICE", TangibleObjectImplementation::PETCONTROLDEVICE);
	setGlobalInt("VEHICLECONTROLDEVICE", TangibleObjectImplementation::VEHICLECONTROLDEVICE);
	setGlobalInt("SHIPCONTROLDEVICE", TangibleObjectImplementation::SHIPCONTROLDEVICE);
	setGlobalInt("DROIDCONTROLDEVICE", TangibleObjectImplementation::DROIDCONTROLDEVICE);
	setGlobalInt("MISC", TangibleObjectImplementation::MISC);
	setGlobalInt("AMMUNITION", TangibleObjectImplementation::AMMUNITION);
	setGlobalInt("CHEMICAL", TangibleObjectImplementation::CHEMICAL);
	setGlobalInt("CONTAINER", TangibleObjectImplementation::CONTAINER);
	setGlobalInt("CRAFTINGSTATION", TangibleObjectImplementation::CRAFTINGSTATION);
	setGlobalInt("ELECTRONICS", TangibleObjectImplementation::ELECTRONICS);
	setGlobalInt("FLORA", TangibleObjectImplementation::FLORA);
	setGlobalInt("FOOD", TangibleObjectImplementation::FOOD);
	setGlobalInt("FURNITURE", TangibleObjectImplementation::FURNITURE);
	setGlobalInt("INSTRUMENT", TangibleObjectImplementation::INSTRUMENT);
	setGlobalInt("PHARMACEUTICAL", TangibleObjectImplementation::PHARMACEUTICAL);
	setGlobalInt("SIGN", TangibleObjectImplementation::SIGN);
	setGlobalInt("COUNTER", TangibleObjectImplementation::COUNTER);
	setGlobalInt("FACTORYCRATE", TangibleObjectImplementation::FACTORYCRATE);
	setGlobalInt("TRAVELTICKET", TangibleObjectImplementation::TRAVELTICKET);
	setGlobalInt("GENERICITEM", TangibleObjectImplementation::GENERICITEM);
	setGlobalInt("TRAP", TangibleObjectImplementation::TRAP);
	setGlobalInt("WEARABLECONTAINER", TangibleObjectImplementation::WEARABLECONTAINER);
	setGlobalInt("FISHINGPOLE", TangibleObjectImplementation::FISHINGPOLE);
	setGlobalInt("FISHINGBAIT", TangibleObjectImplementation::FISHINGBAIT);
	setGlobalInt("DRINK", TangibleObjectImplementation::DRINK);
	setGlobalInt("FIREWORK", TangibleObjectImplementation::FIREWORK);
	setGlobalInt("ITEM", TangibleObjectImplementation::ITEM);
	setGlobalInt("PETMEDECINE", TangibleObjectImplementation::PETMEDECINE);
	setGlobalInt("FIREWORKSHOW", TangibleObjectImplementation::FIREWORKSHOW);
	setGlobalInt("CLOTHINGATTACHMENT", TangibleObjectImplementation::CLOTHINGATTACHMENT);
	setGlobalInt("LIVESAMPLE", TangibleObjectImplementation::LIVESAMPLE);
	setGlobalInt("ARMORATTACHMENT", TangibleObjectImplementation::ARMORATTACHMENT);
	setGlobalInt("COMMUNITYCRAFTINGPROJECT", TangibleObjectImplementation::COMMUNITYCRAFTINGPROJECT);
	setGlobalInt("CRYSTAL", TangibleObjectImplementation::CRYSTAL);
	setGlobalInt("DROIDPROGRAMMINGCHIP", TangibleObjectImplementation::DROIDPROGRAMMINGCHIP);
	setGlobalInt("ASTEROID", TangibleObjectImplementation::ASTEROID);
	setGlobalInt("PILOTCHAIR", TangibleObjectImplementation::PILOTCHAIR);
	setGlobalInt("OPERATIONSCHAIR", TangibleObjectImplementation::OPERATIONSCHAIR);
	setGlobalInt("TURRETACCESSLADDER", TangibleObjectImplementation::TURRETACCESSLADDER);
	setGlobalInt("CONTAINER2", TangibleObjectImplementation::CONTAINER2);
	setGlobalInt("TOOL", TangibleObjectImplementation::TOOL);
	setGlobalInt("CRAFTINGTOOL", TangibleObjectImplementation::CRAFTINGTOOL);
	setGlobalInt("SURVEYTOOL", TangibleObjectImplementation::SURVEYTOOL);
	setGlobalInt("REPAIRTOOL", TangibleObjectImplementation::REPAIRTOOL);
	setGlobalInt("CAMPKIT", TangibleObjectImplementation::CAMPKIT);
	setGlobalInt("SHIPCOMPONENTREPAIRITEM", TangibleObjectImplementation::SHIPCOMPONENTREPAIRITEM);
	setGlobalInt("VEHICLE", TangibleObjectImplementation::VEHICLE);
	setGlobalInt("HOVERVEHICLE", TangibleObjectImplementation::HOVERVEHICLE);
	setGlobalInt("WEAPON", TangibleObjectImplementation::WEAPON);
	setGlobalInt("MELEEWEAPON", TangibleObjectImplementation::MELEEWEAPON);
	setGlobalInt("RANGEDWEAPON", TangibleObjectImplementation::RANGEDWEAPON);
	setGlobalInt("THROWNWEAPON", TangibleObjectImplementation::THROWNWEAPON);
	setGlobalInt("HEAVYWEAPON", TangibleObjectImplementation::HEAVYWEAPON);
	setGlobalInt("MINE", TangibleObjectImplementation::MINE);
	setGlobalInt("SPECIALHEAVYWEAPON", TangibleObjectImplementation::SPECIALHEAVYWEAPON);
	setGlobalInt("ONEHANDMELEEWEAPON", TangibleObjectImplementation::ONEHANDMELEEWEAPON);
	setGlobalInt("TWOHANDMELEEWEAPON", TangibleObjectImplementation::TWOHANDMELEEWEAPON);
	setGlobalInt("POLEARM", TangibleObjectImplementation::POLEARM);
	setGlobalInt("PISTOL", TangibleObjectImplementation::PISTOL);
	setGlobalInt("CARBINE", TangibleObjectImplementation::CARBINE);
	setGlobalInt("RIFLE", TangibleObjectImplementation::RIFLE);
	setGlobalInt("RESOURCECONTAINER", TangibleObjectImplementation::RESOURCECONTAINER);
	setGlobalInt("ENERGYGAS", TangibleObjectImplementation::ENERGYGAS);
	setGlobalInt("ENERGYLIQUID", TangibleObjectImplementation::ENERGYLIQUID);
	setGlobalInt("ENERGYRADIOACTIVE", TangibleObjectImplementation::ENERGYRADIOACTIVE);
	setGlobalInt("ENERGYSOLID", TangibleObjectImplementation::ENERGYSOLID);
	setGlobalInt("INORGANICCHEMICAL", TangibleObjectImplementation::INORGANICCHEMICAL);
	setGlobalInt("INORGANICGAS", TangibleObjectImplementation::INORGANICGAS);
	setGlobalInt("INORGANICMINERAL", TangibleObjectImplementation::INORGANICMINERAL);
	setGlobalInt("WATER", TangibleObjectImplementation::WATER);
	setGlobalInt("ORGANICFOOD", TangibleObjectImplementation::ORGANICFOOD);
	setGlobalInt("ORGANICHIDE", TangibleObjectImplementation::ORGANICHIDE);
	setGlobalInt("ORGANICSTRUCTURAL", TangibleObjectImplementation::ORGANICSTRUCTURAL);
	setGlobalInt("WEAPONPOWERUP", TangibleObjectImplementation::WEAPONPOWERUP);
	setGlobalInt("MELEEWEAPONPOWERUP", TangibleObjectImplementation::MELEEWEAPONPOWERUP);
	setGlobalInt("RANGEDWEAPONPOWERUP", TangibleObjectImplementation::RANGEDWEAPONPOWERUP);
	setGlobalInt("THROWNWEAPONPOWERUP", TangibleObjectImplementation::THROWNWEAPONPOWERUP);
	setGlobalInt("HEAVYWEAPONPOWERUP", TangibleObjectImplementation::HEAVYWEAPONPOWERUP);
	setGlobalInt("MINEPOWERUP", TangibleObjectImplementation::MINEPOWERUP);
	setGlobalInt("SPECIALHEAVYWEAPONPOWERUP", TangibleObjectImplementation::SPECIALHEAVYWEAPONPOWERUP);
	setGlobalInt("LIGHTSABER", TangibleObjectImplementation::LIGHTSABER);
	setGlobalInt("ONEHANDSABER", TangibleObjectImplementation::ONEHANDSABER);
	setGlobalInt("TWOHANDSABER", TangibleObjectImplementation::TWOHANDSABER);
	setGlobalInt("POLEARMSABER", TangibleObjectImplementation::POLEARMSABER);
	setGlobalInt("DEED", TangibleObjectImplementation::DEED);
	setGlobalInt("BUILDINGDEED", TangibleObjectImplementation::BUILDINGDEED);
	setGlobalInt("INSTALLATIONDEED", TangibleObjectImplementation::INSTALLATIONDEED);
	setGlobalInt("PETDEED", TangibleObjectImplementation::PETDEED);
	setGlobalInt("DROIDDEED", TangibleObjectImplementation::DROIDDEED);
	setGlobalInt("VEHICLEDEED", TangibleObjectImplementation::VEHICLEDEED);
	setGlobalInt("CLOTHING", TangibleObjectImplementation::CLOTHING);
	setGlobalInt("BANDOLIER", TangibleObjectImplementation::BANDOLIER);
	setGlobalInt("BELT", TangibleObjectImplementation::BELT);
	setGlobalInt("BODYSUIT", TangibleObjectImplementation::BODYSUIT);
	setGlobalInt("CAPE", TangibleObjectImplementation::CAPE);
	setGlobalInt("CLOAK", TangibleObjectImplementation::CLOAK);
	setGlobalInt("FOOTWEAR", TangibleObjectImplementation::FOOTWEAR);
	setGlobalInt("DRESS", TangibleObjectImplementation::DRESS);
	setGlobalInt("HANDWEAR", TangibleObjectImplementation::HANDWEAR);
	setGlobalInt("EYEWEAR", TangibleObjectImplementation::EYEWEAR);
	setGlobalInt("HEADWEAR", TangibleObjectImplementation::HEADWEAR);
	setGlobalInt("JACKET", TangibleObjectImplementation::JACKET);
	setGlobalInt("PANTS", TangibleObjectImplementation::PANTS);
	setGlobalInt("ROBE", TangibleObjectImplementation::ROBE);
	setGlobalInt("SHIRT", TangibleObjectImplementation::SHIRT);
	setGlobalInt("VEST", TangibleObjectImplementation::VEST);
	setGlobalInt("WOOKIEGARB", TangibleObjectImplementation::WOOKIEGARB);
	setGlobalInt("MISCCLOTHING", TangibleObjectImplementation::MISCCLOTHING);
	setGlobalInt("SKIRT", TangibleObjectImplementation::SKIRT);
	setGlobalInt("ITHOGARB", TangibleObjectImplementation::ITHOGARB);
	
	//Armor Piercing
	setGlobalInt("WEAPON_NONE", WeaponImplementation::NONE);
	setGlobalInt("WEAPON_LIGHT", WeaponImplementation::LIGHT);
	setGlobalInt("WEAPON_MEDIUM", WeaponImplementation::MEDIUM);
	setGlobalInt("WEAPON_HEAVY", WeaponImplementation::HEAVY);
	
	//Damage Type
	setGlobalInt("WEAPON_KINETIC", WeaponImplementation::KINETIC);
	setGlobalInt("WEAPON_ENERGY", WeaponImplementation::ENERGY);
	setGlobalInt("WEAPON_ELECTRICITY", WeaponImplementation::ELECTRICITY);
	setGlobalInt("WEAPON_STUN", WeaponImplementation::STUN);
	setGlobalInt("WEAPON_BLAST", WeaponImplementation::BLAST);
	setGlobalInt("WEAPON_HEAT", WeaponImplementation::HEAT);
	setGlobalInt("WEAPON_COLD", WeaponImplementation::COLD);
	setGlobalInt("WEAPON_ACID", WeaponImplementation::ACID);
	setGlobalInt("WEAPON_LIGHTSABER", WeaponImplementation::LIGHTSABER);
	
	//Armor Type
	setGlobalInt("ARMOR_CHEST", ArmorImplementation::CHEST);
	setGlobalInt("ARMOR_HAND", ArmorImplementation::HAND);
	setGlobalInt("ARMOR_BRACERL", ArmorImplementation::BRACERL);
	setGlobalInt("ARMOR_BICEPL", ArmorImplementation::BICEPL);
	setGlobalInt("ARMOR_BRACERR", ArmorImplementation::BRACERR);
	setGlobalInt("ARMOR_BICEPR", ArmorImplementation::BICEPR);
	setGlobalInt("ARMOR_LEG", ArmorImplementation::LEG);
	setGlobalInt("ARMOR_FOOT", ArmorImplementation::FOOT);
	setGlobalInt("ARMOR_HEAD", ArmorImplementation::HEAD);
	setGlobalInt("ARMOR_BELT", ArmorImplementation::BELT);
	
	//Instrument Type
	setGlobalInt("INSTR_TRAZ", InstrumentImplementation::TRAZ);
	setGlobalInt("INSTR_SLITHERHORN", InstrumentImplementation::SLITHERHORN);
	setGlobalInt("INSTR_FANFAR", InstrumentImplementation::FANFAR);
	setGlobalInt("INSTR_FLUTEDROOPY", InstrumentImplementation::FLUTEDROOPY);
	setGlobalInt("INSTR_KLOOHORN", InstrumentImplementation::KLOOHORN);
	setGlobalInt("INSTR_FIZZ", InstrumentImplementation::FIZZ);
	setGlobalInt("INSTR_BANDFILL", InstrumentImplementation::BANDFILL);
	setGlobalInt("INSTR_OMNIBOX", InstrumentImplementation::OMNIBOX);
	setGlobalInt("INSTR_NALARGON", InstrumentImplementation::NALARGON);
	setGlobalInt("INSTR_MANDOVIOL", InstrumentImplementation::MANDOVIOL);
}

int ItemManagerImplementation::runProfessionFile(lua_State* L) {
	string filename = getStringParameter(L);
	
	runFile("scripts/professions/" + filename, L);
	
	return 0;
}

int ItemManagerImplementation::addPlayerItem(lua_State * l) {
	LuaObject item(l);

	if (!item.isValidTable())
			return 1;
	
	Player* player = instance->getPlayerManager()->getPlayer(*(new string(item.getStringField("owner"))));
	int crc = item.getIntField("objectCRC");
	string name = item.getStringField("objectName");
	string templ = item.getStringField("templateName");
	bool equipped = bool(item.getByteField("equipped"));
	int type = item.getIntField("objectType");
	
	TangibleObjectImplementation* itemImpl = createPlayerObjectTemplate(type, player->getNewItemID(), crc, unicode(name), (char *) templ.c_str(), equipped);
	itemImpl->setObjectSubType(type);
	
	//ADD ATTRIBUTES
	if (type & TangibleObjectImplementation::ARMOR) {		
		int armorType = item.getIntField("armorType");
		
		((ArmorImplementation*) itemImpl)->setType(armorType);
	} else if (type & TangibleObjectImplementation::INSTRUMENT) {		
		int instType = item.getIntField("instrumentType");
				
		((InstrumentImplementation*) itemImpl)->setInstrumentType(instType);
	} else if (type & TangibleObjectImplementation::WEAPON) {
		int damageType = item.getIntField("damageType");
		int ap = item.getIntField("armorPiercing");
		string cert = item.getStringField("certification");
		
		((WeaponImplementation*) itemImpl)->setDamageType(damageType);
		((WeaponImplementation*) itemImpl)->setArmorPiercing(ap);
		if(!cert.empty())
			((WeaponImplementation*) itemImpl)->setCert(cert);
	}

	player->addInventoryItem(itemImpl->deploy());
	
	return 0;
}

void ItemManagerImplementation::loadDefaultPlayerItems(Player* player) {
	string prof = player->getStartingProfession();
	prof = prof.substr(prof.find_first_of("_") + 1);
	
	string race = player->getRaceFileName();
	int ls = race.find_last_of("/");
	int fu = race.find_first_of("_");
	int dot = race.find_last_of(".");
	
	string species = race.substr(ls + 1, fu - ls - 1);
	string sex = race.substr(fu + 1, dot - fu -1);
	
	LuaFunction createItems(getLuaState(), "createItems", 1);
	createItems << player->getFirstName();
	createItems << prof;
	createItems << species;
	createItems << sex;
	callFunction(&createItems);
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
	 MountCreature* land2 = (MountCreature*) DistributedObjectBroker::instance()->deploy(Land2.str(), land2Impl);
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
	 MountCreature* jet = (MountCreature*) DistributedObjectBroker::instance()->deploy(Jet.str(), jetImpl);
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
