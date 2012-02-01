/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef INSURECOMMAND_H_
#define INSURECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/sui/callbacks/InsuranceMenuSuiCallback.h"

class InsureCommand : public QueueCommand {
public:

	InsureCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		SceneObject* term = NULL;

		SortedVector<ManagedReference<QuadTreeEntry*> >* closeSceneObjects = creature->getCloseObjects();

		info(String::valueOf(closeSceneObjects->size()));

		for (int i=0; i < closeSceneObjects->size(); i++) {
			SceneObject* scno = cast<SceneObject*>(closeSceneObjects->get(i).get());

			if (scno == NULL)
				continue;

			if (scno->getGameObjectType() == SceneObjectType::INSURANCE) {
				term = scno;
				break;
			}
		}

		if (term == NULL) {
			return GENERALERROR;
		}


		if (creature->isInRange(term, 15.0f)) {
			ManagedReference<SuiListBox*> suiInsuranceMenuBox = new SuiListBox(creature, SuiWindowType::INSURANCE_MENU, SuiListBox::HANDLETHREEBUTTON);

			suiInsuranceMenuBox->setPromptTitle("@sui:mnu_insure");
			suiInsuranceMenuBox->setPromptText("Select which items you would like to buy insurance for from the list below.");

			PlayerManager* playerManager = creature->getZoneServer()->getPlayerManager();

			Vector<ManagedReference<SceneObject*> > insurableItems = playerManager->getInsurableItems(creature);

			if (insurableItems.size() == 0) {
				creature->sendSystemMessage("@terminal_ui:no_insurable_items");
				return GENERALERROR;
			}

			suiInsuranceMenuBox->setCallback(new InsuranceMenuSuiCallback(creature->getZoneServer()));

			for (int i = 0; i < insurableItems.size(); i++) {
				SceneObject* item = insurableItems.get(i);

				if (item != NULL)
					suiInsuranceMenuBox->addMenuItem(item->getObjectName()->getDisplayedName(), item->getObjectID());
			}

			suiInsuranceMenuBox->setCancelButton(true, "Cancel");
			suiInsuranceMenuBox->setOtherButton(true, "@sui:mnu_insure_all");
			suiInsuranceMenuBox->setUsingObject(term);

			suiInsuranceMenuBox->setForceCloseDistance(32);

			creature->getPlayerObject()->addSuiBox(suiInsuranceMenuBox);
			creature->sendMessage(suiInsuranceMenuBox->generateMessage());
		} else {
			StringIdChatParameter params;
			params.setStringId("@container_error_message:container09_prose");
			params.setTT("@terminal_name:terminal_insurance");
			creature->sendSystemMessage(params);
			return GENERALERROR;
		}



		return SUCCESS;
	}

};

#endif //INSURECOMMAND_H_
