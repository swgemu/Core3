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
	String description;

public:
	VeteranReward() {
		milestone = 0;
		oneTime = false;
	}

	VeteranReward(const VeteranReward& obj) : Object() {
		templateFile = obj.templateFile;
		milestone = obj.milestone;
		oneTime = obj.oneTime;
		description = obj.description;
	}

	VeteranReward& operator=(const VeteranReward& obj) {
		if (this == &obj)
			return *this;

		templateFile = obj.templateFile;
		milestone = obj.milestone;
		oneTime = obj.oneTime;
		description = obj.description;

		return *this;
	}

	void parseFromLua(LuaObject* luaObject) {
		templateFile = luaObject->getStringField("templateFile");
		milestone = luaObject->getIntField("milestone");
		oneTime = luaObject->getBooleanField("oneTime");
		description = luaObject->getStringField("description");
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

	inline void setDescription( const String& desc ){
		description = desc;
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

	inline String& getDescription(){
		return description;
	}

};

#endif /* VETERANREWARD_H_ */
