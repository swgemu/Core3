/*
 * VendorInfoCommand.h
 *
 *  Created on: Apr 6, 2011
 *      Author: polonel
 */

#ifndef VENDORINFOCOMMAND_H_
#define VENDORINFOCOMMAND_H_

#include "engine/engine.h"
#include "server/zone/managers/vendor/VendorManager.h"
#include "server/zone/managers/auction/AuctionManager.h"
#include "server/zone/managers/auction/AuctionsMap.h"

class VendorInfoCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		if (!creature->isPlayerCreature())
			return 1;


		return 0;
	}

};

#endif /* VENDORINFOCOMMAND_H_ */
