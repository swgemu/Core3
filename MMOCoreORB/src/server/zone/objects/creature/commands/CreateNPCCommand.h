/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATENPCCOMMAND_H_
#define CREATENPCCOMMAND_H_

#include "server/zone/managers/director/DirectorManager.h"

class CreateNPCCommand : public QueueCommand {
public:

	CreateNPCCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		StringTokenizer args(arguments.toString());

		if (!args.hasMoreTokens())
			return INVALIDPARAMETERS;

		String arg = "";

		args.getStringToken(arg);

		if (arg == "tools") {
			Lua* lua = DirectorManager::instance()->getLuaInstance();

			Reference<LuaFunction*> staffTools = lua->createFunction("StaffTools", "openToolsSUI", 0);
			*staffTools << creature;

			staffTools->callFunction();
		}

		return SUCCESS;
	}

};

#endif //CREATENPCCOMMAND_H_
