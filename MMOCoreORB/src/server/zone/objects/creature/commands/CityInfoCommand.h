/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CITYINFOCOMMAND_H_
#define CITYINFOCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CityInfoCommand : public QueueCommand {
public:
	CityInfoCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		PlayerObject* ghost = creature->getPlayerObject();

		if(ghost == NULL || !ghost->isPrivileged()) {
			return GENERALERROR;
		}

		byte rank = 0;
		StringTokenizer args(arguments.toString());
		String planet;

		if(args.hasMoreTokens()) {
			args.getStringToken(planet);
		} else {
			sendSyntax(creature);
			return INVALIDSYNTAX;
		}

		if (args.hasMoreTokens()) {
			rank = args.getIntToken();
			if(rank < 1 || rank > 5) {
				creature->sendSystemMessage("Rank, if specified, must be between 1 and 5.");
				return INVALIDPARAMETERS;
			}

		}

		if(creature->getZoneServer() == NULL)
			return GENERALERROR;

		CityManager* cityManager = creature->getZoneServer()->getCityManager();

		if(cityManager == NULL)
			return GENERALERROR;

		cityManager->sendCityReport(creature, planet, rank);
		return SUCCESS;
	}

	static void sendSyntax(CreatureObject* creature) {
		String syntax = "/cityinfo [planetname] <rank>";
		creature->sendSystemMessage(syntax);
	}
};

#endif //CITYINFOCOMMAND_H_
