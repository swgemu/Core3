/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATENPCCOMMAND_H_
#define CREATENPCCOMMAND_H_

#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "templates/params/ship/ShipFlag.h"
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

		auto zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		String arg = "";

		args.getStringToken(arg);

		arg = arg.toLowerCase();

		ManagedReference<SceneObject*> targetObject = zoneServer->getObject(creature->getTargetID());

		if (arg == "tools") {
			Lua* lua = DirectorManager::instance()->getLuaInstance();

			Reference<LuaFunction*> staffTools = lua->createFunction("StaffTools", "openToolsSUI", 0);
			*staffTools << creature;

			staffTools->callFunction();
		} else if (arg == "toggledebug") {
			if (targetObject == nullptr)
				return GENERALERROR;

			StringBuffer msg;

			if (targetObject->isAiAgent()) {
				AiAgent* aiAgent = targetObject->asAiAgent();

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
			} else if (targetObject->isShipAiAgent()) {
				ShipAiAgent* agent = targetObject->asShipAiAgent();

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
		} else if (arg == "shipfollow") {
			if (targetObject == nullptr || !targetObject->isShipAiAgent())
				return GENERALERROR;

			ShipAiAgent* shipAgent = targetObject->asShipAiAgent();

			if (shipAgent == nullptr)
				return GENERALERROR;

			ManagedReference<SceneObject*> rootParent = creature->getRootParent();

			if (rootParent == nullptr || !rootParent->isShipObject()) {
				return GENERALERROR;
			}

			ShipObject* shipParent = rootParent->asShipObject();

			if (shipParent == nullptr)
				return GENERALERROR;

			Locker clocker(shipAgent, creature);

			shipAgent->addShipFlag(ShipFlag::ESCORT);
			shipAgent->setShipAiTemplate();

			shipAgent->setFollowShipObject(shipParent);

			return SUCCESS;
		}


		return SUCCESS;
	}

};

#endif //CREATENPCCOMMAND_H_
