/*
 * DirectorManager.h
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#ifndef DIRECTORMANAGER_H_
#define DIRECTORMANAGER_H_

#include "DirectorSharedMemory.h"
#include "server/zone/managers/director/QuestStatus.h"
#include "server/zone/managers/director/ScreenPlayTask.h"
#include "server/zone/managers/director/QuestVectorMap.h"

#include "system/util/SynchronizedSortedVector.h"
#include "system/util/SynchronizedHashTable.h"
#include "system/util/SynchronizedVectorMap.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace conversation {

	class ConversationScreen;
	class ConversationTemplate;
}
}
}
}
}

using namespace server::zone::objects::creature::conversation;

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
   class PersistentEvent;
   class ScreenPlayTask;

	class DirectorManager : public Singleton<DirectorManager>, public Object, public Logger, public ReadWriteLock {
		ThreadLocal<Lua*> localLua;
		ThreadLocal<uint32*> localScreenPlayVersion;
		AtomicInteger masterScreenPlayVersion;
		VectorMap<String, bool> screenPlays;
		SynchronizedVectorMap<String, Reference<QuestStatus*> > questStatuses;
		SynchronizedVectorMap<String, Reference<QuestVectorMap*> > questVectorMaps;
		SynchronizedSortedVector<Reference<ScreenPlayTask*> > screenplayTasks;

#ifdef WITH_STM
		TransactionalReference<DirectorSharedMemory* > sharedMemory;
#else
		Reference<DirectorSharedMemory* > sharedMemory;
#endif
		static SynchronizedHashTable<uint32, Reference<PersistentEvent*> > persistentEvents;
	public:
		static int DEBUG_MODE;

		enum LUA_ERROR_CODE { NO_ERROR = 0, MAIN_FILE_ERROR, GENERAL_ERROR, INCORRECT_ARGUMENTS };
		static int ERROR_CODE;

	public:
		DirectorManager();

		~DirectorManager() {
			sharedMemory = NULL;
		}

		void loadPersistentEvents();
		void loadPersistentStatus();

		void startGlobalScreenPlays();
		void startScreenPlay(CreatureObject* creatureObject, const String& screenPlayName);
		void reloadScreenPlays();
		void activateEvent(ScreenPlayTask* task);
		ConversationScreen* getNextConversationScreen(const String& luaClass, ConversationTemplate* conversationTemplate, CreatureObject* conversingPlayer, int selectedOption, CreatureObject* conversingNPC);
		ConversationScreen* runScreenHandlers(const String& luaClass, ConversationTemplate* conversationTemplate, CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen);

		void setQuestStatus(const String& keyString, const String& valString);
		String getQuestStatus(const String& keyString);
		void removeQuestStatus(const String& key);

		String readStringSharedMemory(const String& key);
		uint64 readSharedMemory(const String& key);

		QuestVectorMap* getQuestVectorMap(const String& keyString);
		QuestVectorMap* createQuestVectorMap(const String& keyString);
		void removeQuestVectorMap(const String& keyString);

		Vector<Reference<ScreenPlayTask*> > getObjectEvents(SceneObject* obj);
		String getStringSharedMemory(const String& key);

		virtual Lua* getLuaInstance();
		int runScreenPlays();

		static int writeScreenPlayData(lua_State* L);
		static int readScreenPlayData(lua_State* L);
		static int deleteScreenPlayData(lua_State* L);
		static int clearScreenPlayData(lua_State* L);
		static int registerScreenPlay(lua_State* L);
		static int includeFile(lua_State* L);
		static int createEvent(lua_State* L);
		static int createEventActualTime(lua_State* L);
		static int createServerEvent(lua_State* L);
		static int hasServerEvent(lua_State* L);
		static int rescheduleServerEvent(lua_State* L);
		static int getServerEventID(lua_State* L);
		static int getServerEventTimeLeft(lua_State* L);
		static int createObserver(lua_State* L);
		static int dropObserver(lua_State* L);
		static int hasObserver(lua_State* L);
		static int spawnMobile(lua_State* L);
		static int spawnEventMobile(lua_State* L);
		static int spawnSceneObject(lua_State* L);
		static int spawnActiveArea(lua_State* L);
		static int spawnBuilding(lua_State* L);
		static int destroyBuilding(lua_State* L);
		static int createLoot(lua_State* L);
		static int createLootSet(lua_State* L);
		static int createLootFromCollection(lua_State* L);

		static int getRandomNumber(lua_State* L);
		static int spatialChat(lua_State* L);
		static int spatialMoodChat(lua_State* L);
		static int readSharedMemory(lua_State* L);
		static int writeSharedMemory(lua_State* L);
		static int deleteSharedMemory(lua_State* L);
		static int readStringSharedMemory(lua_State* L);
		static int writeStringSharedMemory(lua_State* L);
		static int deleteStringSharedMemory(lua_State* L);
		static int getSceneObject(lua_State* L);
		static int getCreatureObject(lua_State* L);
		static int addStartingItemsInto(lua_State* L);
		static int addStartingWeaponsInto(lua_State* L);
		static int setAuthorizationState(lua_State* L);
		static int giveItem(lua_State* L);
		static int giveControlDevice(lua_State* L);
		static int checkTooManyHirelings(lua_State* L);
		static int checkInt64Lua(lua_State* L);
		static int getChatMessage(lua_State* L);
		static int createConversationScreen(lua_State* L);
		static int getStringId(lua_State* L);
		static int getRankName(lua_State* L);
		static int getRankCost(lua_State* L);
		static int getRankDelegateRatioFrom(lua_State* L);
		static int getRankDelegateRatioTo(lua_State* L);
		static int isHighestRank(lua_State* L);
		static int getZoneByName(lua_State* L);
		static int isZoneEnabled(lua_State* L);
		static int getFactionPointsCap(lua_State* L);
		static int getRegion(lua_State* L);
		static int forcePeace(lua_State* L);
		static int getObjectTemplatePathByCRC(lua_State* L);
		static int getContainerObjectByTemplate(lua_State* L);
		static int updateCellPermission(lua_State* L);
		static int updateCellPermissionGroup(lua_State* L);
		static int getTimestamp(lua_State* L);
		static int getTimestampMilli(lua_State* L);
		static int getFormattedTime(lua_State* L);
		static int getSpawnPoint(lua_State* L);
		static int getSpawnArea(lua_State* L);
		static int makeCreatureName(lua_State* L);
		static int getGCWDiscount(lua_State* L);
		static int getTerrainHeight(lua_State* L);
		static int checkArgumentCount(lua_State*L, int args);
		static int awardSkill(lua_State* L);
		static int getCityRegionAt(lua_State* L);
		static int setDungeonTicketAttributes(lua_State* L);
		static int setQuestStatus(lua_State* L);
		static int getQuestStatus(lua_State* L);
		static int removeQuestStatus(lua_State* L);
		static int getControllingFaction(lua_State* L);
		static int getImperialScore(lua_State* L);
		static int getRebelScore(lua_State* L);
		static int getWinningFactionDifficultyScaling(lua_State* L);
		static int playClientEffectLoc(lua_State* L);
		static int getQuestInfo(lua_State* L);
		static int getPlayerQuestID(lua_State* L);
		static int getQuestVectorMap(lua_State* L);
		static int removeQuestVectorMap(lua_State* L);
		static int createQuestVectorMap(lua_State* L);
		static int createNavMesh(lua_State* L);
		static int creatureTemplateExists(lua_State* L);
		static int printLuaError(lua_State* L);
		static int getSpawnPointInArea(lua_State* L);
		static int getPlayerByName(lua_State* L);
		static int sendMail(lua_State* L);
		static int spawnTheaterObject(lua_State* L);
		static int getSchematicItemName(lua_State* L);
		static int getBadgeListByType(lua_State* L);

	private:
		void setupLuaPackagePath(Lua* luaEngine);
		static void printTraceError(lua_State* L, const String& error);
		void initializeLuaEngine(Lua* luaEngine);
		int loadScreenPlays(Lua* luaEngine);
		void loadJediManager(Lua* luaEngine);
		static Vector3 generateSpawnPoint(String zoneName, float x, float y, float minimumDistance, float maximumDistance, float extraNoBuildRadius, float sphereCollision, bool forceSpawn = false);

		static Reference<PersistentEvent*> getServerEvent(const String& eventName);
		static void dropServerEventReference(const String& eventName);
	};

   }
  }
 }
}

using namespace server::zone::managers::director;

#endif /* DIRECTORMANAGER_H_ */
