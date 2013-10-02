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

#include "JediManager.h"
#include "server/zone/managers/director/DirectorManager.h"

JediManager::JediManager() : Logger("JediManager") {
	jediProgressionType = NOJEDIPROGRESSION;
}

JediManager::~JediManager() {

}

String JediManager::getJediManagerName() {
	ReadLocker locker(this);

	String ret = jediManagerName;

	return ret;
}

void JediManager::loadConfiguration(Lua* luaEngine) {
	luaEngine->runFile("scripts/managers/jedi_manager.lua");

	jediProgressionType = luaEngine->getGlobalInt(String("jediProgressionType"));

	switch (jediProgressionType) {
	case HOLOCRONJEDIPROGRESSION:
		luaEngine->runFile("scripts/managers/holocron_jedi_manager.lua");
		break;
	case VILLAGEJEDIPROGRESSION:
		luaEngine->runFile("scripts/managers/village_jedi_manager.lua");
		break;
	case CUSTOMJEDIPROGRESSION:
		luaEngine->runFile(luaEngine->getGlobalString(String("customJediProgressionFile")));
		break;
	default:
		break;
	}

	Locker writeLock(this);

	jediManagerName = luaEngine->getGlobalString(String("jediManagerName"));

	info("Loaded.", true);
}

void JediManager::start(Lua* luaEngine) {
	LuaFunction luaStart(luaEngine->getLuaState(), jediManagerName, "start", 0);

	luaStart.callFunction();
}

void JediManager::onPlayerCreated(CreatureObject* creature) {
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	LuaFunction luaOnPlayerCreated(lua->getLuaState(), getJediManagerName(), "onPlayerCreated", 0);
	luaOnPlayerCreated << creature;

	luaOnPlayerCreated.callFunction();
}

void JediManager::onPlayerLoggedIn(CreatureObject* creature) {
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	LuaFunction luaOnPlayerLoggedIn(lua->getLuaState(), getJediManagerName(), "onPlayerLoggedIn", 0);
	luaOnPlayerLoggedIn << creature;

	luaOnPlayerLoggedIn.callFunction();
}

void JediManager::onPlayerLoggedOut(CreatureObject* creature) {
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	LuaFunction luaOnPlayerLoggedOut(lua->getLuaState(), getJediManagerName(), "onPlayerLoggedOut", 0);
	luaOnPlayerLoggedOut << creature;

	luaOnPlayerLoggedOut.callFunction();
}

void JediManager::checkForceStatusCommand(CreatureObject* creature) {
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	LuaFunction luaCheckForceStatusCommand(lua->getLuaState(), getJediManagerName(), "checkForceStatusCommand", 0);
	luaCheckForceStatusCommand << creature;

	luaCheckForceStatusCommand.callFunction();
}

void JediManager::useHolocron(SceneObject* holocron, CreatureObject* creature) {
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	LuaFunction luaUseHolocron(lua->getLuaState(), getJediManagerName(), "useHolocron", 0);
	luaUseHolocron << holocron;
	luaUseHolocron << creature;

	luaUseHolocron.callFunction();
}
