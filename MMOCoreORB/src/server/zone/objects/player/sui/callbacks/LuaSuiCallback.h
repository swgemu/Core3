/*
 * LuaSuiCallback.h
 *
 *  Created on: Jan 28, 2012
 *      Author: xyborn
 */

#ifndef LUASUICALLBACK_H_
#define LUASUICALLBACK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "system/lang/String.h"
#include "system/platform.h"

namespace server {
namespace zone {
class ZoneServer;
namespace objects {
namespace creature {
class CreatureObject;
}  // namespace creature
namespace player {
namespace sui {
class SuiBox;
}  // namespace sui
}  // namespace player
}  // namespace objects
}  // namespace zone
}  // namespace server
namespace sys {
namespace lang {
class UnicodeString;
}  // namespace lang
namespace util {
template <class E> class Vector;
}  // namespace util
}  // namespace sys

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
