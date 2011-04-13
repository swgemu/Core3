/*
 * TangibleObject.h
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#ifndef TANGIBLEOBJECT_H_
#define TANGIBLEOBJECT_H_

#include "engine/engine.h"

#include "../scene/SceneObject.h"

class TangibleObject : public SceneObject {
	float complexity;

	int volume;

	String custString;

	uint32 optionsBitmask;

	int count;

	int conditionDamage;
	int maxCondition;

	byte unknown;
public:
	TangibleObject(LuaObject* templateData);

	void parseBaseline3(Message* message);
	void parseBaseline6(Message* message);
};


#endif /* TANGIBLEOBJECT_H_ */
