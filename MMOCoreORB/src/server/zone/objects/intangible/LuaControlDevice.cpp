#include "LuaControlDevice.h"
#include "ControlDevice.h"

const char LuaControlDevice::className[] = "LuaControlDevice";

Luna<LuaControlDevice>::RegType LuaControlDevice::Register[] = {
		{ "_setObject", &LuaControlDevice::_setObject },
		{ "setControlledObject", &LuaControlDevice::setControlledObject },
		{ "getControlledObject", &LuaControlDevice::getControlledObject },
		{ 0, 0 }
};


LuaControlDevice::LuaControlDevice(lua_State *L) : LuaIntangibleObject(L) {
	realObject = (ControlDevice*)lua_touserdata(L, 1);
}

LuaControlDevice::~LuaControlDevice() {
}

int LuaControlDevice::_setObject(lua_State* L) {
	realObject = (ControlDevice*)lua_touserdata(L, -1);

	return 0;
}

int LuaControlDevice::setControlledObject(lua_State* L) {
	TangibleObject* obj = (TangibleObject*)lua_tostring(L, -1);

	realObject->setControlledObject(obj);

	return 0;
}

int LuaControlDevice::getControlledObject(lua_State* L) {
	TangibleObject* obj = realObject->getControlledObject();

	if (obj == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, obj);
	}

	return 1;
}
