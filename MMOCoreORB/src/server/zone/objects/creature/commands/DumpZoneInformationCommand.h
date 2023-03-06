/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DUMPZONEINFORMATIONCOMMAND_H_
#define DUMPZONEINFORMATIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/ZoneServer.h"
#include "server/chat/ChatManager.h"
#include "QueueCommand.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "templates/tangible/SharedStructureObjectTemplate.h"
#include "terrain/manager/TerrainManager.h"

class DumpZoneInformationCommand : public QueueCommand {
public:

	DumpZoneInformationCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		CreatureObject* player = creature;

		Zone* zone = player->getZone();

		if (zone == nullptr)
			return GENERALERROR;

		PlanetManager* planetManager = zone->getPlanetManager();
		TerrainManager* terrainManager = planetManager->getTerrainManager();

		int cityPlayerCount = 0;

		ManagedReference<CityRegion*> city = player->getCityRegion().get();

		if (city != nullptr) {
			cityPlayerCount = city->getCurrentPlayerCount();
		}

		ManagedReference<SceneObject*> cell = creature->getParent().get();

		int cellid = 0;
		uint32 buildingTemplate = 0;
		SharedStructureObjectTemplate* buildingTemplateObject = nullptr;
		ManagedReference<SceneObject*> building;

		if (cell != nullptr && cell->isCellObject()) {
			cellid = (cast<CellObject*>(cell.get()))->getCellNumber();
			building = cell->getParent().get();
			buildingTemplate = building->getServerObjectCRC();
			buildingTemplateObject = dynamic_cast<SharedStructureObjectTemplate*>(building->getObjectTemplate());
		}

		StringBuffer msg;

		float posX = creature->getPositionX(), posZ = creature->getPositionZ(), posY = creature->getPositionY();
		const Quaternion* direction = creature->getDirection();

		float collisionZ = CollisionManager::getWorldFloorCollision(posX, posY, zone, false);

		msg << "x = " << posX << ", z = " << posZ << ", y = " << posY << ", ow = " << direction->getW()
				<< ", ox = " << direction->getX() << ", oz = " << direction->getZ() << ", oy = " << direction->getY()
				<< ", cellid = " << cellid
				<< ", collisionZ = " << collisionZ;

		if (buildingTemplate != 0)
			msg << endl << TemplateManager::instance()->getTemplateFile(buildingTemplate);

		if (cityPlayerCount != 0)
			msg << endl << "current players in the city:" << cityPlayerCount;

		CloseObjectsVector* vec = (CloseObjectsVector*) player->getCloseObjects();

		if (vec != nullptr) {
			msg << endl << "in range object count = " << vec->size() << endl;
		}

		msg << "active areas size = " << player->getActiveAreasSize() << endl;

		int heightCacheHitCount = terrainManager->getCacheHitCount();
		int heightCacheMissCount = terrainManager->getCacheMissCount();
		int cacheClearCount = terrainManager->getCacheClearCount();
		int cacheClearHeightCount = terrainManager->getCacheClearHeightsCount();
		int cacheSize = terrainManager->getCachedValuesCount();
		int evictCount = terrainManager->getCacheEvictCount();

		int total = Math::max(heightCacheHitCount + heightCacheMissCount, 1);

		msg << "height cache total hit count = " << heightCacheHitCount << ", total miss count = " << heightCacheMissCount
				<< ", total hit rate = " << ((float)heightCacheHitCount / (float)total) * 100 << "% "
						", clear count = " << cacheClearCount <<
						", clear hit count = " << cacheClearHeightCount <<
						", evict count = " << evictCount <<
						", cache size = " << cacheSize << endl;

		creature->sendSystemMessage(msg.toString());

		ChatManager* chatManager = server->getZoneServer()->getChatManager();

		// Dump first 10 active areas
		SortedVector<ManagedReference<ActiveArea*>> areas = *player->getActiveAreas();

		if (areas.size() > 0) {
			msg << endl << "-- active area detail (max 10) --" << endl << endl;

			for (int i = 0; i < Math::min(areas.size(), 10); ++i) {
					ManagedReference<ActiveArea*>& area = areas.get(i);
					JSONSerializationType areaJSON;
					area->writeJSON(areaJSON);
					msg << areaJSON.dump().c_str() << endl << endl;
			}
		}

		chatManager->sendMail("System", "dumpZoneInformation", msg.toString(), player->getFirstName());

		return SUCCESS;
	}

};

#endif //DUMPZONEINFORMATIONCOMMAND_H_
