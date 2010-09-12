/*
 * SharedDraftSchematicObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: kyle
 */

#ifndef DRAFTSCHEMATICOBJECTTEMPLATE_H_
#define DRAFTSCHEMATICOBJECTTEMPLATE_H_

#include "SharedDraftSchematicObjectTemplate.h"
#include "server/zone/objects/draftschematic/draftslot/DraftSlot.h"
#include "server/zone/objects/draftschematic/resourceweight/ResourceWeight.h"

class DraftSchematicObjectTemplate : public SharedDraftSchematicObjectTemplate {
protected:

	String customObjectName;
	String groupName;

	int craftingToolTab;
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
	 * 8192 = genetics								 0010 0000 0000 0000
	 * 16384 = Tailor, Mandalorian					 0100 0000 0000 0000
	 * 32768 = armorsmith, Mandalorian				 1000 0000 0000 0000
	 * 65536 = Droid Engineer, Mandalorian		0001 0000 0000 0000 0000
	 * 131072 = Starship Components				0010 0000 0000 0000 0000
	 * 262144 = Ship Tools						0100 0000 0000 0000 0000
	 * 524288 = Misc							1000 0000 0000 0000 0000
	 * 2148007936 = Mission      1000 0000 0000 1000 0000 0000 0000 0000
	 * * */

	short complexity;
	short size;

	String xpType;
	int xp;

	String assemblySkill;
	String experimentingSkill;
	String customizationSkill;

	Vector<byte>* customizationOptions;
	Vector<String>* customizationStringNames;
	Vector<byte>* customizationDefaultValues;

	Vector<String>* ingredientTemplateNames;
	Vector<String>* ingredientTitleNames;
	Vector<short>* ingredientSlotType;
	Vector<String>* resourceTypes;
	Vector<int>* resourceQuantities;
	Vector<short>* combineTypes;
	Vector<short>* contribution;

	Vector<short>* numberExperimentalProperties;
	Vector<String>* experimentalProperties;
	Vector<short>* experimentalWeights;
	Vector<String>* experimentalGroupTitles;
	Vector<String>* experimentalSubGroupTitles;
	Vector<int>* experimentalMin;
	Vector<int>* experimentalMax;
	Vector<short>* experimentalPrecision;

	uint32 tanoCRC;

	Vector<Reference<DraftSlot* > >* draftSlots;

	Vector<Reference<ResourceWeight* > >* resourceWeights;

public:
	DraftSchematicObjectTemplate();

	~DraftSchematicObjectTemplate();

	void readObject(LuaObject* templateData);


	Vector<Reference<DraftSlot* > >* getDraftSlots() {
        return draftSlots;
    }

	Vector<Reference<ResourceWeight* > >* getResourceWeights() {
        return resourceWeights;
    }

    void addSlot(DraftSlot* slot) {
		draftSlots->add(slot);
	}

    void addResourceWeight(ResourceWeight* weight) {
		resourceWeights->add(weight);
	}

    String getAssemblySkill() {
        return assemblySkill;
    }

    Vector<short >* getCombineTypes() {
        return combineTypes;
    }

    short getComplexity() {
        return complexity;
    }

    Vector<short >* getContribution() {
        return contribution;
    }

    int getCraftingToolTab() {
        return craftingToolTab;
    }

    Vector<String>* getExperimentalGroupTitles() {
        return experimentalGroupTitles;
    }

    Vector<int>* getExperimentalMax() {
        return experimentalMax;
    }

    Vector<int>* getExperimentalMin() {
        return experimentalMin;
    }

    Vector<short >* getExperimentalPrecision() {
        return experimentalPrecision;
    }

    Vector<String>* getExperimentalProperties() {
        return experimentalProperties;
    }

    Vector<String>* getExperimentalSubGroupTitles() {
        return experimentalSubGroupTitles;
    }

    Vector<short >* getExperimentalWeights() {
        return experimentalWeights;
    }

    String getExperimentingSkill() {
        return experimentingSkill;
    }

    String getCustomizationSkill() {
    	return customizationSkill;
    }

    Vector<byte>* getCustomizationOptions() {
        return customizationOptions;
    }

    Vector<String>* getCustomizationStringNames() {
        return customizationStringNames;
    }

    Vector<byte>* getCustomizationDefaultValues() {
        return customizationDefaultValues;
    }

    String getGroupName() {
        return groupName;
    }

    Vector<short >* getIngredientSlotType() {
        return ingredientSlotType;
    }

    Vector<String>* getIngredientTemplateNames() {
        return ingredientTemplateNames;
    }

    Vector<String>* getIngredientTitleNames() {
        return ingredientTitleNames;
    }

    Vector<short >* getNumberExperimentalProperties() {
        return numberExperimentalProperties;
    }

    Vector<int>* getResourceQuantities() {
        return resourceQuantities;
    }

    Vector<String>* getResourceTypes() {
        return resourceTypes;
    }

    short getSize() {
        return size;
    }

    uint32 getTanoCRC() {
        return tanoCRC;
    }

    int getXp() {
        return xp;
    }

    String getXpType() {
        return xpType;
    }

    String getCustomObjectName() {
        return customObjectName;
    }

};


#endif /* DRAFTSCHEMATICOBJECTTEMPLATE_H_ */
