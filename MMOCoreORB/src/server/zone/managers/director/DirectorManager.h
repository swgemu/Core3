/*
 * DirectorManager.h
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#ifndef DIRECTORMANAGER_H_
#define DIRECTORMANAGER_H_

#include "engine/engine.h"

class ScreenPlayTask;

namespace server {
 namespace zone {
  namespace objects {
   namespace creature {
    class CreatureObject;
   }
  }
 }
}

using namespace server::zone::objects::creature;

namespace server {
 namespace zone {
  namespace managers {
   namespace director {

	class DirectorManager : public Singleton<DirectorManager>, public Object, public Logger, public ReadWriteLock {
		ThreadLocal<Lua*> localLua;

		HashTable<String, String> sharedMemory;

	public:
		DirectorManager();

		void startScreenPlay(CreatureObject* creatureObject, const String& screenPlayName);
		void activateEvent(ScreenPlayTask* task);

		Lua* getLuaInstance();

		static int includeFile(lua_State* L);
		static int createEvent(lua_State* L);
		static int createObserver(lua_State* L);
		static int spawnMobile(lua_State* L);
		static int spatialChat(lua_State* L);
		static int readSharedMemory(lua_State* L);
		static int writeSharedMemory(lua_State* L);

	private:
		void initializeLuaEngine(Lua* lua);
	};

   }
  }
 }
}

using namespace server::zone::managers::director;

#endif /* DIRECTORMANAGER_H_ */
