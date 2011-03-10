/*
 * SharedTangibleObjectTemplate.cpp
 *
 *  Created on: 30/04/2010
 *      Author: victor
 */

#include "SharedTangibleObjectTemplate.h"

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
}
