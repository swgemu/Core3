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
	StringBuffer msg;
	msg << "sending cell number " << cellNumber << " baselines";
	info(msg.toString());

	BaseMessage* cellMsg3 = new CellObjectMessage3(getObjectID(), cellNumber);
	player->sendMessage(cellMsg3);

	BaseMessage* cellMsg6 = new CellObjectMessage6(getObjectID());
	player->sendMessage(cellMsg6);

	BaseMessage* perm = new UpdateCellPermissionsMessage(getObjectID());
	player->sendMessage(perm);
}
