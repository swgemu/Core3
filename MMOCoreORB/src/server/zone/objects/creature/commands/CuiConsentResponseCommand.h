/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CUICONSENTRESPONSECOMMAND_H_
#define CUICONSENTRESPONSECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CuiConsentResponseCommand : public QueueCommand {
public:

	CuiConsentResponseCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		//if (!checkStateMask(creature))
			//return INVALIDSTATE;

		//if (!checkInvalidLocomotions(creature))
			//return INVALIDLOCOMOTION;

		error("CuiConsentResponseCommand got called!!!!!!!!!!!!!!!!!!!!");

		return SUCCESS;
	}

};

#endif //CUICONSENTRESPONSECOMMAND_H_
