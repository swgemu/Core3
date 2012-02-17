/*
 * WeatherCommand.h
 *
 *  Created on: 31/03/2011
 *      Author: victor
 */

#ifndef WEATHERCOMMAND_H_
#define WEATHERCOMMAND_H_

#include "engine/engine.h"
#include "server/zone/managers/weather/WeatherManager.h"

class WeatherCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		if (!creature->isPlayerCreature())
			return 1;

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(creature);
		ManagedReference<WeatherManager*> weatherManager = player->getZone()->getPlanetManager()->getWeatherManager();

		//Check for valid zone. Handle this in your manager.
		//if (player->getZone()->getZoneID() > 9) {
		//	player->sendSystemMessage("You can't use the weather command in this zone.");
	//		return 1;
		//}

		//Parse the weather command.
		StringTokenizer tokenizer(arguments.toString());
		if (!tokenizer.hasMoreTokens()) {
			sendSyntax(player);
			return 1;
		}

		String command;
		tokenizer.getStringToken(command);
		command = command.toLowerCase();

		if (command == "enable") {
			weatherManager->enableWeather(player);

		} else if (command == "disable") {
			weatherManager->disableWeather(player);

		} else if (command == "change") {
			if (!tokenizer.hasMoreTokens()) {
				sendSyntax(player);
				return 1;
			}

			int weatherID = tokenizer.getIntToken();
			if (!(weatherID >= 0 && weatherID < 5)) {
				sendSyntax(player);
				return 1;
			}

			weatherManager->changeWeather(player, weatherID);

		} else if (command == "info") {

			weatherManager->printInfo(player);

		} else {
			sendSyntax(player);
			return 1;
		}

		return 0;

	}

	static void sendSyntax(CreatureObject* player) {
		if (player != NULL)
			player->sendSystemMessage("Syntax: /server weather [enable/disable/info/change] [0-4]");
	}

};

#endif /* WEATHERCOMMAND_H_ */
