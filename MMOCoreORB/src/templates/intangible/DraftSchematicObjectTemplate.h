/*
 * SharedDraftSchematicObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: kyle
 */

#ifndef DRAFTSCHEMATICOBJECTTEMPLATE_H_
#define DRAFTSCHEMATICOBJECTTEMPLATE_H_

#include "SharedDraftSchematicObjectTemplate.h"
#include "templates/SharedTangibleObjectTemplate.h"
#include "templates/crafting/draftslot/DraftSlot.h"

class DraftSchematicObjectTemplate : public SharedDraftSchematicObjectTemplate {
protected:

	String customObjectName;

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

	bool isMagic;
	String assemblySkill;
	String experimentingSkill;
	String customizationSkill;

	Vector<String>* ingredientTemplateNames;
	Vector<String>* ingredientTitleNames;
	Vector<short>* ingredientSlotType;
	Vector<String>* ingredientAppearance;
	Vector<String>* resourceTypes;
	Vector<int>* resourceQuantities;
	Vector<short>* contribution;

	Vector<String>* additionalTemplates;

	Vector<Reference<DraftSlot* > >* draftSlots;

	SharedTangibleObjectTemplate* tangibleTemplate;

	uint32 tanoCRC;

	VectorMap<String, int> skillMods;

	Vector<VectorMap<String, int> > weaponDots;

	int labratory;

	int factoryCrateSize;

public:
	enum LabType {
		RESOURCE_LAB = 0x00,
		GENETIC_LAB = 0x01,
		DROID_LAB = 0x02
	};

	DraftSchematicObjectTemplate();

	~DraftSchematicObjectTemplate();

	void readObject(LuaObject* templateData);

	void parseVariableData(const String& varName, LuaObject* data);

	const Vector<Reference<DraftSlot* > >* getDraftSlots() const {
		return draftSlots;
	}

	void addSlot(DraftSlot* slot) {
		draftSlots->add(slot);
	}

	bool getIsMagic() const {
		return isMagic;
	}

	const String& getAssemblySkill() const {
		return assemblySkill;
	}

	short getComplexity() const {
		return complexity;
	}

	const Vector<short >* getContribution() const {
		return contribution;
	}

	int getCraftingToolTab() const {
		return craftingToolTab;
	}

	const String& getExperimentingSkill() const {
		return experimentingSkill;
	}

	const String& getCustomizationSkill() const {
		return customizationSkill;
	}

	const Vector<short >* getIngredientSlotType() const {
		return ingredientSlotType;
	}

	const Vector<String>* getIngredientAppearance() const {
		return ingredientAppearance;
	}

	const String& getIngredientAppearance(int i) const {
		return ingredientAppearance->get(i);
	}

	const Vector<String>* getIngredientTemplateNames() const {
		return ingredientTemplateNames;
	}

	const Vector<String>* getIngredientTitleNames() const {
		return ingredientTitleNames;
	}

	const Vector<int>* getResourceQuantities() const {
		return resourceQuantities;
	}

	const Vector<String>* getResourceTypes() const {
		return resourceTypes;
	}

	short getSize() const {
		return size;
	}

	uint32 getTanoCRC() const {
		return tanoCRC;
	}

	int getXp() const {
		return xp;
	}

	const String& getXpType() const {
		return xpType;
	}

	const String& getCustomObjectName() const {
		return customObjectName;
	}

	int getTemplateListSize() const {
		return additionalTemplates->size();
	}

	const String& getTemplate(int i) const {
		return additionalTemplates->get(i);
	}

	const Vector<Reference<ResourceWeight* > >* getResourceWeights();

	const VectorMap<String, int>* getSkillMods() const {
		return &skillMods;
	}

	int getSkillMod(const String& mod) const {
		return skillMods.get(mod);
	}

	const Vector<VectorMap<String, int> >* getWeaponDots() const {
		return &weaponDots;
	}

	int getLabratory() const {
		return labratory;
	}

	int getFactoryCrateSize() const {
		return factoryCrateSize;
	}

};


#endif /* DRAFTSCHEMATICOBJECTTEMPLATE_H_ */
