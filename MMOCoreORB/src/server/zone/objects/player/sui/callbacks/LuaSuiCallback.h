/*
 * LuaSuiCallback.h
 *
 *  Created on: Jan 28, 2012
 *      Author: xyborn
 */

#ifndef LUASUICALLBACK_H_
#define LUASUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/creature/CreatureObject.h"

class LuaSuiCallback : public SuiCallback {
	String screenPlay;
	String screenPlayCallback;

public:
	LuaSuiCallback(ZoneServer* zserv, const String& play, const String& callback) : SuiCallback(zserv) {
		screenPlay = play;
		screenPlayCallback = callback;
	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args);
};

#endif /* LUASUICALLBACK_H_ */
