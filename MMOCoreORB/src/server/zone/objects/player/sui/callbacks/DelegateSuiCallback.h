/*
 * DelegateSuiCallback.h
 *
 *  Created on: 19/01/2012
 *      Author: victor
 */

#ifndef DELEGATESUICALLBACK_H_
#define DELEGATESUICALLBACK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
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

class DelegateSuiCallback : public SuiCallback {
public:
	DelegateSuiCallback(ZoneServer* serv);

	void run(server::zone::objects::creature::CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args);
};

#endif /* DELEGATESUICALLBACK_H_ */
