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
#include "../../ZoneProcessServerImplementation.h"

#include "../player/PlayerManager.h"
#include "../creature/CreatureManager.h"

#include "ItemManagerImplementation.h"

StartingItemList * ItemManagerImplementation::startingItems = NULL;
BlueFrogItemSet * ItemManagerImplementation::bfItemSet = NULL;
BlueFrogProfessionSet * ItemManagerImplementation::bfProfSet = NULL;
bool ItemManagerImplementation::bfEnabled = false;

ItemManagerImplementation::ItemManagerImplementation(ZoneServer* serv, ZoneProcessServerImplementation* pServ) :
	ItemManagerServant(), Lua() {
	server = serv;
	pServer = pServ;

	nextStaticItemID = 0x90000000;

	startingItems = new StartingItemList();
	bfItemSet = new BlueFrogItemSet();
	bfProfSet = new BlueFrogProfessionSet();

	Lua::init();
	registerFunctions();
	registerGlobals();
	info("Loading Starting Items...", true);
	runFile("scripts/items/starting/main.lua");
	info("Loading Blue Frog Items...", true);
	runFile("scripts/items/bluefrog/main.lua");
}

ItemManagerImplementation::~ItemManagerImplementation() {
	delete startingItems;
	startingItems = NULL;

	delete bfItemSet;
	bfItemSet = NULL;

	delete bfProfSet;
	bfProfSet = NULL;

}

void ItemManagerImplementation::loadStaticWorldObjects() {

}

void ItemManagerImplementation::loadPlayerItems(Player* player) {
	try {
		stringstream query;
		query << "select * from `character_items` where `character_id` = " << player->getCharacterID() << " and `deleted` = 0";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		int i = 0;

		while (res->next())	{
			bool equipped = res->getBoolean(7);

			if (!equipped && (++i > InventoryImplementation::MAXUNEQUIPPEDCOUNT)) {
				uint64 objectID = res->getUnsignedLong(0);

				stringstream query;
				query << "DELETE FROM character_items WHERE item_id = '" << objectID <<"';";

				ServerDatabase::instance()->executeStatement(query);
				continue;
			}

			createPlayerObject(player, res);
		}

		loadPlayerDatapadItems(player);

		delete res;
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	} catch (...) {
		cout << "unreported exception caught in ItemManagerImplementation::loadPlayerItems(Player* player)\n";
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
	} catch (...) {
		cout << "unreported exception caught in TangibleObject* ItemManagerImplementation::getPlayerItem(Player* player, uint64 objectid)\n";
	}

	return tano;
}

TangibleObject* ItemManagerImplementation::createPlayerObjectTemplate(int objecttype, uint64 objectid,
		uint32 objectcrc, const unicode& objectname, const string& objecttemp, bool equipped, bool makeStats, string lootAttributes, int level) {
	TangibleObject* item = NULL;

	if (objecttype & TangibleObjectImplementation::WEAPON || objecttype & TangibleObjectImplementation::LIGHTSABER) {
		switch (objecttype) {
		case TangibleObjectImplementation::MELEEWEAPON:
			item = new UnarmedMeleeWeapon(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::ONEHANDMELEEWEAPON:
			item = new OneHandedMeleeWeapon(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::TWOHANDMELEEWEAPON:
			item = new TwoHandedMeleeWeapon(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::POLEARM:
			item = new PolearmMeleeWeapon(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::PISTOL:
			item = new PistolRangedWeapon(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::CARBINE:
			item = new CarbineRangedWeapon(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::RIFLE:
			item = new RifleRangedWeapon(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::ONEHANDSABER:
			item = new OneHandedJediWeapon(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::TWOHANDSABER:
			item = new TwoHandedJediWeapon(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::POLEARMSABER:
			item = new PolearmJediWeapon(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::SPECIALHEAVYWEAPON:
			item = new SpecialHeavyRangedWeapon(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		case TangibleObjectImplementation::HEAVYWEAPON:
			item = new HeavyRangedWeapon(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		}

		if (item != NULL && makeStats) {
			item->setAttributes(lootAttributes );
			item->parseItemAttributes();
			Weapon* dummy = (Weapon*)item;
			dummy->setWeaponStats(level);
		}

	} else if (objecttype & TangibleObjectImplementation::CLOTHING) {
		item = new Wearable(objectid, objectcrc, objectname, objecttemp, equipped);
		item->setObjectSubType(objecttype);
		if (makeStats)
			item->setConditionDamage(System::random(item->getMaxCondition() * 3 / 4));

	} else if (objecttype & TangibleObjectImplementation::ARMOR) {
		item = new Armor(objectid, objectcrc, objectname, objecttemp, equipped);
		if (makeStats) {
			item->setAttributes(lootAttributes);
			item->parseItemAttributes();
			Armor* dummy = (Armor*)item;
			dummy->setArmorStats(level);
		}

	} else if (objecttype & TangibleObjectImplementation::MISC) {
		switch (objecttype) {
		case TangibleObjectImplementation::TRAVELTICKET:
			item = new Ticket(objectid, objectcrc, objectname, objecttemp);
			if (makeStats) {
				item->setAttributes(lootAttributes );
				item->parseItemAttributes();
			}
			break;

		case TangibleObjectImplementation::INSTRUMENT:
			item = new Instrument(objectid, objectcrc, objectname, objecttemp, equipped);
			if (makeStats) {
				item->setAttributes(lootAttributes );
				item->parseItemAttributes();
			}
			break;

		case TangibleObjectImplementation::CLOTHINGATTACHMENT:
			item = new Attachment(objectid, AttachmentImplementation::CLOTHING);
			if (makeStats) {
				Attachment* dummy = (Attachment*)item;
				dummy->setSkillMods(level / 2);
			}
			break;

		case TangibleObjectImplementation::ARMORATTACHMENT:
			item = new Attachment(objectid, AttachmentImplementation::ARMOR);
			if (makeStats) {
				Attachment* dummy = (Attachment*)item;
				dummy->setSkillMods((level+20) / 2);
			}
			break;

		case TangibleObjectImplementation::CRAFTINGSTATION:
			item = new CraftingStation(objectid, objectcrc, objectname, objecttemp);
			if (makeStats) {
				item->setAttributes(lootAttributes );
				item->parseItemAttributes();
			}
			break;

		case TangibleObjectImplementation::FACTORYCRATE:
			item = new FactoryCrate(objectid, objectcrc, objectname, objecttemp);
			item->setObjectCount(5);
			break;

		case TangibleObjectImplementation::PHARMACEUTICAL:
			item = createSubObject(objectid, objectcrc, objectname, objecttemp, equipped);
			if (makeStats) {
				item->setAttributes(lootAttributes );
				item->parseItemAttributes();
			}
			break;

		default:
			item = new TangibleObject(objectid, objectcrc, objectname, objecttemp, objecttype);
			if (makeStats) {
				item->setAttributes(lootAttributes );
				item->parseItemAttributes();
			}
			break;
		}

	} else if ( objecttype & TangibleObjectImplementation::RESOURCECONTAINER ) {
		item = new ResourceContainer(objectid, objectcrc, objectname, objecttemp);

	} else if (objecttype & TangibleObjectImplementation::TOOL) {

		switch (objecttype) {
		case TangibleObjectImplementation::CRAFTINGTOOL:
			item = new CraftingTool(objectid, objectcrc, objectname, objecttemp);
			if (makeStats) {
				item->setAttributes(lootAttributes );
				item->parseItemAttributes();
			}
			break;

		case TangibleObjectImplementation::SURVEYTOOL:
			item = new SurveyTool(objectid, objectcrc, objectname, objecttemp);
			if (makeStats) {
				item->setAttributes(lootAttributes );
				item->parseItemAttributes();
			}
			break;

		case TangibleObjectImplementation::REPAIRTOOL:
			break;
		case TangibleObjectImplementation::CAMPKIT:
			break;
		case TangibleObjectImplementation::SHIPCOMPONENTREPAIRITEM:
			break;
		}

	} else if (objecttype & TangibleObjectImplementation::WEAPONPOWERUP) {
		item = new Powerup(objectid, objectcrc, objectname, objecttemp);
		if (makeStats) {
			Powerup* dummy = (Powerup*)item;
			dummy->setPowerupStats(level);
		}

	} else if (objecttype & TangibleObjectImplementation::COMPONENT) {
		item = new Component(objectid, objectcrc, objectname, objecttemp);
		if (makeStats) {
			item->setAttributes(lootAttributes );
			item->parseItemAttributes();
		}
	} else if (objecttype & TangibleObjectImplementation::DEED) {
		switch (objecttype) {
			case DeedObjectImplementation::INSTALLATIONDEED:

				//item = new HarvesterDeed(objectid, objectcrc, objectname, objecttemp);
				switch(DeedObjectImplementation::getSubType(objectcrc)){
					case DeedObjectImplementation::HARVESTER:
						item = new HarvesterDeed(objectid, objectcrc, objectname, objecttemp);
						break;
					case DeedObjectImplementation::FACTORY:
						item = new FactoryDeed(objectid, objectcrc, objectname, objecttemp);
						break;
					case DeedObjectImplementation::GENERATOR:
						item = new GeneratorDeed(objectid, objectcrc, objectname, objecttemp);
						break;
					case DeedObjectImplementation::TURRET:
						break;
					case DeedObjectImplementation::MINEFIELD:
						break;
				}
				break;
			case TangibleObjectImplementation::BUILDINGDEED:
				item = new PlayerHouseDeed(objectid, objectcrc, objectname, objecttemp);
				break;
			case TangibleObjectImplementation::PETDEED:

				break;
			case TangibleObjectImplementation::DROIDDEED:

				break;
			case TangibleObjectImplementation::VEHICLEDEED:
				item = new VehicleDeed(objectid, objectcrc, objectname, objecttemp);
				break;
		}
	}
	/*else {
		item = new TangibleObjectImplementation(objectid, objectname, objecttemp, objectcrc, equipped);
	} */

	return item;
}

TangibleObject* ItemManagerImplementation::createSubObject(uint64 objectid, uint32 objectcrc, const unicode& objectname, const string& objecttemp, bool equipped) {
	TangibleObject* item = NULL;

	switch (objectcrc) {
	//Pharmaceutical EnhancePacks
	case 0xF0D47A7E:
	case 0x2BC3D2E9:
	case 0x62CEB564:
	case 0x992D9E70:
	case 0x67D14C62:
	case 0xBCC6E4F5:
	case 0xF5CB8378:
	case 0x0E28A86C:
	case 0xD3231B08:
	case 0x0834B39F:
	case 0x4139D412:
	case 0x756B0C42:
	case 0xAE7CA4D5:
	case 0xE771C358:
	case 0x1C92E84C:
	case 0x758A2A26:
	case 0xAE9D82B1:
	case 0xE790E53C:
	case 0xB735A208:
	case 0x6C220A9F:
	case 0x252F6D12:
	case 0xDECC4606:
	case 0x1210D7DD:
	case 0xC9077F4A:
	case 0x800A18C7:
	case 0x7BE933D3:
	case 0x7914128C:
	case 0xA203BA1B:
	case 0xEB0EDD96:
	case 0x10EDF682:
		item = new EnhancePack(objectid, objectcrc, objectname, objecttemp);
		break;
		//Pharmaceutical StimPacks
	case 0x904FA809:
	case 0x4B58009E:
	case 0x02556713:
	case 0xF9B64C07:
	case 0xB0BB2B8A:
	case 0x7751C746:
	case 0xAC466FD1:
	case 0xE54B085C:
	case 0x1EA82348:
	case 0x57A544C5:
		item = new StimPack(objectid, objectcrc, objectname, objecttemp);
		break;
	case 0xE960F4C8:
	case 0x32775C5F:
	case 0x7B7A3BD2:
	case 0x809910C6:
	case 0xC994774B:
	case 0xEFD65BB8:
	case 0x34C1F32F:
	case 0x7DCC94A2:
	case 0x862FBFB6:
	case 0xCF22D83B:
	case 0x6CDF82F4:
	case 0xB7C82A63:
	case 0xFEC54DEE:
	case 0x052666FA:
	case 0x4C2B0177:
	case 0xB17AB627:
	case 0x6A6D1EB0:
	case 0x2360793D:
	case 0xD8835229:
	case 0x918E35A4:
	case 0xC8464AA2:
	case 0x1351E235:
	case 0x5A5C85B8:
	case 0xA1BFAEAC:
	case 0xE8B2C921:
	case 0x1198F0B3:
	case 0xCA8F5824:
	case 0x83823FA9:
	case 0x786114BD:
	case 0x316C7330:
		item = new WoundPack(objectid, objectcrc, objectname, objecttemp);
		break;
		//Pharmaceutical RevivePack
	case 0x35431212:
		item = new RevivePack(objectid, objectcrc, objectname, objecttemp);
		break;
	case 0xE907B936:
	case 0x321011A1:
	case 0xFF779812:
	case 0x24603085:
	case 0xD4FA5279:
	case 0x0FEDFAEE:
	case 0x3E9B3371:
	case 0xE58C9BE6:
		item = new StatePack(objectid, objectcrc, objectname, objecttemp);
		break;
	case 0x9CA116FF:
	case 0x47B6BE68:
	case 0x0EBBD9E5:
	case 0xB791A080:
	case 0x6C860817:
	case 0x258B6F9A:
	case 0xC6F551AE: //fireblanket
		item = new CurePack(objectid, objectcrc, objectname, objecttemp);
		break;
	default:
		item = new TangibleObject(objectid, objectcrc, objectname, objecttemp, TangibleObjectImplementation::MISC);
		break;
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

	uint16 itemMask = result->getUnsignedInt(11);

	BinaryData cust(appearance);

	string custStr;
	cust.decode(custStr);

	bool equipped = result->getBoolean(7);

	if (result->getBoolean(8) != 0) // deleted
		return NULL;

	string attributes = result->getString(9);

	TangibleObject* item = createPlayerObjectTemplate(objecttype, objectid, objectcrc,
			unicode(objectname), objecttemp, equipped, false, "", 0);

	if (item == NULL) {
		//cout << "NULL ITEM objectType:[" << objecttype << "] objectname[" << objectname << "]" << endl;
		return NULL;
	}

	item->setAttributes(attributes);
	item->parseItemAttributes();

	item->setPlayerUseMask(itemMask);

	item->setCustomizationString(custStr);

	item->setPersistent(true);

	if (player != NULL) {
		((CreatureObject*)player)->addInventoryItem(item);

		if(item->isEquipped())
			player->equipPlayerItem(item);
	}

	return item;
}

TangibleObject* ItemManagerImplementation::initializeTangibleForCrafting(
		int objecttype, uint64 objectid, uint32 objectcrc, string objectn,
		string objecttemp, bool equipped){

	unicode objectname(objectn);

	TangibleObject * item = NULL;

	item = createPlayerObjectTemplate(objecttype, objectid, objectcrc,
			objectname.c_str(), objecttemp, equipped, false, "", 0);

	/*if (item == NULL) {
		cout << "NULL ITEM" << endl;
		return NULL;

	}*/

	return item;
}

//Temporary Fix until we get a global clone() method implemented
//TODO: remove this function when a global clone() method is implemented for all objects
TangibleObject* ItemManagerImplementation::clonePlayerObjectTemplate(uint64 objectid, TangibleObject* templ) {

	if(templ == NULL)
	{
		return NULL;
	}
	//the name is passed in a hackish way to stop buffer overflows.. anyone know why it was doing that?
	TangibleObject* newTempl = createPlayerObjectTemplate(templ->getObjectSubType(),
			objectid, templ->getObjectCRC(), unicode(templ->getName().c_str()),
			(char *) templ->getTemplateName().c_str(), templ->isEquipped(), false, "", 0);

	newTempl->setAttributes(templ->getAttributes());
	newTempl->parseItemAttributes();

	newTempl->setPlayerUseMask(templ->getPlayerUseMask());

	return newTempl;
}

void ItemManagerImplementation::registerFunctions() {
	lua_register(getLuaState(), "AddPlayerItem", addPlayerItem);
	lua_register(getLuaState(), "RunItemLUAFile", runItemLUAFile);
	lua_register(getLuaState(), "SetBlueFrogsEnabled", enableBlueFrogs);
	lua_register(getLuaState(), "AddBFItem", addBFItem);
	lua_register(getLuaState(), "AddBFProf", addBFProf);
	lua_register(getLuaState(), "AddBFGroup", addBFGroup);
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

	//Pharmaceutical Medical Pack Type
	setGlobalInt("ENHANCEPACK", PharmaceuticalImplementation::ENHANCEPACK);
	setGlobalInt("WOUNDPACK", PharmaceuticalImplementation::WOUNDPACK);
	setGlobalInt("CUREPACK", PharmaceuticalImplementation::CUREPACK);
	setGlobalInt("STATEPACK", PharmaceuticalImplementation::STATEPACK);
	setGlobalInt("STIMPACK", PharmaceuticalImplementation::STIMPACK);
	setGlobalInt("REVIVEPACK", PharmaceuticalImplementation::REVIVEPACK);

	setGlobalInt("HEALTH", PharmaceuticalImplementation::HEALTH);
	setGlobalInt("ACTION", PharmaceuticalImplementation::ACTION);
	setGlobalInt("MIND", PharmaceuticalImplementation::MIND);
	setGlobalInt("CONSTITUTION", PharmaceuticalImplementation::CONSTITUTION);
	setGlobalInt("STRENGTH", PharmaceuticalImplementation::STRENGTH);
	setGlobalInt("QUICKNESS", PharmaceuticalImplementation::QUICKNESS);
	setGlobalInt("STAMINA", PharmaceuticalImplementation::STAMINA);
	setGlobalInt("FOCUS", PharmaceuticalImplementation::FOCUS);
	setGlobalInt("WILLPOWER", PharmaceuticalImplementation::WILLPOWER);

	setGlobalInt("INTIMIDATED_STATE", CreatureObjectImplementation::INTIMIDATED_STATE);
	setGlobalInt("STUNNED_STATE", CreatureObjectImplementation::STUNNED_STATE);
	setGlobalInt("DIZZY_STATE", CreatureObjectImplementation::DIZZY_STATE);
	setGlobalInt("BLINDED_STATE", CreatureObjectImplementation::BLINDED_STATE);

	setGlobalInt("ONFIRE_STATE", CreatureObjectImplementation::ONFIRE_STATE);
	setGlobalInt("DISEASED_STATE", CreatureObjectImplementation::DISEASED_STATE);
	setGlobalInt("POISONED_STATE", CreatureObjectImplementation::POISONED_STATE);

	//ItemMasks
	setGlobalShort("MALE", TangibleObjectImplementation::MALE);
	setGlobalShort("FEMALE", TangibleObjectImplementation::FEMALE);

	setGlobalShort("HUMAN", TangibleObjectImplementation::HUMAN);
	setGlobalShort("TRANDOSHAN", TangibleObjectImplementation::TRANDOSHAN);
	setGlobalShort("TWILEK", TangibleObjectImplementation::TWILEK);
	setGlobalShort("BOTHAN", TangibleObjectImplementation::BOTHAN);
	setGlobalShort("ZABRAK", TangibleObjectImplementation::ZABRAK);
	setGlobalShort("RODIAN", TangibleObjectImplementation::RODIAN);
	setGlobalShort("MONCALAMARI", TangibleObjectImplementation::MONCALAMARI);
	setGlobalShort("WOOKIEE", TangibleObjectImplementation::WOOKIEE);
	setGlobalShort("SULLUSTAN", TangibleObjectImplementation::SULLUSTAN);
	setGlobalShort("ITHORIAN", TangibleObjectImplementation::ITHORIAN);

	setGlobalShort("NEUTRAL", TangibleObjectImplementation::NEUTRAL);
	setGlobalShort("IMPERIAL", TangibleObjectImplementation::IMPERIAL);
	setGlobalShort("REBEL", TangibleObjectImplementation::REBEL);
	setGlobalShort("COVERT", TangibleObjectImplementation::COVERT);

	setGlobalShort("ALL", TangibleObjectImplementation::ALL);
	setGlobalShort("ALLSEXES", TangibleObjectImplementation::ALLSEXES);
	setGlobalShort("ALLFACTIONS", TangibleObjectImplementation::ALLFACTIONS);
	setGlobalShort("HUMANOIDS", TangibleObjectImplementation::HUMANOIDS);
	setGlobalShort("HUMANOID_FOOTWEAR", TangibleObjectImplementation::HUMANOID_FOOTWEAR);
	setGlobalShort("HUMANOID_MALES", TangibleObjectImplementation::HUMANOID_MALES);
	setGlobalShort("HUMANOID_FEMALES", TangibleObjectImplementation::HUMANOID_FEMALES);
	setGlobalShort("HUMANOID_IMPERIALS", TangibleObjectImplementation::HUMANOID_IMPERIALS);
	setGlobalShort("HUMANOID_REBELS", TangibleObjectImplementation::HUMANOID_REBELS);
	setGlobalShort("WOOKIEES", TangibleObjectImplementation::WOOKIEES);
	setGlobalShort("ITHORIANS", TangibleObjectImplementation::ITHORIANS);
	setGlobalShort("TWILEKS", TangibleObjectImplementation::TWILEKS);
}

int ItemManagerImplementation::runItemLUAFile(lua_State* L) {
	string filename = getStringParameter(L);

	runFile("scripts/items/" + filename, L);

	return 0;
}

TangibleObject* ItemManagerImplementation::createTemplateFromLua(LuaObject itemconfig) {

	int crc = itemconfig.getIntField("objectCRC");
	string name = itemconfig.getStringField("objectName");
	string templ = itemconfig.getStringField("templateName");
	bool equipped = bool(itemconfig.getByteField("equipped"));
	int type = itemconfig.getIntField("objectType");
	uint16 itemMask = itemconfig.getIntField("itemMask");

	TangibleObject* item = createPlayerObjectTemplate(type, 1, crc, unicode(name), templ, equipped, false, "", 0);

	item->setObjectSubType(type);
	item->setPlayerUseMask(itemMask);

	//ADD ATTRIBUTES
	if (type & TangibleObjectImplementation::ARMOR) {
		int armorType = itemconfig.getIntField("armorType");
		int actionEncum = itemconfig.getIntField("actionEncum");
		int healthEncum = itemconfig.getIntField("healthEncum");
		int mindEncum = itemconfig.getIntField("mindEncum");
		float acidResist = itemconfig.getFloatField("acidResist");
		float blastResist = itemconfig.getFloatField("blastResist");
		float coldResist = itemconfig.getFloatField("coldResist");
		float electricityResist = itemconfig.getFloatField("electricityResist");
		float energyResist = itemconfig.getFloatField("energyResist");
		float heatResist = itemconfig.getFloatField("heatResist");
		float kineticResist = itemconfig.getFloatField("kineticResist");
		float lightSaberResist = itemconfig.getFloatField("lightSaberResist");

		((Armor*) item)->setType(armorType);
		((Armor*) item)->setActionEncumbrance(actionEncum);
		((Armor*) item)->setMindEncumbrance(mindEncum);
		((Armor*) item)->setHealthEncumbrance(healthEncum);
		((Armor*) item)->setAcid(acidResist);
		((Armor*) item)->setBlast(blastResist);
		((Armor*) item)->setCold(coldResist);
		((Armor*) item)->setElectricity(electricityResist);
		((Armor*) item)->setEnergy(energyResist);
		((Armor*) item)->setHeat(heatResist);
		((Armor*) item)->setKinetic(kineticResist);
		((Armor*) item)->setLightSaber(lightSaberResist);

	} else if (type == TangibleObjectImplementation::INSTRUMENT) {
		int instType = itemconfig.getIntField("instrumentType");

		((Instrument*) item)->setInstrumentType(instType);
	} else if (type & TangibleObjectImplementation::WEAPON) {
		int damageType = itemconfig.getIntField("damageType");
		int ap = itemconfig.getIntField("armorPiercing");
		string cert = itemconfig.getStringField("certification");
		float as = itemconfig.getFloatField("attackSpeed");
		float mindmg = itemconfig.getFloatField("minDamage");
		float maxdmg = itemconfig.getFloatField("maxDamage");

		Weapon* weapon = (Weapon*) item;
		weapon->setDamageType(damageType);
		weapon->setArmorPiercing(ap);
		weapon->setAttackSpeed(as);
		weapon->setMinDamage(mindmg);
		weapon->setMaxDamage(maxdmg);

		if (!cert.empty())
			weapon->setCert(cert);
	} else if (type == TangibleObjectImplementation::PHARMACEUTICAL) {
		int medpackType = itemconfig.getIntField("medpackType");
		int usesRemaining = itemconfig.getIntField("usesRemaining");
		int medicineUse = itemconfig.getIntField("medicineUse");

		Pharmaceutical* pharma = (Pharmaceutical*) item;
		pharma->setMedpackType(medpackType);
		pharma->setUsesRemaining(usesRemaining);
		pharma->setMedicineUseRequired(medicineUse);

		switch (medpackType) {
		case PharmaceuticalImplementation::ENHANCEPACK:
		{
			float eff = itemconfig.getFloatField("effectiveness");
			float dur = itemconfig.getFloatField("duration");
			int pool = itemconfig.getIntField("poolAffected");

			EnhancePack* enhance = (EnhancePack*) item;
			enhance->setEffectiveness(eff);
			enhance->setDuration(dur);
			enhance->setPoolAffected(pool);
			break;
		}
		case PharmaceuticalImplementation::WOUNDPACK:
		{
			float eff = itemconfig.getFloatField("effectiveness");
			int pool = itemconfig.getIntField("poolAffected");

			WoundPack* wound = (WoundPack*) item;
			wound->setEffectiveness(eff);
			wound->setPoolAffected(pool);
			break;
		}
		case PharmaceuticalImplementation::CUREPACK:
		{
			float eff = itemconfig.getFloatField("effectiveness");
			uint64 condition = itemconfig.getLongField("conditionCured");

			CurePack* curepack = (CurePack*) item;
			curepack->setEffectiveness(eff);
			curepack->setConditionCured(condition);
			break;
		}
		case PharmaceuticalImplementation::STATEPACK:
		{
			uint64 state = itemconfig.getLongField("stateAffected");

			StatePack* statepack = (StatePack*) item;
			statepack->setStateAffected(state);
			break;
		}
		case PharmaceuticalImplementation::REVIVEPACK:
		{
			float hw = itemconfig.getFloatField("healthWoundHealed");
			float hh = itemconfig.getFloatField("healthHealed");
			float aw = itemconfig.getFloatField("actionWoundHealed");
			float ah = itemconfig.getFloatField("actionHealed");
			float mw = itemconfig.getFloatField("mindWoundHealed");
			float mh = itemconfig.getFloatField("mindHealed");

			RevivePack* revive = (RevivePack*) item;
			revive->setHealthWoundHealed(hw);
			revive->setHealthHealed(hh);
			revive->setActionWoundHealed(aw);
			revive->setActionHealed(ah);
			revive->setMindWoundHealed(mw);
			revive->setMindHealed(mh);
			break;
		}
		case PharmaceuticalImplementation::STIMPACK:
		{
			float eff = itemconfig.getFloatField("effectiveness");

			StimPack* stim = (StimPack*) item;
			stim->setEffectiveness(eff);
			break;
		}
		default:
			break;
		}
	}

	return item;
}
int ItemManagerImplementation::addPlayerItem(lua_State * l) {
	LuaObject itemwrapper(l);

	string species = itemwrapper.getStringField("species");
	string sex = itemwrapper.getStringField("sex");
	string profession = itemwrapper.getStringField("profession");

	LuaObject itemconfig(itemwrapper.getObjectField("item"));

	TangibleObject* item = createTemplateFromLua(itemconfig);

	startingItems->addItemToProfession(profession, species, sex, item);

	return 0;
}

int ItemManagerImplementation::addBFItem(lua_State * l) {
	LuaObject itemwrapper(l);

	string name = itemwrapper.getStringField("name");

	LuaObject itemconfig(itemwrapper.getObjectField("item"));

	TangibleObject* item = createTemplateFromLua(itemconfig);

	bfItemSet->addItem(name, item);

	return 0;
}

int ItemManagerImplementation::addBFProf(lua_State * l) {

	LuaObject itemwrapper(l);

	string name = itemwrapper.getStringField("name");

	string prof = itemwrapper.getStringField("prof");

	string group = itemwrapper.getStringField("group");

	bfProfSet->addProfession(name, group, prof);

	return 0;
}

int ItemManagerImplementation::addBFGroup(lua_State * l) {
	LuaObject itemwrapper(l);

	string name = itemwrapper.getStringField("name");

	string parent = itemwrapper.getStringField("parent");

	bfProfSet->addGroup(name, parent);

	return 0;
}

void ItemManagerImplementation::giveBFItemSet(Player * player, string& set) {
	Inventory* inventory = player->getInventory();
	Vector<TangibleObject*>* itemSet = bfItemSet->get(set);

	if (inventory->getUnequippedItemCount() + itemSet->size()
			>= InventoryImplementation::MAXUNEQUIPPEDCOUNT) {

		player->sendSystemMessage("You don't have enough space in your inventory");
		return;
	}

	for (int i = 0; i < itemSet->size(); i++) {
		TangibleObject* item = clonePlayerObjectTemplate(player->getNewItemID(), itemSet->get(i));
		//item->setObjectID(player->getNewItemID());
		if(item == NULL) {
			cout << "ItemManagerImplementation::giveBFItemSet(...), item == NULL!, set = " << set << endl;
		} else {
			player->addInventoryItem(item);

			item->sendTo(player);
		}
	}
}

//TODO: Modify this function when a global clone() function is available for all objects
void ItemManagerImplementation::loadDefaultPlayerItems(Player* player) {
	string prof = player->getStartingProfession();
	prof = prof.substr(prof.find_first_of("_") + 1);

	string race = player->getRaceFileName();
	int ls = race.find_last_of("/");
	int fu = race.find_first_of("_");
	int dot = race.find_last_of(".");

	string species = race.substr(ls + 1, fu - ls - 1);
	string sex = race.substr(fu + 1, dot - fu -1);

	string gen = "general";
	string all = "all";

	Vector<TangibleObject*>* items;

	//Make profession items for species
	items = startingItems->getProfessionItems(prof, species, sex);
	for (int j = 0; j < items->size(); ++j) {
		TangibleObject* obj = clonePlayerObjectTemplate(player->getNewItemID(), items->get(j));
		//obj->setObjectID(player->getNewItemID());
		player->addInventoryItem(obj);
	}

	//Make profession items for that apply to all species
	items = startingItems->getProfessionItems(prof, all, sex);
	for (int j = 0; j < items->size(); ++j) {
		TangibleObject* obj = clonePlayerObjectTemplate(player->getNewItemID(), items->get(j));
		//obj->setObjectID(player->getNewItemID());
		player->addInventoryItem(obj);
	}

	//Make general items for species
	items = startingItems->getProfessionItems(gen, species, sex);
	for (int j = 0; j < items->size(); ++j) {
		TangibleObject* obj = clonePlayerObjectTemplate(player->getNewItemID(), items->get(j));
		//obj->setObjectID(player->getNewItemID());
		player->addInventoryItem(obj);
	}

	//Make general items that apple to all species
	items = startingItems->getProfessionItems(gen, all, sex);
	for (int j = 0; j < items->size(); ++j) {
		TangibleObject* obj = clonePlayerObjectTemplate(player->getNewItemID(), items->get(j));
		//obj->setObjectID(player->getNewItemID());
		player->addInventoryItem(obj);
	}

}

void ItemManagerImplementation::loadPlayerDatapadItems(Player* player) {
	try {
		stringstream query;

		query << "SELECT datapad.inx, datapad.character_id, datapad.name, datapad.itnocrc, datapad.item_crc, "
			<< "datapad.file_name, datapad.attributes, datapad.appearance, datapad.itemMask, datapad.obj_id "
			<< "FROM datapad where character_id = " << player->getCharacterID() << ";";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		MountCreature* land = NULL;

		while (res->next()) {
			string appearance = res->getString(7);

			land = new MountCreature(player, res->getString(2), "monster_name",
					res->getLong(3), res->getLong(4), res->getUnsignedLong(9));

			land->setZoneProcessServer(pServer);

			if (appearance != "") {
				BinaryData cust(appearance);
				string custStr;
				cust.decode(custStr);

				land->setCharacterAppearance(custStr);
			}

			land->addToDatapad();

		}

		delete res;

	} catch (DatabaseException& e) {
		player->error("Load Datapad exception in : ItemManagerImplementation::loadDefaultPlayerDatapadItems(Player* player)");
		player->error(e.getMessage());
	} catch (...) {
		cout << "Exception in ItemManagerImplementation::loadDefaultPlayerDatapadItems(Player* player)\n";
		player->error("Load Datapad unknown exception in : ItemManagerImplementation::loadDefaultPlayerDatapadItems(Player* player)");
	}


	//ToDO: If the datapad load is working fine for a while, delete this commented stuff here
	/*
	// SWOOP
	MountCreature* swoop = new MountCreature(player, "speederbike_swoop", "monster_name",
			String::hashCode("object/intangible/vehicle/shared_speederbike_swoop_pcd.iff"), 0xAF6D9F4F, player->getNewItemID());
	swoop->addToDatapad();

	// flash speeder
	MountCreature* flash = new MountCreature(player, "speederbike_flash", "monster_name", String::hashCode("object/intangible/vehicle/shared_speederbike_flash_pcd.iff"),
			0x4E3534, player->getNewItemID());
	flash->addToDatapad();

	// landspeeder
	MountCreature* land = new MountCreature(player, "landspeeder_x31", "monster_name",
			String::hashCode("object/intangible/vehicle/shared_landspeeder_x31_pcd.iff"), 0x273A9C02, player->getNewItemID());
	land->addToDatapad();

	 // xp 38 doesnt work
	 //MountCreatureImplementation* land2Impl = new MountCreatureImplementation(player, "landspeeder_xp38", "monster_name",
	 //String::hashCode("object/intangible/vehicle/shared_vehicle_pcd_base.iff"), 0x3F6E7BA7, player->getNewItemID());
	 //stringstream Land2;
	 //Land2 << "Mount" << land2Impl->getObjectID();
	 //MountCreature* land2 = (MountCreature*) DistributedObjectBroker::instance()->deploy(Land2.str(), land2Impl);
	 //land2->addToDatapad();

	// x34
	MountCreature* land3 = new MountCreature(player, "landspeeder_x34", "monster_name",
			String::hashCode("object/intangible/vehicle/shared_landspeeder_x34_pcd.iff"), 0x4EC3780C, player->getNewItemID());
	land3->addToDatapad();

	// av21
	MountCreature* land4 = new MountCreature(player, "landspeeder_av21", "monster_name",
			String::hashCode("object/intangible/vehicle/shared_landspeeder_av21_pcd.iff"), 0xA965DDBA, player->getNewItemID());
	land4->addToDatapad();

	// speederbike
	MountCreature* speed = new MountCreature(player, "speederbike", "monster_name",
			String::hashCode("object/intangible/vehicle/shared_speederbike_pcd.iff"), 0x729517EF, player->getNewItemID());
	speed->addToDatapad();

	// jetpack
	MountCreatureImplementation* jetImpl = new MountCreatureImplementation(player, "jetpack", "monster_name",
	String::hashCode("object/intangible/vehicle/shared_jetpack_pcd.iff"), 0x60250B32, player->getNewItemID());
	jetImpl->setInstantMount(true);
	stringstream Jet;
	Jet << "Mount" << jetImpl->getObjectID();
	MountCreature* jet = (MountCreature*) DistributedObjectBroker::instance()->deploy(Jet.str(), jetImpl);
	jet->addToDatapad();
	*/
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

		try {
			stringstream query;
			query << "UPDATE `characters` set itemShift = " << player->getItemShift() << " ";
			query << "WHERE character_id = " << player->getCharacterID() << ";";

			ServerDatabase::instance()->executeStatement(query);
		} catch (DatabaseException& e) {
			cout << e.getMessage() << "\n";
		}

	}
}

void ItemManagerImplementation::createPlayerItem(Player* player, TangibleObject* item) {
	try {
		string itemname = item->getName().c_str();
		MySqlDatabase::escapeString(itemname);

		string appearance;
		string itemApp;
		item->getCustomizationString(itemApp);
		BinaryData cust(itemApp);
		cust.encode(appearance);

		string attr = item->getAttributes();
		MySqlDatabase::escapeString(attr);

		stringstream query;
		query << "INSERT INTO `character_items` "
		<< "(`item_id`,`character_id`,`name`,`template_crc`,`template_type`,`template_name`,`equipped`,`attributes`,`appearance`, `itemMask`)"
		<< " VALUES(" << item->getObjectID() << "," << player->getCharacterID()
		<< ",'\\" << itemname << "',"
		<< item->getObjectCRC() << "," << item->getObjectSubType() << ",'" << item->getTemplateName() << "',"
		<< item->isEquipped() << ",'" << attr
		<< "','" << appearance.substr(0, appearance.size() - 1) << "', " << item->getPlayerUseMask() << ")";

		ServerDatabase::instance()->executeStatement(query);


		item->setPersistent(true);

	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	} catch (...) {
		cout << "unreported exception caught in ItemManagerImplementation::createPlayerItem(Player* player, TangibleObject* item)\n";
	}
}

void ItemManagerImplementation::savePlayerItem(Player* player, TangibleObject* item) {
	try {
		string appearance = "";
		string itemApp;
		item->getCustomizationString(itemApp);
		BinaryData cust(itemApp);
		cust.encode(appearance);

		string attr = item->getAttributes();
		MySqlDatabase::escapeString(attr);

		stringstream query;
		query << "update `character_items` set equipped = " << item->isEquipped();
		query << ", character_id = " << player->getCharacterID() << " ";
		query << ", attributes = '" << attr << "' ";
		query << ", appearance = '" << appearance.substr(0, appearance.size() - 1) << "' ";
		query << ", itemMask = " << item->getPlayerUseMask() << " ";
		query << "where item_id = " << item->getObjectID();

		ServerDatabase::instance()->executeStatement(query);

	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	} catch (...) {
		cout << "unreported exception caught in ItemManagerImplementation::savePlayerItem(Player* player, TangibleObject* item)\n";
	}
}

void ItemManagerImplementation::deletePlayerItem(Player* player, TangibleObject* item, bool notify) {
	try {
		stringstream query;
		query << "update `character_items` set deleted = " << 1 << " where item_id = " << item->getObjectID();

		ServerDatabase::instance()->executeStatement(query);

		//cout << query.str() << endl;

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
