/*
 * CityReportCommand.h
 *
 *  Created on: Aug 9, 2013
 *      Author: swgemu
 */

#ifndef CITYREPORTCOMMAND_H_
#define CITYREPORTCOMMAND_H_
#include "engine/engine.h"
#include "server/zone/managers/city/CityManager.h"

class CityReportCommand {
public:



	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		if (!creature->isPlayerCreature())
			return 1;

		PlayerObject* ghost = creature->getPlayerObject();

		if(ghost == NULL || !ghost->isPrivileged() || ghost->getAdminLevel() < 15) {
			return 1;
		}

		byte rank = 0;

		StringTokenizer args(arguments.toString());
		String planet;

		if(args.hasMoreTokens()){
			args.getStringToken(planet);
		} else {
			sendSyntax(creature);
			return QueueCommand::INVALIDSYNTAX;
		}

		if (args.hasMoreTokens()) {

			rank = args.getIntToken();
			if(rank < 1 || rank > 5) {
				creature->sendSystemMessage("Rank must be between 1 and 5");
				return QueueCommand::INVALIDPARAMETERS;
			}

		} else {
			sendSyntax(creature);
			return QueueCommand::INVALIDSYNTAX;
		}

		if(creature->getZoneServer() == NULL)
			return QueueCommand::GENERALERROR;

		CityManager* cityManager = creature->getZoneServer()->getCityManager();

		if(cityManager == NULL)
			return QueueCommand::GENERALERROR;

		cityManager->sendCityReport(creature, planet, rank);
		return 0;
	}

	static void sendSyntax(CreatureObject* creature){
		String syntax = "/server cityreport [planetname] [rank]";
		creature->sendSystemMessage(syntax);
	}
};


#endif /* CITYREPORTCOMMAND_H_ */
