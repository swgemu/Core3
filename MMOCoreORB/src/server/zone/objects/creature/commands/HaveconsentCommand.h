/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HAVECONSENTCOMMAND_H_
#define HAVECONSENTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/RevokeConsentSuiCallback.h"

class HaveconsentCommand : public QueueCommand {
public:

	HaveconsentCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		CreatureObject* player = cast<CreatureObject*>(creature);

		PlayerObject* ghost = player->getPlayerObject();

		ghost->closeSuiWindowType(SuiWindowType::CLONE_REQUEST);

		if (ghost->getConsentListSize() <= 0) {
			player->sendSystemMessage("@error_message:consent_to_empty"); //You have not granted consent to anyone.
			return GENERALERROR;
		}

		Reference<SuiListBox*> consentBox = new SuiListBox(player, SuiWindowType::MEDIC_CONSENT);
		ZoneServer* server = player->getZoneServer();
		consentBox->setCallback(new RevokeConsentSuiCallback(server));
		consentBox->setPromptTitle("@ui:consent_title");
		consentBox->setPromptText("All players whom you have given your consent to are listed below.\n\nHighlight a player's name and click OK to revoke consent.");
		consentBox->setCancelButton(true, "");

		for (int i = 0; i < ghost->getConsentListSize(); ++i) {
			String entryName = ghost->getConsentName(i);

			if (!entryName.isEmpty())
				consentBox->addMenuItem(entryName);
		}

		player->getPlayerObject()->addSuiBox(consentBox);
		player->sendMessage(consentBox->generateMessage());

		return SUCCESS;
	}

};

#endif //HAVECONSENTCOMMAND_H_
