/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GCWSTATUSCOMMAND_H_
#define GCWSTATUSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/chat/StringIdChatParameter.h"

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
		if(zone == NULL)
			return GENERALERROR;

		GCWManager* gcwMan = zone->getGCWManager();

		if(gcwMan == NULL)
			return GENERALERROR;

		int rebelBases = gcwMan->getRebelBaseCount();
		int imperialBases = gcwMan->getImperialBaseCount();

		int rebelScore = gcwMan->getRebelScore();
		int imperialScore = gcwMan->getImperialScore();



		String results = "@faction_perk:gcw_tied";  // Neither the rebellion or the Empire has teh advantage

		if(rebelScore > imperialScore)
			results = "@faction_perk:gcw_rebel_ahead"; // the rebellion has the advantage over the empire
		else if (imperialScore > rebelScore)
			results = "@faction_perk:gcw_imperial_ahead";  // the empire has the advantage over the rebellion

		creature->sendSystemMessage(results);

		// temporary for testing gcw bases
		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
		if(ghost != NULL && ghost->isPrivileged()){
			StringBuffer msg;
			msg << "Rebel Score: " + String::valueOf(rebelScore) << endl;
			msg << "Imperial Score " + String::valueOf(imperialScore) << endl;
			msg << "Rebel Bases: " + String::valueOf(rebelBases) << endl;
			msg << "Imperial Bases: " + String::valueOf(imperialBases);
			creature->sendSystemMessage(msg.toString());
		}
		return SUCCESS;
	}

};

#endif //GCWSTATUSCOMMAND_H_
