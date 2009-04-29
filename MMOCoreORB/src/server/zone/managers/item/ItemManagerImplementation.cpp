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
		query << "select * from `character_items` where `character_id` = " << player->getCharacterID()
		<< " and `deleted` = 0 and in_bank = 0 order by container asc";

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

void ItemManagerImplementation::loadBankItems(Player* player) {
	if (player->getBankContainer() == NULL)
		return;

	Container* bankContainer = player->getBankContainer();

	if (bankContainer == NULL)
		return;

	bankContainer->sendTo(player);

	try {
		StringBuffer query;

		query << "select * from `character_items` where in_bank = 1 and deleted = 0 "
		<< "and character_id = " << player->getCharacterID() << " and deleted = 0 order by container asc";
		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		while (res->next()) {
			TangibleObject* tano = createPlayerObject(player, res);

			if (tano != NULL)
				tano->sendTo(player);
		}

		delete res;

		bankContainer->openTo(player);

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	} catch (...) {
		System::out << "unreported exception caught in ItemManagerImplementation::loadBankItems(Player* player)\n";
	}
}

TangibleObject* ItemManagerImplementation::getPlayerItem(Player* player, uint64 objectid) {
	TangibleObject* tano = NULL;
	SceneObject* item = NULL;

	if (player != NULL) {
		item = player->getPlayerItem(objectid);
		if((item != NULL) && (item->isTangible()))
				return (TangibleObject*) item;
	}

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

TangibleObject* ItemManagerImplementation::createPlayerObjectTemplate(Player* player, int objecttype, uint64 objectid,
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
		case TangibleObjectImplementation::THROWNWEAPON:
			item = new GrenadeThrowableWeapon(objectid, objectcrc, objectname, objecttemp, equipped);
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

	} else if (objecttype & TangibleObjectImplementation::MISC && objecttype != TangibleObjectImplementation::TRAP) {
		switch (objecttype) {

		case TangibleObjectImplementation::CONTAINER :
		case TangibleObjectImplementation::CONTAINER2 :
		case TangibleObjectImplementation::WEARABLECONTAINER :
			item = new Container(objectid);
			item->setObjectCRC(objectcrc);
			item->setCustomName(objectname);
			item->setObjectSubType(objecttype);
			item->setStfName(objecttemp);
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
				Attachment* attachmemt = (Attachment*)item;

			}
			break;

		case TangibleObjectImplementation::ARMORATTACHMENT:
			item = new Attachment(objectid, AttachmentImplementation::ARMOR);
			if (makeStats) {
				Attachment* attachmemt = (Attachment*)item;

			}
			break;

		case TangibleObjectImplementation::CRAFTINGSTATION:
			item = new CraftingStation(objectid, objectcrc, objectname, objecttemp);
			if (makeStats) {
				item->setAttributes(lootAttributes );
				item->parseItemAttributes();
			}
			break;

		case TangibleObjectImplementation::FOOD:
			item = new Food(objectid, objectcrc, objectname, objecttemp);
			if(makeStats) {
				item->setAttributes(lootAttributes);
				item->parseItemAttributes();
			}
			break;

		case TangibleObjectImplementation::DRINK:
			item = new Drink(objectid, objectcrc, objectname, objecttemp);
			if(makeStats) {
				item->setAttributes(lootAttributes);
				item->parseItemAttributes();
			}
			break;

		case TangibleObjectImplementation::FACTORYCRATE:
			item = new FactoryCrate(objectid, objectcrc, objectname, objecttemp);
			if(makeStats) {
				item->setAttributes(lootAttributes);
				item->parseItemAttributes();
			}
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
			item = new RepairTool(objectid, objectcrc, objectname, objecttemp);
			if (makeStats) {
				item->setAttributes(lootAttributes );
				item->parseItemAttributes();
			}
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
		switch (objecttype) {
		case TangibleObjectImplementation::ARMORCOMPONENT:
			item = new ArmorComponent(objectid, objectcrc, objectname, objecttemp);
			break;
		default:
			item = new Component(objectid, objectcrc, objectname, objecttemp);
			break;
		}
		if (makeStats) {
			item->setAttributes(lootAttributes);
			item->parseItemAttributes();
		}
	}  else if (objecttype & TangibleObjectImplementation::DEED) {
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
	} else if (objecttype & TangibleObjectImplementation::VEHICLE){
		if (player != NULL) {
			item = new MountCreature(player,objectid, objectcrc, objectname, objecttemp);
			MountCreature* mount = (MountCreature*) item;

			item->setZoneProcessServer(player->getZoneProcessServer());
			if (makeStats && item != NULL) {
				item->setAttributes(lootAttributes);
				item->parseItemAttributes();
			}
		}
	}
	//System::out << "on: " << objectname.toString() << " = " << objecttype << "\n";
	/*else {
		item = new TangibleObjectImplementation(objectid, objectname, objecttemp, objectcrc, equipped);
	} */

	return item;
}

TangibleObject* ItemManagerImplementation::createSubObject(uint64 objectid, uint32 objectcrc,
		const UnicodeString& objectname, const String& objecttemp, bool equipped) {
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
	case 0x7DB8D61:
	case 0xDCCC25F6:
	case 0x95C1427B:
	case 0x8194445E:
	case 0x5A83ECC9:
	case 0x138E8B44:
	case 0xC6F551AE: //fireblanket
		item = new CurePack(objectid, objectcrc, objectname, objecttemp);
		break;
	case 0xF44F43F:
	case 0xD4535CA8:
	case 0x9D5E3B25:
	case 0x66BD1031:
	case 0x2FB077BC:
	case 0x5D62E08E:
	case 0x86754819:
	case 0xCF782F94: //ranged stimpack
		item = new RangedStimPack(objectid, objectcrc, objectname, objecttemp);
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
    case 0xE87446BF:
    case 0x1A0F19FE:
    case 0xF9E2CBB8:
    case 0x15ADE9E5:
    case 0xCEBA4172:
    case 0x87B726FF:
    case 0x7C540DEB:
    case 0x35596A66:
    case 0x47888310:
    case 0x0E85E49D:
    case 0x06618416:
    case 0x50E06D6C:
    case 0x1A8A9B32:
    case 0xFB00F899:
    case 0xA0E061DC:
    	item = new Firework(objectid, objectcrc, objectname, objecttemp);
    	break;
	case 0xEEF26656: //poison start
	case 0x35E5CEC1:
	case 0x7CE8A94C:
	case 0x6B4D106A:
	case 0xB05AB8FD:
	case 0xF957DF70:
	case 0xD649AF2:
	case 0xD6733265:
	case 0x9F7E55E8:
	case 0xC867155A:
	case 0x1370BDCD:
	case 0x5A7DDA40:
	case 0x4DD86366:
	case 0x96CFCBF1:
	case 0xDFC2AC7C:
	case 0x5EE6FF15:
	case 0x85F15782:
	case 0xCCFC300F: //poison end
	case 0x54B7E9D5: //disease start
	case 0x8FA04142:
	case 0xC6AD26CF:
	case 0xE49B8CF4:
	case 0x3F8C2463:
	case 0x768143EE:
	case 0x4A354089:
	case 0x9122E81E:
	case 0xD82F8F93:
	case 0xFBC965A9:
	case 0x20DECD3E:
	case 0x69D3AAB3:
	case 0x6124FAC8:
	case 0xBA33525F:
	case 0xF33E35D2:
	case 0xBE444D92:
	case 0x6553E505:
	case 0x2C5E8288:
	case 0x482239BB:
	case 0x9335912C:
	case 0xDA38F6A1:
	case 0x2F3F071:
	case 0xD9E458E6:
	case 0x90E93F6B:
	case 0xD62265FC:
	case 0xD35CD6B:
	case 0x4438AAE6:
	case 0x99D4FEB7:
	case 0x42C35620:
	case 0xBCE31AD:
	case 0xF22A80EF:
	case 0x293D2878:
	case 0x60304FF5:
	case 0x3302CBB1:
	case 0xE8156326:
	case 0xA11804AB:
	case 0xD1089FE9:
	case 0xA1F377E:
	case 0x431250F3:
	case 0x556264D1:
	case 0x8E75CC46:
	case 0xC778ABCB:
	case 0xF744DB8A:
	case 0x2C53731D:
	case 0x655E1490:
	case 0x93A85C0F:
	case 0x48BFF498:
	case 0x1B29315:
	case 0xAC523DD5:
	case 0x77459542:
	case 0x3E48F2CF:
	case 0x26B21C86:
	case 0xFDA5B411:
	case 0xB4A8D39C: //disease end
    	item = new DotPack(objectid, objectcrc, objectname, objecttemp);
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
	String objecttempname = result->getString(5);
	char* objecttemp = result->getString(6); // template_name

	uint64 container = result->getUnsignedLong(7);

	String appearance = result->getString(11);

	uint16 itemMask = result->getUnsignedInt(12);
	uint32 optionsBitmask = result->getUnsignedInt(13);

	if (itemMask == 0)
		itemMask = TangibleObjectImplementation::ALL;

	BinaryData cust(appearance);

	String custStr;
	cust.decode(custStr);

	bool equipped = result->getBoolean(8);

	if (result->getBoolean(9) != 0) // deleted
		return NULL;

	String attributes = result->getString(10);

	TangibleObject* item = createPlayerObjectTemplate(player, objecttype, objectid, objectcrc,
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

	if (container != 0 && player != NULL) {
		Zone* zone = player->getZone();

		if (zone != NULL) {
			SceneObject* contiSCO = zone->lookupObject(container);

			if (contiSCO == NULL) {
				if (container == player->getObjectID() + 0x004) { //The items is stored in the bank
					Container* conti = player->getBankContainer();
					if (conti != NULL) {
						conti->addObject(item);
						updateItemLink(player, item, conti, true);
					}
				}
			} else if (contiSCO != NULL && contiSCO->isTangible() && ((TangibleObject*)contiSCO)->isContainer()) {
				server->addObject(item);
				contiSCO->addObject(item);
				updateItemLink(player, item, contiSCO, true);
			}
		}
	} else if (player != NULL)
		((CreatureObject*)player)->addInventoryItem(item);

	if(item->isEquipped() && player != NULL)
		player->equipPlayerItem(item, false);

	return item;
}

TangibleObject* ItemManagerImplementation::initializeTangibleForCrafting(Player* player,
		int objecttype, uint64 objectid, uint32 objectcrc, String objectn,
		String objecttemp, bool equipped){

	UnicodeString objectname(objectn);

	TangibleObject* item = NULL;

	item = createPlayerObjectTemplate(player, objecttype, objectid, objectcrc,
			objectname.toString(), objecttemp, equipped, false, "", 0);

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
	TangibleObject* newTempl = createPlayerObjectTemplate(NULL, templ->getObjectSubType(),
			objectid, templ->getObjectCRC(), UnicodeString(templ->getCustomName()),
			(char *) templ->getStfName().toCharArray(), templ->isEquipped(), false, "", 0);

	newTempl->setStfFile(templ->getStfFile());

	newTempl->setAttributes(templ->getAttributes());
	newTempl->parseItemAttributes();

	newTempl->setPlayerUseMask(templ->getPlayerUseMask());
	newTempl->setOptionsBitmask(templ->getOptionsBitmask());
	String customization;
	templ->getCustomizationString(customization);
	newTempl->setCustomizationString(customization);

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
	setGlobalInt("GRENADE", TangibleObjectImplementation::THROWNWEAPON);
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
	setGlobalInt("RANGEDSTIMPACK", PharmaceuticalImplementation::RANGEDSTIMPACK);
	setGlobalInt("POISONDELIVERYUNIT", PharmaceuticalImplementation::POISONDELIVERYUNIT);
	setGlobalInt("DISEASEDELIVERYUNIT", PharmaceuticalImplementation::DISEASEDELIVERYUNIT);


	setGlobalInt("HEALTH", CreatureAttribute::HEALTH);
	setGlobalInt("ACTION", CreatureAttribute::ACTION);
	setGlobalInt("MIND", CreatureAttribute::MIND);
	setGlobalInt("CONSTITUTION", CreatureAttribute::CONSTITUTION);
	setGlobalInt("STRENGTH", CreatureAttribute::STRENGTH);
	setGlobalInt("QUICKNESS", CreatureAttribute::QUICKNESS);
	setGlobalInt("STAMINA", CreatureAttribute::STAMINA);
	setGlobalInt("FOCUS", CreatureAttribute::FOCUS);
	setGlobalInt("WILLPOWER", CreatureAttribute::WILLPOWER);
	setGlobalInt("POISONRESISTANCE", BuffAttribute::POISON);
	setGlobalInt("DISEASERESISTANCE", BuffAttribute::DISEASE);

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

	TangibleObject* item = createPlayerObjectTemplate(NULL, type, 1, crc, UnicodeString(name), templ, equipped, false, "", 0);

	item->setObjectSubType(type);
	item->setPlayerUseMask(itemMask);
	item->setOptionsBitmask(optionsBitmask);
	item->setSlicable(slicable);

	//ADD ATTRIBUTES
	if (type & TangibleObjectImplementation::ARMOR) {
		int armorPiece = itemconfig.getIntField("armorType");
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

		((Armor*) item)->setArmorPiece(armorPiece);
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
		float area = itemconfig.getFloatField("area");

		Weapon* weapon = (Weapon*) item;
		weapon->setDamageType(damageType);
		weapon->setArmorPiercing(ap);
		weapon->setAttackSpeed(as);
		weapon->setMinDamage(mindmg);
		weapon->setMaxDamage(maxdmg);
		weapon->setArea(area);

		if (type & TangibleObjectImplementation::LIGHTSABER) {
			int forceCost = itemconfig.getIntField("forceCost");
			weapon->setForceCost(forceCost);
		}

		if (weapon->isTrap()) {
			int uses =  itemconfig.getIntField("uses");
			String skill = itemconfig.getStringField("skill");

			((TrapThrowableWeapon*) weapon)->setUsesRemaining(uses);
			((TrapThrowableWeapon*) weapon)->setSkill(skill);
		}

		if (weapon->isGrenade()) {
			int uses =  itemconfig.getIntField("uses");

			((GrenadeThrowableWeapon*) weapon)->setUsesRemaining(uses);
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

						//System::out << "surplusMaintenance: " << surplusMaintenance << ", maintainanceRate: "
						//<< maintenanceRate << ", surplusPower: " << surplusPower << ", extractionRate: "
						//<< extractionRate << ", hopperSize: " << hopperSize << endl;


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
			float area = itemconfig.getFloatField("area");
			uint64 condition = itemconfig.getLongField("conditionCured");

			CurePack* curepack = (CurePack*) item;
			curepack->setEffectiveness(eff);
			curepack->setState(condition);
			curepack->setArea(area);

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
		case PharmaceuticalImplementation::RANGEDSTIMPACK:
		{
			float eff = itemconfig.getFloatField("effectiveness");
			float range = itemconfig.getFloatField("range");
			float area = itemconfig.getFloatField("area");

			RangedStimPack* stim = (RangedStimPack*) item;
			stim->setEffectiveness(eff);
			stim->setRange(range);
			stim->setArea(area);

			break;
		}
		case PharmaceuticalImplementation::POISONDELIVERYUNIT:
		{
			float eff = itemconfig.getFloatField("effectiveness");
			float range = itemconfig.getFloatField("range");
			float area = itemconfig.getFloatField("area");
			float potency = itemconfig.getFloatField("potency");

			DotPack* dot = (DotPack*) item;
			dot->setEffectiveness(eff);
			dot->setRange(range);
			dot->setArea(area);
			dot->setPotency(potency);
			break;
		}
		case PharmaceuticalImplementation::DISEASEDELIVERYUNIT:
		{
			float eff = itemconfig.getFloatField("effectiveness");
			float range = itemconfig.getFloatField("range");
			float area = itemconfig.getFloatField("area");
			float potency = itemconfig.getFloatField("potency");

			DotPack* dot = (DotPack*) item;
			dot->setEffectiveness(eff);
			dot->setRange(range);
			dot->setArea(area);
			dot->setPotency(potency);
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
		container->setContainerVolumeLimit(attributeSlots);
	} else if (type == TangibleObjectImplementation::CAMOKIT) {
		CamoKit* camoKit = (CamoKit*) item;
		//int planet = itemconfig.getIntField("planetType");
		int uses = itemconfig.getIntField("uses");
		//int cMin = itemconfig.getIntField("concealSkill");
		//camoKit->setPlanet(planet);
		camoKit->setUsesRemaining(uses);
		//camoKit->setConcealMin(cMin);
	} else if (type == TangibleObjectImplementation::CAMPKIT) {
				CampKit* campKit = (CampKit*) item;
				int campCRC = itemconfig.getIntField("campType");;
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

void ItemManagerImplementation::giveBFItemSet(Player* player, String& set) {
	Inventory* inventory = player->getInventory();
	Vector<TangibleObject*>* itemSet = bfItemSet->get(set);

	if (inventory->getUnequippedItemCount() + itemSet->size()
			>= InventoryImplementation::MAXUNEQUIPPEDCOUNT) {

		player->sendSystemMessage("@error_message:inv_full");
		return;
	}

	for (int i = 0; i < itemSet->size(); i++) {
		TangibleObject* item = clonePlayerObjectTemplate(player->getNewItemID(), itemSet->get(i));
		if (item == NULL) {
			System::out << "ItemManagerImplementation::giveBFItemSet(...), item == NULL!, set = " << set << endl;
		} else {
			server->addObject(item);
            player->addInventoryItem(item);

            item->sendTo(player);
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
		server->addObject(obj);
		player->addInventoryItem(obj);
	}

	//Make profession items for that apply to all species
	items = startingItems->getProfessionItems(prof, all, sex);
	for (int j = 0; j < items->size(); ++j) {
		TangibleObject* obj = clonePlayerObjectTemplate(player->getNewItemID(), items->get(j));

		server->addObject(obj);
		player->addInventoryItem(obj);
	}

	//Make general items for species
	items = startingItems->getProfessionItems(gen, species, sex);
	for (int j = 0; j < items->size(); ++j) {
		TangibleObject* obj = clonePlayerObjectTemplate(player->getNewItemID(), items->get(j));
		server->addObject(obj);
		player->addInventoryItem(obj);
	}

	//Make general items that apple to all species
	items = startingItems->getProfessionItems(gen, all, sex);
	for (int j = 0; j < items->size(); ++j) {
		TangibleObject* obj = clonePlayerObjectTemplate(player->getNewItemID(), items->get(j));
		server->addObject(obj);
		player->addInventoryItem(obj);
	}
}

void ItemManagerImplementation::loadPlayerDatapadItems(Player* player) {
	try {
		StringBuffer query;

		query << "SELECT * FROM datapad where character_id = " << player->getCharacterID() << " AND deleted = 0;";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		while (res->next()) {
			loadDatapadItem(player, res);
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

void ItemManagerImplementation::loadDatapadItem(Player* player, ResultSet* result) {
	SceneObject* item = NULL;

	uint64 objectid = result->getUnsignedLong(0);

	uint64 objecttype = result->getUnsignedLong(2);

	String name = result->getString(3);

	String stringFile = result->getString(4);
	String stringName = result->getString(5);

	uint32 objectcrc = result->getUnsignedInt(6);

	String attributes = result->getString(7);

	String appearance = result->getString(8);

	uint64 tanoID = result->getUnsignedLong(9);

	BinaryData cust(appearance);
	String custStr;
	cust.decode(custStr);

	SceneObject* scno = loadDatapadLinkedItem(player, tanoID);

	if (objecttype == SceneObjectImplementation::MANUFACTURESCHEMATIC) {
		item = new ManufactureSchematic(objectid, name, stringFile, stringName, objectcrc);

		if(scno != NULL && scno->isTangible()) {
			((ManufactureSchematic*)item)->setTangibleObject(((TangibleObject*)scno));
		}

	} else if (objecttype == SceneObjectImplementation::MISSION) {
		//will implement this with more info on missions.

	} else if (objecttype == SceneObjectImplementation::INTANGIBLE) {
		item = new IntangibleObject(objectid, name, stringFile, stringName, objectcrc, player->getDatapad());

		if(scno == NULL || !scno->isNonPlayerCreature())
			return;

		Creature* creo = (Creature*) scno;
		if (creo->isVehicle()) {
			((MountCreature*)scno)->setDatapadItem(item);
			//((MountCreature*)scno)->setLinkedCreature(player);

			((IntangibleObject*)item)->setWorldObject(scno);
		} else {
			((CreaturePet*)scno)->setDatapadItem(item);
			//((CreaturePet*)scno)->setLinkedCreature(player);

			((IntangibleObject*)item)->setWorldObject(scno);
		}
	}

	if (item == NULL)
		return;

	item->setCustomizationString(custStr);

	item->setAttributes(attributes);
	item->parseItemAttributes();

	item->setPersistent(true);
	item->setUpdated(false);

	item->setZoneProcessServer(player->getZoneProcessServer());

	server->addObject(item);

	item->setParent(player->getDatapad());

	player->addDatapadItem(item);
}

SceneObject* ItemManagerImplementation::loadDatapadLinkedItem(Player* player, uint64 oid) {

	StringBuffer query;

	query << "SELECT * FROM datapad_items where item_id = " << oid << ";";

	ResultSet* result = ServerDatabase::instance()->executeQuery(query);

	SceneObject* item = NULL;

	while (result->next()) {

		uint64 objectid = result->getUnsignedLong(0);

		int objecttype = result->getInt(4);
		uint32 objectcrc = result->getUnsignedInt(3);

		String objectname = result->getString(2);
		String objecttempname = result->getString(5);
		char* objecttemp = result->getString(6); // template_name

		uint64 container = result->getUnsignedLong(7);

		String appearance = result->getString(11);

		uint16 itemMask = result->getUnsignedInt(12);
		uint32 optionsBitmask = result->getUnsignedInt(13);

		if (itemMask == 0)
			itemMask = TangibleObjectImplementation::ALL;

		BinaryData cust(appearance);

		String custStr;
		cust.decode(custStr);

		bool equipped = result->getBoolean(8);

		if (result->getBoolean(9) != 0) // deleted
			return NULL;

		String attributes = result->getString(10);

		item = createPlayerObjectTemplate(player, objecttype,
				objectid, objectcrc, UnicodeString(objectname), objecttemp,
				equipped, false, "", 0);

		if(item == NULL) {
			switch(objectcrc) {
			case 0x60250B32:
			case 0xA965DDBA:
			case 0x25D1DAF3:
			case 0x273A9C02:
			case 0x4EC3780C:
			case 0x3F6E7BA7:
			case 0x729517EF:
			case 0x7E1D9C63:
			case 0x4E3534:
			case 0xAF6D9F4F:
			case 0x5FAC5956:
				item = new MountCreature(player, objectid, objectcrc, UnicodeString(objectname), objecttemp);

				break;
			default:
				item = new CreaturePet(player,objectid);
				item->setCustomName(UnicodeString(objectname));
				break;
			}
		}

		if (item == NULL)
			return NULL;

		item->setAttributes(attributes);
		item->parseItemAttributes();

		if (item->isTangible()) {
			((TangibleObject*)item)->setObjectSubType(objecttype);

			((TangibleObject*)item)->setPlayerUseMask(itemMask);

			((TangibleObject*)item)->setOptionsBitmask(optionsBitmask);
		}

		item->setCustomizationString(custStr);

		item->setPersistent(true);
		item->setUpdated(false);

		server->addObject(item);
	}
	return item;
}

void ItemManagerImplementation::unloadPlayerItems(Player* player) {
	Inventory* inventory = player->getInventory();

	for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
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

void ItemManagerImplementation::unloadDatapadItems(Player* player) {

	Datapad* datapad = player->getDatapad();

	for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {

		SceneObject* item = datapad->getObject(i);

		if (item != NULL) {

			if (!item->isPersistent()) {
				createDatapadItem(player, item);
				if (item->isIntangible()) {
					IntangibleObject* itno = (IntangibleObject*)item;
					SceneObject* worldObject = itno->getWorldObject();
					if (worldObject != NULL)
						createDatapadLinkedItem(player, worldObject);
				}
			} else if (item->isUpdated()) {
				saveDatapadItem(player, item);
				if (item->isIntangible()) {
					IntangibleObject* itno = (IntangibleObject*)item;
					SceneObject* worldObject = itno->getWorldObject();
					if (worldObject != NULL)
						saveDatapadLinkedItem(player, worldObject);
				}
			}
		}
	}
}

void ItemManagerImplementation::createDatapadItem(Player* player, SceneObject* item) {

	try {
		String itemname = item->getCustomName().toString();
		MySqlDatabase::escapeString(itemname);

		String appearance;
		String itemApp;
		item->getCustomizationString(itemApp);
		BinaryData cust(itemApp);
		cust.encode(appearance);

		String attr = item->getAttributes();
		MySqlDatabase::escapeString(attr);

		SceneObject* scno = (SceneObject*) item->getObject(0);
		uint64 worldID;
		if(scno == NULL)
			worldID = 0;
		else
			worldID = scno->getObjectID();

		StringBuffer query;

		query << "REPLACE DELAYED INTO `datapad` "
		<< "(`object_id`,`character_id`,`object_type`,`custom_name`,`stringFile`,`stringName`,`object_crc`,`attributes`,`appearance`, `linked_tano_id`)"
		<< " VALUES(" << item->getObjectID() << "," << player->getCharacterID()
		<< "," << item->getObjectType() << ",'" << itemname << "','"
	    << item->getStfName() << "','"<< item->getStfFile() << "',"<< item->getObjectCRC() << ",'"
		<< attr << "','" << appearance.subString(0, appearance.length() - 1) << "', " << worldID <<")";

		ServerDatabase::instance()->executeStatement(query);

		item->setPersistent(true);
		item->setUpdated(false);

		if(scno != NULL) {
			createDatapadLinkedItem(player, scno);
		}
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	} catch (...) {
		System::out << "unreported exception caught in ItemManagerImplementation::createDatapadItem(Player* player, TangibleObject* item)\n";
	}
}

void ItemManagerImplementation::createDatapadLinkedItem(Player* player, SceneObject* item) {
	try {
		String itemname = item->getCustomName().toString();
		MySqlDatabase::escapeString(itemname);

		String appearance;
		String itemApp;
		item->getCustomizationString(itemApp);
		BinaryData cust(itemApp);
		cust.encode(appearance);

		String attr = item->getAttributes();
		MySqlDatabase::escapeString(attr);

		StringBuffer query;

		if(item->isTangible()) {
			TangibleObject* tano = (TangibleObject*) item;

			query << "REPLACE DELAYED INTO `datapad_items` "
			<< "(`item_id`,`character_id`,`name`,`template_crc`,`template_type`,`template_type_name`,`template_name`,`equipped`,`deleted`,`attributes`,`appearance`, `itemMask`, `optionsBitmask`)"
			<< " VALUES(" << tano->getObjectID() << "," << player->getCharacterID()
			<< ",'" << itemname << "',"
			<< tano->getObjectCRC() << "," << tano->getObjectSubType() << ",'" << tano->getStfFile() << "','"<< tano->getStfName() << "',"
			<< tano->isEquipped() << ",0,'" << attr
			<< "','" << appearance.subString(0, appearance.length() - 1) << "', " << tano->getPlayerUseMask() << ", " << tano->getOptionsBitmask() << ")";

		} else {
			query << "REPLACE DELAYED INTO `datapad_items` "
			<< "(`item_id`,`character_id`,`name`,`template_crc`,`template_type`,`template_type_name`,`template_name`,`equipped`,`deleted`,`attributes`,`appearance`)"
			<< " VALUES(" << item->getObjectID() << "," << player->getCharacterID()
			<< ",'" << itemname << "',"
			<< item->getObjectCRC() << "," << item->getObjectType() << ",'" << item->getStfFile() << "','"<< item->getStfName() << "',"
			<< false << ",0,'" << attr
			<< "','" << appearance.subString(0, appearance.length() - 1) << "')";
		}

		ServerDatabase::instance()->executeStatement(query);

		item->setPersistent(true);

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	} catch (...) {
		System::out << "unreported exception caught in ItemManagerImplementation::createDatapadTangibleItem(Player* player, TangibleObject* item)\n";
	}
}

void ItemManagerImplementation::createPlayerItem(Player* player, TangibleObject* item) {
	try {
		String itemname = item->getCustomName().toString();
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
		<< "(`item_id`,`character_id`,`name`,`template_crc`,`template_type`,`template_type_name`,`template_name`,`equipped`,`deleted`,`attributes`,`appearance`, `itemMask`, `optionsBitmask`)"
		<< " VALUES(" << item->getObjectID() << "," << player->getCharacterID()
		<< ",'" << itemname << "',"
		<< item->getObjectCRC() << "," << item->getObjectSubType() << ",'" << item->getStfFile() << "','"<< item->getStfName() << "',"
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

		StringBuffer query;

		query << "UPDATE `character_items` set equipped = " << item->isEquipped();
		query << ", character_id = " << player->getCharacterID() << " ";
		query << ", attributes = '" << attr << "' ";
		query << ", appearance = '" << appearance.subString(0, appearance.length() - 1) << "' ";
		query << ", itemMask = " << item->getPlayerUseMask() << " ";
		query << ", optionsBitmask = " << item->getOptionsBitmask() << " ";
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
		query << "update `character_items` set deleted = 1, container = 0 where item_id = " << item->getObjectID();

		ServerDatabase::instance()->executeStatement(query);

		if (notify) {
			StringBuffer playertxt;
			playertxt << "You have destroyed " << item->getCustomName().toString() << ".";
			player->sendSystemMessage(playertxt.toString());
		}

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	}
}

void ItemManagerImplementation::saveDatapadItem(Player* player, SceneObject* item) {
	try {
		/*String appearance = " ";//i think there is supposed to be a space here. dont remove it!
		String itemApp = "";
		String attr = "";

		SceneObject* scno = item->getObject(0);
		if(scno != NULL){
			if(scno->isTangible() || scno->isNonPlayerCreature()){
				TangibleObject* tano = (TangibleObject*) scno;

				tano->getCustomizationString(itemApp);
				BinaryData cust(itemApp);
				cust.encode(appearance);

				attr = tano->getAttributes();
			}
		}

		MySqlDatabase::escapeString(attr); */

		StringBuffer query;

		query << "UPDATE `datapad` set character_id = " << player->getCharacterID() << " ";
		query << ", attributes = '" << item->getAttributes() << "' ";
		query << ", custom_name = '" << item->getCustomName().toString() << "' ";
		query << "where object_id = " << item->getObjectID();

		//System::out << "query : " << query.toString() << "\n";

		ServerDatabase::instance()->executeStatement(query);

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	} catch (...) {
		System::out << "unreported exception caught in ItemManagerImplementation::savePlayerDatapadItem(Player* player, IntangibleObject* item)\n";
	}
}

void ItemManagerImplementation::saveDatapadLinkedItem(Player* player, SceneObject* item) {
	try {

		StringBuffer query;

		query << "UPDATE `datapad_items` set attributes = '" << item->getAttributes() << "' ";
		query << ", name = '" << item->getCustomName().toString() << "' ";
		query << "where item_id = " << item->getObjectID();

		//System::out << "query : " << query.toString() << "\n";

		ServerDatabase::instance()->executeStatement(query);

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	} catch (...) {
		System::out << "unreported exception caught in ItemManagerImplementation::savePlayerDatapadLinkedItem(Player* player, IntangibleObject* item)\n";
	}
}
void ItemManagerImplementation::deleteDatapadItem(Player* player, SceneObject* item, bool notify) {
	try {

		uint64 tanoId = item->getObject(0)->getObjectID();

		StringBuffer query;
		query << "update `datapad_items` set deleted = 1 where item_id = " << tanoId;
		ServerDatabase::instance()->executeStatement(query);

		query.removeAll();
		query << "update `datapad` set deleted = 1 where object_id = " << item->getObjectID();
		ServerDatabase::instance()->executeStatement(query);

		StringBuffer playertxt;
		if (notify)
			playertxt << "You have destroyed " << item->getCustomName().toString() << ".";

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

		query.removeAll();

		query << "DELETE FROM datapad_items "
		<< "LEFT JOIN datapad "
		<< "ON (cdatapad_items.item_id = datapad.object_id) "
		<< "WHERE datapad.deleted=1;";

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
           server->addObject(item);
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
		   server->addObject(item);
           player->addInventoryItem(item);
		   item->sendTo(player);

		   //Give additional identical items.
		   for (int i = 0; i < count - 1; i++) {
		       objectID = player->getNewItemID();
		       item = clonePlayerObjectTemplate(objectID, item);

		       server->addObject(item);
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
	    	if (value != DraftSchematicValuesImplementation::VALUENOTFOUND) {

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
	    	if (value != DraftSchematicValuesImplementation::VALUENOTFOUND) {
	    	    value += System::random((int)value * 3);
	    	   	component->changeAttributeValue(property, value);
	    	}
    }

   return item;
}

void ItemManagerImplementation::transferContainerItem(Player* player, TangibleObject* item, uint64 destinationID) {
	//pre: Item null checked, called from OBJC

	if (!item->getPickupFlag())
		return;

	SceneObject* parentSCO;
	ManagedReference<SceneObject> destination = NULL;
	TangibleObject* destinationTano;

	try {
		item->wlock(player);

		//is the operation exceeding storage space?
		if (!checkDestinationSpace(player, item, destinationID)) {
			item->unlock();
			return;
		}

		//Remove the item from its source object
		if (!removeItemFromSource(player, item)) {
			player->sendSystemMessage("@container_error_message:container01");//Container Transfer unsuccessful

			item->unlock();
			return;
		}

		//Determine the target object we move the item to
		destination = getTargetObject(player, destinationID);
		if (destination == NULL) {
			player->sendSystemMessage("@container_error_message:container01");//Container Transfer unsuccessful

			item->unlock();
			return;
		}

		TangibleObject* destinationTano = (TangibleObject*) destination.get();

		//Operation allowed?
		if (!checkProhibitedNesting(player, destinationTano, item)) {
			player->sendSystemMessage("@container_error_message:container12"); //This item is too bulky to fit inside this container.

			item->unlock();
			return;
		}

		//All fine, move the item finally
		if (!moveItemToDestination(player, item, destination)) {
			player->sendSystemMessage("@container_error_message:container01");//Container Transfer unsuccessful

			item->unlock();
			return;
		}

		//Reflect the operation in the database
		reflectItemMovementInDB(player, item, destination);

		item->unlock();

	} catch (...) {
		item->unlock();
		System::out << "Unreported exception caught in ItemManagerImplementation::transferContainerItem(Player* player, TangibleObject* item, uint64 destinationID)\n";
	}
}

void ItemManagerImplementation::deleteItemFromPlayerStorageDB(TangibleObject* item) {
	//Item cant be NULL here, checked in call already
	try {
		item->wlock();

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

void ItemManagerImplementation::moveNestedItemsToPlayerStorage(Player* player, Container* contain) {
	TangibleObject* item;

	try {
		contain->wlock();

		StringBuffer query;

		query << "START TRANSACTION";
		ServerDatabase::instance()->executeStatement(query);

		for (int i = 0; i < contain->getContainerObjectsSize(); ++i) {
			item = (TangibleObject*) contain->getObject(i);
			try {
				item->wlock(contain);

				query.deleteAll();

				query << "UPDATE character_items"
				<< " set deleted = 1, container = " << contain->getObjectID()
				<< " WHERE item_id = " << item->getObjectID() << ";";

				ServerDatabase::instance()->executeStatement(query);

				uint64 containerID = 0;

				containerID = contain->getObjectID();

				String itemname = item->getCustomName().toString();
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
				<< item->getObjectCRC() << "," << item->getObjectSubType() << ",'" << item->getStfName() << "',"
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

		contain->unlock();
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		contain->unlock();

	} catch (...) {
		System::out << "unreported exception caught in moveNestedItemsToPlayerStorage(Player* player, TangibleObject* item)\n";
		contain->unlock();
	}
}

void ItemManagerImplementation::moveNestedItemsToInventoryContainer(Player* player, Container* contain) {
	TangibleObject* item;

	int inBank = 0;
	if (contain->getParent() != NULL && contain->getParent()->getObjectID() == player->getObjectID() + 0x004)
		inBank = 1;

	try {
		contain->wlock();

		StringBuffer query;
		StringBuffer query2;

		query << "START TRANSACTION";
		ServerDatabase::instance()->executeStatement(query);

		for (int i = 0; i < contain->getContainerObjectsSize(); ++i) {
			item = (TangibleObject*) contain->getObject(i);
			if (item != NULL) {
				try {
					item->wlock(contain);

					query.deleteAll();
					query << "UPDATE character_items"
					<< " set character_id = " << player->getCharacterID() << ", deleted = 0, in_bank = " << inBank
					<< ", container = " << contain->getObjectID()
					<< " WHERE item_id = " << item->getObjectID() << ";";
					ServerDatabase::instance()->executeStatement(query);

					query2.deleteAll();
					query2 << "DELETE from player_storage WHERE item_id = " << item->getObjectID() << ";";
					ServerDatabase::instance()->executeStatement(query2);

					item->unlock();
				} catch (...) {
					item->unlock();
				}
			}
		}

		query.deleteAll();
		query << "COMMIT";
		ServerDatabase::instance()->executeStatement(query);

		contain->unlock();
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		contain->unlock();

	} catch (...) {
		System::out << "unreported exception caught in moveNestedItemsToInventoryContainer(Player* player, TangibleObject* item)\n";
		contain->unlock();
	}
}

void ItemManagerImplementation::insertItemIntoPlayerStorage(Player* player, TangibleObject* item) {
	SceneObject* itemParent;

	try {
		uint64 structureID = 0;
		uint64 containerID = 0;
		uint64 parentID = 0;

		if (item->getParent() == NULL)
			return;

		itemParent = item->getParent();

		itemParent->wlock();

		if (itemParent->isCell()) {
			structureID = itemParent->getParentID();
			parentID = itemParent->getObjectID();
		}

		if (((TangibleObject*) itemParent)->isContainer()) {
			if (itemParent->getParent() == NULL) {
				itemParent->unlock();
				return;
			}

			structureID = 0;
			containerID = itemParent->getObjectID();
			parentID = 0;
		}

		if (itemParent->getParent() != NULL && item->getParentID() == player->getObjectID() + 0x004) {
			structureID = 0;
			containerID = player->getObjectID() + 0x004;
			parentID = 0;
		}

		itemParent->unlock();

		String itemname = item->getCustomName().toString();
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
		<< item->getObjectCRC() << "," << item->getObjectSubType() << ",'" << item->getStfName() << "',"
		<< containerID << "," << parentID << ",'" << appearance.subString(0, appearance.length() - 1)
		<< "','" << attr << "'," << item->getPlayerUseMask() << "," << item->getOptionsBitmask() << ","
		<< x << "," << y << "," << z << "," << oX << "," << oY << "," << oZ << "," << oW << "," << player->getCharacterID() << ")";
		ServerDatabase::instance()->executeStatement(query);

		StringBuffer query2;
		query2 << "UPDATE `character_items` set deleted = 1, container = " << containerID << " where item_id = " << item->getObjectID();
		ServerDatabase::instance()->executeStatement(query2);


		if (item->isContainer()) {
			item->unlock();
			moveNestedItemsToPlayerStorage(player, ((Container*) item));
			item->wlock(player);
		}

	} catch (DatabaseException& e) {
		itemParent->unlock();
		System::out << e.getMessage() << "\n";
	} catch (...) {
		itemParent->unlock();
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

	if (!building->getStorageLoaded())
		loadContainersInStructures(player, building, cellSCO );
}

void ItemManagerImplementation::loadContainersInStructures(Player* player, BuildingObject* building, SceneObject* cell) {
	TangibleObject* item;

	try {
		ResultSet* result = NULL;
		Zone* zone = NULL;

		zone = building->getZone();

		if (zone == NULL || cell == NULL)
			return;

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

			try {
				item = createPlayerObjectTemplate(player, objecttype, objectid, objectcrc,
						UnicodeString(objectname), objecttemp, equipped, false, "", 0);

				if (item == NULL) {
					delete result;
					return;
				}

				item->wlock();

				item->initializePosition(X,Z,Y);
				item->setDirection(oX,oZ,oY,oW);

				item->setAttributes(attributes);
				item->parseItemAttributes();

				item->setParent(cell);

				item->setPlayerUseMask(itemMask);

				item->setOptionsBitmask(optionsBitmask);

				item->setCustomizationString(custStr);

				item->setPersistent(true);

				item->setPickupFlag(true);

				server->addObject(item);

				item->insertToZone(zone);

				item->setZoneProcessServer(pServer);

				updateItemLinkWithParent(player, item, cell, false);

				item->unlock();

				if (item->isContainer())
					loadItemsInContainersForStructure(player, (Container*) item);
			} catch (...) {
				System::out << "unreported exception caught in ItemManagerImplementation::loadContainersInStructures(Player* player, BuildingObject* building)\n";
				item->unlock();
				return;
			}
		}

		building->setStorageLoaded(true);

		delete result;

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	} catch (...) {
		System::out << "unreported exception caught in ItemManagerImplementation::loadContainersInStructures(Player* player, BuildingObject* building)\n";
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

			TangibleObject* item = createPlayerObjectTemplate(player, objecttype, objectid, objectcrc,
					UnicodeString(objectname), objecttemp, equipped, false, "", 0);

			if (item == NULL) {
				delete contiResult;

				conti->unlock();
				return;
			}

			try {
				item->wlock();

				item->initializePosition(0,0,0);
				item->setDirection(0,0,1,0);

				item->setAttributes(attributes);
				item->parseItemAttributes();

				item->setPlayerUseMask(itemMask);
				item->setOptionsBitmask(optionsBitmask);

				item->setCustomizationString(custStr);

				item->setPersistent(true);

				server->addObject(item);

				conti->addObject(item);

				updateItemLinkWithParent(player, item, conti, false);

				item->unlock();
			} catch (...) {
				item->unlock();
			}
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

void ItemManagerImplementation::moveItemToInventoryDB(Player* player, TangibleObject* item) {
	try {
		uint64 containerID = 0;
		uint8 inBank = 0;

		TangibleObject* parent;
		parent = (TangibleObject*) item->getParent();

		if (parent != NULL) {
			if (parent->getObjectID() != player->getObjectID() + 1) { //...goes NOT to inventory - set container value
				containerID = parent->getObjectID();
			}

			if (parent->getObjectID() == player->getObjectID() + 0x004) { //...goes to bank storage
				inBank = 1;
			}

			if (parent->getParent() != NULL) {
				if (parent->getParent()->getObjectID() == player->getObjectID() + 0x004) { //...goes inside a container in the bank
					inBank = 1;
				}
			}
		}

		StringBuffer query;
		query << "UPDATE character_items set character_id = " << player->getCharacterID() << ", deleted = 0, in_bank = "
		<< inBank << ", container = " << containerID << " where item_id = " << item->getObjectID() << ";";
		ServerDatabase::instance()->executeStatement(query);

		StringBuffer query2;
		query2 << "DELETE from player_storage where item_id = " << item->getObjectID() << ";";
		ServerDatabase::instance()->executeStatement(query2);

		if (item->isContainer()) {
			item->unlock();
			moveNestedItemsToInventoryContainer(player, ((Container*) item));
			item->wlock(player);
		}

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	} catch (...) {
		System::out << "unreported exception caught in ItemManagerImplementation::moveItemToInventoryDB(Player* player, TangibleObject* item)\n";
	}
}


void ItemManagerImplementation::publishItemToSurroundingPlayers(Player* player, TangibleObject* item, int meter) {
	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	try {
		zone->lock();

		if (meter < 1)
			meter = 1;

		for (int i = 0; i < player->inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) player->getInRangeObject(i))->_this);

			if (object->isPlayer()) {
				Player* creature = (Player*) object;

				if (player->isInRange(creature, meter)) {
					item->sendTo(creature);
				}
			}
		}

		zone->unlock();
	} catch (...) {
		zone->unlock();
	}
}

void ItemManagerImplementation::closeExternalContainer(TangibleObject* item) {
	//pre: container (item) locked

	Zone* zone;
	BuildingObject* building;

	if (item == NULL || !item->isContainer())
		return;

	if ( ( item->getParent() != NULL && item->getParent()->isCell())
		|| ( (item->getParent() != NULL && item->getParent()->getParent() != NULL && item->getParent()->getParent()->isCell())) ) {

		zone = item->getZone();
		if (zone != NULL) {
			item->removeFromZone();
			zone->getZoneServer()->addObject(item);
		}
	}
}

void ItemManagerImplementation::updateItemLinkWithParent(Player* player, TangibleObject* item, SceneObject* destination, bool singleMode) {
	BaseMessage* linkmsg = item->link(destination);

	if (!singleMode)
		player->broadcastMessage(linkmsg);
	else
		player->sendMessage(linkmsg);

	UpdateTransformWithParentMessage* transformMessage = new UpdateTransformWithParentMessage(item);

	if (!singleMode)
		player->broadcastMessage(transformMessage);
	else
		player->sendMessage(transformMessage);
}

void ItemManagerImplementation::updateItemLink(Player* player, TangibleObject* item, SceneObject* destination, bool singleMode) {
	BaseMessage* linkmsg = item->link(destination);

	if (!singleMode)
		player->broadcastMessage(linkmsg);
	else
		player->sendMessage(linkmsg);

	UpdateTransformMessage* transformMessage = new UpdateTransformMessage(item, 0, 0, 0);

	if (!singleMode)
		player->broadcastMessage(transformMessage);
	else
		player->sendMessage(transformMessage);

}

bool ItemManagerImplementation::checkDestinationSpace(Player* player, TangibleObject* item, uint64 destinationID) {
	//pre: item locked
	SceneObject* destination;

	int amountToMove = 1, volumeLimit = 0, currentAmount = 0;

	if (item->isContainer())
		amountToMove = item->getContainerObjectsWithChildsSize() + 1;

	Zone* zone = player->getZone();
	if (zone == NULL)
		return false;

	try {
		destination = zone->lookupObject(destinationID);

		if (destination == NULL) {
			if (destinationID == player->getInventory()->getObjectID()) {
				destination = player->getInventory();
				currentAmount = ((Inventory*) destination)->getUnequippedItemCount();

			} else if (destinationID == player->getBankContainer()->getObjectID()) {
				destination = player->getBankContainer();
				currentAmount = destination->getContainerObjectsWithChildsSize();

			} else {
				player->sendSystemMessage("@container_error_message:container01");
				return false;
			}
		} else {
			currentAmount = destination->getContainerObjectsWithChildsSize();
		}

		//Check the target object for space:
		volumeLimit = destination->getContainerVolumeLimit();

		if ((currentAmount + amountToMove > volumeLimit) && volumeLimit > 0) { //For now: Safety net, there are still many containerObjects with a containerVolume = -1
			if (destination->isCell())
				player->sendSystemMessage("@container_error_message:container13"); //The house is full
			else
				player->sendSystemMessage("@container_error_message:container03"); //Container/unventory full

			return false;
		}

		//Check topmost parent and its children for space:
		SceneObject* topmost = destination;
		String error = "@container_error_message:container03";

		while (topmost->getParentID() > 0) {
			try {
				if (player != topmost)
					topmost->wlock();

				if (topmost->isPlayerInventory()) {
					Inventory* inventory = player->getInventory();
					currentAmount = inventory->getUnequippedItemCount();
					error = "@error_message:inv_full";
					if (player != topmost)
						topmost->unlock();
					break;
				} else if (topmost->isPlayerBankStorage()) {
					currentAmount = topmost->getContainerObjectsWithChildsSize();
					if (player != topmost)
						topmost->unlock();
					break;
				} else if (topmost->isBuilding()) {
					currentAmount = topmost->getContainerObjectsWithChildsSize();
					if (player != topmost)
						topmost->unlock();
					break;
				} else {
					if (player != topmost)
						topmost->unlock();
				}
			} catch(...) {
				if (player != topmost)
					topmost->unlock();
			}

			//Changing the parent at the END of the loop -not at the beginning- so we also catch the current level (in case its the inventory)
			topmost = topmost->getParent();
		}

		volumeLimit = topmost->getContainerVolumeLimit();

		if ((currentAmount + amountToMove > volumeLimit) && volumeLimit > 0) { //For now: Safety net, there are still many containerObjects with a containerVolume = -1
			player->sendSystemMessage(error);
			return false;
		}

	} catch (...) {
		System::out << "Unreported exception caught in ItemManagerImplementation::checkDestinationSpace\n";
	}

	return true;
}

bool ItemManagerImplementation::checkProhibitedNesting(Player* player, TangibleObject* destinationTano, TangibleObject* item) {
	//pre: item locked
	if (destinationTano->isContainer() && item->isContainer() && !destinationTano->isPlayerBankStorage())
		return false;

	return true;
}

void ItemManagerImplementation::loadFactoryContainerItems(FactoryObject* fact, Container* conti) {
	try {
		conti->wlock();

		uint64 contiID = conti->getObjectID();
		//System::out << "loading factory items\n\n\n\n\n\n";
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

			TangibleObject* item = createPlayerObjectTemplate(NULL, objecttype, objectid, objectcrc,
					UnicodeString(objectname), objecttemp, false, false, "", 0);
			//System::out << "trying to make an item\n\n\n\n";
			if (item == NULL) {
				delete contiResult;

				conti->unlock();
				return;
			}

			try {
				item->wlock();

				item->initializePosition(0,0,0);
				item->setDirection(0,0,1,0);

				item->setAttributes(attributes);
				item->parseItemAttributes();

				item->setPlayerUseMask(itemMask);
				item->setOptionsBitmask(optionsBitmask);

				item->setCustomizationString(custStr);

				item->setPersistent(true);

				server->addObject(item);

				conti->addObject((SceneObject*)item);
				//System::out << conti->getContainerObjectsSize() << "\n";
				//if(sc != NULL)
				//	System::out << "item is NOT null\n";
				//else
				//	System::out << "item is NULL\n";

				BaseMessage* linkmsg = item->link(conti);
				fact->broadcastMessage(linkmsg);

				UpdateTransformMessage* transformMessage = new UpdateTransformMessage(item, 0, 0, 0);
				fact->broadcastMessage(transformMessage);

				item->unlock();
			} catch (...) {
				item->unlock();
			}
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

bool ItemManagerImplementation::removeItemFromSource(Player* player, TangibleObject* item) {
	//pre: item locked

	SceneObject* parentSCO = item->getParent();

	if (item->isContainer())
		closeExternalContainer(item);

	if (parentSCO != NULL) {
		try {
			if (parentSCO != player && !parentSCO->isCell())
				parentSCO->wlock(player);

			if (!parentSCO->isCell()) {
				if (!parentSCO->removeObject(item->getObjectID())) {
					player->sendSystemMessage("@container_error_message:container01"); //Container Transfer unsuccessful

					if (parentSCO != player && !parentSCO->isCell())
						parentSCO->unlock();

					return false;
				}
			} else {
				BuildingObject* parentBuilding = (BuildingObject*) parentSCO->getParent();

				if (parentBuilding != NULL)
					item->removeFromBuilding(parentBuilding);
			}

			if (parentSCO != player && !parentSCO->isCell())
				parentSCO->unlock();

		} catch (...) {
			player->sendSystemMessage("@container_error_message:container01");//Container Transfer unsuccessful

			if (parentSCO != player && !parentSCO->isCell())
				parentSCO->unlock();

			return false;
		}
	}

	return true;
}

SceneObject* ItemManagerImplementation::getTargetObject(Player* player, uint64 destinationID) {
	Zone* zone = player->getZone();
	if (zone == NULL)
		return NULL;

	SceneObject* destination = NULL;

	destination = zone->lookupObject(destinationID);

	if (destination == NULL) {
		if (destinationID == player->getInventory()->getObjectID()) {
			destination = (SceneObject*) player->getInventory();

		} else if (destinationID == player->getBankContainer()->getObjectID()) {
			destination = (SceneObject*) player->getBankContainer();

		} else
			return NULL;
	}

	return destination;
}

void ItemManagerImplementation::reflectItemMovementInDB(Player* player, TangibleObject* item, SceneObject* destination) {
	SceneObject* topmost;
	topmost = destination;

	while (topmost->getParentID() > 0) {
		if (topmost->isPlayerInventory()) {
			moveItemToInventoryDB(player, item); //Nested in inventory
			break;

		} else if (topmost->isPlayerBankStorage()) {
			moveItemToInventoryDB(player, item); //Nested in bank
			break;

		} else if (topmost->isCell()) {
			insertItemIntoPlayerStorage(player, item); //Nested in a cell
			break;
		} else if (topmost->isTangible()) {
			TangibleObject* tano = (TangibleObject*) topmost;
			if(tano->isContainer()) {
				//TODO:get saving working
				//insertItemIntoPlayerStorage(player, item); //In a factory hopper
				break;
			}
		}

		topmost = topmost->getParent();
	}
}

bool ItemManagerImplementation::moveItemToDestination(Player* player, TangibleObject* item, SceneObject* destination) {
	Zone* zone = player->getZone();

	if (zone == NULL)
		return false;

	item->initializePosition(player->getPositionX(), player->getPositionZ()+0.08, player->getPositionY());

	if (destination->isCell()) { //Dropping to a cell object
		item->setParent(destination);
		item->insertToZone(zone);

		publishItemToSurroundingPlayers(player, item, 32);

		updateItemLinkWithParent(player, item, destination, false);

	} else if (((TangibleObject*) destination)->isContainer()) { //destination is a container
		if (!destination->isPlayer())
			destination->wlock(player);

		destination->addObject(item);

		publishItemToSurroundingPlayers(player, item, 32); //make the item known to others if it's an external container
		updateItemLink(player, item, destination, false);

		if (!destination->isPlayer())
			destination->unlock();

	} else 	if (destination->isPlayerInventory()) { //destination is inventory
		Inventory* playerInventory = player->getInventory();

		if (playerInventory != NULL) {
			playerInventory->addObject(item);
			updateItemLink(player, item, destination, false);
		}

	} else 	if (destination->isPlayerBankStorage()) {
		destination->addObject(item);
		updateItemLink(player, item, destination, true);
	}

	item->sendTo(player);

	return true;
}
