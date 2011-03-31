/*
 * WeatherCommand.h
 *
 *  Created on: 31/03/2011
 *      Author: victor
 */

#ifndef WEATHERCOMMAND_H_
#define WEATHERCOMMAND_H_

#include "engine/engine.h"

class WeatherCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		return 0;
	}
};

#endif /* WEATHERCOMMAND_H_ */
