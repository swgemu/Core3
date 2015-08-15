/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DUMPZONEINFORMATIONCOMMAND_H_
#define DUMPZONEINFORMATIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/ZoneServer.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/terrain/layer/boundaries/BoundaryRectangle.h"

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

		if (zone == NULL)
			return GENERALERROR;

		PlanetManager* planetManager = zone->getPlanetManager();
		TerrainManager* terrainManager = planetManager->getTerrainManager();

		int cityPlayerCount = 0;

		ManagedReference<CityRegion*> city = player->getCityRegion();

		if (city != NULL) {
			cityPlayerCount = city->getCurrentPlayerCount();
		}

		ManagedReference<SceneObject*> cell = creature->getParent();

		int cellid = 0;
		uint32 buildingTemplate = 0;
		SharedStructureObjectTemplate* buildingTemplateObject = NULL;
		ManagedReference<SceneObject*> building;

		if (cell != NULL && cell->isCellObject()) {
			cellid = (cast<CellObject*>(cell.get()))->getCellNumber();
			building = cell->getParent();
			buildingTemplate = building->getServerObjectCRC();
			buildingTemplateObject = dynamic_cast<SharedStructureObjectTemplate*>(building->getObjectTemplate());
		}

		StringBuffer msg;

		float posX = creature->getPositionX(), posZ = creature->getPositionZ(), posY = creature->getPositionY();
		Quaternion* direction = creature->getDirection();

		msg << "x = " << posX << ", z = " << posZ << ", y = " << posY << ", ow = " << direction->getW()
				<< ", ox = " << direction->getX() << ", oz = " << direction->getZ() << ", oy = " << direction->getY()
				<< ", cellid = " << cellid;

		if (buildingTemplate != 0)
			msg << endl << TemplateManager::instance()->getTemplateFile(buildingTemplate);

		if (cityPlayerCount != 0)
			msg << endl << "current players in the city:" << cityPlayerCount;
			
		CloseObjectsVector* vec = (CloseObjectsVector*) player->getCloseObjects();
		
		if (vec != NULL) {
			msg << endl << "in range object count = " << vec->size() << endl;
		}

		msg << "active areas size = " << player->getActiveAreasSize() << endl;

		int heightCacheHitCount = terrainManager->getCacheHitCount();
		int heightCacheMissCount = terrainManager->getCacheMissCount();
		int cacheClearCount = terrainManager->getCacheClearCount();
		int cacheClearHeightCount = terrainManager->getCacheClearHeightsCount();
		int cacheSize = terrainManager->getCachedValuesCount();

		int total = MAX(heightCacheHitCount + heightCacheMissCount, 1);

		msg << "height cache total hit count = " << heightCacheHitCount << ", total miss count = " << heightCacheMissCount
				<< ", total hit rate = " << ((float)heightCacheHitCount / (float)total) * 100 << "% "
						", clear count = " << cacheClearCount << ", "
						"clear hit count = " << cacheClearHeightCount << ", "
						"cache size = " << cacheSize << endl;

		creature->sendSystemMessage(msg.toString());

		ChatManager* chatManager = server->getZoneServer()->getChatManager();
		chatManager->sendMail("System", "dumpZoneInformation", msg.toString(), player->getFirstName());

		return SUCCESS;
	}

};

#endif //DUMPZONEINFORMATIONCOMMAND_H_
