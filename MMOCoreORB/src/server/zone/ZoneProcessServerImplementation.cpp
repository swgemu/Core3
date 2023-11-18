/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "server/zone/managers/player/creation/PlayerCreationManager.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/ZonePacketHandler.h"

#include "server/zone/managers/sui/SuiManager.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/holocron/HolocronManager.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/managers/vendor/VendorManager.h"

#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/minigames/FishingManager.h"
#include "server/zone/managers/minigames/GamblingManager.h"
#include "server/zone/managers/minigames/ForageManager.h"
#include "server/zone/managers/ship/ShipManager.h"

ZoneProcessServerImplementation::ZoneProcessServerImplementation(ZoneServer* server) {
	zoneServer = server;
	nameManager = nullptr;
	holocronManager = nullptr;
	suiManager = nullptr;
	objectController = nullptr;
	professionManager = nullptr;
	zonePacketHandler = nullptr;
	vendorManager = nullptr;
	fishingManager = nullptr;
	gamblingManager = nullptr;
	forageManager = nullptr;
}

void ZoneProcessServerImplementation::stop() {
	zonePacketHandler = nullptr;
	nameManager = nullptr;
	holocronManager = nullptr;
	suiManager = nullptr;
	professionManager = nullptr;
	vendorManager = nullptr;
	fishingManager = nullptr;
	gamblingManager = nullptr;
	forageManager = nullptr;
	zoneServer = nullptr;
	playerCreationManager = nullptr;

	if (objectController != nullptr) {
		objectController->finalize();
		objectController = nullptr;
	}
}

void ZoneProcessServerImplementation::initialize() {
	//StructureManager::instance();

	vendorManager = VendorManager::instance();
	vendorManager->initialize(_this.getReferenceUnsafeStaticCast());

	professionManager = SkillManager::instance();
	professionManager->loadLuaConfig();
	professionManager->loadClientData();
	//professionManager->setObjectController(objectController);
	//professionManager->initialize();

	playerCreationManager = PlayerCreationManager::instance();

	zonePacketHandler = new ZonePacketHandler("ZonePacketHandler", _this.getReferenceUnsafeStaticCast());
	zonePacketHandler->setLogging(false);

	nameManager = new NameManager(_this.getReferenceUnsafeStaticCast());

	holocronManager = new HolocronManager(_this.getReferenceUnsafeStaticCast());
	suiManager = SuiManager::instance();
	suiManager->setZoneProcessServer(_this.getReferenceUnsafeStaticCast());

	objectController = new ObjectController(_this.getReferenceUnsafeStaticCast());

	fishingManager = new FishingManager();
	fishingManager->initialize();

	gamblingManager = new GamblingManager();
	gamblingManager->deploy();

	forageManager = new ForageManager();
	forageManager->deploy();

	ShipManager::instance();

}
