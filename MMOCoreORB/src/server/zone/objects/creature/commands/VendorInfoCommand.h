/*
 * VendorInfoCommand.h
 *
 *  Created on: Apr 6, 2011
 *      Author: polonel
 */

#ifndef VENDORINFOCOMMAND_H_
#define VENDORINFOCOMMAND_H_

#include "engine/engine.h"

class VendorInfoCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		if (!creature->isPlayerCreature())
			return 1;


		return 0;
	}

};

#endif /* VENDORINFOCOMMAND_H_ */
