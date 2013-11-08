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
	vendorManager->initialize(_this.get());

	professionManager = SkillManager::instance();
	professionManager->loadLuaConfig();
	professionManager->loadClientData();
	//professionManager->setObjectController(objectController);
	//professionManager->initialize();

	playerCreationManager = PlayerCreationManager::instance();

	zonePacketHandler = new ZonePacketHandler("ZonePacketHandler", _this.get());
	zonePacketHandler->setLogging(false);

	nameManager = new NameManager(_this.get());
	//nameManager->test();
	holocronManager = new HolocronManager(_this.get());
	suiManager = SuiManager::instance();
	suiManager->setZoneProcessServer(_this.get());

	objectController = new ObjectController(_this.get());

	fishingManager = new FishingManager();
	fishingManager->deploy();

	gamblingManager = new GamblingManager();
	gamblingManager->deploy();

	forageManager = new ForageManager();
	forageManager->deploy();

	ShipManager::instance();

}
