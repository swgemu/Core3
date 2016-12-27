/*
 * SignTemplate.h
 *
 *  Created on: 3/15/2014
 *      Author: Klivian
 */

#ifndef SIGNTEMPLATE_H_
#define SIGNTEMPLATE_H_

#include "templates/ChildObject.h"

class SignTemplate : public ChildObject {

	String requiredSkill;
	String suiItem;

public:
	SignTemplate() : ChildObject() {

	}

	SignTemplate(const SignTemplate& obj) : ChildObject( obj ) {
		requiredSkill = obj.requiredSkill;
		suiItem = obj.suiItem;
	}

	SignTemplate& operator=(const SignTemplate& obj) {
		if (this == &obj)
			return *this;

		position = obj.position;
		direction = obj.direction;
		templateFile = obj.templateFile;
		cellid = obj.cellid;
		containmentType = obj.containmentType;
		requiredSkill = obj.requiredSkill;
		suiItem = obj.suiItem;

		return *this;
	}

	void parseFromLua(LuaObject* luaObject) {
		ChildObject::parseFromLua(luaObject);
		requiredSkill = luaObject->getStringField("requiredSkill");
		suiItem = luaObject->getStringField("suiItem");
	}

	inline String& getSuiItem() {
		return suiItem;
	}

	inline String& getRequiredSkill() {
		return requiredSkill;
	}

};

#endif /* SIGNTEMPLATE_H_ */
