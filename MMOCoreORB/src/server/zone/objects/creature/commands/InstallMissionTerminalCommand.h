/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INSTALLMISSIONTERMINALCOMMAND_H_
#define INSTALLMISSIONTERMINALCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/creature/commands/sui/InstallMissionTerminalSuiCallback.h"

class InstallMissionTerminalCommand : public QueueCommand {
public:

	InstallMissionTerminalCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		PlayerObject* ghost = creature->getPlayerObject();
		if (ghost == NULL)
			return GENERALERROR;

		if (!ghost->hasAbility("installmissionterminal"))
			return GENERALERROR;

		ManagedReference<CityRegion*> city = creature->getCityRegion();

		if (city == NULL)
			return GENERALERROR;

		if (!city->isMayor(creature->getObjectID()))
			return GENERALERROR;

		ManagedReference<SuiListBox*> suiTerminalType = new SuiListBox(creature, SuiWindowType::INSTALL_MISSION_TERMINAL, 0);
		suiTerminalType->setCallback(new InstallMissionTerminalSuiCallback(server->getZoneServer()));

		suiTerminalType->setPromptTitle("@city/city:job_n"); // Install Mission Terminal
		suiTerminalType->setPromptText("@city/city:job_d");

		suiTerminalType->addMenuItem("@city/city:mt_generic", 0);
		suiTerminalType->addMenuItem("@city/city:mt_artisan", 1);
		suiTerminalType->addMenuItem("@city/city:mt_bounty", 2);
		suiTerminalType->addMenuItem("@city/city:mt_entertainer", 3);
		suiTerminalType->addMenuItem("@city/city:mt_scout", 4);
		suiTerminalType->addMenuItem("@city/city:mt_imperial", 5);
		suiTerminalType->addMenuItem("@city/city:mt_rebel", 6);

		ghost->addSuiBox(suiTerminalType);
		creature->sendMessage(suiTerminalType->generateMessage());

		return SUCCESS;
	}

};

#endif //INSTALLMISSIONTERMINALCOMMAND_H_
