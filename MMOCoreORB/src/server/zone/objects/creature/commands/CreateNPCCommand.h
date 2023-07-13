/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATENPCCOMMAND_H_
#define CREATENPCCOMMAND_H_

#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"
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
			auto zoneServer = server->getZoneServer();

			if (zoneServer == nullptr)
				return GENERALERROR;

			ManagedReference<SceneObject*> target = zoneServer->getObject(creature->getTargetID());

			if (target == nullptr)
				return GENERALERROR;

			StringBuffer msg;

			if (target->isAiAgent()) {
				AiAgent* aiAgent = target->asAiAgent();

				if (aiAgent == nullptr)
					return GENERALERROR;

				Locker clocker(aiAgent, creature);

				bool curDebug = aiAgent->getAIDebug();

				aiAgent->setAIDebug(!curDebug);

				msg << "AiAgent " << aiAgent->getObjectID() << " debug set to " << aiAgent->getAIDebug();

	#ifndef DEBUG_AI
				msg << " not compiled with DEBUG_AI, using LogLevel";
	#endif // DEBUG_AI

				String logFileName = aiAgent->getLogFileName();

				if (!logFileName.isEmpty()) {
					msg << " logging to " << logFileName;
				}
			} else if (target->isShipAiAgent()) {
				ShipAiAgent* agent = target->asShipAiAgent();

				if (agent == nullptr)
					return GENERALERROR;

				Locker clocker(agent, creature);

				bool curDebug = agent->getShipAiDebug();

				agent->setShipAiDebug(!curDebug);

				msg << "AiAgent: " << agent->getDisplayedName() << " ID: " << agent->getObjectID() << " debug set to " << agent->getShipAiDebug();
			} else {
				msg << "Failed to start debug on target.";
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
