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

#ifndef CRAFTINGTOOLIMPLEMENTATION_H_
#define CRAFTINGTOOLIMPLEMENTATION_H_

#include "../../../managers/crafting/CraftingManager.h"

#include "../../../packets.h"
#include "CraftingTool.h"
#include "CraftingSlots.h"
#include "../ContainerImplementation.h"

#include "engine/engine.h"

class CreatureObject;
class SceneObject;
class Player;
class CreateObjectEvent;
class Container;


class CraftingToolImplementation : public CraftingToolServant {
protected:
	float effectiveness;
	int tooltype;
	int state;

	Vector<uint64> tabIds;
	Vector<ManagedReference<DraftSchematic> > schematicsToSend;

	TangibleObject* currentTano;
	DraftSchematic* currentDraftSchematic;

	Vector<TangibleObject*> tempIngredient;

	CraftingSlots* craftingSlots;

	Container* hopper;

	string status;
	int assemblyResults;

	int assemblyMod;
	int experimentationMod;

	// To see if is first resource inserted in a crafting session
	int insertCount;

	bool experimentingEnabled;
	bool recoverResources;

	float craftingToolModifier;

public:
	static const int CLOTHING = 1; // Clothing and Armor Crafting Tool
	static const int FOOD = 2; // Food and Chemical Crafting Tool
	static const int GENERIC = 3; // Generic Crafting Tool
	static const int JEDI = 4; // Lightsaber Crafting Tool
	static const int SPACE = 5; // Starship Crafting Tool
	static const int STRUCTURE = 6; // Structure and Furniture Crafting Tool
	static const int WEAPON = 7; // Weapon Droid and General Item Crafting Tool

public:
	CraftingToolImplementation(uint64 object_id, uint32 tempCRC, const unicode& n, const string& tempn);
	CraftingToolImplementation(CreatureObject* creature, uint32 tempCRC, const unicode& n, const string& tempn);

	~CraftingToolImplementation();

	void init();

	int useObject(Player* player);
	void sendTo(Player* player, bool doClose = true);

	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);

	void updateCraftingValues(DraftSchematic* draftSchematic);

	void parseItemAttributes();
	void generateAttributes(SceneObject* obj);
	void addAttributes(AttributeListMessage* alm);

	void sendToolStart(Player* player);

	uint64 findCraftingStation(Player* player, float& workingStationComplexity);

	void getSchematicsForTool(Player* player, float workingStationComplexity);

	void setWorkingTano(TangibleObject * tano);
	void setWorkingDraftSchematic(DraftSchematic * draftSchematic);

	void resetSlots();

	Container * getHopper(Player * player);
	void retriveHopperItem(Player * player);

	void cleanUp(Player * player);

	void updateCraftedValues(Player * player, DraftSchematic * draftSchematic);
	// Setters

	inline void setToolEffectiveness(float eff) {
		effectiveness = eff;
		string temp = "effectiveness";
		itemAttributes->setFloatAttribute(temp, eff);
	}

	inline void setCraftingState(int s){
		state = s;
	}

	inline void setStatusReady(){
		status = "@crafting:tool_status_ready";
	}

	inline void setStatusWorking(){
		status = "@crafting:tool_status_working";
	}

	inline void setStatusFinished(){
		status = "@crafting:tool_status_finished";
	}

	inline void setInsertCount(int count){
		insertCount = count;
	}

	inline void setAssemblyResults(int results){
		assemblyResults = results;
	}

	inline void setRecoverResources(bool in){
		recoverResources = in;
	}

	inline void setToolType(int in){
		tooltype = in;
	}

	inline bool addIngredientToSlot(int slot, TangibleObject* tano){
		return craftingSlots->putIngredientInSlot(slot, tano);
	}

	inline void clearIngredientInSlot(int slot){

		craftingSlots->clearIngredientInSlot(slot);
	}

	inline void addTempIngredient(TangibleObject* tano){
		tempIngredient.add(tano);
		tano->setContainer(_this);
	}

	inline void increaseInsertCount(){
		insertCount++;
	}

	// Getters
	inline int getCraftingState(){
		return state;
	}
	float getToolEffectiveness() {
		return effectiveness;
	}

	inline TangibleObject* getWorkingTano(){
		return currentTano;
	}

	inline DraftSchematic* getWorkingDraftSchematic(){
		return currentDraftSchematic;
	}

	inline int getInsertCount(){
		return insertCount;
	}

	inline TangibleObject* getIngredientInSlot(int slot){

		return craftingSlots->getIngredientInSlot(slot);

	}

	inline int getIngredientInSlotQuantity(int slot){

		return craftingSlots->getIngredientCount(slot);

	}

	inline DraftSchematic* getCurrentDraftSchematic(int slot){
		try {

			return  schematicsToSend.get(slot);
		}
		catch(...) {
			return NULL;
		}
	}

	inline int getSlotCount(){
		return  craftingSlots->size();
	}

	inline int getAssemblyResults(){
		return assemblyResults;
	}

	inline float getCraftingToolModifier(){
		return assemblyResults;
	}

	bool isReady() {
		return status == "@crafting:tool_status_ready";
	}

	bool isFinished() {
		return status == "@crafting:tool_status_finished";
	}

	bool isWorking() {
		return status == "@crafting:tool_status_working";
	}

	bool isExperimenting() {
		return experimentingEnabled;
	}

	int getToolType(){
		return tooltype;
	}
};

#endif /*CRAFTINGTOOLIMPLEMENTATION_H_*/
