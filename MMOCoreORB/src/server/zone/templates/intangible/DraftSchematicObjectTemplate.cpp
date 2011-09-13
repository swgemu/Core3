/*
 * SharedDraftSchematicObjectTemplate.cpp
 *
 *  Created on: 06/05/2010
 *      Author: kyle
 */

#include "DraftSchematicObjectTemplate.h"
#include "server/zone/managers/templates/TemplateManager.h"

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

	draftSlots = new Vector<Reference<DraftSlot* > >();

	additionalTemplates = new Vector<String>();

	tangibleTemplate = NULL;

	tanoCRC = 0;
}

DraftSchematicObjectTemplate::~DraftSchematicObjectTemplate() {
	/*while(draftSlots->size() > 0)
		delete draftSlots->remove(0);

	while(resourceWeights->size() > 0)
		delete resourceWeights->remove(0);*/

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

	delete additionalTemplates;

	delete draftSlots;

}

void DraftSchematicObjectTemplate::readObject(LuaObject* templateData) {
	SharedDraftSchematicObjectTemplate::readObject(templateData);

	customObjectName = templateData->getStringField("customObjectName");

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

	tanoCRC = templateData->getStringField("targetTemplate").hashCode();

	LuaObject availableTemplateList = templateData->getObjectField("additionalTemplates");
	for (int i = 1; i <= availableTemplateList.getTableSize(); ++i) {
		additionalTemplates->add(availableTemplateList.getStringAt(i));
	}
	contributionList.pop();
}


Vector<Reference<ResourceWeight* > >* DraftSchematicObjectTemplate::getResourceWeights() {

	try {
		if (tangibleTemplate == NULL)
			tangibleTemplate
					= dynamic_cast<SharedTangibleObjectTemplate*> (TemplateManager::instance()->getTemplate(
							tanoCRC));

		if (tangibleTemplate == NULL) {
			Logger::console.error("Template not found for server crc: " + additionalTemplates->get(0));
			return NULL;
		}
	} catch (...) {
		Logger::console.error("Unhandled exception in DraftSchematicObjectTemplate::getResourceWeights");
		return NULL;
	}

	return tangibleTemplate->getResourceWeights();


}
