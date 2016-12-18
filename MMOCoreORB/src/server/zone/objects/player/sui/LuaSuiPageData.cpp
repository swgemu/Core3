/*
 * LuaSuiPageData.cpp
 *
 *  Created on: Nov 7, 2013
 *      Author: crush
 */

#include "LuaSuiPageData.h"
#include "server/zone/objects/player/sui/SuiPageData.h"
#include "server/zone/objects/creature/CreatureObject.h"

const char LuaSuiPageData::className[] = "LuaSuiPageData";

Luna<LuaSuiPageData>::RegType LuaSuiPageData::Register[] = {
		{ "_setObject", &LuaSuiPageData::_setObject },
		{ "_getObject", &LuaSuiPageData::_getObject },
		{ "sendTo", &LuaSuiPageData::sendTo },
		{ "sendUpdateTo", &LuaSuiPageData::sendUpdateTo },
		{ "getPageId", &LuaSuiPageData::getPageId },
		{ "setTargetNetworkId", &LuaSuiPageData::setTargetNetworkId },
		{ "getTargetNetworkId", &LuaSuiPageData::getTargetNetworkId },
		{ "setForceCloseDistance", &LuaSuiPageData::setForceCloseDistance },
		{ "setProperty", &LuaSuiPageData::setProperty },
		{ "setDefaultCallback", &LuaSuiPageData::setDefaultCallback },
		{ "addDataItem", &LuaSuiPageData::addDataItem },
		{ "clearDataSource", &LuaSuiPageData::clearDataSource },
		{ "addDataSourceContainer", &LuaSuiPageData::addDataSourceContainer },
		{ "clearDataSourceContainer", &LuaSuiPageData::clearDataSourceContainer },
		{ "addChildWidget", &LuaSuiPageData::addChildWidget },
		{ "subscribeToEvent", &LuaSuiPageData::subscribeToEvent },
		{ "subscribeToPropertyForEvent", &LuaSuiPageData::subscribeToPropertyForEvent },
		{ "setStoredData", &LuaSuiPageData::setStoredData },
		{ "getStoredData", &LuaSuiPageData::getStoredData },
		{ "deleteStoredData", &LuaSuiPageData::deleteStoredData },
		{ "getPropertyValue", &LuaSuiPageData::getPropertyValue },
		{ 0, 0 }
};

LuaSuiPageData::LuaSuiPageData(lua_State *L) {
	if (lua_isstring(L, 1))
		realObject = new SuiPageData(lua_tostring(L, 1));
	else
		realObject = static_cast<SuiPageData*>(lua_touserdata(L, 1));
}

LuaSuiPageData::~LuaSuiPageData() {
}

int LuaSuiPageData::_setObject(lua_State* L) {
	realObject = static_cast<SuiPageData*>(lua_touserdata(L, -1));

	return 0;
}

int LuaSuiPageData::_getObject(lua_State* L) {
	if (realObject == NULL)
		lua_pushnil(L);
	else
		lua_pushlightuserdata(L, realObject.get());

	return 1;
}

int LuaSuiPageData::setTargetNetworkId(lua_State* L) {
	uint64 targetId = lua_tonumber(L, -1);

	realObject->setTargetNetworkId(targetId);

	return 0;
}

int LuaSuiPageData::setForceCloseDistance(lua_State* L) {
	int dist = lua_tonumber(L, -1);

	realObject->setForceCloseDistance(dist);

	return 0;
}


int LuaSuiPageData::getPageId(lua_State* L) {
	lua_pushinteger(L, realObject->getPageId());

	return 1;
}

//const String& defaultCallback
int LuaSuiPageData::setDefaultCallback(lua_State* L) {
	String callback = lua_tostring(L, -1);

	realObject->subscribeToEvent(0x09, "", callback); // OK Button
	realObject->subscribeToEvent(0x0A, "", callback); // Cancel Button

	return 0;
}

//const String& widget, const String& property, const UnicodeString& value
int LuaSuiPageData::setProperty(lua_State* L) {
	String widget = lua_tostring(L, -3);
	String property = lua_tostring(L, -2);
	UnicodeString value = lua_tostring(L, -1);

	realObject->setProperty(widget, property, value);

	return 0;
}

//const String& widget, const String& property, const UnicodeString& value
int LuaSuiPageData::addDataItem(lua_State* L) {
	String widget = lua_tostring(L, -3);
	String property = lua_tostring(L, -2);
	UnicodeString value = lua_tostring(L, -1);

	realObject->addDataItem(widget, property, value);

	return 0;
}

int LuaSuiPageData::clearDataSource(lua_State* L) {
	String dataSource = lua_tostring(L, -1);

	realObject->clearDataSource(dataSource);

	return 0;
}

int LuaSuiPageData::addDataSourceContainer(lua_State* L) {
	String parent = lua_tostring(L, -2);
	String name = lua_tostring(L, -1);

	realObject->addDataSourceContainer(parent, name);

	return 0;
}

int LuaSuiPageData::clearDataSourceContainer(lua_State* L) {
	String dataSourceContainer = lua_tostring(L, -1);

	realObject->clearDataSourceContainer(dataSourceContainer);

	return 0;
}

int LuaSuiPageData::addChildWidget(lua_State* L) {
	String parent = lua_tostring(L, -3);
	String type = lua_tostring(L, -2);
	String name = lua_tostring(L, -1);

	realObject->addChildWidget(parent, type, name);

	return 0;
}

//const byte& eventType, const String& parent, const String& callback
int LuaSuiPageData::subscribeToEvent(lua_State* L) {
	byte eventType = lua_tonumber(L, -3);
	String parent = lua_tostring(L, -2);
	String callback = lua_tostring(L, -1);

	realObject->subscribeToEvent(eventType, parent, callback);

	return 0;
}

//const byte& eventType, const String& widget, const String& property
int LuaSuiPageData::subscribeToPropertyForEvent(lua_State* L) {
	byte eventType = lua_tonumber(L, -3);
	String widget = lua_tostring(L, -2);
	String property = lua_tostring(L, -1);

	realObject->subscribeToPropertyForEvent(eventType, widget, property);

	return 0;
}

int LuaSuiPageData::sendTo(lua_State* L) {
	CreatureObject* creo = static_cast<CreatureObject*>(lua_touserdata(L, -1));

	if (creo != NULL)
		realObject->sendTo(creo);

	return 0;
}

int LuaSuiPageData::sendUpdateTo(lua_State* L) {
	CreatureObject* creo = static_cast<CreatureObject*>(lua_touserdata(L, -1));

	if (creo != NULL)
		realObject->sendUpdateTo(creo);

	return 0;
}

int LuaSuiPageData::getTargetNetworkId(lua_State* L) {
	lua_pushinteger(L, realObject->getTargetNetworkId());

	return 1;
}

int LuaSuiPageData::getPropertyValue(lua_State* L) {
	String widget = lua_tostring(L, -2);
	String property = lua_tostring(L, -1);

	lua_pushstring(L, realObject->getPropertyValue(widget, property).toString().toCharArray());

	return 1;
}

int LuaSuiPageData::setStoredData(lua_State* L) {
	String key = lua_tostring(L, -2);
	String value = lua_tostring(L, -1);

	realObject->setStoredData(key, value);

	return 0;
}

int LuaSuiPageData::getStoredData(lua_State* L) {
	String key = lua_tostring(L, -1);

	lua_pushstring(L, realObject->getStoredData(key).toCharArray());

	return 1;
}

int LuaSuiPageData::deleteStoredData(lua_State* L) {
	String key = lua_tostring(L, -1);

	realObject->deleteStoredData(key);

	return 0;
}
