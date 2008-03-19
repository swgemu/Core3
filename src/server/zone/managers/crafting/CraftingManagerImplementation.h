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

#ifndef CRAFTINGMANAGERIMPLEMENTATION_H_
#define CRAFTINGMANAGERIMPLEMENTATION_H_

#include "engine/engine.h"

#include "../../../db/ServerDatabase.h"

#include "../../Zone.h"
#include "../../ZoneServer.h"
#include "../../ZoneProcessServerImplementation.h"

#include "CraftingManager.h"

#include "../../objects/draftschematic/DraftSchematic.h"
#include "../../objects/draftschematic/DraftSchematicImplementation.h"
#include "../../objects/draftschematic/DraftSchematicGroup.h"
#include "../../objects/draftschematic/DraftSchematicGroupImplementation.h"

#include "../../objects.h"

#include "../../packets.h"

#include "events/CreateObjectEvent.h"

class ZoneServer;

class CraftingManagerImplementation : public CraftingManagerServant, public Mutex {
	ZoneServer* server;
	ZoneProcessServerImplementation * processor;
	
	CreateObjectEvent * createObjectEvent;
	
	// Use a groupName to recieve a vector of draftSchematics back
	VectorMap<string, DraftSchematicGroup*> draftSchematicsMap;
	
public:
	CraftingManagerImplementation(ZoneServer* serv, ZoneProcessServerImplementation* proc) :
		CraftingManagerServant(), Mutex("CraftingManagerMutex") {
		
		server = serv;
		processor = proc;
		
		loadDraftSchematicsFromDatabase();
	}
	
	void loadDraftSchematicsFromDatabase() {
		lock();
		
		ResultSet* result;
			
		stringstream query;
		query << "SELECT * FROM draft_schematics";

		result = ServerDatabase::instance()->executeQuery(query);
		
		while (result->next()) {
			DraftSchematic* draftSchematic = loadDraftSchematic(result);
			
			string groupName = draftSchematic->getGroupName();
			
			if (draftSchematic != NULL)
				if (!draftSchematicsMap.contains(groupName)) {
					DraftSchematicGroupImplementation* dsgImp = new DraftSchematicGroupImplementation();
					DraftSchematicGroup* dsg = (DraftSchematicGroup*) dsgImp->deploy();
					
					dsg->addDraftSchematic(draftSchematic);
					
					draftSchematicsMap.put(groupName, dsg);
				} else
					draftSchematicsMap.get(draftSchematic->getGroupName())->addDraftSchematic(draftSchematic);
		}
		
		delete result;
		
		unlock();
	}
	
	DraftSchematic* loadDraftSchematic(ResultSet* result) {
		//TODO: Use string tokenizer to parse the data from the db
		
		// The objName is the name you want the object to have
		// example: object/draft_schematic/item/shared_item_battery_droid.iff
		// objName could be "A Droid Battery"
		char* objName(result->getString(1));
		
		// The objTemplateCRC is the CRC value of the object using it's .iff file
		// example: object/draft_schematic/item/shared_item_battery_droid.iff
		// objCRC would be 0xD1207EFF
		uint32 objCRC = result->getUnsignedInt(2);
		
		// The groupName will be used as the key to return a list of schematics with that groupName
		// example: "craftArtisanNewbieGroupA" (this is one groupName from Novice Artisan)
		// this groupName will include, CDEF Carbine, CDEF Rifle, Bofa Treat, etc...
		char* groupName = result->getString(3);
		
		// The objID is two of the crc combined to make a uint64
		uint32 schematicID = objCRC;
		
		// The complexity will give a number that will correspond to which level of crafting tools and or
		// crafting stations are required
		uint32 complexity = result->getUnsignedInt(4);
		
		// I have no idea what the schematicSize is used for :D, but it's a part of all draft schematics
		uint32 schematicSize = result->getUnsignedInt(5);
		
		DraftSchematicImplementation* dsImpl = new DraftSchematicImplementation(schematicID, objName, objCRC, groupName,
				complexity, schematicSize);
		
		DraftSchematic* ds = (DraftSchematic*) dsImpl->deploy();
		
		// Parse the Ingredient data of DraftSchematic from DB

		// example: craft_food_ingredients_n, craft_food_ingredients_n, craft_food_ingredients_n
		string unparIngredientTemplateNames = result->getString(6);
		Vector<string> parsedIngredientTemplateNames = parseStringsFromString(unparIngredientTemplateNames);
		
		// example: dried Fruit, crust, additive
		string unparIngredientTitleNames = result->getString(7);
		Vector<string> parsedIngredientTitleNames = parseStringsFromString(unparIngredientTitleNames);
		
		// example: 1 for optional, 0 for mandatory
		string unparOptionalFlags = result->getString(8);
		Vector<uint32> parsedOptionalFlags = parseUnsignedInt32sFromString(unparOptionalFlags);
		
		
		// example: organic, cereal, object/tangible/food/crafted/additive/shared_additive_light.iff
		string unparResourceTypes = result->getString(9);
		Vector<string> parsedResourceTypes = parseStringsFromString(unparResourceTypes);
		
		// example: 3,8,1
		string unparResourceQuantities = result->getString(10);
		Vector<uint32> parsedResourceQuantities = parseUnsignedInt32sFromString(unparResourceQuantities);
		
		// Add resource requirement sets to schematic
		// Each vector just parsed should all have the same .size() so any .size() will work
		// for the amount of times the loop should execute
		for (int i = 0; i < parsedIngredientTemplateNames.size(); i++) {
			ds->addIngredient(parsedIngredientTemplateNames.get(i), parsedIngredientTitleNames.get(i),
					(bool)parsedOptionalFlags.get(i), parsedResourceTypes.get(i), parsedResourceQuantities.get(i));
		}
		
		// Parse Experimental Properties of Draft Schematic from DB
		
		// example: 1, 1, 1, 2, 2, 2, 2
		string unparNumberExperimentalProperties = result->getString(11);
		Vector<uint32> parsedNumberExperimentalProperties = parseUnsignedInt32sFromString(unparNumberExperimentalProperties);

		// example: XX, XX, XX, OQ, PE, FL, OQ, DR, PE, DR, OQ
		string unparExperimentalProperties = result->getString(12);
		Vector<string> parsedExperimentalProperties = parseStringsFromString(unparExperimentalProperties);

		// example: 0, 0, 0, 1, 2, 2, 1, 1, 3, 3, 1
		string unparExperimentalWeights = result->getString(13);
		Vector<uint32> parsedExperimentalWeights = parseUnsignedInt32sFromString(unparExperimentalWeights);

		// example: exp_filling, exp_flavor, exp_nutrition, exp_quantity
		string unparExperimentalGroupTitles = result->getString(14);
		Vector<string> parsedExperimentalGroupTitles = parseStringsFromString(unparExperimentalGroupTitles);

		for(int i = 0; i < parsedExperimentalGroupTitles.size(); i++) {
			ds->addExpPropTitle(parsedExperimentalGroupTitles.get(i));
		}
		
		// Add experimental properties groups to the draft schematic
		uint32 iterator = 0;
		for (uint32 i = 0; i < parsedNumberExperimentalProperties.size(); i++) {
			for (uint32 j = 0; j < parsedNumberExperimentalProperties.get(i); j++) {
				ds->addExperimentalProperty(i, parsedExperimentalProperties.get(iterator), parsedExperimentalWeights.get(iterator)); 
				iterator++;
			}
		}

		// Save schematics tano attributes
		string tanoAttributes = result->getString(15);
		ds->setTanoAttributes(tanoAttributes);
		
		return ds;
	}

	Vector<string> parseStringsFromString(const string& unparsedStrings) {
		string parseHelper;
		Vector<string> parsedStrings;
		
		for (int i = 0; i < unparsedStrings.size(); i++) {
			char currentChar = unparsedStrings.at(i);
			
			if (currentChar != ' ') {
				if(currentChar == ',') {
					parsedStrings.add(parseHelper);
					parseHelper.clear();
				} else {
					parseHelper += currentChar;
				}
			}
		}
		
		// The last template name has to be added because it was not added during the loop
		parsedStrings.add(parseHelper);

		return parsedStrings;
	}
	
	Vector<uint32> parseUnsignedInt32sFromString(const string& unparsedInts) {
		string parseHelper;
		Vector<uint32> parsedInts;
		
		for (int i = 0; i < unparsedInts.size(); i++) {
			char currentChar = unparsedInts.at(i);
			
			if (currentChar != ' ') {
				if (currentChar == ',') {
					uint32 resourceQuantity = (uint32)atoi(parseHelper.c_str());
					parsedInts.add(resourceQuantity);
					parseHelper.clear();
				} else {
					parseHelper += currentChar;
				}
			}
		}
		
		// The last template name has to be added because it was not added during the loop
		uint32 resourceQuantity = (uint32)atoi(parseHelper.c_str());
		parsedInts.add(resourceQuantity);

		return parsedInts;
	}
	
	
	// Crafting Methods
	void prepareCraftingSession(Player* player, CraftingTool * ct, DraftSchematic* ds) {
		
		// link the DS to the crafting tool (the ds gets cloned)
		ct->setDs(ds);
		
		createDraftSchematic(player, ct);

		createTangibleObject(player, ct);

		setupIngredients(player, ct);

	}
	
	void createDraftSchematic(Player* player, CraftingTool * ct) {
		DraftSchematic* ds = ct->getDs();
		
		// Scene Object Create the DraftSchematic
		ds->setObjectID(player->getNewItemID());

		SceneObjectCreateMessage* soCreateMsg = new SceneObjectCreateMessage(ds->getObjectID(), 0x3819C409);
		player->sendMessage(soCreateMsg);
		
		// Update Containment Message
		UpdateContainmentMessage* ucMsg = new UpdateContainmentMessage(ds->getObjectID(), ct->getObjectID(), 4);
		player->sendMessage(ucMsg);

		// MSCO3
		float complexity = ds->getComplexity();
		unicode& uniPlayerName = player->getCharacterName();
		ManufactureSchematicObjectMessage3* msco3 = new ManufactureSchematicObjectMessage3(ds->getObjectID(), 
				complexity, uniPlayerName);
		player->sendMessage(msco3);
		
		// MSCO6
		uint32 schematicCRC = ds->getSchematicCRC();
		ManufactureSchematicObjectMessage6* msco6 = new ManufactureSchematicObjectMessage6(ds->getObjectID(), ds->getSchematicCRC());
		player->sendMessage(msco6);
		
		// MSCO8
		ManufactureSchematicObjectMessage8* msco8 = new ManufactureSchematicObjectMessage8(ds->getObjectID());
		player->sendMessage(msco8);
		
		// MSCO9
		ManufactureSchematicObjectMessage9* msco9 = new ManufactureSchematicObjectMessage9(ds->getObjectID());
		player->sendMessage(msco9);
		
		//Scene Object Close
		SceneObjectCloseMessage* soCloseMsg = new SceneObjectCloseMessage(ds->getObjectID());
		player->sendMessage(soCloseMsg);
		
	}
	
	void createTangibleObject(Player* player, CraftingTool * ct) {			
		
		DraftSchematic* ds = ct->getDs();
		
		// Generates the tangible for crafting
		TangibleObject* tano = generateTangibleObject(player, ds);
		
		// Scene Object Create Message
		SceneObjectCreateMessage* soCreateMsg = new SceneObjectCreateMessage(tano->getObjectID(), tano->getObjectCRC());
		player->sendMessage(soCreateMsg);
		
		// Update Containment Message
		UpdateContainmentMessage* ucMsg = new UpdateContainmentMessage(tano->getObjectID(), ct->getObjectID(), 0);
		player->sendMessage(ucMsg);
	
		// Tano3
		TangibleObjectMessage3* tano3 = new TangibleObjectMessage3(tano);
		player->sendMessage(tano3);
		
		// Scene Object Close
		SceneObjectCloseMessage* soCloseMsg = new SceneObjectCloseMessage(tano->getObjectID());
		player->sendMessage(soCloseMsg);
		
		// Dplay9
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(player->getPlayerObject());
		dplay9->setCraftingState(2);
		ct->setCraftingState(2);
		dplay9->close();
		player->sendMessage(dplay9);
		
		ct->setTano(tano);
		ct->setInsertCount(1);
	}
	
	void setupIngredients(Player* player, CraftingTool * ct) {
		
		DraftSchematic* ds = ct->getDs();
		
		// Object Controller w/ Ingredients
		ObjectControllerMessage* objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x0103);	
		objMsg->insertLong(ct->getObjectID());
		objMsg->insertLong(ds->getObjectID());
		objMsg->insertLong(ct->getTano()->getObjectID());
		objMsg->insertInt(2);		
		objMsg->insertByte(1);		
		ds->helperSendIngredientsToPlayer(objMsg); 
		player->sendMessage(objMsg);
		
		// MSCO7
		ManufactureSchematicObjectMessage7* msco7 = new ManufactureSchematicObjectMessage7(ds->getObjectID(), ds);
		player->sendMessage(msco7);
	}	
	
	
	void addResourceToCraft(Player * player, ResourceContainer * rcno, int slot, int counter){

		CraftingTool * ct = player->getCurrentCraftingTool();
		DraftSchematic * ds = ct->getDs(); 

		ResourceContainerObjectDeltaMessage3* dRcno3 = new ResourceContainerObjectDeltaMessage3(rcno);
		DraftSchematicIngredient* dsi = ds->getIngredient(slot);		
		dRcno3->setQuantity((rcno->getContents() - dsi->getResourceQuantity()));
		dRcno3->close();
		player->sendMessage(dRcno3);
		
		
		ManufactureSchematicObjectDeltaMessage6* dMsco6 = new ManufactureSchematicObjectDeltaMessage6(ds->getObjectID());
		dMsco6->insertToResourceSlot(ct->getInsertCount());//slot + 1);
		dMsco6->close();
		player->sendMessage(dMsco6); 
				
		
		ManufactureSchematicObjectDeltaMessage7* dMsco7 = new ManufactureSchematicObjectDeltaMessage7(ds->getObjectID());
		if(ct->getInsertCount() == 1){
			dMsco7->fullUpdate(ds, ds->getIngredientListSize(), slot, rcno->getObjectID(), dsi->getResourceQuantity());
		}
		else {
			dMsco7->partialUpdate(slot, ds->getIngredientListSize() + ct->getInsertCount(), rcno->getObjectID(), dsi->getResourceQuantity());		
		}
		dMsco7->close();
		player->sendMessage(dMsco7); 
		
		
		//Object Controller 
		ObjectControllerMessage* objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x010C);
		objMsg->insertInt(0x107);
		objMsg->insertInt(0);
		objMsg->insertByte(counter);
		player->sendMessage(objMsg);
		
		ct->increaseInsertCount();
	}
	void nextCraftingStage(Player * player, string test){
		
		CraftingTool * ct = player->getCurrentCraftingTool();
		DraftSchematic * ds = ct->getDs(); 
		
		int counter = atoi(test.c_str());
		
		if(ct->getCraftingState() == 5){
			
			finishStage1(player, counter);
			
		}
		else if(ct->getCraftingState() == 6){
			
			finishStage2(player, counter);
			
		} else {
			
			assembleWithoutExperimenting(player, ct, ds, counter);
			
		}
		
	}
	void createPrototype(Player * player, string test){
		
		CraftingTool * ct = player->getCurrentCraftingTool();
		DraftSchematic * ds = ct->getDs(); 
		
		StringTokenizer tokenizer(test);

		int counter = tokenizer.getIntToken();
		int practice = tokenizer.getIntToken();		

		//Object Controller - Closes Window
		ObjectControllerMessage* objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x010C);
		objMsg->insertInt(0x10A);
		objMsg->insertInt(1);
		objMsg->insertByte(counter); //?!?! 		
		player->sendMessage(objMsg);
		
		//if(practice == 1){
			createObjectInInventory(player, 5);
		//}
		
	}
	void assembleWithoutExperimenting(Player * player, CraftingTool * ct, DraftSchematic * ds, int counter){
		
		ManufactureSchematicObjectDeltaMessage3* dMsco3 = new ManufactureSchematicObjectDeltaMessage3(ds->getObjectID());
		dMsco3->updateCraftedValues(ds);
		dMsco3->close();
		player->sendMessage(dMsco3);
		

		ManufactureSchematicObjectDeltaMessage7* dMsco7 = new ManufactureSchematicObjectDeltaMessage7(ds->getObjectID());
		dMsco7->updateForAssembly();
		dMsco7->close();	
		player->sendMessage(dMsco7); 
		

			
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(player->getPlayerObject());
		dplay9->insertShort(5);
		dplay9->insertInt(0x0B);
		dplay9->setCraftingState(4);
		ct->setCraftingState(4);
		dplay9->close();
		player->sendMessage(dplay9);
		
		
		TangibleObjectMessage3* tano3 = new TangibleObjectMessage3(ct->getTano());
		player->sendMessage(tano3);
		
		
		//Object Controller  
		ObjectControllerMessage* objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x01BE);
		objMsg->insertInt(0x109);
		objMsg->insertInt(1);
		
		objMsg->insertByte(counter); //?!?! 		
		player->sendMessage(objMsg);
	}
	void craftingCustomization(Player * player, string name, int condition){
		
		CraftingTool * ct = player->getCurrentCraftingTool();
		DraftSchematic * ds = ct->getDs(); 	
		
		TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(ct->getTano());
		dtano3->updateName(name);
		dtano3->close();
		player->sendMessage(dtano3);
		
		ManufactureSchematicObjectDeltaMessage3* dMsco3 = new ManufactureSchematicObjectDeltaMessage3(ds->getObjectID());
		dMsco3->updateName(name);
		dMsco3->updateCondition(condition);
		dMsco3->close();
		player->sendMessage(dMsco3);
		
		//Object Controller  
		ObjectControllerMessage* objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x010C);
		objMsg->insertInt(0x15A);
		objMsg->insertInt(0);
		objMsg->insertByte(0);		
		player->sendMessage(objMsg);
		
		ct->setCraftingState(5);
		
	}
	void finishStage1(Player * player, int counter){
		
		CraftingTool* ct = player->getCurrentCraftingTool();
		
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(player->getPlayerObject());
		//dplay9->insertShort(5);
		//dplay9->insertInt(0xFFFFFFFF);
		dplay9->setCraftingState(5);
		dplay9->close();
		player->sendMessage(dplay9);
		
		
		//Object Controller 
		ObjectControllerMessage* objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x01BE);
		objMsg->insertInt(0x109);
		objMsg->insertInt(4);
		objMsg->insertByte(counter); //?!?! 		
		player->sendMessage(objMsg);
		
		ct->setCraftingState(6);
	}
	
	void finishStage2(Player * player, int counter){
		
		CraftingTool* ct = player->getCurrentCraftingTool();
		
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(player->getPlayerObject());
		dplay9->insertShort(5);
		dplay9->insertInt(0xFFFFFFFF);
		dplay9->setCraftingState(0);
		ct->setCraftingState(0);
		dplay9->close();
		player->sendMessage(dplay9);
		
		//Object Controller 
		ObjectControllerMessage* objMsg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x010C);
		objMsg->insertInt(0x10A);
		objMsg->insertInt(1);
		objMsg->insertByte(counter); //?!?! 		
		player->sendMessage(objMsg);
		
	}
	
	void createObjectInInventory(Player * player, int timer){
		
		CraftingTool* ct = player->getCurrentCraftingTool();
		
		createObjectEvent = new CreateObjectEvent(player, ct);
		
		if(processor != NULL){
			processor->addEvent(createObjectEvent, timer);
		}
		else{
			cout << "Serv == NULL\n"; 
		}
	}
	
	TangibleObject * generateTangibleObject(Player * player, DraftSchematic * ds) {

		ItemManager * itemManager = player->getZone()->getZoneServer()->getItemManager();

		string attributes = ds->getTanoAttributes();

		ItemAttributes* itemAttributes = new ItemAttributes();
		itemAttributes->setAttributes(attributes);

		uint64 objectid = player->getNewItemID();

		string temp = "objecttype";
		int objecttype = itemAttributes->getIntAttribute(temp);

		temp = "objectcrc";
		uint32 objectcrc = itemAttributes->getUnsignedLongAttribute(temp);

		unicode objectname = ds->getName();

		temp = "objecttemp";
		string objecttemp = itemAttributes->getStringAttribute(temp);

		//(objectid, objectcrc, objectname, objecttemp, false); 
		// Set these defaults in case
		/*string appearance = result->getString(10);
		 BinaryData cust(appearance);
		 string custStr;
		 cust.decode(custStr);*/

		TangibleObjectImplementation* item = NULL;

		bool equipped = false;

		// Set these defaults in case
		//string attributes = result->getString(9);

		if (objecttype & TangibleObjectImplementation::WEAPON || objecttype
				& TangibleObjectImplementation::LIGHTSABER) {
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
		} else if (objecttype & TangibleObjectImplementation::RESOURCECONTAINER) {

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

		if (item == NULL)
			item = new TangibleObjectImplementation(objectid, objectname, objecttemp, objectcrc);

		//item->setAttributes(attributes);
		//item->parseItemAttributes();

		//item->setCustomizationString(custStr);


		//item->setPersistent(true);

		TangibleObject* tano = (TangibleObject*) item->deploy();

		//player->addInventoryItem(tano);

		return tano;
	}
	
	/*void WriteDraftSchematicToDB(DraftSchematic* ds) {
		try { 
			stringstream query;
			query << "INSERT INTO `draft_schematics` "
				  << "(`object_id`,`name`,`object_crc`, `group_name`)"
				  << " VALUES(" << ds->getObjectID() << ",'\\" << ds->getName().c_str() << "'," 
				  << ds->getObjectCRC() << ",'" << ds->getGroupName() << "'," << ")";
			
			ServerDatabase::instance()->executeStatement(query);
			
			ds->setPersistent(true);
		} catch (DatabaseException& e) {
			cout << e.getMessage() << "\n";
		}	
	}*/
		
	void addDraftSchematicsFromGroupName(Player* player, const string& schematicGroupName) {
		lock();
		
		if (draftSchematicsMap.contains(schematicGroupName)){
			DraftSchematicGroup* dsg = draftSchematicsMap.get(schematicGroupName);
			
			if (dsg != NULL) {
				for (int i = 0; i < dsg->getSizeOfDraftSchematicList(); i++) {
					DraftSchematic* ds = dsg->getDraftSchematic(i);
					player->addDraftSchematic(ds);
				}
			}
		}
		
		unlock();
	}	
	
	void subtractDraftSchematicsFromGroupName(Player* player, const string& schematicGroupName) {
		lock();
		
		if (draftSchematicsMap.contains(schematicGroupName)){
			DraftSchematicGroup* dsg = draftSchematicsMap.get(schematicGroupName);
			
			if (dsg != NULL) {
				for (int i = 0; i < dsg->getSizeOfDraftSchematicList(); i++) {
					DraftSchematic* ds = dsg->getDraftSchematic(i);
					player->subtractDraftSchematic(ds);
				}
			}
		}
		
		unlock();
	}	
};
	
#endif /*CRAFTINGMANAGERIMPLEMENTATION_H_*/
