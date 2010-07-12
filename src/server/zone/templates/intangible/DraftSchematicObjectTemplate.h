/*
 * SharedDraftSchematicObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef DRAFTSCHEMATICOBJECTTEMPLATE_H_
#define DRAFTSCHEMATICOBJECTTEMPLATE_H_

#include "SharedDraftSchematicObjectTemplate.h"
#include "server/zone/objects/draftschematic/draftslot/DraftSlot.h"
#include "server/zone/objects/draftschematic/resourceweight/ResourceWeight.h"

class DraftSchematicObjectTemplate : public SharedDraftSchematicObjectTemplate {
protected:

	String groupName;

	int craftingToolTab;
	short complexity;
	short size;

	String xpType;
	int xp;

	String assemblySkill;
	String experimentingSkill;

	Vector<String> ingredientTemplateNames;
	Vector<String> ingredientTitleNames;
	Vector<short> ingredientSlotType;
	Vector<String> resourceTypes;
	Vector<int> resourceQuantities;
	Vector<short> combineTypes;
	Vector<short> contribution;

	Vector<short> numberExperimentalProperties;
	Vector<String> experimentalProperties;
	Vector<short> experimentalWeights;
	Vector<String> experimentalGroupTitles;
	Vector<String> experimentalSubGroupTitles;
	Vector<int> experimentalMin;
	Vector<int> experimentalMax;
	Vector<short> experimentalPrecision;

	uint32 tanoCRC;

	Vector<Reference<DraftSlot* > > draftSlots;

	Vector<Reference<ResourceWeight* > > resourceWeights;

public:
	DraftSchematicObjectTemplate();

	~DraftSchematicObjectTemplate();

	void readObject(LuaObject* templateData);

	Vector<Reference<DraftSlot* > > getDraftSlots() {
        return draftSlots;
    }

	Vector<Reference<ResourceWeight* > > getResourceWeights() {
        return resourceWeights;
    }

    void addSlot(DraftSlot* slot) {
		draftSlots.add(slot);
	}

    void addResourceWeight(ResourceWeight* weight) {
		resourceWeights.add(weight);
	}

    String getAssemblySkill() {
        return assemblySkill;
    }

    Vector<short > getCombineTypes() {
        return combineTypes;
    }

    short getComplexity() {
        return complexity;
    }

    Vector<short > getContribution() {
        return contribution;
    }

    int getCraftingToolTab() {
        return craftingToolTab;
    }

    Vector<String> getExperimentalGroupTitles() {
        return experimentalGroupTitles;
    }

    Vector<int> getExperimentalMax() {
        return experimentalMax;
    }

    Vector<int> getExperimentalMin() {
        return experimentalMin;
    }

    Vector<short > getExperimentalPrecision() {
        return experimentalPrecision;
    }

    Vector<String> getExperimentalProperties() {
        return experimentalProperties;
    }

    Vector<String> getExperimentalSubGroupTitles() {
        return experimentalSubGroupTitles;
    }

    Vector<short > getExperimentalWeights() {
        return experimentalWeights;
    }

    String getExperimentingSkill() {
        return experimentingSkill;
    }

    String getGroupName() {
        return groupName;
    }

    Vector<short > getIngredientSlotType() {
        return ingredientSlotType;
    }

    Vector<String> getIngredientTemplateNames() {
        return ingredientTemplateNames;
    }

    Vector<String> getIngredientTitleNames() {
        return ingredientTitleNames;
    }

    Vector<short > getNumberExperimentalProperties() {
        return numberExperimentalProperties;
    }

    Vector<int> getResourceQuantities() {
        return resourceQuantities;
    }

    Vector<String> getResourceTypes() {
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

};


#endif /* DRAFTSCHEMATICOBJECTTEMPLATE_H_ */
