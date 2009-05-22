/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "FeatureManager.h"

VectorMap<String, String>* FeatureManager::stringFeature = NULL;
VectorMap<String, int>* FeatureManager::intFeature = NULL;
VectorMap<String, float>* FeatureManager::floatFeature = NULL;
VectorMap<String, VectorMap<String, String>*>* FeatureManager::setFeature;

FeatureManager::FeatureManager() : Mutex(), Lua() {

	stringFeature = new VectorMap<String, String>();
	stringFeature->setInsertPlan(SortedVector<String>::NO_DUPLICATE);

	intFeature = new VectorMap<String, int>();
	intFeature->setInsertPlan(SortedVector<String>::NO_DUPLICATE);

	floatFeature = new VectorMap<String, float>();
	floatFeature->setInsertPlan(SortedVector<String>::NO_DUPLICATE);

	setFeature = new VectorMap<String, VectorMap<String, String>*>();
	setFeature->setInsertPlan(SortedVector<String>::NO_DUPLICATE);
	setFeature->setNullValue(NULL);

	init();

	if (!loadFeatures())
		System::out << "error loading Features\n";
}

void FeatureManager::init() {
	Lua::init();
	registerFunctions();
	registerGlobals();
}

void FeatureManager::registerFunctions() {
	lua_register(getLuaState(), "AddStringFeature", addStringFeature);
	lua_register(getLuaState(), "AddIntegerFeature", addIntegerFeature);
	lua_register(getLuaState(), "AddFloatFeature", addFloatFeature);
	lua_register(getLuaState(), "AddSetFeature", addSetFeature);
}

void FeatureManager::registerGlobals() {

}

FeatureManager::~FeatureManager() {
	if (stringFeature != NULL) {
		delete stringFeature;
		stringFeature = NULL;
	}

	if (floatFeature!= NULL) {
		delete floatFeature;
		floatFeature = NULL;
	}

	if (intFeature != NULL) {
		delete intFeature;
		intFeature = NULL;
	}

	if (setFeature != NULL) {
		VectorMap<String,String>* value;
		for (int i = 0 ; i < setFeature->size() ; i++) {
			VectorMapEntry<String, VectorMap<String,String>*>* entry = ((SortedVector<VectorMapEntry<String, VectorMap<String,String>*>*>*)setFeature)->get(i);

			value = entry->getValue();
			delete value;
		}
		delete setFeature;
		setFeature = NULL;
	}
}

bool FeatureManager::loadFeatures() {
	if (!runFile("features.lua")) {
		return false;
	}
	return true;
}

int FeatureManager::addStringFeature(lua_State* L) {
	int paramNum = lua_gettop(L);

	if (paramNum != 2)
		return 0;

	String key = lua_tostring(L, 1);
	String value = lua_tostring(L, 2);

	stringFeature->put(key,value);
	return 0;
}

int FeatureManager::addIntegerFeature(lua_State* L) {
	int paramNum = lua_gettop(L);

	if (paramNum != 2)
		return 0;

	String key = lua_tostring(L, 1);
	int value = lua_tointeger(L, 2);

	intFeature->put(key,value);
	return 0;
}

int FeatureManager::addFloatFeature(lua_State* L) {
	int paramNum = lua_gettop(L);

	if (paramNum != 2)
		return 0;

	String key = lua_tostring(L, 1);
	float value = lua_tonumber(L, 2);

	floatFeature->put(key,value);
	return 0;
}

int FeatureManager::addSetFeature(lua_State* L) {
	int paramNum = lua_gettop(L);

	if (paramNum < 2)
		return 0;

	String key = lua_tostring(L, 1);

	VectorMap<String, String>* featureSet;

	if (setFeature->contains(key)) {
		featureSet = setFeature->get(key);
	}
	else {
		featureSet = new VectorMap<String, String>();
		featureSet->setInsertPlan(SortedVector<String>::NO_DUPLICATE);
	}

	for (int i = 2 ; i <= paramNum; i++) {
		String value = lua_tostring(L, i);
		featureSet->put(value,"");
	}
	setFeature->put(key,featureSet);
	return 0;
}
