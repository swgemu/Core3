/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INSURECOMMAND_H_
#define INSURECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/sui/callbacks/InsuranceMenuSuiCallback.h"

class InsureCommand : public QueueCommand {
public:

	InsureCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		SceneObject* term = NULL;

		CloseObjectsVector* closeSceneObjects = (CloseObjectsVector*) creature->getCloseObjects();

		SortedVector<QuadTreeEntry*> closeObjects;
		closeSceneObjects->safeCopyTo(closeObjects);

		for (int i=0; i < closeObjects.size(); i++) {
			SceneObject* scno = cast<SceneObject*>(closeObjects.get(i));

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
					suiInsuranceMenuBox->addMenuItem(item->getDisplayedName(), item->getObjectID());
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
