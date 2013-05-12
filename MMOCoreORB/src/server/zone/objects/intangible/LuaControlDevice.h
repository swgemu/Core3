#ifndef LUACONTROLDEVICE_H_
#define LUACONTROLDEVICE_H_

#include "LuaIntangibleObject.h"

#include "ControlDevice.h"

class LuaControlDevice : public LuaIntangibleObject {
public:
	// Constants
	static const char className[];
	static Luna<LuaControlDevice>::RegType Register[];

	// Initialize the pointer
	LuaControlDevice(lua_State *L);
	~LuaControlDevice();

	int _setObject(lua_State* L);
	// Methods we will need to use
	int setControlledObject(lua_State* L);
	int getControlledObject(lua_State* L);

private:
	// The pointer to the 'real object' defined in object.cc
	Reference<ControlDevice*> realObject;
};


#endif /* LUACONTROLDEVICE_H_ */
