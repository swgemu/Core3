/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "StringIdParameter.h"

#include "StringId.h"
#include "server/zone/objects/scene/SceneObject.h"

StringIdParameter::StringIdParameter(const StringIdParameter& par) : Object(), Serializable() {
	addSerializableVariables();

	pointerParameter = par.pointerParameter;
	stringID = par.stringID;
	customName = par.customName;
}

#ifdef CXX11_COMPILER
StringIdParameter::StringIdParameter(StringIdParameter&& par) : Object(), Serializable(),
		pointerParameter(par.pointerParameter), stringID(std::move(par.stringID)),
		customName(std::move(par.customName)) {
	addSerializableVariables();
}
#endif


void StringIdParameter::set(SceneObject* obj) {
	clear();

	pointerParameter = obj->getObjectID();
}

void StringIdParameter::set(StringId* sid) {
	set(*sid);
}

void StringIdParameter::set(StringId& sid) {
	clear();

	stringID = sid;
}
