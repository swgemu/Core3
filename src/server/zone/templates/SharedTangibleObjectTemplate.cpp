/*
 * SharedTangibleObjectTemplate.cpp
 *
 *  Created on: 30/04/2010
 *      Author: victor
 */

#include "SharedTangibleObjectTemplate.h"

SharedTangibleObjectTemplate::SharedTangibleObjectTemplate() {

	numberExperimentalProperties = new Vector<short>();
	experimentalProperties = new Vector<String>();
	experimentalWeights = new Vector<short>();
	experimentalGroupTitles = new Vector<String>();
	experimentalSubGroupTitles = new Vector<String>();
	experimentalMin = new Vector<int>();
	experimentalMax = new Vector<int>();
	experimentalPrecision = new Vector<short>();

	resourceWeights = new Vector<Reference<ResourceWeight* > >();
}

SharedTangibleObjectTemplate::~SharedTangibleObjectTemplate() {

	delete numberExperimentalProperties;
	delete experimentalProperties;
	delete experimentalWeights;
	delete experimentalGroupTitles;
	delete experimentalSubGroupTitles;
	delete experimentalMin;
	delete experimentalMax;
	delete experimentalPrecision;

	delete resourceWeights;
}

void SharedTangibleObjectTemplate::readObject(LuaObject* templateData) {
	SharedObjectTemplate::readObject(templateData);

	LuaObject certifications = templateData->getObjectField("certificationsRequired");

	for (int i = 1; i <= certifications.getTableSize(); ++i) {
		certificationsRequired.add(certifications.getStringAt(i));
	}

	certifications.pop();

	structureFootprintFileName = templateData->getStringField("structureFootprintFileName");

	targetable = templateData->getByteField("targetable");

	playerUseMask = templateData->getShortField("playerUseMask");

	useCount = templateData->getIntField("useCount");

	maxCondition = templateData->getIntField("maxCondition");
	level = templateData->getIntField("level");

	optionsBitmask = templateData->getIntField("optionsBitmask");
	pvpStatusBitmask = templateData->getIntField("pvpStatusBitmask");

	sliceable = templateData->getIntField("sliceable");

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
}
