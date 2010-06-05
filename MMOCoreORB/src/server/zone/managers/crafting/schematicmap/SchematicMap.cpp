/*
Copyright (C) 2010 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 3 of the License,
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

/**
 * \file SchematicMap.cpp
 * \author Kyle Burkhardt
 * \date 6-01-10
 */

#include "SchematicMap.h"
#include "engine/engine.h"

ObjectManager* SchematicMap::objectManager = NULL;
VectorMap<String, DraftSchematicGroup* > SchematicMap::groupMap;
SchematicMap* SchematicMap::instance = NULL;

SchematicMap::SchematicMap(ObjectManager* objman) {

	objectManager = objman;
	Lua::init();
	registerFunctions();
	instance = this;
	loadDraftSchematicFile();
}

SchematicMap::~SchematicMap() {
	while(instance->groupMap.size() > 0)
		delete instance->groupMap.get(0);
}

void SchematicMap::registerFunctions() {
	//lua_register(getLuaState(), "RunCraftingConfiguration", runCraftingConfiguration);
	lua_register(getLuaState(), "RunDraftSchematicFile", runDraftSchematicFile);
	lua_register(getLuaState(), "AddDraftSchematicToServer", addDraftSchematicToServer);
}

void SchematicMap::loadDraftSchematicFile() {
	runFile("scripts/crafting/main.lua");
}

int SchematicMap::runDraftSchematicFile(lua_State* L) {
	String filename = getStringParameter(L);

	runFile("scripts/crafting/" + filename, L);

	return 0;
}

int SchematicMap::addDraftSchematicToServer(lua_State *L) {
	LuaObject schematic(L);

	String objectName = "";

	if (!schematic.isValidTable())
		return 1;

	try {

		// The objName is the name you want the object to have
		// example: object/draft_schematic/item/shared_item_battery_droid.iff
		// objName could be "A Droid Battery"
		objectName = schematic.getStringField("objectName");

		String stfName = schematic.getStringField("stfName");

		String stfFile = schematic.getStringField("stfFile");

		// The objTemplateCRC is the CRC value of the object using it's .iff file
		// example: object/draft_schematic/item/shared_item_battery_droid.iff
		// objCRC would be 0xD1207EFF
		uint32 objCRC = schematic.getIntField("objectCRC");

		// The groupName will be used as the key to return a list of schematics with that groupName
		// example: "craftArtisanNewbieGroupA" (this is one groupName from Novice Artisan)
		// this groupName will include, CDEF Carbine, CDEF Rifle, Bofa Treat, etc...
		String groupName = schematic.getStringField("groupName");

		ManagedReference<DraftSchematic* > draftSchematic = (DraftSchematic*) objectManager->createObject(objCRC, 0, "DraftSchematics");

		/*
		// The groupName will be used as the key to return a list of schematics with that groupName
		// example: "craftArtisanNewbieGroupA" (this is one groupName from Novice Artisan)
		// this groupName will include, CDEF Carbine, CDEF Rifle, Bofa Treat, etc...
		String groupName = schematic.getStringField("groupName");

		// The number that tells the client which crafting tool tab to put the draftSchematic in
		int craftingToolTab = schematic.getIntField("craftingToolTab");

		// The objID is two of the crc combined to make a uint64
		uint32 schematicID = objCRC;

		// The complexity will give a number that will correspond to which level of crafting tools and or
		// crafting stations are required
		uint32 complexity = schematic.getIntField("complexity");

		// I have no idea what the schematicSize is used for :D, but it's a part of all draft schematics
		uint32 schematicSize = schematic.getIntField("size");

		DraftSchematic* draftSchematic = new DraftSchematic(schematicID,
				objectName, stfFile, stfName, objCRC, groupName, complexity, schematicSize,
				craftingToolTab);

		uint64 temp = (((uint64)schematicID) << 32);
		temp += objCRC;
		draftSchematic->setObjectID(temp);

		String xptype = schematic.getStringField("xpType");
		draftSchematic->setXpType(xptype);

		int xp = schematic.getIntField("xp");
		draftSchematic->setXp(xp);

		String assemblySkill = schematic.getStringField("assemblySkill");
		draftSchematic->setAssemblySkill(assemblySkill);

		String experimentingSkill = schematic.getStringField(
				"experimentingSkill");
		draftSchematic->setExperimentingSkill(experimentingSkill);

		// Parse the Ingredient data of DraftSchematic from LUA
		// example: craft_food_ingredients_n, craft_food_ingredients_n, craft_food_ingredients_n
		String unparIngredientTemplateNames = schematic.getStringField(
				"ingredientTemplateNames");
		Vector<String> parsedIngredientTemplateNames =
				instance->parseStringsFromString(unparIngredientTemplateNames);

		// example: dried Fruit, crust, additive
		String unparIngredientTitleNames = schematic.getStringField(
				"ingredientTitleNames");
		Vector<String> parsedIngredientTitleNames =
				instance->parseStringsFromString(unparIngredientTitleNames);

		// example: 2 for identical, 1 for optional, 0 for mandatory
		String unparOptionalFlags = schematic.getStringField(
				"ingredientSlotType");
		Vector<uint32> parsedOptionalFlags =
				instance->parseUnsignedInt32sFromString(unparOptionalFlags);

		// example: organic, cereal, object/tangible/food/crafted/additive/shared_additive_light.iff
		String unparResourceTypes = schematic.getStringField("resourceTypes");
		Vector<String> parsedResourceTypes = instance->parseStringsFromString(
				unparResourceTypes);

		// example: 3,8,1
		String unparResourceQuantities = schematic.getStringField(
				"resourceQuantities");
		Vector<uint32>
				parsedResourceQuantities =
						instance->parseUnsignedInt32sFromString(
								unparResourceQuantities);

		// example: 1,2,3
		String unparCombineTypes = schematic.getStringField("combineTypes");
		Vector<uint32> parsedCombineTypes =
				instance->parseUnsignedInt32sFromString(unparCombineTypes);

		// example: 1,2,3
		String unparContribution = schematic.getStringField("contribution");
		Vector<uint32> parsedContribution =
				instance->parseUnsignedInt32sFromString(unparContribution);

		// Add resource requirement sets to schematic
		// Each vector just parsed should all have the same .size() so any .size() will work
		// for the amount of times the loop should execute
		for (int i = 0; i < parsedIngredientTemplateNames.size(); i++) {
			draftSchematic->addIngredient(parsedIngredientTemplateNames.get(i),
					parsedIngredientTitleNames.get(i),
					parsedOptionalFlags.get(i), parsedResourceTypes.get(
							i), parsedResourceQuantities.get(i),
					parsedCombineTypes.get(i), parsedContribution.get(i));
		}

		// Parse Experimental Properties of Draft Schematic from DB
		// example: 1, 1, 1, 2, 2, 2, 2
		String unparNumberExperimentalProperties = schematic.getStringField(
				"numberExperimentalProperties");
		Vector<uint32> parsedNumberExperimentalProperties =
				instance->parseUnsignedInt32sFromString(
						unparNumberExperimentalProperties);

		// example: XX, XX, XX, OQ, PE, FL, OQ, DR, PE, DR, OQ
		String unparExperimentalProperties = schematic.getStringField(
				"experimentalProperties");
		Vector<String> parsedExperimentalProperties =
				instance->parseStringsFromString(unparExperimentalProperties);

		// example: 0, 0, 0, 1, 2, 2, 1, 1, 3, 3, 1
		String unparExperimentalWeights = schematic.getStringField(
				"experimentalWeights");
		Vector<uint32> parsedExperimentalWeights =
				instance->parseUnsignedInt32sFromString(
						unparExperimentalWeights);

		// example: exp_filling, exp_flavor, exp_nutrition, exp_quantity
		String unparExperimentalGroupTitles = schematic.getStringField(
				"experimentalGroupTitles");
		Vector<String> parsedExperimentalGroupTitles =
				instance->parseStringsFromString(unparExperimentalGroupTitles);

		String unparExperimentalSubGroupTitles = schematic.getStringField(
				"experimentalSubGroupTitles");
		Vector<String> parsedExperimentalSubGroupTitles =
				instance->parseStringsFromString(
						unparExperimentalSubGroupTitles);

		// Set associated exp property
		String unparExperimentalMinToSet = schematic.getStringField(
				"experimentalMin");
		Vector<float> parsedExperimentalMinToSet =
				instance->parseFloatsFromString(unparExperimentalMinToSet);

		// Set associated exp property
		String unparExperimentalMaxToSet = schematic.getStringField(
				"experimentalMax");
		Vector<float> parsedExperimentalMaxToSet =
				instance->parseFloatsFromString(unparExperimentalMaxToSet);

		// Set associated precision
		String unparExperimentalPrecisionToSet = schematic.getStringField(
				"experimentalPrecision");
		Vector<int> parsedExperimentalPrecisionToSet =
				instance->parseInt32sFromString(unparExperimentalPrecisionToSet);

		// Add experimental properties groups to the draft schematic
		uint32 weightIterator = 0;
		String subtitle = "";
		for (uint32 i = 0; i < parsedNumberExperimentalProperties.size(); i++) {
			for (uint32 j = 0; j < parsedNumberExperimentalProperties.get(i); j++) {

				draftSchematic->addExperimentalProperty(i,
						parsedExperimentalProperties.get(weightIterator),
						parsedExperimentalWeights.get(weightIterator),
						parsedExperimentalGroupTitles.get(i),
						parsedExperimentalSubGroupTitles.get(i),
						parsedExperimentalMinToSet.get(i),
						parsedExperimentalMaxToSet.get(i),
						parsedExperimentalPrecisionToSet.get(i));
				weightIterator++;
			}
		}

		// Save schematics tano attributes
		String tanoAttributes = schematic.getStringField("tanoAttributes");
		draftSchematic->setTanoAttributes(tanoAttributes);

		// Save blue frog attributes
		String blueFrogAttributes = schematic.getStringField("blueFrogAttributes");
		draftSchematic->setBlueFrogAttributes(blueFrogAttributes);

		// Save blue frog status
		bool blueFrogEnabled = schematic.getIntField("blueFrogEnabled");
		draftSchematic->setBlueFrogEnabled(blueFrogEnabled);

		// Set Customization options
		String unparCustomizationOptions = schematic.getStringField(
				"customizationOptions");
		Vector<String> parsedCustomizationOptions =
				instance->parseStringsFromString(unparCustomizationOptions);

		// Set Default Customization values
		String unparCustomizationValues = schematic.getStringField(
				"customizationDefaults");
		Vector<uint32> parsedCustomizationValues =
				instance->parseUnsignedInt32sFromString(unparCustomizationValues);

		for (int i = 0; i < parsedCustomizationOptions.size(); ++i) {
			draftSchematic->addCustomizationOption(parsedCustomizationOptions.get(i),
					parsedCustomizationValues.get(i));
		}

		// Save schematics tano attributes
		String customizationSkill = schematic.getStringField("customizationSkill");
		draftSchematic->setCustomizationSkill(customizationSkill);*/

		mapDraftSchematic(groupName, draftSchematic);

	} catch (...) {

		System::out << "Failed to load " << objectName << endl;

	}

	return 0;
}

void SchematicMap::mapDraftSchematic(String groupname, DraftSchematic* schematic) {

	DraftSchematicGroup* group = groupMap.get(groupname);

	if(group == NULL) {
		group = new DraftSchematicGroup();
		groupMap.put(groupname, group);
	}

	group->add(schematic);
	instance->put(schematic->getClientObjectCRC(), schematic);
}

void SchematicMap::addSchematics(PlayerObject* playerObject,
		Vector<String> schematicgroups, bool updateClient) {

	Vector<ManagedReference<DraftSchematic* > > schematics;

	for (int i = 0; i < schematicgroups.size(); ++i) {

		String groupName = schematicgroups.get(i);

		if (groupMap.contains(groupName)) {

			DraftSchematicGroup* dsg = groupMap.get(groupName);

			for(int j = 0; j < dsg->size(); ++j)
				schematics.add(dsg->get(j));
		}
	}

	if (schematics.size() > 0)
		playerObject->addSchematics(schematics, updateClient);
}

void SchematicMap::removeSchematics(PlayerObject* playerObject,
		Vector<String> schematicgroups, bool updateClient) {

	Vector<ManagedReference<DraftSchematic* > > schematics;

	for (int i = 0; i < schematicgroups.size(); ++i) {

		String groupName = schematicgroups.get(i);

		if (groupMap.contains(groupName)) {

			DraftSchematicGroup* dsg = groupMap.get(groupName);

			for(int j = 0; j < dsg->size(); ++j)
				schematics.add(dsg->get(j));
		}
	}

	if (schematics.size() > 0)
		playerObject->removeSchematics(schematics, updateClient);
}
