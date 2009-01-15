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

#include "../loot/LootManager.h"

#include "ItemManagerImplementation.h"
#include "../../objects/creature/skills/CamoSkill.h"

StartingItemList * ItemManagerImplementation::startingItems = NULL;
ForageItemList * ItemManagerImplementation::forageItems = NULL;
BlueFrogItemSet * ItemManagerImplementation::bfItemSet = NULL;
BlueFrogProfessionSet * ItemManagerImplementation::bfProfSet = NULL;
bool ItemManagerImplementation::bfEnabled = false;

ItemManagerImplementation::ItemManagerImplementation(ZoneServer* serv, ZoneProcessServerImplementation* pServ) :
	ItemManagerServant(), Lua() {
	server = serv;
	pServer = pServ;

	nextStaticItemID = 0x90000000;

	startingItems = new StartingItemList();
	forageItems = new ForageItemList();
	bfItemSet = new BlueFrogItemSet();
	bfProfSet = new BlueFrogProfessionSet();

	Lua::init();
	registerFunctions();
	registerGlobals();
	info("Loading Starting Items...", true);
	runFile("scripts/items/starting/main.lua");
	info("Loading Forage Items...", true);
	runFile("scripts/items/forageable/main.lua");
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
		StringBuffer query;

		//Iventory items nested in containers MUST LOAD AT LAST - to assure that all container objects are existing when loading items
		query << "select * from `character_items` where `character_id` = " << player->getCharacterID() << " and `deleted` = 0 order by container asc";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		int i = 0;

		while (res->next())	{
			bool equipped = res->getBoolean(7);

			if (!equipped && (++i > InventoryImplementation::MAXUNEQUIPPEDCOUNT)) {
				uint64 objectID = res->getUnsignedLong(0);

				StringBuffer query;
				query << "DELETE FROM character_items WHERE item_id = '" << objectID <<"';";

				ServerDatabase::instance()->executeStatement(query);
				continue;
			}

			createPlayerObject(player, res);

		}

		loadPlayerDatapadItems(player);

		delete res;
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	} catch (...) {
		System::out << "unreported exception caught in ItemManagerImplementation::loadPlayerItems(Player* player)\n";
	}
}

TangibleObject* ItemManagerImplementation::getPlayerItem(Player* player, uint64 objectid) {
	TangibleObject* tano = NULL;
	SceneObject* item = NULL;

	if (player == NULL)
		return NULL;

	if (player != NULL)
		SceneObject* item = player->getPlayerItem(objectid);

	if (item != NULL && item->isTangible())
		return (TangibleObject*) item;

	try {
		StringBuffer query;
		query << "select * from `character_items` where `item_id` = " << objectid;

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		while (res->next())	{
			tano = createPlayerObject(player, res);
		}

		delete res;

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	} catch (...) {
		System::out << "unreported exception caught in TangibleObject* ItemManagerImplementation::getPlayerItem(Player* player, uint64 objectid)\n";
	}

	return tano;
}

TangibleObject* ItemManagerImplementation::createPlayerObjectTemplate(int objecttype, uint64 objectid,
		uint32 objectcrc, const UnicodeString& objectname, const String& objecttemp, bool equipped, bool makeStats, String lootAttributes, int level) {
	TangibleObject* item = NULL;

	if (objecttype & TangibleObjectImplementation::WEAPON || objecttype & TangibleObjectImplementation::LIGHTSABER || objecttype == TangibleObjectImplementation::TRAP) {
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
		case TangibleObjectImplementation::TRAP:
			item = new TrapThrowableWeapon(objectid, objectcrc, objectname, objecttemp, equipped);
			break;
		//case TangibleObjectImplementation::GRANADE:
		//	item = new ThrowableWeapon(objectid, objectcrc, objectname, objecttemp, equipped);
		//	break;
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

	} else if (objecttype & TangibleObjectImplementation::MISC && objecttype != TangibleObjectImplementation::TRAP) {
		switch (objecttype) {

		case TangibleObjectImplementation::CONTAINER :
		case TangibleObjectImplementation::CONTAINER2 :
		case TangibleObjectImplementation::WEARABLECONTAINER :
			item = new Container(objectid);
			item->setObjectCRC(objectcrc);
			item->setName(objectname);
			item->setObjectSubType(objecttype);
			item->setTemplateName(objecttemp);
			item->setEquipped(equipped);
			if (makeStats) {
				item->setAttributes(lootAttributes );
				item->parseItemAttributes();
			}
			break;

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

        case TangibleObjectImplementation::GENERICITEM:
            item = createSubObject(objectid, objectcrc, objectname, objecttemp, equipped);
            if (makeStats) {
                item->setAttributes(lootAttributes);
                item->parseItemAttributes();
            }
            break;
	    case TangibleObjectImplementation::CAMOKIT:
			item = new CamoKit(objectid, objectcrc, objectname, objecttemp);
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
			item = new CampKit(objectid, objectcrc, objectname, objecttemp);
			if (makeStats) {
				item->setAttributes(lootAttributes );
				item->parseItemAttributes();
			}
			break;
		case TangibleObjectImplementation::SHIPCOMPONENTREPAIRITEM:
			break;
		default:
            item = createSubObject(objectid, objectcrc, objectname, objecttemp, equipped);
            if (makeStats) {
                item->setAttributes(lootAttributes);
                item->parseItemAttributes();
            }
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
			case TangibleObjectImplementation::INSTALLATIONDEED:
				switch(DeedObjectImplementation::getSubType(objectcrc)){
					case TangibleObjectImplementation::HARVESTER:
						item = new HarvesterDeed(objectid, objectcrc, objectname, objecttemp);
						break;
					case TangibleObjectImplementation::FACTORY:
						item = new FactoryDeed(objectid, objectcrc, objectname, objecttemp);
						break;
					case TangibleObjectImplementation::GENERATOR:
						item = new GeneratorDeed(objectid, objectcrc, objectname, objecttemp);
						break;
					case TangibleObjectImplementation::TURRET:
						break;
					case TangibleObjectImplementation::MINEFIELD:
						break;
					case TangibleObjectImplementation::PETDEED:
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
			case TangibleObjectImplementation::RESOURCEDEED:
				item = new ResourceDeed(objectid, objectcrc, objectname, objecttemp);
				break;
		}
		if (makeStats && item != NULL) {
			item->setAttributes(lootAttributes);
			item->parseItemAttributes();
		}
	}
	/*else {
		item = new TangibleObjectImplementation(objectid, objectname, objecttemp, objectcrc, equipped);
	} */

	return item;
}

TangibleObject* ItemManagerImplementation::createSubObject(uint64 objectid, uint32 objectcrc, const UnicodeString& objectname, const String& objecttemp, bool equipped) {
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
    case 0x221F0907:
    case 0x484AC6A6:
    case 0x821DB6E8:
    case 0xBF64B1E4:
    case 0xB5E34222:
    case 0x81B6977D:
    case 0xD474E5E7: //dice
        item = new Dice(objectid, objectcrc, objectname, objecttemp);
        break;
    case 0x9075A4C8: //Armor Upgrade Kit
    	item = new UpgradeKit(objectid, objectcrc, objectname, objecttemp, UpgradeKitImplementation::ARMORKIT);
    	break;
    case 0xC3ABF395: //Weapon Upgrade Kit
    	item = new UpgradeKit(objectid, objectcrc, objectname, objecttemp, UpgradeKitImplementation::WEAPONKIT);
        break;
    case 0xE8C6FD5C:
    	item = new PrecisionLaserKnife(objectid, objectcrc, objectname, objecttemp);
    	break;
    case 0x15013600:
    	item = new FlowAnalyzerNode(objectid, objectcrc, objectname, objecttemp);
    	break;
    case 0x9EC5864C:
    	item = new MolecularClamp(objectid, objectcrc, objectname, objecttemp);
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

	String objectname = result->getString(2);
	char* objecttemp = result->getString(5); // template_name

	uint64 container = result->getUnsignedLong(6);

	String appearance = result->getString(10);

	uint16 itemMask = result->getUnsignedInt(11);
	uint32 optionsBitmask = result->getUnsignedInt(12);

	if (itemMask == 0)
		itemMask = TangibleObjectImplementation::ALL;

	BinaryData cust(appearance);

	String custStr;
	cust.decode(custStr);

	bool equipped = result->getBoolean(7);

	if (result->getBoolean(8) != 0) // deleted
		return NULL;

	String attributes = result->getString(9);

	TangibleObject* item = createPlayerObjectTemplate(objecttype, objectid, objectcrc,
			UnicodeString(objectname), objecttemp, equipped, false, "", 0);

	if (item == NULL)
		return NULL;

	item->setAttributes(attributes);
	item->parseItemAttributes();

	item->setObjectSubType(objecttype);

	item->setPlayerUseMask(itemMask);

	item->setOptionsBitmask(optionsBitmask);

	item->setCustomizationString(custStr);

	item->setPersistent(true);

	server->addObject(item);

	if (container != 0) {
		Zone* zone = player->getZone();

		if (zone != NULL) {
			SceneObject* contiSCO = zone->lookupObject(container);

			if (contiSCO != NULL && contiSCO->isTangible() && ((TangibleObject*)contiSCO)->isContainer()) {
				Container* conti = (Container*) contiSCO;

				item->setParent(contiSCO);

				BaseMessage* linkmsg = item->link(contiSCO);
				player->sendMessage(linkmsg);

				UpdateTransformMessage* transformMessage = new UpdateTransformMessage(item, 0, 0, 0);
				player->sendMessage(transformMessage);

				conti->addObject(item);
			}
		}
	} else if (player != NULL)
		((CreatureObject*)player)->addInventoryItem(item);

	if(item->isEquipped())
		player->equipPlayerItem(item, false);

	return item;
}

TangibleObject* ItemManagerImplementation::initializeTangibleForCrafting(
		int objecttype, uint64 objectid, uint32 objectcrc, String objectn,
		String objecttemp, bool equipped){

	UnicodeString objectname(objectn);

	TangibleObject* item = NULL;

	item = createPlayerObjectTemplate(objecttype, objectid, objectcrc,
			objectname.toString(), objecttemp, equipped, false, "", 0);

	/*if (item == NULL) {
		System::out << "NULL ITEM" << endl;
		return NULL;

	}*/

	return item;
}

//Temporary Fix until we get a global clone() method implemented
//TODO: remove this function when a global clone() method is implemented for all objects
TangibleObject* ItemManagerImplementation::clonePlayerObjectTemplate(uint64 objectid, TangibleObject* templ) {

	if (templ == NULL)
	{
		return NULL;
	}
	//the name is passed in a hackish way to stop buffer overflows.. anyone know why it was doing that?
	TangibleObject* newTempl = createPlayerObjectTemplate(templ->getObjectSubType(),
			objectid, templ->getObjectCRC(), UnicodeString(templ->getName()),
			(char *) templ->getTemplateName().toCharArray(), templ->isEquipped(), false, "", 0);

	newTempl->setAttributes(templ->getAttributes());
	newTempl->parseItemAttributes();

	newTempl->setPlayerUseMask(templ->getPlayerUseMask());
	newTempl->setOptionsBitmask(templ->getOptionsBitmask());

	return newTempl;
}

void ItemManagerImplementation::registerFunctions() {
	lua_register(getLuaState(), "AddPlayerItem", addPlayerItem);
	lua_register(getLuaState(), "RunItemLUAFile", runItemLUAFile);
	lua_register(getLuaState(), "SetBlueFrogsEnabled", enableBlueFrogs);
	lua_register(getLuaState(), "AddBFItem", addBFItem);
	lua_register(getLuaState(), "AddBFProf", addBFProf);
	lua_register(getLuaState(), "AddBFGroup", addBFGroup);
	lua_register(getLuaState(), "CreateForageItemFromLua", createForageItemFromLua);
}

void ItemManagerImplementation::registerGlobals() {
	//Object Types
	setGlobalInt("CAMOKIT", TangibleObjectImplementation::CAMOKIT);
	setGlobalInt("HAIR", TangibleObjectImplementation::HAIR);
	setGlobalInt("TERMINAL", TangibleObjectImplementation::TERMINAL);
	setGlobalInt("TICKETCOLLECTOR", TangibleObjectImplementation::TICKETCOLLECTOR);
	setGlobalInt("LAIR", TangibleObjectImplementation::LAIR);
	setGlobalInt("HOLOCRON", TangibleObjectImplementation::HOLOCRON);
	setGlobalInt("SHIPCOMPONENT", TangibleObjectImplementation::SHIPCOMPONENT);
	setGlobalInt("COMPONENT", TangibleObjectImplementation::COMPONENT);
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
	setGlobalInt("RESOURCEDEED", TangibleObjectImplementation::RESOURCEDEED);
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

	setGlobalInt("HEALTH", CreatureAttribute::HEALTH);
	setGlobalInt("ACTION", CreatureAttribute::ACTION);
	setGlobalInt("MIND", CreatureAttribute::MIND);
	setGlobalInt("CONSTITUTION", CreatureAttribute::CONSTITUTION);
	setGlobalInt("STRENGTH", CreatureAttribute::STRENGTH);
	setGlobalInt("QUICKNESS", CreatureAttribute::QUICKNESS);
	setGlobalInt("STAMINA", CreatureAttribute::STAMINA);
	setGlobalInt("FOCUS", CreatureAttribute::FOCUS);
	setGlobalInt("WILLPOWER", CreatureAttribute::WILLPOWER);

	setGlobalInt("INTIMIDATED", CreatureState::INTIMIDATED);
	setGlobalInt("STUNNED", CreatureState::STUNNED);
	setGlobalInt("DIZZY", CreatureState::DIZZY);
	setGlobalInt("BLINDED", CreatureState::BLINDED);

	setGlobalInt("ONFIRE", CreatureState::ONFIRE);
	setGlobalInt("DISEASED", CreatureState::DISEASED);
	setGlobalInt("POISONED", CreatureState::POISONED);

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

	setGlobalInt("CORELLIA", CamoSkill::CORELLIA);

	setGlobalInt("DANTOOINE", CamoSkill::DANTOOINE);
	setGlobalInt("DATHOMIR", CamoSkill::DATHOMIR);
	setGlobalInt("ENDOR", CamoSkill::ENDOR);
	setGlobalInt("LOK", CamoSkill::LOK);
	setGlobalInt("NABOO", CamoSkill::NABOO);
	setGlobalInt("RORI", CamoSkill::RORI);
	setGlobalInt("TALUS", CamoSkill::TALUS);
	setGlobalInt("TATOOINE", CamoSkill::TATOOINE);
	setGlobalInt("YAVIN", CamoSkill::YAVIN);

	//Smuggling Tools
	setGlobalInt("PRECLASERKNIFE", ToolImplementation::PRECLASERKNIFE);
	setGlobalInt("UPGRADEKIT", ToolImplementation::UPGRADEKIT);
	setGlobalInt("FLOWANALYZERNODE", ToolImplementation::FLOWANALYZERNODE);
	setGlobalInt("MOLECULARCLAMP", ToolImplementation::MOLECULARCLAMP);
	setGlobalInt("ARMORKIT", UpgradeKitImplementation::ARMORKIT);
	setGlobalInt("WEAPONKIT", UpgradeKitImplementation::WEAPONKIT);
}

int ItemManagerImplementation::runItemLUAFile(lua_State* L) {
	String filename = getStringParameter(L);

	runFile("scripts/items/" + filename, L);

	return 0;
}

TangibleObject* ItemManagerImplementation::createTemplateFromLua(LuaObject itemconfig) {

	int crc = itemconfig.getIntField("objectCRC");
	String name = itemconfig.getStringField("objectName");
	String templ = itemconfig.getStringField("templateName");
	bool equipped = bool(itemconfig.getByteField("equipped"));
	int type = itemconfig.getIntField("objectType");
	uint16 itemMask = itemconfig.getIntField("itemMask");
	uint32 optionsBitmask = itemconfig.getIntField("optionsBitmask");
	bool slicable = itemconfig.getByteField("slicable");

	if (itemMask == 0)
		itemMask = TangibleObjectImplementation::ALL;

	TangibleObject* item = createPlayerObjectTemplate(type, 1, crc, UnicodeString(name), templ, equipped, false, "", 0);

	item->setObjectSubType(type);
	item->setPlayerUseMask(itemMask);
	item->setOptionsBitmask(optionsBitmask);
	item->setSlicable(slicable);

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

		((Armor*) item)->setArmorPiece(armorType);
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
	} else if (type & TangibleObjectImplementation::WEAPON ||
			type & TangibleObjectImplementation::LIGHTSABER || type == TangibleObjectImplementation::TRAP) {
		int damageType = itemconfig.getIntField("damageType");
		int ap = itemconfig.getIntField("armorPiercing");
		String cert = itemconfig.getStringField("certification");
		float as = itemconfig.getFloatField("attackSpeed");
		float mindmg = itemconfig.getFloatField("minDamage");
		float maxdmg = itemconfig.getFloatField("maxDamage");

		Weapon* weapon = (Weapon*) item;
		weapon->setDamageType(damageType);
		weapon->setArmorPiercing(ap);
		weapon->setAttackSpeed(as);
		weapon->setMinDamage(mindmg);
		weapon->setMaxDamage(maxdmg);

		if (type & TangibleObjectImplementation::LIGHTSABER) {
			int forceCost = itemconfig.getIntField("forceCost");
			weapon->setForceCost(forceCost);
		}

		if (weapon->isTrap()) {
			int uses =  itemconfig.getIntField("uses");
			String skill = itemconfig.getStringField("skill");  // TODO:  Should use certification

			((TrapThrowableWeapon*) weapon)->setUsesRemaining(uses);
			((TrapThrowableWeapon*) weapon)->setSkill(skill);
		}

		if (!cert.isEmpty())
			weapon->setCert(cert);

	} else if (type & TangibleObjectImplementation::DEED) {

		//System::out << "type & TangibleObjectImplementation::DEED" << endl;

		int surplusMaintenance = 0;
		float maintenanceRate = 0;
		int surplusPower = 0;
		float extractionRate = 0;
		float hopperSize = 0;


		switch (type) {
			case TangibleObjectImplementation::INSTALLATIONDEED:
				switch(DeedObjectImplementation::getSubType(crc)){
					case TangibleObjectImplementation::HARVESTER:
					{
						//System::out << "type & TangibleObjectImplementation::DEED & harvester!!!!" << endl;

						surplusMaintenance = itemconfig.getIntField("surplusMaintenance");
						maintenanceRate = itemconfig.getFloatField("maintenanceRate");
						surplusPower = itemconfig.getIntField("surplusPower");
						extractionRate = itemconfig.getFloatField("extractionRate");
						hopperSize = itemconfig.getFloatField("hopperSize");

						//System::out << "surplusMaintenance: " << surplusMaintenance << ", maintainanceRate: " << maintenanceRate << ", surplusPower: " << surplusPower << ", extractionRate: " << extractionRate << ", hopperSize: " << hopperSize << endl;


						HarvesterDeed* harv = (HarvesterDeed*) item;
						harv->setSurplusMaintenance(surplusMaintenance);
						harv->setMaintenanceRate(maintenanceRate);
						harv->setSurplusPower(surplusPower);
						harv->setExtractionRate(extractionRate);
						harv->setHopperSize(hopperSize);

						break;
					}
					case TangibleObjectImplementation::FACTORY:
					{
						surplusMaintenance = itemconfig.getIntField("surplusMaintenance");
						maintenanceRate = itemconfig.getFloatField("maintenanceRate");
						surplusPower = itemconfig.getIntField("surplusPower");
						hopperSize = itemconfig.getFloatField("hopperSize");

						FactoryDeed* fact = (FactoryDeed*) item;
						fact->setSurplusMaintenance(surplusMaintenance);
						fact->setMaintenanceRate(maintenanceRate);
						fact->setSurplusPower(surplusPower);
						fact->setHopperSize(hopperSize);
						break;
					}
					case TangibleObjectImplementation::GENERATOR:
					{
						surplusMaintenance = itemconfig.getIntField("surplusMaintenance");
						maintenanceRate = itemconfig.getFloatField("maintenanceRate");
						extractionRate = itemconfig.getFloatField("extractionRate");
						hopperSize = itemconfig.getFloatField("hopperSize");

						GeneratorDeed* gen = (GeneratorDeed*) item;
						gen->setSurplusMaintenance(surplusMaintenance);
						gen->setMaintenanceRate(maintenanceRate);
						gen->setExtractionRate(extractionRate);
						gen->setHopperSize(hopperSize);
						break;
					}
					case TangibleObjectImplementation::TURRET:
						break;
					case TangibleObjectImplementation::MINEFIELD:
						break;
				}
				break;
			case TangibleObjectImplementation::BUILDINGDEED:
				break;
			case TangibleObjectImplementation::PETDEED:
				break;
			case TangibleObjectImplementation::DROIDDEED:
				break;
			case TangibleObjectImplementation::VEHICLEDEED:
				break;
		}
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
			enhance->setAttribute(pool);
			break;
		}
		case PharmaceuticalImplementation::WOUNDPACK:
		{
			float eff = itemconfig.getFloatField("effectiveness");
			int pool = itemconfig.getIntField("poolAffected");

			WoundPack* wound = (WoundPack*) item;
			wound->setEffectiveness(eff);
			wound->setAttribute(pool);
			break;
		}
		case PharmaceuticalImplementation::CUREPACK:
		{
			float eff = itemconfig.getFloatField("effectiveness");
			uint64 condition = itemconfig.getLongField("conditionCured");

			CurePack* curepack = (CurePack*) item;
			curepack->setEffectiveness(eff);
			curepack->setState(condition);
			break;
		}
		case PharmaceuticalImplementation::STATEPACK:
		{
			uint64 state = itemconfig.getLongField("stateAffected");

			StatePack* statepack = (StatePack*) item;
			statepack->setState(state);
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
	} else if (type == TangibleObjectImplementation::WEARABLECONTAINER
			|| type == TangibleObjectImplementation::CONTAINER
			|| type == TangibleObjectImplementation::CONTAINER2) {

		int attributeSlots = itemconfig.getIntField("slots");
		Container* container = (Container*) item;
		container->setSlots(attributeSlots);
	} else if (type == TangibleObjectImplementation::CAMOKIT) {
		CamoKit* camoKit = (CamoKit*) item;
		int planet = itemconfig.getIntField("planetType");
		int uses = itemconfig.getIntField("uses");
		int cMin = itemconfig.getIntField("concealSkill");
		camoKit->setPlanet(planet);
		camoKit->setUsesRemaining(uses);
		camoKit->setConcealMin(cMin);
	} else if (type == TangibleObjectImplementation::CAMPKIT) {
				CampKit* campKit = (CampKit*) item;
				int xp = itemconfig.getIntField("xp");
				int duration = itemconfig.getIntField("duration");
				int campCRC = itemconfig.getIntField("campType");;
				campKit->setXP(xp);
				campKit->setDuration(duration);
				campKit->setCampType(campCRC);
    } else if (type == TangibleObjectImplementation::COMPONENT) {
	    Component* component = (Component*) item;
	    String attribute;
	    String title;
	    int charges, power;

	    switch (crc) {
	    case (0xDCC80CD1): //BEC
	    case (0x891C5134): //ABEC

	    	charges = itemconfig.getIntField("charges");
	    	attribute = "Charges";
	    	title = "exp_charges";
	    	component->addProperty(attribute, charges, 0, title);

	    case (0xC8272A3F): //LS
	    case (0x6F0ACB91): //ALS
	    case (0x6F7D65AD): //CRDM
	    case (0x10D04467): //ACRDM
	    case (0x83597C2E): //SDS
	    case (0xAFFCBBEB): //ASDS

            	power = itemconfig.getIntField("power");
            	attribute = "Power";
            	title = "exp_effectiveness";
            	component->addProperty(attribute, power, 0, title);
	    }
    } else if (item->isTool()) {
    	//ToolImplementation
    	Tool* tool = (Tool*) item;

    	uint32 toolType = itemconfig.getIntField("toolType");
    	float effectiveness = itemconfig.getFloatField("effectiveness");

    	tool->setToolType(toolType);
    	tool->setEffectiveness(effectiveness);

    	if (tool->isUpgradeKit()) {
    		uint8 kitType = itemconfig.getIntField("kitType");

    		UpgradeKit* upkit = (UpgradeKit*) tool;
    		upkit->setKitType(kitType);
    	}
    }

	return item;
}

int ItemManagerImplementation::addPlayerItem(lua_State * l) {
	LuaObject itemwrapper(l);

	String species = itemwrapper.getStringField("species");
	String sex = itemwrapper.getStringField("sex");
	String profession = itemwrapper.getStringField("profession");

	LuaObject itemconfig(itemwrapper.getObjectField("item"));

	TangibleObject* item = createTemplateFromLua(itemconfig);

	startingItems->addItemToProfession(profession, species, sex, item);

	return 0;
}

int ItemManagerImplementation::addBFItem(lua_State * l) {
	LuaObject itemwrapper(l);

	String name = itemwrapper.getStringField("name");

	LuaObject itemconfig(itemwrapper.getObjectField("item"));

	TangibleObject* item = createTemplateFromLua(itemconfig);

	bfItemSet->addItem(name, item);

	return 0;
}

int ItemManagerImplementation::addBFProf(lua_State * l) {

	LuaObject itemwrapper(l);

	String name = itemwrapper.getStringField("name");

	String prof = itemwrapper.getStringField("prof");

	String group = itemwrapper.getStringField("group");

	bfProfSet->addProfession(name, group, prof);

	return 0;
}

int ItemManagerImplementation::addBFGroup(lua_State * l) {
	LuaObject itemwrapper(l);

	String name = itemwrapper.getStringField("name");

	String parent = itemwrapper.getStringField("parent");

	bfProfSet->addGroup(name, parent);

	return 0;
}

void ItemManagerImplementation::giveBFItemSet(Player * player, String& set) {
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
		if (item == NULL) {
			System::out << "ItemManagerImplementation::giveBFItemSet(...), item == NULL!, set = " << set << endl;
		} else {
			player->addInventoryItem(item);
			item->sendTo(player);

			if (item->isContainer())
				server->addObject(item);
		}
	}
}

//TODO: Modify this function when a global clone() function is available for all objects
void ItemManagerImplementation::loadDefaultPlayerItems(Player* player) {
	String prof = player->getStartingProfession();
	prof = prof.subString(prof.indexOf('_') + 1);

	String race = player->getRaceFileName();
	int ls = race.lastIndexOf('/');
	int fu = race.indexOf('_');
	int dot = race.lastIndexOf('.');

	String species = race.subString(ls + 1, fu);
	String sex = race.subString(fu + 1, dot);

	String gen = "general";
	String all = "all";

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
		StringBuffer query;

		query << "SELECT datapad.inx, datapad.character_id, datapad.name, datapad.itnocrc, datapad.item_crc, "
			<< "datapad.file_name, datapad.attributes, datapad.appearance, datapad.itemMask, datapad.obj_id "
			<< "FROM datapad where character_id = " << player->getCharacterID() << ";";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		MountCreature* land = NULL;

		while (res->next()) {
			String appearance = res->getString(7);

			land = new MountCreature(player, res->getString(2), "monster_name",
					res->getLong(3), res->getLong(4), res->getUnsignedLong(9));
			land->setObjectFileName(res->getString(5));

			land->setZoneProcessServer(pServer);

			if (appearance != "") {
				BinaryData cust(appearance);
				String custStr;
				cust.decode(custStr);

				land->setCustomizationString(custStr);
			}

			String attributes = res->getString(6);

			land->setAttributes(attributes );
			land->parseItemAttributes();

			land->addToDatapad();

		}

		delete res;

	} catch (DatabaseException& e) {
		player->error("Load Datapad exception in : ItemManagerImplementation::loadDefaultPlayerDatapadItems(Player* player)");
		player->error(e.getMessage());
	} catch (...) {
		System::out << "Exception in ItemManagerImplementation::loadDefaultPlayerDatapadItems(Player* player)\n";
		player->error("Load Datapad unknown exception in : ItemManagerImplementation::loadDefaultPlayerDatapadItems(Player* player)");
	}

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
			StringBuffer query;
			query << "UPDATE `characters` set itemShift = " << player->getItemShift() << " ";
			query << "WHERE character_id = " << player->getCharacterID() << ";";

			ServerDatabase::instance()->executeStatement(query);
		} catch (DatabaseException& e) {
			System::out << e.getMessage() << "\n";
		}

	}
}

void ItemManagerImplementation::createPlayerItem(Player* player, TangibleObject* item) {
	try {
		String itemname = item->getName().toString();
		MySqlDatabase::escapeString(itemname);

		String appearance;
		String itemApp;
		item->getCustomizationString(itemApp);
		BinaryData cust(itemApp);
		cust.encode(appearance);

		String attr = item->getAttributes();
		MySqlDatabase::escapeString(attr);

		StringBuffer query;

		query << "REPLACE DELAYED INTO `character_items` "
		<< "(`item_id`,`character_id`,`name`,`template_crc`,`template_type`,`template_name`,`equipped`,`deleted`,`attributes`,`appearance`, `itemMask`, `optionsBitmask`)"
		<< " VALUES(" << item->getObjectID() << "," << player->getCharacterID()
		<< ",'" << itemname << "',"
		<< item->getObjectCRC() << "," << item->getObjectSubType() << ",'" << item->getTemplateName() << "',"
		<< item->isEquipped() << ",0,'" << attr
		<< "','" << appearance.subString(0, appearance.length() - 1) << "', " << item->getPlayerUseMask() << ", " << item->getOptionsBitmask() << ")";

		ServerDatabase::instance()->executeStatement(query);

		item->setPersistent(true);

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	} catch (...) {
		System::out << "unreported exception caught in ItemManagerImplementation::createPlayerItem(Player* player, TangibleObject* item)\n";
	}
}

void ItemManagerImplementation::savePlayerItem(Player* player, TangibleObject* item) {
	try {
		String appearance = "";
		String itemApp;

		item->getCustomizationString(itemApp);
		BinaryData cust(itemApp);
		cust.encode(appearance);

		String attr = item->getAttributes();
		MySqlDatabase::escapeString(attr);

		//uint64 contiID = 0;
		//Container* conti = (Container*) item->getContainer();

		//if (conti != NULL && !item->getContainer()->isPlayer())
		//	contiID = conti->getObjectID();

		StringBuffer query;

		query << "UPDATE `character_items` set equipped = " << item->isEquipped();
		query << ", character_id = " << player->getCharacterID() << " ";
		query << ", attributes = '" << attr << "' ";
		query << ", appearance = '" << appearance.subString(0, appearance.length() - 1) << "' ";
		query << ", itemMask = " << item->getPlayerUseMask() << " ";
		query << ", optionsBitmask = " << item->getOptionsBitmask() << " ";
		//query << ", container = " << contiID << " ";
		query << "where item_id = " << item->getObjectID();

		ServerDatabase::instance()->executeStatement(query);

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	} catch (...) {
		System::out << "unreported exception caught in ItemManagerImplementation::savePlayerItem(Player* player, TangibleObject* item)\n";
	}
}

void ItemManagerImplementation::deletePlayerItem(Player* player, TangibleObject* item, bool notify) {
	try {
		StringBuffer query;
		query << "update `character_items` set deleted = " << 1 << " where item_id = " << item->getObjectID();

		ServerDatabase::instance()->executeStatement(query);

		//System::out << query.toString() << endl;

		StringBuffer playertxt;
		if (notify)
			playertxt << "You have destroyed " << item->getName().toString() << ".";

		player->sendSystemMessage(playertxt.toString());
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	}
}

void ItemManagerImplementation::showDbStats(Player* player) {
	StringBuffer txt;
	txt << "Database Statistics\n";

	try {
		StringBuffer query;
		query << "select item_id from `character_items`";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		txt << res->size() << " total items in the database\n";

		delete res;
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	}

	try {
		StringBuffer query;
		query << "select item_id from `character_items` where `character_id` = " << player->getCharacterID() << " and `deleted` = 1";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		txt << res->size() << " deleted items in the database.\n";

		delete res;
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	}

	try {
		StringBuffer query;
		query << "select item_id from `character_items` where `character_id` = " << player->getCharacterID() << " and `template_type` = 2";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		txt << res->size() << " Weapon Items, ";

		delete res;
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	}

	try {
		StringBuffer query;
		query << "select item_id from `character_items` where `character_id` = " << player->getCharacterID() << " and `template_type` = 3";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		txt << res->size() << " Clothing Items, ";

		delete res;
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	}

	try {
		StringBuffer query;
		query << "select item_id from `character_items` where `character_id` = " << player->getCharacterID() << " and `template_type` = 4";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		txt << res->size() << " Armor Items.\n";

		delete res;
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	}

	try {
		StringBuffer query;
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

		player->sendSystemMessage(txt.toString());
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	}

	try {
		StringBuffer query;
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

		player->sendSystemMessage(txt.toString());
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	}

	player->sendSystemMessage(txt.toString());
}

void ItemManagerImplementation::showDbDeleted(Player* player) {
	try {
		StringBuffer query;
		query << "select * from `character_items` where `character_id` = " << player->getCharacterID() << " and `deleted` = 1";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		StringBuffer txt;

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

		player->sendSystemMessage(txt.toString());
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	}
}

void ItemManagerImplementation::purgeDbDeleted(Player* player) {
	//Don't delete items flagged DELETED = 1 but existing in the player_storage DB !
	try {
		StringBuffer query;

		query << "DELETE FROM character_items "
			<< "LEFT JOIN player_storage "
			<< "ON (character_items.item_id = player_storage.item_id) "
			<< "WHERE player_storage.item_id IS NULL "
			<< "and character_items.deleted=1;";

		ServerDatabase::instance()->executeStatement(query);

		player->sendSystemMessage("Deleted items purged.");

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	}
}

int ItemManagerImplementation::createForageItemFromLua(lua_State* l) {
	LuaObject itemconfig(l);

	int forageGroup = itemconfig.getIntField("forageGroup");
	TangibleObject* item = createTemplateFromLua(itemconfig);

	forageItems->add(item, forageGroup);

    return 0;
}

void ItemManagerImplementation::giveForageItem(Player* player, int group, int count) {
	TangibleObject* item;
    String crafter;
    String serial;
    String attributeName;
    uint64 objectID;
    int type;
    float value;

	if (group != 6) {
	   for (int i = 0; i < count; i++) {

	       //Pull a random item from the specified loot group.
           item = forageItems->get(group);

           //Set a new object ID.
           objectID = player->getNewItemID();
           item = clonePlayerObjectTemplate(objectID, item);

           //Set the crafter's name blank.
           crafter = " ";
           item->setCraftersName(crafter);

           //Set the serial number.
           serial = player->getZone()->getZoneServer()->getCraftingManager()->generateCraftedSerial();
           item->setCraftedSerial(serial);

           //Randomize the attribute values.
           item = forageStatRandomizer(item);

           //Give item to player.
           player->addInventoryItem(item);
           item->sendTo(player);
       }

	} else { //Exceptional Components.
        if (count > 0) {

		    //Pull a random item from the specified loot group.
		   item = forageItems->get(group);

		   //Set a new object ID.
		   objectID = player->getNewItemID();
		   item = clonePlayerObjectTemplate(objectID, item);

		   //Set the crafter's name blank.
		   crafter = " ";
		   item->setCraftersName(crafter);

		   //Set the serial number.
		   serial = player->getZone()->getZoneServer()->getCraftingManager()->generateCraftedSerial();
		   item->setCraftedSerial(serial);

		   //Give first item.
		   player->addInventoryItem(item);
		   item->sendTo(player);

		   //Give additional identical items.
		   for (int i = 0; i < count - 1; i++) {
		       objectID = player->getNewItemID();
		       item = clonePlayerObjectTemplate(objectID, item);
		       player->addInventoryItem(item);
		       item->sendTo(player);
		   }
        }
    }
}

TangibleObject* ItemManagerImplementation::forageStatRandomizer(TangibleObject* item) {
	int type = item->getObjectSubType();
	float value;
	String property;
	uint64 crc = item->getObjectCRC();

	Component* component = (Component*)item;

	switch (crc) {
	    case (0xDCC80CD1): //BEC
	    case (0x891C5134): //ABEC
	    	property = "Charges";
	    	value = component->getAttributeValue(property);
	    	if (value != DraftSchematicValuesImplementation::valueNotFound) {

	    	   	value += System::random((int)value * 3);
	    	   	component->changeAttributeValue(property, value);
	    	}
	    case (0xC8272A3F): //LS
	    case (0x6F0ACB91): //ALS
	    case (0x6F7D65AD): //CRDM
	    case (0x10D04467): //ACRDM
	    case (0x83597C2E): //SDS
	    case (0xAFFCBBEB): //ASDS
	    	property = "Power";
	    	value = component->getAttributeValue(property);
	    	if (value != DraftSchematicValuesImplementation::valueNotFound) {
	    	    value += System::random((int)value * 3);
	    	   	component->changeAttributeValue(property, value);
	    	}
    }

   return item;
}

void ItemManagerImplementation::transferContainerItem(Player* player, TangibleObject* item, uint64 destinationID) {
	//Item cant be null here, o/w the function would not have been called
	//This function is called by the ObjectControllerMessage.cpp

	SceneObject* sourceObject = NULL;
	SceneObject* destinationObject = NULL;

	try {
		item->wlock(player);

		if (item->isEquipped()) {
			player->sendSystemMessage("You cannot drop equipped items.");
			item->unlock();
			return;
		}

		SceneObject* object = (SceneObject*) item;

		sourceObject = item->getParent();
		if (sourceObject == NULL) {
			item->unlock();
			return;
		}

		Container* sourceContainer = NULL;

		Zone* zone = player->getZone();
		if (zone == NULL) {
			item->unlock();
			return;
		}

		destinationObject = zone->lookupObject(destinationID);

		bool destinationIsInventory = false;
		if (destinationID == player->getInventory()->getObjectID())
			destinationIsInventory = true;

		if (destinationObject == NULL && !destinationIsInventory) {
			player->sendSystemMessage("You cannot drop items here.");
			item->unlock();
			return;
		}

		//The item comes from...
		bool comesFromCell = false;
		bool comesFromInventory = false;
		bool comesFromInventoryContainer = false;
		bool comesFromExternalContainer = false;
		bool comesFromDeadCreature = false;

		TangibleObject* sourceTano = (TangibleObject*) sourceObject;

		if (sourceObject->getObjectID() == player->getInventory()->getObjectID())
			comesFromInventory = true;
		else {
			item->unlock();

			if (sourceObject != player)
				sourceObject->wlock(player);
		}

		if (!comesFromInventory) {
			if (sourceObject->isCell()) {
				comesFromCell = true;
			} else if (sourceObject->getObjectID() == player->getInventory()->getObjectID()) {
				comesFromInventoryContainer = true;
				sourceContainer = (Container*) sourceObject;
			} else if (sourceTano->isContainer()) {
				comesFromExternalContainer = true;
				sourceContainer = (Container*) sourceObject;
			}

			if (sourceObject != player)
				sourceObject->unlock();

			item->wlock(player);
		}

		//The item goes to...
		bool destinationIsCell = false;
		bool destinationIsExternalContainer = false;
		bool destinationIsInventoryContainer = false;
		bool itemIsContainer = false;

		if (!destinationIsInventory) {
			item->unlock();

			destinationObject->wlock(player);

			if (destinationObject->isCell()) {
				destinationIsCell = true;
			} else {
				if (destinationObject->isTangible()) {
					TangibleObject* destinationTano = (TangibleObject*) destinationObject;

					//We need to test if the PARENT of the destination is
					//a) not NULL (shouldnt be possible)
					//b) is the inventory, so the
					//destination object must be a container, maybe even within the inventory (eg. backpack)

					//I reverse patch 1053. It has a wrong logic and is causing disappearing items.

					if (destinationObject->getParent() != NULL) {

						if (destinationObject->getParentID() == player->getInventory()->getObjectID())
							destinationIsInventoryContainer = true;
						else if (destinationTano->isContainer())
							destinationIsExternalContainer = true;
					}
				}
			}

			if (!destinationIsInventory) {
				destinationObject->unlock();
				item->wlock(player);
			}
		}

		if (item->isContainer())
			itemIsContainer = true;

		item->unlock();

		if ((itemIsContainer && destinationIsInventoryContainer) || (itemIsContainer && destinationIsExternalContainer)) {
			player->sendSystemMessage("You cannot drop a container into another container");
			return;
		}

		if (destinationIsInventoryContainer || destinationIsExternalContainer) {
			int containerItems = ((Container*) destinationObject)->objectsSize();
			int attributeSlots = ((Container*) destinationObject)->getSlots();

			if (containerItems >= attributeSlots) {
				player->sendSystemMessage("The container is full.");
				return;
			}
		}

		if (sourceContainer != NULL && player->getInventory() != sourceContainer && !sourceContainer->isTangible()  && !sourceContainer->isContainer())
			sourceContainer = NULL;

		moveItem(zone, player, item, object, comesFromCell, comesFromInventory, comesFromInventoryContainer,
				comesFromExternalContainer, destinationObject, destinationIsCell, destinationIsInventory,
				destinationIsInventoryContainer, destinationIsExternalContainer,sourceContainer, itemIsContainer);

	} catch (...) {
		item->unlock();
		destinationObject->unlock();
		sourceObject->unlock();

		System::out << "Unreported exception caught in ItemManagerImplementation::transferContainerItem(Player* player, TangibleObject* item, uint64 destinationID)\n";
	}
}

void ItemManagerImplementation::moveItem(Zone* zone, Player* player, TangibleObject* item, SceneObject* object,	bool comesFromCell,
		bool comesFromInventory, bool comesFromInventoryContainer, bool comesFromExternalContainer,	SceneObject* destinationObject,
		bool destinationIsCell, bool destinationIsInventory, bool destinationIsInventoryContainer,bool destinationIsExternalContainer,
		Container* sourceContainer, bool itemIsContainer) {

	BuildingObject* building = NULL;
	Container* conti = NULL;



	uint64 objectID = 0;
	if (object != NULL)
		objectID = object->getObjectID();

	try {
		item->wlock(player);

		if (comesFromInventory)
			player->removeInventoryItem(item);

		if (comesFromInventoryContainer || comesFromExternalContainer) {
			item->unlock();

			if (sourceContainer == NULL)
				return;

			//********** Temporarely debug code for TC
			if (sourceContainer != player->getInventory()) {
				bool container = sourceContainer->isTangible() && sourceContainer->isContainer();
				if (!container) {
					System::out << "ATTENTION - SERIOUS PROBLEM: There is an object considered to be a container, but it isnt. The name of the sourceContainer is "
					<< sourceContainer->getObjectCRC() << "  and the OID is " << sourceContainer->getObjectID() << "\n";

					return;
				}
			}
			//**********

			try {
				sourceContainer->wlock(player);

				sourceContainer->removeObject(item->getObjectID());

				sourceContainer->unlock();
			} catch (...) {
				sourceContainer->unlock();
			}

			item->wlock(player);
		}

		if (destinationIsInventoryContainer || destinationIsExternalContainer)
			conti = (Container*) destinationObject;

		item->initializePosition(player->getPositionX(), player->getPositionZ()+0.08, player->getPositionY());

		if (destinationIsCell) {
			building = (BuildingObject*) destinationObject->getParent();
			if (building == NULL) {
				item->unlock();
				return;
			}

			//if i use item->setParent its diff. from "object->setParent" (clue me in :P )
			try {
				if (item != object)
					object->wlock();

				object->setParent(destinationObject);
				item->setParent(destinationObject);

				object->insertToZone(zone);
				object->setZoneProcessServer(pServer);

				if (item != object)
					object->unlock();
			} catch (...) {
				if (item != object)
					object->unlock();
			}

			BaseMessage* linkmsg = item->link(destinationObject);
			player->broadcastMessage(linkmsg);

			UpdateTransformWithParentMessage* transformMessage = new UpdateTransformWithParentMessage(item);
			player->broadcastMessage(transformMessage);

		} else if (destinationIsInventoryContainer || destinationIsExternalContainer) {
			try {
				if (item != object)
					object->wlock();
				if (comesFromCell) {
					BuildingObject* sourceBuilding = (BuildingObject*) object->getParent()->getParent();

					if (sourceBuilding != NULL) {
						object->removeFromZone();
						Zone* zone = object->getZone();
						if (zone != NULL)
							zone->getZoneServer()->addObject(object);
					}
				}

				object->setParent(destinationObject);
				item->setParent(destinationObject);

				if (item != object)
					object->unlock();
			} catch (...) {
				if (item != object)
					object->unlock();
			}

			BaseMessage* linkmsg = item->link(destinationObject);
			player->broadcastMessage(linkmsg);

			UpdateTransformMessage* transformMessage = new UpdateTransformMessage(item, 0, 0, 0);

			if (comesFromInventory && destinationIsInventoryContainer)
				player->sendMessage(transformMessage);
			else
				player->broadcastMessage(transformMessage);

			if (destinationObject->isTangible() && ((TangibleObject*)destinationObject)->isContainer())
				((Container*) destinationObject)->addObject(item);
			else {
				System::out << "error destination is not a container its a " << destinationObject->getObjectType();
				if (destinationObject->isTangible()) {
					System::out << " tano subtype " << ((TangibleObject*)destinationObject)->getObjectSubType() << " crc:" << destinationObject->getObjectCRC();
				}
			}

		} else if (destinationIsInventory) {
			try {
				if (item != object)
					object->wlock();

				if (comesFromCell) {
					BuildingObject* sourceBuilding = (BuildingObject*) object->getParent()->getParent();

					//If a s container gets picked up, we need to close the container for others.
					//This is done by removing the object from zone and re-inserting. We also re-send
					//the item to the player picking up, o/w the item won't show up in inventory

					if (sourceBuilding != NULL) {
						Zone* zone = object->getZone();

						object->removeFromZone();

						if (zone != NULL) {
							zone->getZoneServer()->addObject(object);
						}
					}
				}

				Inventory* inventory = player->getInventory();
				if (inventory == NULL) {
					if (item != object)
						object->unlock();
					item->unlock();
					return;
				}

				object->setParent(inventory);
				item->setParent(inventory, 0xFFFFFFFF);

				inventory->addObject(item);
				createPlayerItem(player, item);

				object->sendTo(player);

				BaseMessage* linkmsg = item->link(inventory);
				player->broadcastMessage(linkmsg);

				UpdateTransformMessage* transformMessage = new UpdateTransformMessage(item, 0, 0, 0);
				player->broadcastMessage(transformMessage);

				if (item != object)
					object->unlock();
			} catch (...) {
				if (item != object)
					object->unlock();
			}
		}

		item->unlock();

	}  catch (Exception& e) {
		item->unlock();

		System::out << "exception caught in ItemManagerImplementation::moveItem(....)\n" << e.getMessage();
		return;
	}	catch (...) {
		item->unlock();

		System::out << "Unreported exception caught in ItemManagerImplementation::moveItem(....)\n";
		return;
	}

	reflectItemMovementInDB(player, item, comesFromCell, comesFromInventory, comesFromInventoryContainer,
			comesFromExternalContainer,	destinationObject, destinationIsCell, destinationIsInventory,
			destinationIsInventoryContainer, destinationIsExternalContainer, itemIsContainer, conti, building);
}

void ItemManagerImplementation::reflectItemMovementInDB(Player* player, TangibleObject* item, bool comesFromCell,
		bool comesFromInventory, bool comesFromInventoryContainer, bool comesFromExternalContainer,	SceneObject* destinationObject,
		bool destinationIsCell, bool destinationIsInventory, bool destinationIsInventoryContainer, bool destinationIsExternalContainer,
		bool itemIsContainer, Container* conti,	BuildingObject* building) {

	if (comesFromCell || comesFromExternalContainer) {
		deleteItemFromPlayerStorageDB(item);

		if (destinationIsInventory) {
			if (itemIsContainer) {
				Container* container = (Container*) item;
				moveNestedItemsToInventoryContainer(player, container);
			}

			/* Can never happen
			else if (destinationIsInventoryContainer)
				createPlayerItemInInventoryContainer(player, item, destinationObject);
			*/
		}

	} else if (comesFromInventory) {
		if (destinationIsInventoryContainer)
			moveItemInInventory(player, item, destinationObject, false);

		if (destinationIsCell || destinationIsExternalContainer) {
			deletePlayerItem(player, item, false);

			insertItemIntoPlayerStorage(player, item, destinationObject, conti, building);

			if (itemIsContainer && destinationIsCell) {
				Container* container = (Container*) item;

				if (container != NULL)
					moveNestedItemsToPlayerStorage(player, container);
			}
		}

	} else if (comesFromInventoryContainer) {
		if (destinationIsInventory)
			moveItemInInventory(player, item, NULL, true);
		else if (destinationIsCell || destinationIsExternalContainer) {
			deletePlayerItem(player, item, false);
			insertItemIntoPlayerStorage(player, item, destinationObject, conti, building);
		}
	}
}

void ItemManagerImplementation::deleteItemFromPlayerStorageDB(TangibleObject* item) {
	//Item cant be NULL here, checked in call already

	try {
		item->lock();

		StringBuffer query;

		query << "DELETE FROM player_storage where item_id = " << item->getObjectID() << " or container=" << item->getObjectID() << ";";
		ServerDatabase::instance()->executeStatement(query);

		item->unlock();

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		item->unlock();

	} catch (...) {
		System::out << "unreported exception caught in ItemManagerImplementation::deleteItemFromPlayerStorageDB(TangibleObject* item)\n";
		item->unlock();
	}
}

void ItemManagerImplementation::moveNestedItemsToPlayerStorage(Player* player, Container* container) {
	TangibleObject* item;

	try {
		container->wlock();

		StringBuffer query;

		query << "START TRANSACTION";
		ServerDatabase::instance()->executeStatement(query);

		for (int i = 0; i < container->objectsSize(); ++i) {
			item = (TangibleObject*) container->getObject(i);

			try {
				item->wlock(container);

				query.deleteAll();

				query << "UPDATE character_items"
				<< " set character_id = " << player->getCharacterID() << ", deleted = 1, container = 0"
				<< " WHERE item_id = " << item->getObjectID() << ";";

				ServerDatabase::instance()->executeStatement(query);

				uint64 containerID = 0;

				containerID = container->getObjectID();

				String itemname = item->getName().toString();
				MySqlDatabase::escapeString(itemname);

				String appearance;
				String itemApp;

				item->getCustomizationString(itemApp);
				BinaryData cust(itemApp);
				cust.encode(appearance);

				String attr = item->getAttributes();
				MySqlDatabase::escapeString(attr);

				float x = 0;
				float y = 0;
				float z = 0;

				float oX = 0;
				float oY = 0;
				float oZ = 0;
				float oW = 0;

				query.deleteAll();

				query << "REPLACE DELAYED INTO `player_storage` "
				<< "(`item_id`,`structure_id`,`name`,`template_crc`,`template_type`"
				<< ",`template_name`,`container`,`parent_id`,`appearance`, `attributes`,`itemMask`,`optionsBitmask`,X,Y,Z,oX,oY,oZ,oW,dropped_by_character) "
				<< "VALUES (" << item->getObjectID() << ",0,'" << itemname << "',"
				<< item->getObjectCRC() << "," << item->getObjectSubType() << ",'" << item->getTemplateName() << "',"
				<< containerID << ",0,'" << appearance.subString(0, appearance.length() - 1)
				<< "','" << attr << "'," << item->getPlayerUseMask() << "," << item->getOptionsBitmask() << ","
				<< x << "," << y << "," << z << "," << oX << "," << oY << "," << oZ << "," << oW << "," << player->getCharacterID() << ")";

				ServerDatabase::instance()->executeStatement(query);

				item->unlock();
			} catch (...) {
				item->unlock();
			}
		}

		query.deleteAll();

		query << "COMMIT";

		ServerDatabase::instance()->executeStatement(query);

		container->unlock();
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		container->unlock();

	} catch (...) {
		System::out << "unreported exception caught in moveNestedItemsToPlayerStorage(Player* player, TangibleObject* item)\n";
		container->unlock();
	}
}

void ItemManagerImplementation::moveNestedItemsToInventoryContainer(Player* player, Container* container) {
	TangibleObject* item;

	try {
		container->wlock();

		StringBuffer query;

		query << "START TRANSACTION";
		ServerDatabase::instance()->executeStatement(query);

		for (int i = 0; i < container->objectsSize(); ++i) {
			item = (TangibleObject*) container->getObject(i);
			if (item != NULL) {
				try {
					item->wlock(container);

					query.deleteAll();

					query << "UPDATE character_items"
					<< " set character_id = " << player->getCharacterID() << ", deleted = 0, container = " << container->getObjectID()
					<< " WHERE item_id = " << item->getObjectID() << ";";

					ServerDatabase::instance()->executeStatement(query);

					item->unlock();
				} catch (...) {
					item->unlock();
				}
			}
		}

		query.deleteAll();

		query << "COMMIT";

		ServerDatabase::instance()->executeStatement(query);

		container->unlock();
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		container->unlock();

	} catch (...) {
		System::out << "unreported exception caught in moveNestedItemsToInventoryContainer(Player* player, TangibleObject* item)\n";
		container->unlock();
	}
}

void ItemManagerImplementation::createPlayerItemInInventoryContainer(Player* player, TangibleObject* item, SceneObject* destinationObject) {
	try {
		destinationObject->wlock();
		item->wlock();

		StringBuffer query;

		query.deleteAll();
		query << "UPDATE character_items"
		<< " set character_id = " << player->getCharacterID() << ", deleted = 0, container = " << destinationObject->getObjectID()
		<< " WHERE item_id = " << item->getObjectID() << ";";

		ServerDatabase::instance()->executeStatement(query);

		item->unlock();
		destinationObject->unlock();

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		item->unlock();
		destinationObject->unlock();
	} catch (...) {
		System::out << "unreported exception caught in ItemManagerImplementation::deleteItemFromPlayerStorageDB(TangibleObject* item)\n";
		item->unlock();
		destinationObject->unlock();
	}
}

void ItemManagerImplementation::moveItemInInventory(Player* player, TangibleObject* item, SceneObject* destinationObject,bool destinationIsInventory) {
	uint64 containerID = 0;
	uint64 itemID;

	try {
		if (item == NULL)
			return;

		if (!destinationIsInventory)
			destinationObject->wlock();

		item->wlock();

		itemID = item->getObjectID();

		item->unlock();


		if (destinationObject != NULL) {
			if (destinationObject->isTangible()) {
				TangibleObject* destinationItem = (TangibleObject*) destinationObject;

				if (destinationItem->isContainer())
					containerID = destinationItem->getObjectID();
			}
		}

		StringBuffer query;
		query.deleteAll();

		query << "UPDATE character_items"
			<< " set character_id = " << player->getCharacterID() << ", deleted = 0, container = " << containerID
			<< " WHERE item_id = " << itemID << ";";

		ServerDatabase::instance()->executeStatement(query);

		if (!destinationIsInventory)
			destinationObject->unlock();

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";

		if (!destinationIsInventory)
			destinationObject->unlock();

	} catch (...) {
		System::out << "unreported exception caught in createPlayerItemInInventoryContainer(Player* player, TangibleObject* item, SceneObject* destinationObject)\n";

		if (!destinationIsInventory)
			destinationObject->unlock();
	}
}

void ItemManagerImplementation::insertItemIntoPlayerStorage(Player* player, TangibleObject* item,
		SceneObject* destinationObject, Container* conti, BuildingObject* building) {

	try {
		item->wlock();

		uint64 structureID = 0;
		uint64 containerID = 0;
		uint64 parentID = 0;

		if (building != NULL)
			structureID = building->getObjectID();

		if (conti != NULL)
			containerID = conti->getObjectID();

		if (destinationObject->getParent() != NULL && conti == NULL)
			parentID = destinationObject->getObjectID();

		String itemname = item->getName().toString();
		MySqlDatabase::escapeString(itemname);

		String appearance = " "; //Whitespace intended!
		String itemApp;

		item->getCustomizationString(itemApp);
		BinaryData cust(itemApp);
		cust.encode(appearance);

		String attr = item->getAttributes();
		MySqlDatabase::escapeString(attr);

		float x = item->getPositionX();
		float y =  item->getPositionY();
		float z = item->getPositionZ();

		float oX = item->getDirectionX();
		float oY = item->getDirectionY();
		float oZ = item->getDirectionZ();
		float oW = item->getDirectionW();

		StringBuffer query;

		query << "REPLACE DELAYED INTO `player_storage` "
		<< "(`item_id`,`structure_id`,`name`,`template_crc`,`template_type`"
		<< ",`template_name`,`container`,`parent_id`,`appearance`, `attributes`,`itemMask`,`optionsBitmask`,X,Y,Z,oX,oY,oZ,oW,dropped_by_character) "
		<< "VALUES (" << item->getObjectID() << "," << structureID << ",'" << itemname << "',"
		<< item->getObjectCRC() << "," << item->getObjectSubType() << ",'" << item->getTemplateName() << "',"
		<< containerID << "," << parentID << ",'" << appearance.subString(0, appearance.length() - 1)
		<< "','" << attr << "'," << item->getPlayerUseMask() << "," << item->getOptionsBitmask() << ","
		<< x << "," << y << "," << z << "," << oX << "," << oY << "," << oZ << "," << oW << "," << player->getCharacterID() << ")";

		ServerDatabase::instance()->executeStatement(query);

		item->unlock();
	} catch (DatabaseException& e) {
		item->unlock();
		System::out << e.getMessage() << "\n";

	} catch (...) {
		item->unlock();
		System::out << "unreported exception caught in insertItemIntoPlayerStorage(TangibleObject* item, SceneObject* destinationObject, Container* conti, BuildingObject* building)\n";
	}
}

void ItemManagerImplementation::loadStructurePlayerItems(Player* player, uint64 cellID) {
	Zone* zone = player->getZone();
	if (zone == NULL)
		return;


	SceneObject* cellSCO = zone->lookupObject(cellID);
	if (cellSCO == NULL)
		return;

	if (!cellSCO->isCell())
		return;

	BuildingObject* building = (BuildingObject*) cellSCO->getParent();
	if (building == NULL)
		return;


	// this is totally fucked up
	/*if (!building->getStorageLoaded())
		loadContainersInStructures(player, building);*/
}

void ItemManagerImplementation::loadContainersInStructures(Player* player, BuildingObject* building) {
	try {
		ResultSet* result = NULL;
		Zone* zone = NULL;

		building->wlock();

		zone = building->getZone();

		if (zone == NULL) {
			building->unlock();
			return;
		}

		StringBuffer query;

		query << "select * from `player_storage` where `structure_id` = " << building->getObjectID() << " and container = 0;";

		result = ServerDatabase::instance()->executeQuery(query);

		while (result->next())	{
			uint64 objectid = result->getUnsignedLong(0);
			int objecttype = result->getInt(4);
			uint32 objectcrc = result->getUnsignedInt(3);
			String objectname = result->getString(2);
			char* objecttemp = result->getString(5);
			uint64 container = result->getUnsignedLong(6);
			uint64 parentID = result->getUnsignedLong(7);
			String appearance = result->getString(9);
			uint16 itemMask = result->getUnsignedInt(10);

			float X = result->getFloat(11);
			float Y = result->getFloat(12);
			float Z = result->getFloat(13);

			float oX = result->getFloat(14);
			float oY = result->getFloat(15);
			float oZ = result->getFloat(16);
			float oW = result->getFloat(17);

			uint32 optionsBitmask = result->getUnsignedInt(19);

			BinaryData cust(appearance);

			String custStr;
			cust.decode(custStr);

			bool equipped = false;

			String attributes = result->getString(8);

			TangibleObject* item = createPlayerObjectTemplate(objecttype, objectid, objectcrc,
					UnicodeString(objectname), objecttemp, equipped, false, "", 0);

			if (item == NULL) {
				building->unlock();

				delete result;
				return;
			}

			item->initializePosition(X,Z,Y);
			item->setDirection(oX,oZ,oY,oW);

			item->setAttributes(attributes);
			item->parseItemAttributes();

			item->setPlayerUseMask(itemMask);

			item->setOptionsBitmask(optionsBitmask);

			item->setCustomizationString(custStr);

			item->setPersistent(true);

			server->addObject(item);

			SceneObject* cell = zone->lookupObject(parentID);
			if (cell != NULL) {
				item->setParent(cell);
				item->setParent(cell);

				item->insertToZone(zone);
				item->setZoneProcessServer(pServer);

				BaseMessage* linkmsg = item->link(cell);
				player->broadcastMessage(linkmsg);

				UpdateTransformWithParentMessage* transformMessage = new UpdateTransformWithParentMessage(item);
				player->broadcastMessage(transformMessage);

				if (item->isContainer())
					loadItemsInContainersForStructure(player, (Container*) item);
			}
		}

		building->setStorageLoaded(true);

		building->unlock();

		delete result;
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";

		building->unlock();
	} catch (...) {
		System::out << "unreported exception caught in ItemManagerImplementation::loadContainersInStructures(Player* player, BuildingObject* building)\n";

		building->unlock();
	}
}

void ItemManagerImplementation::loadItemsInContainersForStructure(Player* player, Container* conti) {
	try {
		conti->wlock();

		uint64 contiID = conti->getObjectID();

		StringBuffer query;

		query << "select * from `player_storage` where `container` = " << contiID << ";";

		ResultSet* contiResult = ServerDatabase::instance()->executeQuery(query);

		while (contiResult->next())	{
			uint64 objectid = contiResult->getUnsignedLong(0);
			int objecttype = contiResult->getInt(4);
			uint32 objectcrc = contiResult->getUnsignedInt(3);
			String objectname = contiResult->getString(2);
			char* objecttemp = contiResult->getString(5);
			uint64 container = contiResult->getUnsignedLong(6);
			uint64 parentID = contiResult->getUnsignedLong(7);
			String appearance = contiResult->getString(9);
			uint16 itemMask = contiResult->getUnsignedInt(10);
			uint32 optionsBitmask = contiResult->getUnsignedInt(19);

			BinaryData cust(appearance);

			String custStr;
			cust.decode(custStr);

			bool equipped = false;

			String attributes = contiResult->getString(8);

			TangibleObject* item = createPlayerObjectTemplate(objecttype, objectid, objectcrc,
					UnicodeString(objectname), objecttemp, equipped, false, "", 0);

			if (item == NULL) {
				delete contiResult;

				conti->unlock();
				return;
			}

			item->initializePosition(0,0,0);
			item->setDirection(0,0,1,0); // TODO: Verify oY should be 1 and not oW

			item->setAttributes(attributes);
			item->parseItemAttributes();

			item->setPlayerUseMask(itemMask);
			item->setOptionsBitmask(optionsBitmask);

			item->setCustomizationString(custStr);

			item->setPersistent(true);

			server->addObject(item);

			item->setParent(conti);

			BaseMessage* linkmsg = item->link(conti);
			player->broadcastMessage(linkmsg);

			UpdateTransformMessage* transformMessage = new UpdateTransformMessage(item, 0, 0, 0);
			player->broadcastMessage(transformMessage);

			conti->addObject(item);
		}

		delete contiResult;

		conti->unlock();
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";

		conti->unlock();
	} catch (...) {
		System::out << "unreported exception caught in ItemManagerImplementation::loadItemsInContainersForStructure(Player* player, Container* conti)\n";

		conti->unlock();
	}
}
