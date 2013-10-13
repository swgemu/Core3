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
	MOCK_METHOD1(addArgument, void(String& str));
	MOCK_METHOD1(addArgument, void(const char* str));
	MOCK_METHOD1(addArgument, void(void* pointer));

	virtual void operator<<(int number) { addArgument(number); }
	virtual void operator<<(sys::uint32 number) { addArgument(number); }
	virtual void operator<<(float number) { addArgument(number); }
	virtual void operator<<(double number) { addArgument(number); }
	virtual void operator<<(int64 number) { addArgument(number); }
	virtual void operator<<(uint64 number) { addArgument(number); }
	virtual void operator<<(bool boolean) { addArgument(boolean); }
	virtual void operator<<(String& str) { addArgument(str); }
	virtual void operator<<(const char* str) { addArgument(str); }
	virtual void operator<<(void* pointer) { addArgument(pointer); }
};

}
}

using namespace engine::lua;

#endif /* MOCKLUAFUNCTION_H_ */
