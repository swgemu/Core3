/*
 *	LootTableManagerImplementationStub
 */
#include "engine/engine.h"

#include "../../ZoneServer.h"
#include "../../ZoneProcessServerImplementation.h"

//#include "events/SpawnResourcesEvent.h"

#include "LootTableManager.h"
#include "LootTableManagerImplementation.h"

#include "../../objects/creature/Creature.h"
//#include "../../objects/tangible/ItemAttributes.h"
//#include "../name/NameManager.h"

//#include "../../objects/tangible/resource/ResourceContainerImplementation.h"
//#include "../../objects/tangible/surveytool/SurveyToolImplementation.h"

#include "../../packets.h"
#include "../../objects.h"


LootTableManagerImplementation::LootTableManagerImplementation(ZoneServer* inserver,
		ZoneProcessServerImplementation* inserv) : LootTableManagerServant(), Mutex("LootTableManager"), Lua() {

	setLoggingName("LootTableManager");

	init();

	serv = inserv;

	setLogging(false);
	setGlobalLogging(true);

}

LootTableManagerImplementation::~LootTableManagerImplementation() {

	if (lootTableMap != NULL) {
		delete lootTableMap;
		lootTableMap = NULL;
	}
	
	if (selectedLootTableMap != NULL) {
		delete selectedLootTableMap;
		selectedLootTableMap = NULL;
	}

}


void LootTableManagerImplementation::init() {
	lootTableMap = new Vector<LootTableTemplate*>();
	selectedLootTableMap = new Vector<LootTableTemplate*>();

	info("Initializing Loot Table Manager");
	buildLootMap();

}

void LootTableManagerImplementation::buildLootMap() {
	LootTableTemplate* lootTableTemp;	
	
	int i = 0;
	ResultSet* lootRes;
		
	try {
		stringstream query;
		query << "SELECT "
				<< "loottable.lootgroup,loottable.name,loottable.template_crc,loottable.template_type,"
				<< "loottable.template_name,loottable.container,loottable.attributes,loottable.appearance,loottable.level,"
				<< "loottable.chance,loottable.lastdropstamp,loottable.dontdropbefore,loottable.`unique`,loottable.notrade,"
				<< "loottable.race,loottable.developernote,object_crc_string_table.`hex`,object_crc_string_table.path, "
				<< "loottable.item_string, HEX(loottable.`template_type`) "
				<< "FROM loottable "
				<< "Inner Join object_crc_string_table ON loottable.template_crc = object_crc_string_table.`decimal` ;";

		lootRes = ServerDatabase::instance()->executeQuery(query);
	
	} catch (...) {
		cout << "Exception in DB query LootTableManagerImplementation::loadLootItems \n";
	}
	
	while (lootRes->next()) {
		i++;
		lootTableTemp = new LootTableTemplate;
		
		lootTableTemp->setLootItemGroup(lootRes->getInt(0));
		lootTableTemp->setLootItemName(lootRes->getString(1));
		lootTableTemp->setLootItemTemplateCRC(lootRes->getUnsignedLong(2));
		lootTableTemp->setLootItemTemplateType(lootRes->getUnsignedLong(3));
		lootTableTemp->setLootItemTemplateName(lootRes->getString(4));
		lootTableTemp->setLootItemAttributes(lootRes->getString(6));
		lootTableTemp->setLootItemAppearance(lootRes->getString(7));
		lootTableTemp->setLootItemLevel(lootRes->getInt(8));
		lootTableTemp->setLootItemChance(lootRes->getInt(9));
		lootTableTemp->setLootItemLastDropStamp(lootRes->getString(10));
		lootTableTemp->setLootItemDontDropBefore(lootRes->getString(11));
		lootTableTemp->setLootItemUnique(lootRes->getInt(12));
		lootTableTemp->setLootItemNoTrade(lootRes->getInt(13));
		lootTableTemp->setLootItemRace(lootRes->getString(14));
		lootTableTemp->setLootItemPath(lootRes->getString(17));
		lootTableTemp->setLootItemString(lootRes->getString(18));
		lootTableTemp->setLootItemTypeHex(lootRes->getString(19));
		lootTableTemp->setLootItemDeveloperNote("");
		
		lootTableMap->add(lootTableTemp);
	}
	delete lootRes;
	
	stringstream msg;
	msg << "Loot table built from database with <" << i << "> loot items.";
	
	info(msg.str());
	
}


void LootTableManagerImplementation::createLootItem(Creature* creature, int level, Player* player) {
	lock();
	
	if (creature == NULL || selectedLootTableMap == NULL) {
		unlock();
		return;
	}
	
	int i, itemcount;
	i = 0;

	uint32 objectCRC = creature->getObjectCRC();
	
	LootTableTemplate* lootTableTemp;
	
	selectedLootTableMap->removeAll();

	for (int i = 0; i < lootTableMap->size(); ++i) {
		lootTableTemp = lootTableMap->get(i);
			
		if (lootTableTemp->getLootItemLevel() <= level) {
			if ( (lootTableTemp->getLootItemGroup() == creature->getLootGroup()) || lootTableTemp->getLootItemGroup() == 0) {
				int compare = lootTableTemp->getLootItemRace().find (player->getSpeciesName());
				
				if (compare >= 0 || lootTableTemp->getLootItemRace() == "all" )
					selectedLootTableMap->add(lootTableTemp);			
			}
		}
	}
	
	
	//How many loot items will spawn
	itemcount = System::random(level / 20) + 1;
	
	if (itemcount > 5 )
		itemcount = 5;
		
	//For testing: itemcount = 100;
	
	//make sure our map is  at least = itemcount
	if (itemcount > selectedLootTableMap->size())
		itemcount = selectedLootTableMap->size();
		
	//Randomized offset for the loot item map to avoid looting the same items all time
	int offset = System::random(selectedLootTableMap->size() - itemcount);
	
	//Make sure we are not pointing behind the last item
	if (offset + itemcount > selectedLootTableMap->size())
		offset = selectedLootTableMap->size() - itemcount;

		
	for (int i = 0; i < itemcount; ++i) {	
		lootTableTemp = selectedLootTableMap->get(i+offset);
		
		TangibleObject* titem = NULL;
		Armor* aitem = NULL;
		Instrument* iitem = NULL;
		StimPack* sitem = NULL;
		EnhancePack* eitem = NULL;
		Ticket* ttitem = NULL;
		Attachment* attachmentItem = NULL;
		Wearable* clothingItem = NULL;		
		Powerup* puItem = NULL;
		Holocron* holoItem = NULL;
		
				
		int itemType = lootTableTemp->getLootItemTemplateType();
		unicode clearName = (unicode)lootTableTemp->getLootItemName();
		uint64 itemCRC = lootTableTemp->getLootItemTemplateCRC();
		string itemName = lootTableTemp->getLootItemTemplateName();
		string lootAttributes = lootTableTemp->getLootItemAttributes();
		string lootTypeHex = lootTableTemp->getLootItemTypeHex();
		string itemPath = lootTableTemp->getLootItemPath();
		string itemString = lootTableTemp->getLootItemString();
		
		//for testing: cout << "Selected lootitem is " << lootTableTemp->getLootItemName() << endl;
		
		switch (itemType) {
			case 805306373 : //Holocron
				holoItem = new Holocron((Player*)creature, itemCRC, clearName, itemName);
				creature->addLootItem(holoItem);			
				break;
			
			case 524288 : //Weapon Powerup
				puItem = new Powerup(creature->getNewItemID());
				puItem->setPowerupStats(level);

				creature->addLootItem(puItem);			
				break;		
		
			case 8201 : //Flora Loot (was on eg. Dantaris, Mooks, Jantas)
				//ToDO: Not in yet
				break;
				
			case 8202 : //Food Loot (was on eg. Dantaris, Mooks, Jantas)
				//ToDO: Not in yet
				break;
				
			case 8203 : //Furniture
				//ToDO: Not in yet
				break;
				
			case 8205 : //Pharmaceutical
				//Pharmaceutical StimPack A
				if ( itemCRC == 0x7751C746) {
					sitem = new StimPack(creature, itemCRC, clearName, itemName);
					sitem->setEffectiveness(System::random(70));	

					sitem->setAttributes(lootAttributes );
					sitem->parseItemAttributes();
				
					creature->addLootItem(sitem);
				}
				break;
			
			case 8210 : //TravelTicket
				//ToDO: Create faked junk loot travel ticket
				break;
			
			case 8211 : //generic item
				titem = new TangibleObject(creature, clearName, itemName, itemCRC, itemType);

				titem->setAttributes(lootAttributes );
				titem->parseItemAttributes();

				creature->addLootItem(titem);
				break;
				
			case 8213 : //Wearable Container (Backpacks etc)
				//not in yet
				break;
			
			case 8216 : //Drinks
				//not in yet
				break;				
			
			case 8221 : //Clothing Attachment
				attachmentItem = new Attachment(creature->getNewItemID(), AttachmentImplementation::CLOTHING);
				attachmentItem->setSkillMods(level / 2);	
				creature->addLootItem(attachmentItem);
				break;				
			
			case 8223 : //Armor Attachment
				attachmentItem = new Attachment(creature->getNewItemID(), AttachmentImplementation::ARMOR);
				attachmentItem->setSkillMods((level+20) / 2);
				creature->addLootItem(attachmentItem);
				break;
				
			//******************************* WEAPONS *****************************
			case 131072 :
			case 131073 :
			case 131074 :
			case 131075 :
			case 131076 :
			case 131077 :
			case 131078 :
			case 131079 :
			case 131080 :
			case 131081 :
			case 131082 :
			case 131083 :
			case 131084 :
				Weapon* witem;
				
				if (itemString == "UnarmedMeleeWeapon")
					witem = new UnarmedMeleeWeapon(creature, itemPath, clearName, itemName, false);
					
				if (itemString == "TwoHandedMeleeWeapon")
					witem = new TwoHandedMeleeWeapon(creature, itemPath, clearName, itemName, false);
					
				if (itemString == "RifleRangedWeapon")
					witem = new RifleRangedWeapon(creature, itemPath, clearName, itemName, false);

				if (itemString == "PistolRangedWeapon")
					witem = new PistolRangedWeapon(creature, itemPath, clearName, itemName, false);
					
				if (itemString == "OneHandedMeleeWeapon")
					witem = new OneHandedMeleeWeapon(creature, itemPath, clearName, itemName, false);

				if (itemString == "HeavyRangedWeapon")
					witem = new HeavyRangedWeapon(creature, itemPath, clearName, itemName, false);

				if (itemString == "CarbineRangedWeapon")
					witem = new CarbineRangedWeapon(creature, itemPath, clearName, itemName, false);
			

				if (witem != NULL) {
					witem->setAttributes(lootAttributes );
					witem->parseItemAttributes();
					witem->setWeaponStats(level);
					
					creature->addLootItem(witem);
				}
				break;

			//Armor
			case 256 :
			case 257 :
			case 258 :
			case 259 :
			case 260 :
			case 261 :
			case 262 :
			case 263 :
			case 264 :
				aitem = new Armor(creature, itemCRC, clearName, itemName, false);
				aitem->setType(itemCRC);
				
				aitem->setAttributes(lootAttributes);
				aitem->parseItemAttributes();
				aitem->setArmorStats(level);		
				
				creature->addLootItem(aitem);
				break;	
				
			default:
				//Clothing
				if (itemString == "Clothing") {
					clothingItem = new Wearable(creature, itemCRC, clearName, itemName, false);

					//Conversion stunt from uint64 to hex int
					stringstream ssHex;
					ssHex << hex << lootTypeHex;
					
					int hexValue;
					ssHex >> hexValue;
					
					clothingItem->setObjectSubType(hexValue);					
					clothingItem->setConditionDamage(System::random(clothingItem->getMaxCondition() * 3 / 4));
					
					creature->addLootItem(clothingItem);
				}
		}
	}
		
	unlock();
}


void LootTableManagerImplementation::stop() {
	lock();

	lootTableMap->removeAll();

	unlock();
}
