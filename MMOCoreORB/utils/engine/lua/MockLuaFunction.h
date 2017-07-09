/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MOCKLUAFUNCTION_H_
#define MOCKLUAFUNCTION_H_

#include "engine/lua/LuaFunction.h"

namespace engine {
namespace lua {

class MockLuaFunction: public LuaFunction {
public:

	MOCK_METHOD0(callFunction, lua_State*());
	MOCK_METHOD1(addArgument, void(int number));
	MOCK_METHOD1(addArgument, void(sys::uint32 number));
	MOCK_METHOD1(addArgument, void(float number));
	MOCK_METHOD1(addArgument, void(double number));
	MOCK_METHOD1(addArgument, void(int64 number));
	MOCK_METHOD1(addArgument, void(uint64 number));
	MOCK_METHOD1(addArgument, void(bool boolean));
	MOCK_METHOD1(addArgument, void(const String& str));
	MOCK_METHOD1(addArgument, void(const char* str));
	MOCK_METHOD1(addArgument, void(void* pointer));

	virtual void operator<<(int number) { addArgument(number); }
	virtual void operator<<(sys::uint32 number) { addArgument(number); }
	virtual void operator<<(float number) { addArgument(number); }
	virtual void operator<<(double number) { addArgument(number); }
	virtual void operator<<(int64 number) { addArgument(number); }
	virtual void operator<<(uint64 number) { addArgument(number); }
	virtual void operator<<(bool boolean) { addArgument(boolean); }
	virtual void operator<<(const String& str) { addArgument(str); }
	virtual void operator<<(const char* str) { addArgument(str); }
	virtual void operator<<(void* pointer) { addArgument(pointer); }
};

}
}

using namespace engine::lua;

#endif /* MOCKLUAFUNCTION_H_ */
