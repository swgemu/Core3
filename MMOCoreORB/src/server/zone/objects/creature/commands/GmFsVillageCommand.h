/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GMFSVILLAGECOMMAND_H_
#define GMFSVILLAGECOMMAND_H_

#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/managers/jedi/JediManager.h"

class GmFsVillageCommand : public QueueCommand {
public:

	GmFsVillageCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (JediManager::instance()->getJediProgressionType() != JediManager::VILLAGEJEDIPROGRESSION)
			return GENERALERROR;

		Lua* lua = DirectorManager::instance()->getLuaInstance();

		Reference<LuaFunction*> luaVillageGmCmd = lua->createFunction("VillageGmSui", "showMainPage", 0);
		*luaVillageGmCmd << creature;

		luaVillageGmCmd->callFunction();

		return SUCCESS;
	}

};

#endif //GMFSVILLAGECOMMAND_H_
