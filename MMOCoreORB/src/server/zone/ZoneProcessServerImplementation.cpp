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
#include "server/zone/objects/creature/variables/Skill.h"
#include "server/zone/managers/vendor/VendorManager.h"

#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/minigames/FishingManager.h"
#include "server/zone/managers/minigames/GamblingManager.h"
#include "server/zone/managers/minigames/ForageManager.h"
#include "server/zone/managers/space/SpaceManager.h"


ZoneProcessServerImplementation::ZoneProcessServerImplementation(ZoneServer* server) {
	zoneServer = server;

	nameManager = NULL;
	holocronManager = NULL;
	suiManager = NULL;

	objectController = NULL;

	professionManager = NULL;

	zonePacketHandler = NULL;

	vendorManager = NULL;

	fishingManager = NULL;
	gamblingManager = NULL;
	forageManager = NULL;
}

void ZoneProcessServerImplementation::finalize() {
	zonePacketHandler = NULL;

	nameManager = NULL;

	holocronManager = NULL;

	suiManager = NULL;

	professionManager = NULL;

	vendorManager = NULL;

	fishingManager = NULL;
	gamblingManager = NULL;
	forageManager = NULL;
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
	//nameManager->test();
	holocronManager = new HolocronManager(_this.getReferenceUnsafeStaticCast());
	suiManager = SuiManager::instance();
	suiManager->setZoneProcessServer(_this.getReferenceUnsafeStaticCast());

	objectController = new ObjectController(_this.getReferenceUnsafeStaticCast());

	fishingManager = new FishingManager();
	fishingManager->deploy();

	gamblingManager = new GamblingManager();
	gamblingManager->deploy();

	forageManager = new ForageManager();
	forageManager->deploy();

	ShipManager::instance();

}
