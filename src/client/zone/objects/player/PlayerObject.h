/*
 * PlayerObject.h
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#ifndef PLAYEROBJECT_H_
#define PLAYEROBJECT_H_

#include "engine/engine.h"
#include "../intangible/IntangibleObject.h"

class PlayerObject : public IntangibleObject {
public:
	PlayerObject(LuaObject* templateData);
};


#endif /* PLAYEROBJECT_H_ */
