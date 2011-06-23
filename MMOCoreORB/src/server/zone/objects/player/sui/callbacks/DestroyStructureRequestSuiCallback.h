/*
 * DestroyStructureRequestSuiCallback.h
 *
 *  Created on: Jun 22, 2011
 *      Author: crush
 */

#ifndef DESTROYSTRUCTUREREQUESTSUICALLBACK_H_
#define DESTROYSTRUCTUREREQUESTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"


class DestroyStructureRequestSuiCallback : public SuiCallback {
public:
	DestroyStructureRequestSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(PlayerCreature* player, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
	}
};

#endif /* DESTROYSTRUCTUREREQUESTSUICALLBACK_H_ */
