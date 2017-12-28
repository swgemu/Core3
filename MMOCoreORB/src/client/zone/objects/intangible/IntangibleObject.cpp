/*
 * IntangibleObject.cpp
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#include "IntangibleObject.h"

#include "zone/objects/scene/SceneObject.h"

namespace engine {
namespace lua {
class LuaObject;
}  // namespace lua
}  // namespace engine

IntangibleObject::IntangibleObject(LuaObject* templateData) : SceneObject(templateData) {
	setLoggingName("IntangibleObject");
}
