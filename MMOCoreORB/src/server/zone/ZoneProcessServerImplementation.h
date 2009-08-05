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

#ifndef ZONEPROCESSSERVERIMPLEMENTATION_H_
#define ZONEPROCESSSERVERIMPLEMENTATION_H_

#include "engine/engine.h"

/*class Zone;
class SceneObject;

class UserManager;
class PlayerManager;
class CraftingManager;
class ItemManager;
class GuildManager;
class BankManager;
class ChatManager;
class MissionManager;

// Static managers
class CombatManager;
class ProfessionManager;
class SkillManager;
class RadialManager;
class GroupManager;
class LootManager;
class SuiManager;*/

class NameManager;

#include "ZoneServer.h"

namespace server {
namespace chat {
class ChatManager;
}
}

using namespace server::chat;

namespace server {
namespace zone {

class ZonePacketHandler;
class ZoneMessageProcessorThread;
class ZoneServer;

namespace managers {
  namespace player {
	class PlayerManager;
  }
}

class ZoneProcessServerImplementation : public ServiceMessageHandlerThread {
	ZoneServer* server;

	ZonePacketHandler* zonephandler;

	ZoneMessageProcessorThread** processors;
	int procThreadCount;

	//Static Managers
	NameManager* nameManager;

	/*CombatManager* combatManager;
	ProfessionManager* professionManager;
	SkillManager* skillManager;
	RadialManager* radialManager;
	GroupManager* groupManager;
	LootManager* lootManager;
	SuiManager* suiManager;
	*/

public:
	ZoneProcessServerImplementation(ZoneServer* serv, int processingThreads);

	~ZoneProcessServerImplementation();

	void init();

	void run();

	void stop();

	ServiceClient* createConnection(Socket* sock, SocketAddress& addr) {
		return NULL;
	}

	// setters and getters
	inline ZoneServer* getZoneServer() {
		return server;
	}

	inline PlayerManager* getPlayerManager() {
		return server->getPlayerManager();
	}

	inline NameManager* getNameManager() {
		return nameManager;
	}

	inline ChatManager* getChatManager() {
		return server->getChatManager();
	}

	/*inline UserManager* getUserManager() {
		return server->getUserManager();
	}

	inline CraftingManager* getCraftingManager() {
		return server->getCraftingManager();
	}

	inline ItemManager* getItemManager() {
		return server->getItemManager();
	}

	inline GuildManager* getGuildManager() {
		return server->getGuildManager();
	}

	inline BankManager* getBankManager() {
		return server->getBankManager();
	}

	inline MissionManager* getMissionManager() {
		return server->getMissionManager();
	}

	inline CombatManager* getCombatManager() {
		return combatManager;
	}

	inline ProfessionManager* getProfessionManager() {
		return professionManager;
	}

	inline SkillManager* getSkillManager() {
		return skillManager;
	}

	inline RadialManager* getRadialManager() {
		return radialManager;
	}

	inline GroupManager* getGroupManager() {
		return groupManager;
	}

	inline LootManager* getLootManager() {
		return lootManager;
	}

	inline SuiManager* getSuiManager() {
		return suiManager;
	}

	*/

};

}
}

using namespace server::zone;

#endif /*ZONEPROCESSSERVERIMPLEMENTATION_H_*/
