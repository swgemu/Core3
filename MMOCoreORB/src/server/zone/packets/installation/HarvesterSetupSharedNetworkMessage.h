/*
 * HarvesterSetupSharedNetworkMessage.h
 *
 *  Created on: Oct 7, 2008
 *      Author: swgemu
 */

#ifndef HARVESTERSETUPSHAREDNETWORKMESSAGE_H_
#define HARVESTERSETUPSHAREDNETWORKMESSAGE_H_

#include "server/zone/packets/object/ObjectControllerMessage.h"
#include "server/zone/objects/installation/InstallationObject.h"

class HarvesterSetupSharedNetworkMessage : public ObjectControllerMessage {
public:
	HarvesterSetupSharedNetworkMessage(InstallationObject* inso)
		: ObjectControllerMessage(inso->getObjectID(), 0x1B, 0x022B) {

	}
};

#endif /* HARVESTERSETUPSHAREDNETWORKMESSAGE_H_ */
