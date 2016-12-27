/*
 * IntangibleObject.h
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#ifndef INTANGIBLEOBJECT_H_
#define INTANGIBLEOBJECT_H_

#include "client/zone/objects/scene/SceneObject.h"

class IntangibleObject : public SceneObject {
public:
	IntangibleObject(LuaObject* templateData);
};

#endif /* INTANGIBLEOBJECT_H_ */
