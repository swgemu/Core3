/*
 * CellObjectImplementation.cpp
 *
 *  Created on: 23/07/2009
 *      Author: TheAnswer
 */

#include "CellObject.h"
#include "server/zone/packets/cell/CellObjectMessage3.h"
#include "server/zone/packets/cell/CellObjectMessage6.h"
#include "server/zone/packets/cell/UpdateCellPermissionsMessage.h"

CellObjectImplementation::CellObjectImplementation(LuaObject* templateData) :
	SceneObjectImplementation(templateData) {

	setLoggingName("CellObject");

	cellNumber = 0;

	containerVolumeLimit = 0xFFFFFFFF;

	containerType = 2;
}

void CellObjectImplementation::sendBaselinesTo(SceneObject* player) {
	info("sending cell baselines");

	BaseMessage* cellMsg3 = new CellObjectMessage3(objectID, cellNumber);
	player->sendMessage(cellMsg3);

	BaseMessage* cellMsg6 = new CellObjectMessage6(objectID);
	player->sendMessage(cellMsg6);

	BaseMessage* perm = new UpdateCellPermissionsMessage(objectID);
	player->sendMessage(perm);
}
