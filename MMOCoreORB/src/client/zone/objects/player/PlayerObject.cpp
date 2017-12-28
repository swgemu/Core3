/*
 * PlayerObject.cpp
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#include "PlayerObject.h"

#include "zone/objects/intangible/IntangibleObject.h"

namespace engine {
namespace lua {
class LuaObject;
}  // namespace lua
}  // namespace engine

PlayerObject::PlayerObject(LuaObject* templateData) : IntangibleObject(templateData) {
	setLoggingName("PlayerObject");
}
