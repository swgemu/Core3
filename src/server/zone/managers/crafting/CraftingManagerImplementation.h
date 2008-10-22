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


class ZoneServer;

class CraftingManagerImplementation : public CraftingManagerServant,
	public Mutex, public Lua {

	ZoneServer* server;
	ZoneProcessServerImplementation * processor;

	// Use a groupName to recieve a vector of draftSchematics back
	VectorMap<string, DraftSchematicGroup*> draftSchematicsMap;

	static CraftingManagerImplementation* instance;

	static const double CONSTE = 2.71828182845904523536;

	// Crafting error messages
	static const short SLOTOK = 0x00;
	static const short SLOTNOSERVER = 0x01; // No server for Owner
	static const short SLOTNOTASSEMBLYSTAGE = 0x02; // Not in crafting assembly stage
	static const short SLOTNOTCUSTOMIZATIONSTAGE = 0x03; // Not in crafting customization stage
	static const short SLOTNOSCHEMATIC = 0x04; // No Draft Schematic Found
	static const short SLOTNOTOOL = 0x05; // No Crafting tool Found
	static const short SLOTNOMANUFACTURE = 0x06; // No manufacturing schematic found
	static const short SLOTINVALID = 0x07; // Invalid Slot Chosen
	static const short SLOTINVALIDOPTION = 0x08; // Invalid Slot Option Chosen
	static const short SLOTINVALIDINGREDIENTSIZE = 0x09; // Invalid ingredient size for slot
	static const short SLOTFULL = 0x0A; // Slot Full
	static const short SLOTINVALIDINGREDIENT = 0x0B; // Invalid Ingredient
	static const short SLOTINGREDIENTNOTININVENTORY = 0x0C; // Ingredient not in inventory
	static const short SLOTBADCRATE = 0x0D; // Cannot remove resource from crate
	static const short SLOTBADRESOURCEFORSLOT = 0x0E; // Bad resource for Slot
	static const short SLOTCOMPONENTDAMAGED = 0x0F; // Component too damaged for use
	static const short SLOTNOCOMPONENTTRANSFER = 0x10; // Cannot transfer componenet
	static const short SLOTBADCOMPONENT = 0x11; // Bad component for slot
	static const short SLOTNOINVENTORY = 0x12; // Inventory Missing
	static const short SLOTBADSTATIONHOPPER = 0x13; // Bad station Hopper
	static const short SLOTBADTARGETCONTAINER = 0x14; // Bad target container
	static const short SLOTEMPTYISEMPTY = 0x15; // Empty slot is empty
	static const short SLOTFAILEDRESOURCECREATE = 0x16; // Cannot create resource container
	static const short SLOTEMPTYSLOTASSEMBLE = 0x17; // Trying to assemble with empty slot
	static const short SLOTPARTIALSLOTASSEMBLE = 0x18; // Trying to assemble with patially full slot
	static const short SLOTPROTOTYPENOTFOUND = 0x19; // Prototype not found
	static const short SLOTBADNAME = 0x1A; // Rename object and resend
	static const short SLOTMYSTERY = 0x1B; // Didn't read this one
	static const short SLOTFAILEDTOTRANSFER = 0x1C; // Failed to transfer resources to station

	// Ingredient math types
	static const short RESOURCE = 0x01;
	static const short PERCENTAGEADDPROPERTIES = 0x02;
	static const short LINEARADDPROPERTIES = 0x03;
	static const short SIMULATEWEIGHTEDVALUE = 0x04;


public:

	void init();

	// LUA Methods
	void registerFunctions();
	void loadDraftSchematicFile() {
		runFile("scripts/crafting/main.lua");
	}

	static int runDraftSchematicFile(lua_State* L);

	static int addDraftSchematicToServer(lua_State *L);

public:

	CraftingManagerImplementation(ZoneServer* serv, ZoneProcessServerImplementation* proc);
	~CraftingManagerImplementation();

	void reloadSchematicTable();

	// Setup initial crafting process
	void prepareCraftingSession(Player* player, CraftingTool* craftingTool, DraftSchematic* draftSchematic);

	// Methods relating to adding Items to the crafting process
	void addIngredientToSlot(Player* player, TangibleObject* tano, int slot, int counter);

	// Methods relating to removing Items to the crafting process
	void removeIngredientFromSlot(Player* player, int slot, int counter);

	// Pretty Self explanitory
	void putComponentBackInInventory(Player* player, Component* component);

	// Crafting Methods
	void nextCraftingStage(Player* player, string test);
	void craftingCustomization(Player* player, string name, int condition);
	void handleExperimenting(Player* player, int counter, int numRowsAttempted, string expstring);
	void createPrototype(Player* player, string count);
	void createSchematic(Player* player, string count);


	float getWeightedValue(Player* player, CraftingTool* craftingTool, DraftSchematic* draftSchematic, int type);
	float getAssemblyPercentage(float value);
	float calculateAssemblyValueModifier(CraftingTool* craftingTool);

	void addDraftSchematicsFromGroupName(Player* player, const string& schematicGroupName);
	void subtractDraftSchematicsFromGroupName(Player* player, const string& schematicGroupName);

	void refreshDraftSchematics(Player* player);

private:
	void mapDraftSchematic(DraftSchematic* draftSchematic);
	// End LUA Methods

	// Methods to setup the crafting sequence
	void createDraftSchematic(Player* player, CraftingTool* craftingTool, DraftSchematic* draftSchematic);
	void createTangibleObject(Player* player, CraftingTool* craftingTool, DraftSchematic* draftSchematic);
	void setupIngredients(Player* player, CraftingTool* craftingTool, DraftSchematic* draftSchematic);
	TangibleObject * generateTangibleObject(Player* player, DraftSchematic* draftSchematic);

	// Slot manipulation
	void sendSlotMessage(Player* player, int counter, short message);
	ResourceContainer * makeNewResourceStack(Player* player, string name, int quantity);
	bool slotIsFull(Player* player, CraftingTool* craftingTool, TangibleObject* tano, TangibleObject* ingredientInSlot,
			int slot, int quantity, int counter);
	TangibleObject* transferIngredientToSlot(Player* player, TangibleObject* tano,
			CraftingTool* craftingTool, int& quantity);
	TangibleObject* transferResourceToSlot(Player* player, ResourceContainer* rcno,
			CraftingTool* craftingTool, int& quantity);
	TangibleObject* transferComponentToSlot(
			Player* player, Component* component, CraftingTool* craftingTool,
			int& quantity);

	// Turn on Experimentation window
	void enableExperimentation(Player* player, CraftingTool* craftingTool);

	// Setting initial crafting values
	void initialAssembly(Player* player, CraftingTool* craftingTool, DraftSchematic* draftSchematic, int counter, int stage);
	bool addSubcomponentTraitsToNewTano(CraftingTool* craftingTool);
	void setInitialCraftingValues(Player* player, CraftingTool* craftingTool, DraftSchematic* draftSchematic);
	bool applyComponentBoost(DraftSchematic* draftSchematic, CraftingTool* craftingTool);
	//float applyComponentPercentageBoost(string subtitle, DraftSchematic* draftSchematic, CraftingTool* craftingTool);

	// Experimenting
	void experimentRow(DraftSchematicValues* craftingValues,
			int rowEffected, int pointsAttempted, float failure, int assemblyResult);

	// Final creation methods
	void finishAssembly(Player* player, CraftingTool* craftingTool, DraftSchematic* draftSchematic, int counter);
	void finishStage1(Player* player, int counter);
	void finishStage2(Player* player, int counter);
	void createObjectInInventory(Player* player, int timer, bool create);

	// Calculations

	void calculateAssemblySuccess(Player* player, CraftingTool* craftingTool, DraftSchematic* draftSchematic, float modifier);
	int calculateAssemblyFailureRate(Player* player, CraftingTool* craftingTool, float assemblyPoints);
	float calculateExperimentationFailureRate(Player* player, CraftingTool* craftingTool, DraftSchematic* draftSchematic, int pointsUsed);
	void calculateExperimentationSuccess(Player* player, CraftingTool* craftingTool, DraftSchematic* draftSchematic, float failure);
	float calculateAssemblyModifier(CraftingTool* craftingTool);
	float calculateExperimentationValueModifier(int assemblyResult, int pointsAttempted, float failure);
	float getLog(float value);

	int lookUpResourceAttribute(Player* player, TangibleObject* tano, int type,  int slot);

	string generateCraftedSerial();

	Vector<string> parseStringsFromString(const string& unparsedStrings);
	Vector<uint32> parseUnsignedInt32sFromString(const string& unparsedInts);

};

#endif /*CRAFTINGMANAGERIMPLEMENTATION_H_*/
