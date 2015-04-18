/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MOCKLUA_H_
#define MOCKLUA_H_

#include "engine/lua/Lua.h"

namespace engine {
namespace lua {

class MockLua: public Lua {
public:
	MOCK_METHOD1(runFile, bool(const String& filename));
	MOCK_METHOD1(getGlobalInt, sys::uint32(const String& name));
	MOCK_METHOD1(getGlobalString, String(const String& name));
	MOCK_METHOD0(getLuaState, lua_State*());
	MOCK_METHOD2(createFunction, LuaFunction*(const String& func, int argsThatWillReturn));
	MOCK_METHOD3(createFunction, LuaFunction*(const String& object, const String& func, int argsThatWillReturn));
	MOCK_METHOD2(setGlobalInt, void(const String& name, const int value));
};

}
}

using namespace engine::lua;

#endif /* MOCKLUA_H_ */
