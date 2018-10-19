/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "Features.h"
#include "engine/lua/Lua.h"

using namespace server::features;

Features::Features() {
}

bool Features::loadFeatures() {
	Lua lua;

	if (!lua.runFile("conf/features.lua"))
		return false;

	return true;
}
