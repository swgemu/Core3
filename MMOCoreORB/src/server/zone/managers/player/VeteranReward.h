/*
 * VeteranReward.h
 *
 *  Created on: 5/22/2014
 *      Author: Klivian
 */

#ifndef VETERANREWARD_H_
#define VETERANREWARD_H_

class VeteranReward : public Object {

protected:
	String templateFile;
	unsigned int milestone; // days
	bool oneTime;
	String description;
	bool jtlReward;

public:
	VeteranReward() {
		milestone = 0;
		oneTime = false;
		jtlReward = false;
	}

	VeteranReward(const VeteranReward& obj) : Object() {
		templateFile = obj.templateFile;
		milestone = obj.milestone;
		oneTime = obj.oneTime;
		description = obj.description;
		jtlReward = obj.jtlReward;
	}

	VeteranReward& operator=(const VeteranReward& obj) {
		if (this == &obj)
			return *this;

		templateFile = obj.templateFile;
		milestone = obj.milestone;
		oneTime = obj.oneTime;
		description = obj.description;
		jtlReward = obj.jtlReward;

		return *this;
	}

	void parseFromLua(LuaObject* luaObject) {
		templateFile = luaObject->getStringField("templateFile");
		milestone = luaObject->getIntField("milestone");
		oneTime = luaObject->getBooleanField("oneTime");
		description = luaObject->getStringField("description");
		jtlReward = luaObject->getBooleanField("jtlReward");
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

	inline void setJtlReward(bool val) {
		jtlReward = val;
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

	inline bool isJtlReward() {
		return jtlReward;
	}
};

#endif /* VETERANREWARD_H_ */
