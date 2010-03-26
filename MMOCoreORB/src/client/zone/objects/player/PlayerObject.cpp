/*
 * PlayerObject.cpp
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#include "PlayerObject.h"

PlayerObject::PlayerObject(LuaObject* templateData) : IntangibleObject(templateData) {
	setLoggingName("PlayerObject");
}
