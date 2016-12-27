/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TENDDAMAGECOMMAND_H_
#define TENDDAMAGECOMMAND_H_

#include "TendCommand.h"

class TendDamageCommand : public TendCommand {
public:

	TendDamageCommand(const String& name, ZoneProcessServer* server)
			: TendCommand(name, server) {
		effectName = "clienteffect/healing_healdamage.cef";

		mindCost = 200;
		mindWoundCost = 5;

		tendDamage = true;

		healthHealed = 50;
		actionHealed = 50;

		//defaultTime = 5.0;
		range = 6.0;
	}

};

#endif //TENDDAMAGECOMMAND_H_
