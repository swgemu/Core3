/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATENPCCOMMAND_H_
#define CREATENPCCOMMAND_H_

#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"

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
		} else if (arg == "toggledebug") {
			ManagedReference<AiAgent*> aiAgent = server->getZoneServer()->getObject(creature->getTargetID()).castTo<AiAgent*>();

			if (aiAgent == nullptr)
				return GENERALERROR;

			Locker clocker(aiAgent, creature);

			bool curDebug = aiAgent->getAIDebug();

			aiAgent->setAIDebug(!curDebug);

			StringBuffer msg;
			msg << "AiAgent " << aiAgent->getObjectID() << " debug set to " << aiAgent->getAIDebug();

#ifndef DEBUG_AI
			msg << " not compiled with DEBUG_AI, using LogLevel";
#endif // DEBUG_AI

			String logFileName = aiAgent->getLogFileName();

			if (!logFileName.isEmpty()) {
				msg << " logging to " << logFileName;
			}

			creature->sendSystemMessage(msg.toString());
		} else if (arg == "debugregions") {
			if (creature->isDebuggingRegions()) {
				creature->setDebuggingRegions(false);
				creature->sendSystemMessage("Region System Message Debug Disabled");
			} else {
				creature->setDebuggingRegions(true);
				creature->sendSystemMessage("Region System Message Debug Enabled");
			}

		}

		return SUCCESS;
	}

};

#endif //CREATENPCCOMMAND_H_
