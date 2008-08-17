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

#include "../../packets.h"

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
			uint32 schematicSize, int craftingToolTab) :
		DraftSchematicServant() {
		this->schematicID = schematicID;
		this->objName = objName;
		this->schematicCRC = objCRC;
		this->groupName = groupName;
		this->complexity = complexity;
		this->schematicSize = schematicSize;
		this->craftingToolTab = craftingToolTab;

		this->craftingValues = new DraftSchematicValues();

		this->persistent = false;
		this->expPointsUsed = 0;

		this->finished = false;
	}

	DraftSchematicImplementation(DraftSchematic* draftSchematic) :
		DraftSchematicServant() {

		//draftSchematic->toString();

		this->schematicID = draftSchematic->getSchematicID();
		this->objName = draftSchematic->getName();
		this->schematicCRC = draftSchematic->getSchematicCRC();
		this->groupName = draftSchematic->getGroupName();
		this->complexity = draftSchematic->getComplexity();
		this->schematicSize = draftSchematic->getSchematicSize();
		this->craftingToolTab = draftSchematic->getCraftingToolTab();

		this->craftingValues = new DraftSchematicValues();

		this->persistent = false;

		this->finished = false;

		for(int i = 0; i < draftSchematic->getIngredientListSize(); ++i){

			this->dsIngredients.add(draftSchematic->getIngredient(i));

		}

		for(int i = 0; i < draftSchematic->getExpPropGroupListSize(); ++i){

			this->dsExpPropGroups.add(draftSchematic->getExpPropGroup(i));

		}

		string title;
		string subtitle;

		for(int i = 0; i < draftSchematic->getCraftingValues()->getExperimentalPropertyTitleSize(); ++i){

			title = draftSchematic->getCraftingValues()->getExperimentalPropertyTitle(i);

			for(int j = 0; j < draftSchematic->getCraftingValues()->getExperimentalPropertySubtitleSize(title); ++j){

				subtitle = draftSchematic->getCraftingValues()->getExperimentalPropertySubtitle(title, j);

				this->craftingValues->addExperimentalPropertySubtitle(title, subtitle);
			}
		}

		for(int i = 0; i < draftSchematic->getAttributesToSetListSize(); ++i){

			this->attributesToSet.add(draftSchematic->getAttributeToSet(i));

		}

		this->tanoAttributes = draftSchematic->getTanoAttributes();
		this->xpType = draftSchematic->getXpType();
		this->xp = draftSchematic->getXp();

		this->experimentingSkill = draftSchematic->getExperimentingSkill();
		this->assemblySkill = draftSchematic->getAssemblySkill();

		//toString();
	}

	~DraftSchematicImplementation(){
		while (dsExpPropGroups.size() > 0)
			dsExpPropGroups.remove(0)->finalize();

		while (attributesToSet.size() > 0)
			attributesToSet.remove(0)->finalize();

		while (dsIngredients.size() > 0)
			dsIngredients.remove(0)->finalize();

		experimentalProperties.removeAll();

		craftingValues->finalize();
		craftingValues = NULL;

	}

	DraftSchematic* dsClone(DraftSchematic* draftSchematic) {
		if (draftSchematic != NULL) {
			return new DraftSchematic(draftSchematic);
		} else {
			return NULL;
		}
	}



	void close(Player* player) {
		if (player == NULL)
			return;

		BaseMessage* msg = new SceneObjectCloseMessage(_this->getObjectID());
		player->sendMessage(msg);
	}

	void destroy(Player* player) {
		if (player == NULL)
			return;

		BaseMessage* msg = new SceneObjectDestroyMessage(_this->getObjectID());
		player->sendMessage(msg);
	}

	void sendTo(Player* player) {
		// This sends the initial DraftSchematic data to begin the crafting Session

		if (player == NULL)
			return;

		// Scene Create
		BaseMessage* create = new SceneObjectCreateMessage(_this->getObjectID(), 0x3819C409);
		player->sendMessage(create);

		// Link to Crafting Tool
		BaseMessage* link = new UpdateContainmentMessage(_this->getObjectID(), _this->getContainer()->getObjectID(), 4);
		player->sendMessage(link);

		// MSCO3
		unicode& uniPlayerName = player->getCharacterName();

		ManufactureSchematicObjectMessage3* msco3 =
				new ManufactureSchematicObjectMessage3(_this->getObjectID(), _this->getComplexity(), uniPlayerName);
		player->sendMessage(msco3);

		// MSCO6
		ManufactureSchematicObjectMessage6* msco6 =
				new ManufactureSchematicObjectMessage6(_this->getObjectID(), _this->getSchematicCRC());
		player->sendMessage(msco6);

		// MSCO8
		ManufactureSchematicObjectMessage8* msco8 =
				new ManufactureSchematicObjectMessage8(_this->getObjectID());
		player->sendMessage(msco8);

		// MSCO9
		ManufactureSchematicObjectMessage9* msco9 =
				new ManufactureSchematicObjectMessage9(_this->getObjectID());
		player->sendMessage(msco9);

		// Scene Close
		BaseMessage* close = new SceneObjectCloseMessage(_this->getObjectID());
		player->sendMessage(close);

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

	// Ingredient Methods
	void addIngredient(const string& ingredientTemplateName, const string& ingredientTitleName,
			bool optional, const string& resourceType, uint32 resourceQuantity) {
		DraftSchematicIngredient* ingreedient = new DraftSchematicIngredient(ingredientTemplateName,
				ingredientTitleName, optional, resourceType, resourceQuantity);

		dsIngredients.add(ingreedient);
	}

	// THERE IS A BUG WHEN YOU LEAVE YOUR DATAPAD UP AND SURRENDER A SKILL, THE DRAFT SCHEMATICS
	// STILL ARE IN YOUR DATAPAD, SO IF YOU CLICK THEM, IT WILL SAY SCHEMATIC NOT FOUND AND WILL
	// SCREW UP THE CLIENT TRYING TO GET THE INGREDIENTS AND EXP PROPS FROM THERE ON UNTIL THE CLIENT
	// FULLY EXITS THE GAME
	void sendIngredientsToPlayer(Player* player) {
		ObjectControllerMessage* msg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x01BF);

		msg->insertInt(schematicID); // ex: 0x838FF623838FF623 (objID is always the crc value in the upper 4 bytes and the lower 4 bytes)
		msg->insertInt(schematicCRC);
		msg->insertInt(complexity); // ex: 3
		msg->insertInt(schematicSize); // ex: 1
		msg->insertByte(1);

		helperSendIngredientsToPlayer(msg);

		player->sendMessage(msg);
	}

	inline void helperSendIngredientsToPlayer(ObjectControllerMessage* objMsg) {
		int listSize = dsIngredients.size();
		objMsg->insertInt(listSize);

		// Send all the ingredient data
		for (int i = 0; i < listSize; i++) {
			DraftSchematicIngredient* dsi = dsIngredients.get(i);
			dsi->helperSendToPlayer(objMsg);
		}

		/* for debugging
		 stringstream ss;
		 ss << msg->toString();
		 player->info(ss.str());*/

		objMsg->insertShort(0);
	}

	// Experimental Property Methods
	// UPDATE THIS METHOD WHEN WE CAN PASS VECTORS AROUND IN IDL
	void addExperimentalProperty(uint32 groupNumber,
			const string& experimentalProperty, uint32 weight) {
		if (groupNumber < dsExpPropGroups.size()) {
			dsExpPropGroups.get(groupNumber)->addExperimentalProperty(experimentalProperty,
					weight);
		} else {
			DraftSchematicExpPropGroup* dsEpg = new DraftSchematicExpPropGroup();
			dsEpg->addExperimentalProperty(experimentalProperty, weight);

			dsExpPropGroups.add(dsEpg);
		}
	}

	void sendExperimentalPropertiesToPlayer(Player* player) {
		ObjectControllerMessage* msg = new ObjectControllerMessage(player->getObjectID(), 0x1B, 0x0207);

		msg->insertInt(schematicID);
		msg->insertInt(schematicCRC);

		uint8 listSize = dsExpPropGroups.size();

		/*uint32 padding = 0;
		 if (draftSchematicIngredients.size() > 0) {
		 string templateName = draftSchematicIngredients.get(0)->getTemplateName();

		 if( templateName == "craft_chemical_ingredients_n" || templateName == "craft_droid_ingredients_n"
		 || templateName == "craft_munition_ingredients_n" || templateName == "craft_structure_ingredients_n"
		 || templateName == "craft_tissue_ingredients_n" || templateName == "craft_vehicle_ingredients_n"
		 || templateName == "craft_weapon_ingredients_n") {
		 padding = 2;
		 } else {
		 padding = 3;
		 }
		 }*/

		// Have to run the loop twice.  Ask soe why :/

		for (int soeFtl = 0; soeFtl < 2; soeFtl++) {
			// The +3 is for the padding
			//msg->insertByte(listSize + padding);

			msg->insertByte(listSize);

			/* This loop adds the padding required for this packet to work
			 for (int soeIsDumb = 0; soeIsDumb < padding; soeIsDumb++) {
			 msg->insertByte(1);
			 msg->insertByte(0);
			 }*/

			int count = getRequiredIngredientCount();

			// Send all the experimental property data
			for (int i = 0; i < listSize; i++) {
				DraftSchematicExpPropGroup* dsEpg = dsExpPropGroups.get(i);
				// OLD dsEpg->sendToPlayer(msg);
				dsEpg->sendToPlayer(msg, count);
				count++;
			}
		}

		player->sendMessage(msg);
	}

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

	inline int getRequiredIngredientCount(){

		DraftSchematicIngredient* dsi;
		int count = 0;

		for(int i = 0; i < dsIngredients.size(); i++){
			dsi = dsIngredients.get(i);

			if(!dsi->getOptional())
				count++;
		}
		return count;
	}

	inline DraftSchematicValues* getCraftingValues(){
		return craftingValues;
	}

	inline bool isFinished(){
		return finished;
	}

	void toString(){

		cout << "Name: " << objName;
		cout << "\nSchematicID: " << schematicID;
		cout << "\nobjectID: " << objectID;
		cout << "\nschematicCRC: " << schematicCRC;
		cout << "\ngroupName: " << groupName;
		cout << "\ncomplexity: " << complexity;
		cout << "\nschematicSize: " << schematicSize;
		cout << "\ncraftingToolTab: " << craftingToolTab;

		cout << "\nxpType: " << xpType;
		cout << "\nxp: " << xp;
		cout << "\ntanoAttributes: " << tanoAttributes;

		cout << "\nAssembly Skill: " << assemblySkill;
		cout << "\nExperimenting Skill: " << experimentingSkill;

		DraftSchematicIngredient* ingredient;
		for(int i = 0;i < dsIngredients.size(); ++i){

			ingredient = dsIngredients.get(i);

			cout << "\n*************************" << endl;
			cout << "Ingredient " << i << endl;
			cout << "Title: " << ingredient->getTitleName() << endl;
			cout << "Resource Type: " << ingredient->getResourceType() << endl;
			cout << "Template Name: " << ingredient->getTemplateName() << endl;
			cout << "Quantity: " << ingredient->getResourceQuantity() << endl;
			cout << "Optional: " << ingredient->getOptional() << endl;
			cout << "**************************" << endl;

		}

		DraftSchematicExpPropGroup* tempGroup;
		for(int i = 0;i < dsExpPropGroups.size(); ++i){

			tempGroup = dsExpPropGroups.get(i);

			cout << "\n*************************" << endl;
			cout << "Exp Property " << i << endl;
			cout << "Type and Weight: " << tempGroup->getTypeAndWeight(i) << endl;
			cout << "Percentage: " << tempGroup->getExpPropPercentage(i) << endl;
			cout << "**************************" << endl;

		}

		DraftSchematicAttribute* tempAttribute;
		for(int i = 0;i < attributesToSet.size(); ++i){

			tempAttribute = attributesToSet.get(i);

			cout << "\n*************************" << endl;
			cout << "Attribute " << i << endl;
			cout << "Name: " << tempAttribute->getAttributeName() << endl;
			cout << "Property: " << tempAttribute->getAttributeExperimentalProperty() << endl;
			cout << "Min: " << tempAttribute->getMinValue() << endl;
			cout << "Max: " << tempAttribute->getMaxValue() << endl;
			cout << "Range: " << tempAttribute->getRange() << endl;
			cout << "**************************" << endl;

		}

		float tempProperty;
		for(int i = 0;i < experimentalProperties.size(); ++i){

			tempProperty = experimentalProperties.get(i);

			cout << "*************************" << endl;
			cout << "Prop " << i << endl;
			cout << "Prop: " << tempProperty << endl;
			cout << "**************************" << endl;

		}

		craftingValues->toString();

	}

};

#endif /*DRAFTSCHEMATICIMPLEMENTATION_H_*/
