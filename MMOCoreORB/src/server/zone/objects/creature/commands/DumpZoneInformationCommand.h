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
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"

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

		Zone* zone = creature->getZone();

		if (zone == nullptr)
			return GENERALERROR;

		int ret = GENERALERROR;

		if (zone->isSpaceZone()) {
			ret = dumpSpaceZone(creature, zone);
		} else {
			ret = dumpGroundZone(creature, zone);
		}

		return ret;
	}

	int dumpGroundZone(CreatureObject* creature, Zone* zone) const {
		if (creature == nullptr || zone == nullptr || zone->isSpaceZone())
			return GENERALERROR;

		auto zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		PlanetManager* planetManager = zone->getPlanetManager();

		if (planetManager == nullptr)
			return GENERALERROR;

		TerrainManager* terrainManager = planetManager->getTerrainManager();

		if (terrainManager == nullptr)
			return GENERALERROR;

		int cityPlayerCount = 0;

		ManagedReference<CityRegion*> city = creature->getCityRegion().get();

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

		msg << "Player: " << creature->getDisplayedName() << endl;
		msg << "Player ID: " << creature->getObjectID() << endl;
		msg << "Zone Name: " << zone->getZoneName() << endl;

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

		CloseObjectsVector* vec = (CloseObjectsVector*) creature->getCloseObjects();

		if (vec != nullptr) {
			msg << endl << "Total in Range Objects = " << vec->size() << endl;
		}

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

		msg << "Total Active Areas = " << creature->getActiveAreasSize() << endl;

		creature->sendSystemMessage(msg.toString());

		// Dump first 10 active areas
		SortedVector<ManagedReference<ActiveArea*>> areas = *creature->getActiveAreas();

		if (areas.size() > 0) {
			msg << endl << "-- active area detail (max 10) --" << endl << endl;

			for (int i = 0; i < Math::min(areas.size(), 10); ++i) {
					ManagedReference<ActiveArea*>& area = areas.get(i);
					JSONSerializationType areaJSON;
					area->writeJSON(areaJSON);
					msg << areaJSON.dump().c_str() << endl << endl;
			}
		}

		ChatManager* chatManager = zoneServer->getChatManager();

		if (chatManager != nullptr)
			chatManager->sendMail("System", "dumpZoneInformation", msg.toString(), creature->getFirstName());

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, SuiWindowType::NONE);

		if (box != nullptr) {
			StringBuffer titleStr;
			titleStr << "DumpZoneInformation - Ground";

			box->setPromptTitle(titleStr.toString());
			box->setPromptText(msg.toString());

			creature->sendMessage(box->generateMessage());
		}

		return SUCCESS;
	}

	int dumpSpaceZone(CreatureObject* creature, Zone* zone) const {
		if (creature == nullptr || zone == nullptr || !zone->isSpaceZone())
			return GENERALERROR;

		StringBuffer spaceMsg;

		spaceMsg << "Player: " << creature->getDisplayedName() << endl;
		spaceMsg << "Player ID: " << creature->getObjectID() << endl;
		spaceMsg << "Space Zone Name: " << zone->getZoneName() << endl;

		ManagedReference<SceneObject*> parent = creature->getParent().get();
		uint64 parentID = 0;
		String parentName = "";

		if (parent != nullptr) {
			parentID = parent->getObjectID();
			parentName = parent->getDisplayedName();
		}

		Vector3 position = creature->getPosition();
		const Quaternion* direction = creature->getDirection();

		spaceMsg << "Position: " << position.toString() << endl;
		spaceMsg << "Direction: ox = " << direction->getX() << ", oy = " << direction->getY() << ", oz = " << direction->getZ() << ", ow = " << direction->getW() << endl << endl;
		spaceMsg << "ParentID = " << parentID << " Parent Name: " << parentName << endl << endl;

		CloseObjectsVector* vec = (CloseObjectsVector*) creature->getCloseObjects();

		if (vec != nullptr) {
			spaceMsg << "Total in Range Objects = " << vec->size() << endl << endl;

			for (int i = 0; i < vec->size(); i++) {
				auto sceneO = vec->get(i).castTo<SceneObject*>();

				if (sceneO == nullptr)
					continue;

				spaceMsg << "Object #" << i << " - " << sceneO->getDisplayedName() << "      ID: " << sceneO->getObjectID() << endl;

				// Cap at first 20 objects
				if (i >= 20)
					break;
			}
		}

		spaceMsg << endl << "Total Active Areas = " << creature->getActiveAreasSize() << endl;

		creature->sendSystemMessage(spaceMsg.toString());

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, SuiWindowType::NONE);

		if (box != nullptr) {
			StringBuffer titleStr;
			titleStr << "DumpZoneInformation - Space";

			box->setPromptTitle(titleStr.toString());
			box->setPromptText(spaceMsg.toString());

			creature->sendMessage(box->generateMessage());
		}

		return SUCCESS;
	}
};

#endif //DUMPZONEINFORMATIONCOMMAND_H_
