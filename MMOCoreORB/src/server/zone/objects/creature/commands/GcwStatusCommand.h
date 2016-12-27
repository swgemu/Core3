/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GCWSTATUSCOMMAND_H_
#define GCWSTATUSCOMMAND_H_

#include "server/zone/Zone.h"
#include "server/zone/managers/gcw/GCWManager.h"

class GcwStatusCommand : public QueueCommand {
public:

	GcwStatusCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		Zone* zone = creature->getZone();
		if (zone == NULL)
			return GENERALERROR;

		GCWManager* gcwMan = zone->getGCWManager();

		if (gcwMan == NULL)
			return GENERALERROR;

		// temporary for testing gcw bases
		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost != NULL && ghost->isPrivileged()) {
			int rebelBases = gcwMan->getRebelBaseCount();
			int imperialBases = gcwMan->getImperialBaseCount();

			int rebelScore = gcwMan->getRebelScore();
			int imperialScore = gcwMan->getImperialScore();

			StringBuffer msg;
			msg << "Rebel Score: " + String::valueOf(rebelScore) << endl;
			msg << "Imperial Score " + String::valueOf(imperialScore) << endl;
			msg << "Rebel Bases: " + String::valueOf(rebelBases) << endl;
			msg << "Imperial Bases: " + String::valueOf(imperialBases);

			creature->sendSystemMessage(msg.toString());
		} else {
			creature->sendSystemMessage("@gcw:gcw_status_info"); // To see the status of the Galactic Civil War, either talk to your local factional recruiter, or read the newsnet terminals in your nearest starport.
		}

		return SUCCESS;
	}

};

#endif //GCWSTATUSCOMMAND_H_
