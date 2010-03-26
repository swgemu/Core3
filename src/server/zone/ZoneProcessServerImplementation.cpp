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

#include "engine/engine.h"

#include "ZoneProcessServerImplementation.h"

//#include "ZoneClientSession.h"

#include "ZoneServer.h"
//#include "Zone.h"

#include "ZonePacketHandler.h"
#include "ZoneMessageProcessorThread.h"



//#include "ZoneImplementation.h"

//#include "../ServerCore.h"

/*#include "managers/user/UserManager.h"
#include "managers/user/UserManagerImplementation.h"

#include "managers/player/PlayerManager.h"
#include "managers/player/PlayerManagerImplementation.h"

#include "managers/player/ProfessionManager.h"

#include "managers/item/ItemManager.h"
#include "managers/item/ItemManagerImplementation.h"

#include "managers/combat/CombatManager.h"

#include "../chat/ChatManager.h"
#include "../chat/ChatManagerImplementation.h"

#include "managers/mission/MissionManager.h"
#include "managers/mission/MissionManagerImplementation.h"

#include "managers/radial/RadialManager.h"
#include "managers/guild/GuildManager.h"
#include "managers/guild/GuildManagerImplementation.h"
#include "managers/group/GroupManager.h"
#include "managers/skills/SkillManager.h"
#include "managers/loot/LootManager.h"
*/

#include "managers/sui/SuiManager.h"

#include "managers/name/NameManager.h"
#include "managers/professions/ProfessionManager.h"
#include "managers/objectcontroller/ObjectController.h"

ZoneProcessServerImplementation* ZoneProcessServerImplementation::instance = NULL;

ZoneProcessServerImplementation::ZoneProcessServerImplementation(ZoneServer* serv, int processingThreads)
		: ServiceMessageHandlerThread("ZoneProcessorServer") {
	server = serv;

	processors = NULL;
	procThreadCount = processingThreads;

	nameManager = new NameManager(this);
	suiManager = new SuiManager(this);
	objectController = new ObjectController(this);
	professionManager = new ProfessionManager(objectController);

	zonephandler = NULL;

	instance = this;

	setLogging(false);

	taskManager->setLogging(false);
}

ZoneProcessServerImplementation::~ZoneProcessServerImplementation() {
	if (processors != NULL) {
		free(processors);
		processors = NULL;
	}

	if (zonephandler != NULL) {
		delete zonephandler;
		zonephandler = NULL;
	}

	if (nameManager != NULL) {
		delete nameManager;
		nameManager = NULL;
	}

	if (suiManager != NULL) {
		delete suiManager;
		suiManager = NULL;
	}

	if (professionManager != NULL) {
		delete professionManager;
		professionManager = NULL;
	}
}

void ZoneProcessServerImplementation::init() {
	zonephandler = new ZonePacketHandler("ZonePacketHandler", this);
	zonephandler->setLogging(false);

	if (procThreadCount < 1)
		throw new Exception("invalid zone processor thread count");

	processors = (ZoneMessageProcessorThread**) malloc(procThreadCount * sizeof(ZoneMessageProcessorThread*));

	for (int i = 0; i < procThreadCount; ++i) {
		StringBuffer name;
		name << "ZoneProcessor" << i;

		processors[i] = new ZoneMessageProcessorThread(name.toString(), zonephandler);
	}
}

void ZoneProcessServerImplementation::run() {
	info("starting processor instances..");

	for (int i = 0; i < procThreadCount; ++i) {
		ZoneMessageProcessorThread* processor = processors[i];
		processor->start(this);
	}

	info("processor instances started");
}

void ZoneProcessServerImplementation::stop() {
	flushMessages();

	info("stopping processor instances..");

	for (int i = 0; i < procThreadCount; ++i) {
		ZoneMessageProcessorThread* processor = processors[i];
		processor->stop();

		delete processor;
	}

	info("processor instances stopped");
}
