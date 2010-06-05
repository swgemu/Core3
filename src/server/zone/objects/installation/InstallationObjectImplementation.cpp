/*
 * InstallationObjectImplementation.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: crush
 */

#include "InstallationObject.h"
#include "server/zone/packets/installation/InstallationObjectMessage3.h"
#include "server/zone/packets/installation/InstallationObjectMessage6.h"

void InstallationObjectImplementation::sendBaselinesTo(SceneObject* player) {
	//send buios here
	info("sending installation baselines");

	BaseMessage* buio3 = new InstallationObjectMessage3(_this);
	player->sendMessage(buio3);

	BaseMessage* buio6 = new InstallationObjectMessage6(_this);
	player->sendMessage(buio6);
}
