/*
 * VeteranReward.h
 *
 *  Created on: 5/22/2014
 *      Author: Klivian
 */

#ifndef VETERANREWARD_H_
#define VETERANREWARD_H_

#include "engine/engine.h"

class VeteranReward : public Object {

protected:
	String templateFile;
	unsigned int milestone; // days
	bool oneTime;

public:
	VeteranReward() {
		milestone = 0;
		oneTime = false;
	}

	VeteranReward(const VeteranReward& obj) : Object() {
		templateFile = obj.templateFile;
		milestone = obj.milestone;
		oneTime = obj.oneTime;
	}

	VeteranReward& operator=(const VeteranReward& obj) {
		if (this == &obj)
			return *this;

		templateFile = obj.templateFile;
		milestone = obj.milestone;
		oneTime = obj.oneTime;

		return *this;
	}

	void parseFromLua(LuaObject* luaObject) {
		templateFile = luaObject->getStringField("templateFile");
		milestone = luaObject->getIntField("milestone");
		oneTime = luaObject->getBooleanField("oneTime");
	}

	inline void setTemplateFile(const String& file) {
		templateFile = file;
	}

	inline void setMilestone(unsigned int days) {
		milestone = days;
	}

	inline void setOneTime(bool flag) {
		oneTime = flag;
	}

	inline String& getTemplateFile() {
		return templateFile;
	}

	inline unsigned int getMilestone() {
		return milestone;
	}

	inline bool isOneTime() {
		return oneTime;
	}

};

#endif /* VETERANREWARD_H_ */
