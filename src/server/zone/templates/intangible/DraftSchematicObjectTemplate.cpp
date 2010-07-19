/*
 * SharedDraftSchematicObjectTemplate.cpp
 *
 *  Created on: 06/05/2010
 *      Author: kyle
 */

#include "DraftSchematicObjectTemplate.h"

DraftSchematicObjectTemplate::DraftSchematicObjectTemplate() {
	customizationOptions = new Vector<byte>();
	customizationDefaultValues = new Vector<byte>();
	customizationStringNames = new Vector<String>();

	ingredientTemplateNames = new Vector<String>();
	ingredientTitleNames = new Vector<String>();
	ingredientSlotType = new Vector<short>();
	resourceTypes = new Vector<String>();
	resourceQuantities = new Vector<int>();
	combineTypes = new Vector<short>();
	contribution = new Vector<short>();

	numberExperimentalProperties = new Vector<short>();
	experimentalProperties = new Vector<String>();
	experimentalWeights = new Vector<short>();
	experimentalGroupTitles = new Vector<String>();
	experimentalSubGroupTitles = new Vector<String>();
	experimentalMin = new Vector<int>();
	experimentalMax = new Vector<int>();
	experimentalPrecision = new Vector<short>();

	draftSlots = new Vector<Reference<DraftSlot* > >();
	resourceWeights = new Vector<Reference<ResourceWeight* > >();
}

DraftSchematicObjectTemplate::~DraftSchematicObjectTemplate() {
	while(draftSlots->size() > 0)
		delete draftSlots->remove(0);

	while(resourceWeights->size() > 0)
		delete resourceWeights->remove(0);

	delete customizationOptions;
	delete customizationDefaultValues;
	delete customizationStringNames;

	delete ingredientTemplateNames;
	delete ingredientTitleNames;
	delete ingredientSlotType;
	delete resourceTypes;
	delete resourceQuantities;
	delete combineTypes;
	delete contribution;

	delete numberExperimentalProperties;
	delete experimentalProperties;
	delete experimentalWeights;
	delete experimentalGroupTitles;
	delete experimentalSubGroupTitles;
	delete experimentalMin;
	delete experimentalMax;
	delete experimentalPrecision;

	delete draftSlots;
	delete resourceWeights;
}

void DraftSchematicObjectTemplate::readObject(LuaObject* templateData) {
	SharedDraftSchematicObjectTemplate::readObject(templateData);

	customObjectName = templateData->getStringField("customObjectName");

	groupName = templateData->getStringField("groupName");

	craftingToolTab = templateData->getIntField("craftingToolTab");
	complexity = templateData->getShortField("complexity");
	size = templateData->getShortField("size");

	xpType = templateData->getStringField("xpType");
	xp = templateData->getIntField("xp");

	assemblySkill = templateData->getStringField("assemblySkill");
	experimentingSkill = templateData->getStringField("experimentingSkill");
	customizationSkill = templateData->getStringField("customizationSkill");

	LuaObject customizationOptionsList = templateData->getObjectField("customizationOptions");
	for (int i = 1; i <= customizationOptionsList.getTableSize(); ++i) {
		customizationOptions->add(customizationOptionsList.getIntAt(i));
	}
	customizationOptionsList.pop();

	LuaObject customizationStringNamesList = templateData->getObjectField("customizationStringNames");
	for (int i = 1; i <= customizationStringNamesList.getTableSize(); ++i) {
		customizationStringNames->add(customizationStringNamesList.getStringAt(i));
	}
	customizationStringNamesList.pop();

	LuaObject customizationDefaultValuesList = templateData->getObjectField("customizationDefaults");
	for (int i = 1; i <= customizationDefaultValuesList.getTableSize(); ++i) {
		customizationDefaultValues->add(customizationDefaultValuesList.getIntAt(i));
	}
	customizationDefaultValuesList.pop();

	LuaObject ingredientTemplateNamesList = templateData->getObjectField("ingredientTemplateNames");
	for (int i = 1; i <= ingredientTemplateNamesList.getTableSize(); ++i) {
		ingredientTemplateNames->add(ingredientTemplateNamesList.getStringAt(i));
	}
	ingredientTemplateNamesList.pop();

	LuaObject ingredientTitleNamesList = templateData->getObjectField("ingredientTitleNames");
	for (int i = 1; i <= ingredientTitleNamesList.getTableSize(); ++i) {
		ingredientTitleNames->add(ingredientTitleNamesList.getStringAt(i));
	}
	ingredientTitleNamesList.pop();

	LuaObject ingredientSlotTypeList = templateData->getObjectField("ingredientSlotType");
	for (int i = 1; i <= ingredientSlotTypeList.getTableSize(); ++i) {
		ingredientSlotType->add(ingredientSlotTypeList.getIntAt(i));
	}
	ingredientSlotTypeList.pop();

	LuaObject resourceTypesList = templateData->getObjectField("resourceTypes");
	for (int i = 1; i <= resourceTypesList.getTableSize(); ++i) {
		resourceTypes->add(resourceTypesList.getStringAt(i));
	}
	resourceTypesList.pop();

	LuaObject resourceQuantitiesList = templateData->getObjectField("resourceQuantities");
	for (int i = 1; i <= resourceQuantitiesList.getTableSize(); ++i) {
		resourceQuantities->add(resourceQuantitiesList.getIntAt(i));
	}
	resourceQuantitiesList.pop();

	LuaObject combineTypesList = templateData->getObjectField("combineTypes");
	for (int i = 1; i <= combineTypesList.getTableSize(); ++i) {
		combineTypes->add(combineTypesList.getIntAt(i));
	}
	combineTypesList.pop();

	LuaObject contributionList = templateData->getObjectField("contribution");
	for (int i = 1; i <= contributionList.getTableSize(); ++i) {
		contribution->add(contributionList.getIntAt(i));
	}
	contributionList.pop();

	for (int i = 0; i < ingredientTemplateNames->size(); ++i) {
		DraftSlot* newSlot = new DraftSlot();
		newSlot->setStringId(ingredientTemplateNames->get(i),ingredientTitleNames->get(i));
		newSlot->setSlotType(ingredientSlotType->get(i));
		newSlot->setResourceType(resourceTypes->get(i));
		newSlot->setQuantity(resourceQuantities->get(i));
		newSlot->setCombineType(combineTypes->get(i));
		newSlot->setContribution(contribution->get(i));

		addSlot(newSlot);
	}

	LuaObject numberExperimentalPropertiesList = templateData->getObjectField("numberExperimentalProperties");
	for (int i = 1; i <= numberExperimentalPropertiesList.getTableSize(); ++i) {
		numberExperimentalProperties->add(
				numberExperimentalPropertiesList.getIntAt(i));
	}
	numberExperimentalPropertiesList.pop();

	LuaObject experimentalPropertiesList = templateData->getObjectField("experimentalProperties");
	for (int i = 1; i <= experimentalPropertiesList.getTableSize(); ++i) {
		experimentalProperties->add(experimentalPropertiesList.getStringAt(i));
	}
	experimentalPropertiesList.pop();

	LuaObject experimentalWeightsList = templateData->getObjectField("experimentalWeights");
	for (int i = 1; i <= experimentalWeightsList.getTableSize(); ++i) {
		experimentalWeights->add(experimentalWeightsList.getIntAt(i));
	}
	experimentalWeightsList.pop();

	LuaObject experimentalGroupTitlesList = templateData->getObjectField("experimentalGroupTitles");
	for (int i = 1; i <= experimentalGroupTitlesList.getTableSize(); ++i) {
		experimentalGroupTitles->add(experimentalGroupTitlesList.getStringAt(i));
	}
	experimentalGroupTitlesList.pop();

	LuaObject experimentalSubGroupTitlesList = templateData->getObjectField("experimentalSubGroupTitles");
	for (int i = 1; i <= experimentalSubGroupTitlesList.getTableSize(); ++i) {
		experimentalSubGroupTitles->add(
				experimentalSubGroupTitlesList.getStringAt(i));
	}
	experimentalSubGroupTitlesList.pop();

	LuaObject experimentalMinList = templateData->getObjectField("experimentalMin");
	for (int i = 1; i <= experimentalMinList.getTableSize(); ++i) {
		experimentalMin->add(experimentalMinList.getIntAt(i));
	}
	experimentalMinList.pop();

	LuaObject experimentalMaxList = templateData->getObjectField("experimentalMax");
	for (int i = 1; i <= experimentalMaxList.getTableSize(); ++i) {
		experimentalMax->add(experimentalMaxList.getIntAt(i));
	}
	experimentalMaxList.pop();

	LuaObject experimentalPrecisionList = templateData->getObjectField("experimentalPrecision");
	for (int i = 1; i <= experimentalPrecisionList.getTableSize(); ++i) {
		experimentalPrecision->add(experimentalPrecisionList.getIntAt(i));
	}
	experimentalPrecisionList.pop();

	// Add experimental properties groups to the draft schematic
	uint32 weightIterator = 0;
	String subtitle = "";
	for (uint32 i = 0; i < numberExperimentalProperties->size(); i++) {

		ResourceWeight* newWeight = new ResourceWeight();

		newWeight->addProperties(experimentalGroupTitles->get(i),
				experimentalSubGroupTitles->get(i), experimentalMin->get(i),
				experimentalMax->get(i), experimentalPrecision->get(i));

		for (uint32 j = 0; j < numberExperimentalProperties->get(i); j++) {

			newWeight->addWeight(experimentalProperties->get(weightIterator),
					experimentalWeights->get(weightIterator));

			weightIterator++;
		}

		addResourceWeight(newWeight);
	}

	tanoCRC = templateData->getIntField("tanoCRC");
}
