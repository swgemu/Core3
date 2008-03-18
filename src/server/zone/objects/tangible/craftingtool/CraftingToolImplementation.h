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
 
#include "../../../packets.h"
#include "CraftingTool.h"
 
class CreatureObject;
class SceneObject;
class Player;
class CreateObjectEvent;

 
class CraftingToolImplementation : public CraftingToolServant {
protected:
	float effectiveness;
	int state;
	TangibleObject * currentTano;
	DraftSchematic * currentDs;
	
	// To see if is first resource inserted in a crafting session
	int insertCount;
 
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
	void sendTo(Player* player, bool doClose = true);
	void generateAttributes(SceneObject* player);
 
	int useObject(Player* player);
 
	void sendToolStart(Player* player);
	
	// Setters
	inline void setToolEffectiveness(float eff) {
		effectiveness = eff;
	}
	
	inline void setCraftingState(int s){
		state = s;
	}
	
	inline void setTano(TangibleObject * tano){
		currentTano = tano;
	}
	
	inline void setDs(DraftSchematic * ds){
		currentDs = ds;
	}
	
	inline void setInsertCount(int count){
		insertCount = count;
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
 
	inline TangibleObject* getTano(){
		return currentTano;
	}
	
	inline DraftSchematic* getDs(){
		return currentDs;
	}
	
	inline int getInsertCount(){
		return insertCount;
	}
	
	bool isReady() {
		return true;
	}
};
 
#endif /*CRAFTINGTOOLIMPLEMENTATION_H_*/
