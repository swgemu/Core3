/*
 * DroidMaintenanceSessionImplementation.cpp
 *
 *  Created on: 1 13, 2015
 *      Author: Klivian
 */

#include "server/zone/objects/player/sessions/DroidMaintenanceSession.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/player/sessions/sui/DroidMaintenanceSessionRunMenuSuiCallback.h"
#include "server/zone/objects/player/sessions/sui/DroidMaintenanceSessionAddCreditsSuiCallback.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"
#include "server/zone/objects/tangible/components/droid/DroidMaintenanceModuleDataComponent.h"
#include "server/zone/objects/structure/StructureObject.h"


void DroidMaintenanceSessionImplementation::initialize() {
	ManagedReference<CreatureObject*> creature = this->player.get();
	ManagedReference<DroidMaintenanceModuleDataComponent*> module = this->maintModule.get();
	// get the total credits this guy has right now!
	availableCredits = creature->getCashCredits() + creature->getBankCredits();
	module->getStructureList(&structures, creature->getZoneServer(),creature->getZone()->getZoneCRC());
}

void DroidMaintenanceSessionImplementation::sendMaintanceRunBox(){
	// main ui
	selectedStructure = NULL;
	ManagedReference<CreatureObject*> creature = this->player.get();
	ManagedReference<DroidMaintenanceModuleDataComponent*> module = this->maintModule.get();

	ManagedReference<SuiListBox*> box = new SuiListBox(creature, SuiWindowType::DROID_MAINTENANCE_RUN_LIST, SuiListBox::HANDLETHREEBUTTON);
	box->setCallback(new DroidMaintenanceSessionRunMenuSuiCallback(creature->getZoneServer()));
	// we need to add additional text i think
	box->setPromptText("@pet/droid_modules:droid_maint_list_prompt"); // Please select a structure to perform a maintenance run on. Once all structures to be maintained have been selected, press the Go button.
	box->setPromptTitle("@pet/droid_modules:droid_maint_list_title"); // Maintenance Run
	SuiListBox* b;
	box->setOkButton(true, "@go");
	box->setOtherButton(true,"@add");
	box->setCancelButton(true, "@cancel");
	// we have all we need in the session.
	if (structures.size() == 0) {
		creature->sendSystemMessage("@pet/droid_modules:droid_maint_no_valid_struct");
		cancelSession();
		return;
	}
	// we need to add a line item for every structure on this droids list, then track amount per structure + fees + interplanetary. i.e. if not interplanetary capable, dont show them.
	//Vector<StructureObject*> list = module->getStructureList(creature->getZoneServer(),creature->getZone()->getZoneCRC());
	for(int i=0;i<structures.size();i++) {
		ManagedReference<StructureObject*> obj = structures.elementAt(i);
		StringBuffer buff;
		String zoneName = "the void";
		if (obj->getZone() != NULL) {
			zoneName = obj->getZone()->getZoneName();
		}
		buff << obj->getDisplayedName() <<"\t\t\t" << zoneName << "(" << String::valueOf((int)obj->getPositionX()) << "," << String::valueOf((int)obj->getPositionY()) << ")";
		box->addMenuItem( buff.toString(), obj->getObjectID());
	}
	creature->getPlayerObject()->addSuiBox(box);
	creature->sendMessage(box->generateMessage());
}

void DroidMaintenanceSessionImplementation::sendMaintenanceTransferBox(){
	// add result
	if (selectedStructure == NULL) {
		System::out << "selected Structure is NULL\n";
		cancelSession();
		return;
	}
	ManagedReference<CreatureObject*> creature = this->player.get();
	ManagedReference<DroidMaintenanceModuleDataComponent*> module = this->maintModule.get();
	// create transfer box
	ManagedReference<SuiTransferBox*> sui = new SuiTransferBox(creature,SuiWindowType::DROID_ADD_STRUCTURE_AMOUNT);
	sui->setCallback(new DroidMaintenanceSessionAddCreditsSuiCallback(creature->getZoneServer()));
	sui->setPromptTitle("@pet/droid_modules:droid_maint_amount_title"); //Select Amount
	sui->setPromptText("@pet/droid_modules:droid_maint_amount_prompt \n@player_structure:current_maint_pool "+ String::valueOf(selectedStructure->getSurplusMaintenance())+"cr");
	sui->addFrom("@player_structure:total_funds",String::valueOf(availableCredits),String::valueOf(availableCredits), "1");
	sui->addTo("@player_structure:to_pay", "0", "0", "1");
	creature->getPlayerObject()->addSuiBox(sui);
	creature->sendMessage(sui->generateMessage());
}

void DroidMaintenanceSessionImplementation::performMaintenanceRun(){
 // launch the task and set droid cooldown.

}
int DroidMaintenanceSessionImplementation::cancelSession() {
	player.get()->dropActiveSession(SessionFacadeType::DROIDMAINTENANCERUN);
	selectedStructure = NULL;
	return 0;
}
