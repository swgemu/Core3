/*
 * CellObjectImplementation.cpp
 *
 *  Created on: 23/07/2009
 *      Author: TheAnswer
 */

#include "CellObject.h"

CellObjectImplementation::CellObjectImplementation(LuaObject* templateData) :
	SceneObjectImplementation(templateData) {

	setLoggingName("CellObject");

	cellNumber = 0;

	containerVolumeLimit = 0xFFFFFFFF;

	containerType = 2;
}
