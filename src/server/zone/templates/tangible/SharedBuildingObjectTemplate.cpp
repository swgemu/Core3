/*
 * SharedBuildingObjectTemplate.cpp
 *
 *  Created on: 05/05/2010
 *      Author: victor
 */

#include "SharedBuildingObjectTemplate.h"


void SharedBuildingObjectTemplate::readObject(LuaObject* templateData) {
	SharedTangibleObjectTemplate::readObject(templateData);

	terrainModificationFileName = templateData->getStringField("terrainModificationFileName");
	interiorLayoutFileName = templateData->getStringField("interiorLayoutFileName");
}
