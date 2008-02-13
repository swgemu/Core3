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

// this section is what CraftingManagerImplementation.h should have (i think)
#include "engine/engine.h"

#include "../../../db/ServerDatabase.h"

#include "CraftingManager.h"
#include "../../objects/draftschematic/DraftSchematic.h"
#include "../../objects/draftschematic/DraftSchematicImplementation.h"
#include "../../objects/draftschematic/DraftSchematicGroup.h"
#include "../../objects/draftschematic/DraftSchematicGroupImplementation.h"

// End

// this section is what CraftingManagerImplementation.cpp should have (i think)
#include "system/lang.h"

#include "../../objects.h"

#include "../../Zone.h"
#include "../../ZoneServer.h"
#include "../../packets.h"

// End
class ZoneServer;

class CraftingManagerImplementation : public CraftingManagerServant {
	ZoneServer* server;
	
	// Use a groupName to recieve a vector of draftSchematics back
	VectorMap<string, DraftSchematicGroup*> draftSchematicsMap;
	
public:
	CraftingManagerImplementation(ZoneServer* serv) :
		CraftingManagerServant() {
		
		server = serv;
		
		loadDraftSchematicsFromDatabase();
	}
	
	inline void loadDraftSchematicsFromDatabase() {
		
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
					DraftSchematicGroup* dsg = (DraftSchematicGroup*) dsgImp->deploy(groupName);
					dsg->addDraftSchematic(draftSchematic);
					draftSchematicsMap.put(groupName, dsg);
				}
				else
					draftSchematicsMap.get(draftSchematic->getGroupName())->addDraftSchematic(draftSchematic);
		}
		delete result;
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
		DraftSchematic* ds = (DraftSchematic*)dsImpl->deploy(objName);
		
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
		for(int i = 0; i < parsedIngredientTemplateNames.size(); i++) {
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

		// Add experimental properties groups to the draft schematic
		uint32 iterator = 0;
		for(uint32 i = 0; i < parsedNumberExperimentalProperties.size(); i++) {
			for(uint32 j = 0; j < parsedNumberExperimentalProperties.get(i); j++) {
				ds->addExperimentalProperty(i, parsedExperimentalProperties.get(iterator), parsedExperimentalWeights.get(iterator)); 
				iterator++;
			}
		}

		return ds;
	}

	Vector<string> parseStringsFromString(const string& unparsedStrings) {
		
		string parseHelper;
		Vector<string> parsedStrings;
		
		for(int i = 0; i < unparsedStrings.size(); i++) {
			char currentChar = unparsedStrings.at(i); 
			if(currentChar != ' ') {
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
		
		for(int i = 0; i < unparsedInts.size(); i++) {
			char currentChar = unparsedInts.at(i);
			if(currentChar != ' ') {
				if(currentChar == ',') {
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
		
	inline void addDraftSchematicsFromGroupName(Player* player, const string& schematicGroupName) {
		
		if(draftSchematicsMap.contains(schematicGroupName)){
			DraftSchematicGroup* dsg = draftSchematicsMap.get(schematicGroupName);
			if(dsg != NULL) {
				for(int i = 0; i < dsg->getSizeOfDraftSchematicList(); i++) {
					DraftSchematic* ds = dsg->getDraftSchematic(i);
					player->addDraftSchematic(ds);
				}
			}
		}
	}	
	
	inline void subtractDraftSchematicsFromGroupName(Player* player, const string& schematicGroupName) {
				
		if(draftSchematicsMap.contains(schematicGroupName)){
			DraftSchematicGroup* dsg = draftSchematicsMap.get(schematicGroupName);
			if(dsg != NULL) {
				for(int i = 0; i < dsg->getSizeOfDraftSchematicList(); i++) {
					DraftSchematic* ds = dsg->getDraftSchematic(i);
					player->subtractDraftSchematic(ds);
				}
			}
		}
	}	
};
	
#endif /*CRAFTINGMANAGERIMPLEMENTATION_H_*/
