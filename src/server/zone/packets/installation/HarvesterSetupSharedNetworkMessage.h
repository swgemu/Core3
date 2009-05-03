/*
 * HarvesterSetupSharedNetworkMessage.h
 *
 *  Created on: Oct 7, 2008
 *      Author: swgemu
 */

#ifndef HARVESTERSETUPSHAREDNETWORKMESSAGE_H_
#define HARVESTERSETUPSHAREDNETWORKMESSAGE_H_

#include "../object/ObjectControllerMessage.h"

class HarvesterSetupSharedNetworkMessage : public ObjectControllerMessage {
public:
	HarvesterSetupSharedNetworkMessage(Player* player, InstallationObject* inso)
		: HarvesterSetupSharedNetworkMessage(inso->getObjectID(), 0x1B, 0x022B) {

	}

#endif /* HARVESTERSETUPSHAREDNETWORKMESSAGE_H_ */
