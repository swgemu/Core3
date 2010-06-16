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
#include "server/zone/objects/player/PlayerCreature.h"

void CellObjectImplementation::initializeTransientMembers() {
	SceneObjectImplementation::initializeTransientMembers();

	setLoggingName("CellObject");
}

void CellObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	SceneObjectImplementation::loadTemplateData(templateData);

	containerVolumeLimit = 0xFFFFFFFF;

	containerType = 2;
}

void CellObjectImplementation::sendContainerObjectsTo(SceneObject* player) {
	//info("sending cell containers", true);
	for (int j = 0; j < containerObjects.size(); ++j) {
		SceneObject* containerObject = containerObjects.get(j);

		/*if (containerObject->isCreatureObject()
				|| (player->getRootParent() == parent) && (player->isInRange(containerObject, 128))) {*/

			//info("sending cell container contents", true);
			containerObject->sendTo(player, true);
		//}
	}
}

void CellObjectImplementation::sendBaselinesTo(SceneObject* player) {
	/*StringBuffer msg;
	msg << "sending cell number " << cellNumber << " baselines";
	info(msg.toString(), true);*/

	BaseMessage* cellMsg3 = new CellObjectMessage3(getObjectID(), cellNumber);
	player->sendMessage(cellMsg3);

	BaseMessage* cellMsg6 = new CellObjectMessage6(getObjectID());
	player->sendMessage(cellMsg6);

	BaseMessage* perm = new UpdateCellPermissionsMessage(getObjectID());
	player->sendMessage(perm);
}
