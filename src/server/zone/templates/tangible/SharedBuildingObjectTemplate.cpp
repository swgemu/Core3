/*
 * SharedBuildingObjectTemplate.cpp
 *
 *  Created on: 05/05/2010
 *      Author: victor
 */

#include "SharedBuildingObjectTemplate.h"


void SharedBuildingObjectTemplate::readObject(LuaObject* templateData) {
	SharedStructureObjectTemplate::readObject(templateData);

	terrainModificationFileName = templateData->getStringField("terrainModificationFileName");
	interiorLayoutFileName = templateData->getStringField("interiorLayoutFileName");

	LuaObject signObject = templateData->getObjectField("sign");
	ChildObject object;
	object.parseFromLua(&signObject);
	sign = object;
	signObject.pop();

	publicStructure = (bool) templateData->getByteField("publicStructure");

	alwaysPublic = (bool) templateData->getByteField("alwaysPublic");
}
