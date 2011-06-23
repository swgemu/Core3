/*
 * DestroyStructureCodeSuiCallback.h
 *
 *  Created on: Jun 22, 2011
 *      Author: crush
 */

#ifndef DESTROYSTRUCTURECODESUICALLBACK_H_
#define DESTROYSTRUCTURECODESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"


class DestroyStructureCodeSuiCallback : public SuiCallback {
public:
	DestroyStructureCodeSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(PlayerCreature* player, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		player->sendSystemMessage("Hello world");
	}
};

#endif /* DESTROYSTRUCTURECODESUICALLBACK_H_ */
