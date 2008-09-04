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

#ifndef DRAFTSCHEMATICIMPLEMENTATION_H_
#define DRAFTSCHEMATICIMPLEMENTATION_H_

#include "engine/engine.h"

#include "DraftSchematic.h"
#include "DraftSchematicImplementation.h"

#include "DraftSchematicIngredient.h"
#include "DraftSchematicIngredientImplementation.h"

#include "DraftSchematicExpPropGroup.h"
#include "DraftSchematicExpPropGroupImplementation.h"

#include "DraftSchematicAttribute.h"
#include "DraftSchematicAttributeImplementation.h"

#include "DraftSchematicValues.h"
#include "DraftSchematicValuesImplementation.h"

class Player;
class ObjectControllerMessage;

class DraftSchematicImplementation : public DraftSchematicServant {
	// example: 0x838FF623
	uint32 schematicID;

	// example: 0x838FF623
	uint32 schematicCRC;

	// example: Bofa Treat
	string objName;
	// example: craftArtisanNewbieGroupA
	string groupName;

	// example: 3
	uint32 complexity;
	// example: 1
	uint32 schematicSize;

	// The number that tells the client which crafting tool tab to put the draftSchematic in
	/*
	 * BITMASK FOR TABS
	 * 0 = unknown													0000
	 * 1 = weapons													0001
	 * 2 = armor													0010
	 * 4 = food														0100
	 * 8 = clothing													1000
	 * 16 = vehicle											   0001 0000
	 * 32 =	droid											   0010 0000
	 * 64 = chemical										   0100 0000
	 * 128 = tissues									  	   1000 0000
	 * 256 = creatures									  0001 0000 0000
	 * 512 = furniture									  0010 0000 0000
	 * 1024 = installation								  0100 0000 0000
	 * 2048 = lightsaber							 	  1000 0000 0000
	 * 4096 = generic item							 0001 0000 0000 0000
	 * 8192 = genetics								 0010 0000 0000 0000f
	 * 16384 = talior, Mandalorian					 0100 0000 0000 0000
	 * 32768 = armorsmith, Mandalorian				 1000 0000 0000 0000
	 * 65536 = Droid Engineer, Mandalorian		0001 0000 0000 0000 0000
	 * 131072 = Starship Components				0010 0000 0000 0000 0000
	 * 262144 = Ship Tools						0100 0000 0000 0000 0000
	 * 524288 = Misc							1000 0000 0000 0000 0000
	 * * */
	int craftingToolTab;

	// For when it becomes and object during crafting
	uint64 objectID;

	// Ingredient List
	Vector<ManagedReference<DraftSchematicIngredient> > dsIngredients;

	// Experimental Property List With Padding
	Vector<ManagedReference<DraftSchematicExpPropGroup> > dsExpPropGroups;

	// Attributes that are sent in the packets
	Vector<ManagedReference<DraftSchematicAttribute> > attributesToSet;

	VectorMap<string, float> experimentalProperties;

	DraftSchematicValues* craftingValues;

	// Tano Attributes
	string tanoAttributes;

	bool persistent;

	SceneObject* parent;

	string xpType;
	int xp;

	int expPointsUsed;

	int expCounter;

	float experimentalFailureRate;

	string experimentingSkill;
	string assemblySkill;

	bool finished;

public:
	DraftSchematicImplementation(uint32 schematicID, const string& objName,
			uint32 objCRC, const string& groupName, uint32 complexity,
			uint32 schematicSize, int craftingToolTab);

	DraftSchematicImplementation(DraftSchematic* draftSchematic);

	~DraftSchematicImplementation();

	DraftSchematic* dsClone(DraftSchematic* draftSchematic);

	void close(Player* player);

	void destroy(Player* player);

	void sendTo(Player* player);

	// Ingredient Methods
	void addIngredient(const string& ingredientTemplateName, const string& ingredientTitleName,
			bool optional, const string& resourceType, uint32 resourceQuantity);

	// THERE IS A BUG WHEN YOU LEAVE YOUR DATAPAD UP AND SURRENDER A SKILL, THE DRAFT SCHEMATICS
	// STILL ARE IN YOUR DATAPAD, SO IF YOU CLICK THEM, IT WILL SAY SCHEMATIC NOT FOUND AND WILL
	// SCREW UP THE CLIENT TRYING TO GET THE INGREDIENTS AND EXP PROPS FROM THERE ON UNTIL THE CLIENT
	// FULLY EXITS THE GAME
	void sendIngredientsToPlayer(Player* player);

	void helperSendIngredientsToPlayer(ObjectControllerMessage* objMsg);

	// Experimental Property Methods
	// UPDATE THIS METHOD WHEN WE CAN PASS VECTORS AROUND IN IDL
	void addExperimentalProperty(uint32 groupNumber,
			const string& experimentalProperty, uint32 weight);

	void sendExperimentalPropertiesToPlayer(Player* player);

	void toString();

	// setters
	inline void setPersistent(bool status) {
		persistent = status;
	}
	inline void setObjectID(uint64 objID) {
		objectID = objID;
	}

	inline void setTanoAttributes(string attributes) {
		tanoAttributes = attributes;
	}

	inline void setContainer(SceneObject* obj) {
		parent = obj;
	}

	inline void setXpType(string type){
		xpType = type;
	}

	inline void setXp(int x){
		xp = x;
	}

	inline void setExpCounter() {
		expCounter = craftingValues->getExperimentalPropertyTitleSize() + 1;
	}

	inline void increaseExpCounter(){
		expCounter++;
	}

	inline void setExpPoints(int points){
		expPointsUsed = points;
	}

	inline void setExpFailure(float rate){
		experimentalFailureRate = rate;
	}

	inline void setExperimentingSkill(const string& exp){
		experimentingSkill = exp;
	}

	inline void setAssemblySkill(const string& ass){
		assemblySkill = ass;
	}

	inline void increaseComplexity(){
		complexity++;
	}

	inline void setFinished(){
		finished = true;
	}

	//getters
	inline uint32 getSchematicID() {
		return schematicID;
	}

	inline uint32 getSchematicCRC() {
		return schematicCRC;
	}

	inline string& getName() {
		return objName;
	}

	inline string& getGroupName() {
		return groupName;
	}

	inline uint32 getComplexity() {
		return complexity;
	}

	inline uint32 getSchematicSize() {
		return schematicSize;
	}

	inline uint64 getObjectID() {
		return objectID;
	}

	inline string& getTanoAttributes() {
		return tanoAttributes;
	}

	inline int getCraftingToolTab() {
		return craftingToolTab;
	}

	inline SceneObject* getContainer() {
		return parent;
	}

	inline string& getXpType(){
		return xpType;
	}

	inline int getXp(){
		return xp;
	}

	inline string& getExperimentingSkill(){
		return experimentingSkill;
	}

	inline string& getAssemblySkill(){
		return assemblySkill;
	}

	inline void addAttributeToSet(const string& attribute, const float minVal, const float maxVal, const string& attributeExpProp) {
		DraftSchematicAttribute* attrib = new DraftSchematicAttribute(attribute, minVal, maxVal, attributeExpProp);
		attributesToSet.add(attrib);
	}

	inline DraftSchematicAttribute* getAttributeToSet(const int i) {
		return attributesToSet.get(i);
	}

	inline int getAttributesToSetListSize(){
		return attributesToSet.size();
	}

	inline DraftSchematicAttribute* getAttributesToSet(const int i){
		return attributesToSet.get(i);
	}

	inline int getExpPoints(){
		return expPointsUsed;
	}

	inline int getExpCounter(){
		return expCounter;
	}

	inline float getExpFailure(){
		return experimentalFailureRate;
	}

	int getIngredientListSize() {
		return dsIngredients.size();
	}

	DraftSchematicIngredient* getIngredient(int index) {
		return dsIngredients.get(index);
	}

	int getExpPropGroupListSize() {
		return dsExpPropGroups.size();
	}

	DraftSchematicExpPropGroup* getExpPropGroup(int index) {
		return dsExpPropGroups.get(index);
	}

	int getRequiredIngredientCount();

	inline DraftSchematicValues* getCraftingValues(){
		return craftingValues;
	}

	inline bool isFinished(){
		return finished;
	}

};

#endif /*DRAFTSCHEMATICIMPLEMENTATION_H_*/
