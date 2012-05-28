/*
 * AiTemplate.h
 *
 *  Created on: May 17, 2012
 *      Author: da
 */

#ifndef AITEMPLATE_H_
#define AITEMPLATE_H_

#include "engine/engine.h"

class AiTemplate : public Object {
	String templateName;

	VectorMap<String, String> transitions;
	String defaultStateName;

public:
	AiTemplate(const String& name) {
		templateName = name;

		transitions.setNoDuplicateInsertPlan();
		transitions.setNullValue("");
	}

	AiTemplate(const AiTemplate& ait) : Object() {
		templateName = ait.templateName;

		transitions.setNoDuplicateInsertPlan();
		transitions.setNullValue("");

		transitions = ait.transitions;
	}

	AiTemplate& operator=(const AiTemplate& ait) {
		if (this == &ait)
			return *this;

		templateName = ait.templateName;
		transitions = ait.transitions;

		return *this;
	}

	void readObject(LuaObject* lua) {
		defaultStateName = lua->getStringField("defaultState");
		LuaObject rules = lua->getObjectField("transitions");

		if (!rules.isValidTable())
			return;

		lua_State* L = lua->getLuaState();

		for (int i = 1; i <= rules.getTableSize(); ++i) {
			lua_rawgeti(L, -1, i);
			LuaObject rule(L);

			String current = rule.getStringAt(1);
			uint16 msg = rule.getIntAt(2);
			String next = rule.getStringAt(3);

			transitions.put(current + msg, next);

			rule.pop();
		}

		rules.pop();
	}

	String& getTemplateName() {
		return templateName;
	}

	VectorMap<String, String> getTransitions() {
		return transitions;
	}

	String& getDefaultName() {
		return defaultStateName;
	}
};

#endif /* AITEMPLATE_H_ */
