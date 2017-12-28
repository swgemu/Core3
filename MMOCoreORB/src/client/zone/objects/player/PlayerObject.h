/*
 * PlayerObject.h
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#ifndef PLAYEROBJECT_H_
#define PLAYEROBJECT_H_

#include "client/zone/objects/intangible/IntangibleObject.h"

namespace engine {
namespace lua {
class LuaObject;
}  // namespace lua
}  // namespace engine

class PlayerObject : public IntangibleObject {
public:
	PlayerObject(LuaObject* templateData);
};


#endif /* PLAYEROBJECT_H_ */
