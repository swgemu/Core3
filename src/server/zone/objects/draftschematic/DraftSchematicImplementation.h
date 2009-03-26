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

#include "../../packets/manufactureschematic/ManufactureSchematicObjectMessage3.h"
#include "../../packets/manufactureschematic/ManufactureSchematicObjectMessage6.h"
#include "../../packets/manufactureschematic/ManufactureSchematicObjectMessage7.h"
#include "../../packets/manufactureschematic/ManufactureSchematicObjectMessage8.h"
#include "../../packets/manufactureschematic/ManufactureSchematicObjectMessage9.h"
#include "../../packets/manufactureschematic/ManufactureSchematicObjectDeltaMessage3.h"
#include "../../packets/manufactureschematic/ManufactureSchematicObjectDeltaMessage6.h"
#include "../../packets/manufactureschematic/ManufactureSchematicObjectDeltaMessage7.h"

class Player;
class ObjectControllerMessage;

class DraftSchematicImplementation: public DraftSchematicServant {

	// example: 0x838FF623
	uint32 schematicID;

	// example: craftArtisanNewbieGroupA
	String groupName;

	String tanoStfName;

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

	// Ingredient List
	Vector<ManagedReference<DraftSchematicIngredient> > dsIngredients;

	// Experimental Property List With Padding
	Vector<ManagedReference<DraftSchematicExpPropGroup> > dsExpPropGroups;

	// Attributes that are sent in the packets
	//Vector<ManagedReference<DraftSchematicAttribute> > attributesToSet;

	//VectorMap<String, float> experimentalProperties;

	DraftSchematicValues* craftingValues;

	// Tano Attributes
	String tanoAttributes;
	String blueFrogAttributes;

	String xpType;
	int xp;

	int expPointsUsed;

	int expCounter;

	float experimentalFailureRate;

	String experimentingSkill;
	String assemblySkill;
	String customizationSkill;

	Vector<String> customizationOptions;
	Vector<int> customizationDefaults;

	bool finished;
	bool resourcesRemoved;

	int manufacturingLimit;

	Player* crafter;

	bool blueFrogEnabled;

public:
	DraftSchematicImplementation(uint32 schematicID, const String& objName,
			const String& StringFile, const String& StringName, uint32 objCRC, const String& groupName,
			uint32 complexity, uint32 schematicSize, int craftingToolTab);

	DraftSchematicImplementation(DraftSchematic* draftSchematic);

	~DraftSchematicImplementation();

	DraftSchematic* dsClone(DraftSchematic* draftSchematic);

	void close(Player* player);

	void destroy(Player* player);

	void sendTo(Player* player);

	// Ingredient Methods
	void addIngredient(const String& ingredientTemplateName,
			const String& ingredientTitleName, const int slotoption,
			const String& resourceType, uint32 resourceQuantity,
			uint32 combineType, uint32 contribution);

	// THERE IS A BUG WHEN YOU LEAVE YOUR DATAPAD UP AND SURRENDER A SKILL, THE DRAFT SCHEMATICS
	// STILL ARE IN YOUR DATAPAD, SO IF YOU CLICK THEM, IT WILL SAY SCHEMATIC NOT FOUND AND WILL
	// SCREW UP THE CLIENT TRYING TO GET THE INGREDIENTS AND EXP PROPS FROM THERE ON UNTIL THE CLIENT
	// FULLY EXITS THE GAME
	void sendIngredientsToPlayer(Player* player);

	void helperSendIngredientsToPlayer(ObjectControllerMessage* objMsg);

	// Experimental Property Methods
	// UPDATE THIS METHOD WHEN WE CAN PASS VECTORS AROUND IN IDL
	void addExperimentalProperty(uint32 groupNumber, String experimentalProperty,
			uint32 weight, String title, String subtitle, float min, float max, int precision);

	void sendExperimentalPropertiesToPlayer(Player* player);

	void toString();

	// setters
	/*inline void setObjectID(uint64 id) {
		objectID = id;
	}*/

	inline void setTanoAttributes(String attributes) {
		tanoAttributes = attributes;
		ItemAttributes attrib;
		attrib.setAttributes(attributes);

		String name = "stfName";
		tanoStfName = attrib.getStringAttribute(name);
	}

	inline void setBlueFrogAttributes(String attributes) {
		blueFrogAttributes = attributes;
	}

	inline void setBlueFrogEnabled(bool enabled) {
		blueFrogEnabled = enabled;
	}

	inline void setXpType(String type) {
		xpType = type;
	}

	inline void setXp(int x) {
		xp = x;
	}

	inline void setExpCounter(int value) {
		expCounter = value;
	}

	inline void increaseExpCounter() {
		expCounter++;
	}

	inline void setExpPoints(int points) {
		expPointsUsed = points;
	}

	inline void setExpFailure(float rate) {
		experimentalFailureRate = rate;
	}

	inline void setExperimentingSkill(const String& exp) {
		experimentingSkill = exp;
	}

	inline void setCustomizationSkill(const String& cust) {
		customizationSkill = cust;
	}

	inline void addCustomizationOption(const String cust, const int value) {
		customizationOptions.add(cust);
		customizationDefaults.add(value);
	}

	inline void setAssemblySkill(const String& ass) {
		if (ass.indexOf("armor") != -1)
			customizationSkill = "armor_customization";
		if (ass.indexOf("clothing") != -1)
			customizationSkill = "clothing_customization";
		if (ass.indexOf("droid") != -1)
			customizationSkill = "droid_customization";

		assemblySkill = ass;
	}

	inline void setCrafter(Player* player) {
		crafter = player;
	}

	inline void increaseComplexity() {
		complexity++;
	}

	inline void decreaseComplexity() {
		complexity--;
	}

	inline void setFinished() {
		finished = true;
	}

	inline void setResourcesWereRemoved() {
		resourcesRemoved = true;
	}

	inline void setManufacturingLimit(int value) {
		manufacturingLimit = value;
	}

	//getters

	inline uint32 getSchematicID() {
		return schematicID;
	}

	inline String& getTanoStfName() {
		return tanoStfName;
	}

	inline String& getGroupName() {
		return groupName;
	}

	inline uint32 getComplexity() {
		return complexity;
	}

	inline uint32 getSchematicSize() {
		return schematicSize;
	}

	inline String& getTanoAttributes() {
		return tanoAttributes;
	}

	inline String& getBlueFrogAttributes() {
		return blueFrogAttributes;
	}

	inline bool getBlueFrogEnabled() {
		return blueFrogEnabled;
	}

	inline int getCraftingToolTab() {
		return craftingToolTab;
	}

	inline String& getXpType() {
		return xpType;
	}

	inline int getXp() {
		return xp;
	}

	inline String& getExperimentingSkill() {
		return experimentingSkill;
	}

	inline String& getCustomizationSkill() {
		return customizationSkill;
	}

	inline String& getCustomizationOption(const int i) {
		return customizationOptions.get(i);
	}

	inline int getCustomizationDefaultValue(const int i) {
		return customizationDefaults.get(i);
	}

	inline int getCustomizationOptionCount() {
		return customizationOptions.size();
	}

	inline String& getAssemblySkill() {
		return assemblySkill;
	}

	inline int getExpPoints() {
		return expPointsUsed;
	}

	inline int getExpCounter() {
		return expCounter;
	}

	inline float getExpFailure() {
		return experimentalFailureRate;
	}

	inline int getIngredientListSize() {
		return dsIngredients.size();
	}

	inline Player* getCrafter() {
		return crafter;
	}

	inline int getManufacturingLimit() {
		return manufacturingLimit;
	}

	DraftSchematicIngredient* getIngredient(int index) {
		return dsIngredients.get(index);
	}

	DraftSchematicIngredient* cloneIngredient(int index) {
		return new DraftSchematicIngredient(dsIngredients.get(index));
	}

	int getExpPropGroupListSize() {
		return dsExpPropGroups.size();
	}

	DraftSchematicExpPropGroup* getExpPropGroup(int index) {
		return dsExpPropGroups.get(index);
	}

	DraftSchematicExpPropGroup* cloneExpPropGroup(int index) {
		return new DraftSchematicExpPropGroup(dsExpPropGroups.get(index));
	}

	int getRequiredIngredientCount();

	inline DraftSchematicValues* getCraftingValues() {
		return craftingValues;
	}

	inline bool isFinished() {
		return finished;
	}

	inline bool resourcesWereRemoved() {
		return resourcesRemoved;
	}

	inline void resetCraftingValues() {

		if(craftingValues != NULL)
			craftingValues->finalize();

		craftingValues = new DraftSchematicValues();
	}
};

#endif /*DRAFTSCHEMATICIMPLEMENTATION_H_*/
