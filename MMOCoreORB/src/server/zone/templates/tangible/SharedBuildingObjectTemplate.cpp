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

	LuaObject terminalLocation = templateData->getObjectField("terminalLocation");

	if (terminalLocation.getTableSize() == 8) {
		uint8 cellnum = (uint8) terminalLocation.getIntAt(1);
		float posX = terminalLocation.getFloatAt(2);
		float posZ = terminalLocation.getFloatAt(3);
		float posY = terminalLocation.getFloatAt(4);
		float dirX = terminalLocation.getFloatAt(5);
		float dirY = terminalLocation.getFloatAt(6);
		float dirZ = terminalLocation.getFloatAt(7);
		float dirW = terminalLocation.getFloatAt(8);

		structureTerminalLocation = new StructureTerminalLocation(cellnum, posX, posZ, posY, dirX, dirY, dirZ, dirW);
	}

	terminalLocation.pop();

	cityRankRequired = templateData->getByteField("cityRankRequired");

	//TODO: Abilities and skills required
}
