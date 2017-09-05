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
#include "server/zone/objects/intangible/tasks/StorePetTask.h"
#include "server/zone/managers/planet/PlanetManager.h"

void DroidMaintenanceSessionImplementation::initialize() {
	ManagedReference<CreatureObject*> creature = this->player.get();
	ManagedReference<DroidMaintenanceModuleDataComponent*> module = this->maintModule.get();
	// get the total credits this guy has right now!
	availableCredits = creature->getCashCredits() + creature->getBankCredits();
	module->getStructureList(&structures, creature->getZoneServer(),creature->getZone()->getZoneCRC());
	maintenance.removeAll();
	selectedFees = 0;
	fees.removeAll();
}

void DroidMaintenanceSessionImplementation::sendMaintanceRunBox(){
	// main ui
	selectedStructure = NULL;

	ManagedReference<CreatureObject*> creature = this->player.get();

	if (structures.size() == 0 && maintenance.isEmpty()) {
		creature->sendSystemMessage("@pet/droid_modules:droid_maint_no_valid_struct");
		cancelSession();
		return;
	}

	ManagedReference<DroidMaintenanceModuleDataComponent*> module = this->maintModule.get();

	if (module == nullptr)
		return;

	ManagedReference<SuiListBox*> box = new SuiListBox(creature, SuiWindowType::DROID_MAINTENANCE_RUN_LIST, SuiListBox::HANDLETHREEBUTTON);
	box->setCallback(new DroidMaintenanceSessionRunMenuSuiCallback(creature->getZoneServer()));
	// we need to add additional text i think
	StringBuffer promptText;
	box->setPromptTitle("@pet/droid_modules:droid_maint_list_title"); // Maintenance Run
	SuiListBox* b;
	box->setOkButton(true, "@go");
	box->setOtherButton(true,"@add");
	box->setCancelButton(true, "@cancel");
	// we have all we need in the session.
	int addCount = 0;
	// we need to add a line item for every structure on this droids list, then track amount per structure + fees + interplanetary. i.e. if not interplanetary capable, dont show them.
	//Vector<StructureObject*> list = module->getStructureList(creature->getZoneServer(),creature->getZone()->getZoneCRC());
	for(int i=0;i<structures.size();i++) {
		ManagedReference<StructureObject*> obj = structures.elementAt(i);
		StringBuffer buff;
		String zoneName = "the void";
		if (obj->getZone() != NULL) {
			zoneName = obj->getZone()->getZoneName();
		}
		// assume 30 chars per section, 3 sections so 90 chars.
		int nameLength = obj->getDisplayedName().length();
		int zoneNameLength = zoneName.length();
		buff << obj->getDisplayedName();
		if (nameLength < 30) {
			// pad the diff to teh end
			for(int x=0;x<30-nameLength;x++)
				buff << " ";
			nameLength = 30;
		}
		int finalOffset = zoneName.length() + 15;

		buff << "\t" << zoneName << "(" << String::valueOf((int)obj->getPositionX()) << "," << String::valueOf((int)obj->getPositionY()) << ")";
		if (maintenance.contains(obj->getObjectID())) {
			if (addCount == 0)
				promptText << "@pet/droid_modules:droid_maint_list_header\n\n";
			addCount += 1;
			promptText << buff.toString();
			if (finalOffset < 30) {
				for(int x=0;x<30-finalOffset;x++)
					promptText << " ";
			}
			promptText << "+" << maintenance.get(obj->getObjectID()) << "\n";
		} else {
			box->addMenuItem( buff.toString(), obj->getObjectID());
		}
	}
	if (addCount > 0)
		promptText << "\n";
	promptText << "@pet/droid_modules:droid_maint_list_prompt"; // Please select a structure to perform a maintenance run on. Once all structures to be maintained have been selected, press the Go button.
	box->setPromptText(promptText.toString());
	creature->getPlayerObject()->addSuiBox(box);
	creature->sendMessage(box->generateMessage());
}

void DroidMaintenanceSessionImplementation::sendMaintenanceTransferBox(){
	// add result
	if (selectedStructure == NULL) {
		cancelSession();
		return;
	}
	ManagedReference<CreatureObject*> creature = this->player.get();

	if (creature == NULL) {
		cancelSession();
		return;
	}

	ManagedReference<DroidMaintenanceModuleDataComponent*> module = this->maintModule.get();

	if (module == nullptr) {
		cancelSession();
		return;
	}

	// create transfer box
	ManagedReference<SuiTransferBox*> sui = new SuiTransferBox(creature,SuiWindowType::DROID_ADD_STRUCTURE_AMOUNT);
	sui->setCallback(new DroidMaintenanceSessionAddCreditsSuiCallback(creature->getZoneServer()));
	sui->setPromptTitle("@pet/droid_modules:droid_maint_amount_title"); //Select Amount
	bool offplanet = false;
	Zone* zoneStructure = selectedStructure->getZone();
	Zone* zoneCreature = creature->getZone();

	if (!zoneStructure || !zoneCreature) {
		cancelSession();
		return;
	}

	if (zoneStructure != zoneCreature)
		offplanet = true;

	StringBuffer promptText = "@pet/droid_modules:droid_maint_amount_prompt \n@player_structure:current_maint_pool "+ String::valueOf(selectedStructure->getSurplusMaintenance())+"cr";
	selectedFees = 0;
	if (offplanet) {
		PlanetManager* planetManager = zoneCreature->getPlanetManager();
		if (planetManager == NULL) {
			cancelSession();
			return;
		}
		int fee = planetManager->getTravelFare(zoneStructure->getZoneName(),zoneCreature->getZoneName());
		selectedFees = fee;
		promptText << "\n@pet/droid_modules:droid_maint_diff_planet_prefix " << fee << " @pet/droid_modules:droid_maint_diff_planet_suffix \n";
	}
	sui->setPromptText(promptText.toString());
	// check for off planet, it has a fee
	sui->addFrom("@player_structure:total_funds",String::valueOf(availableCredits),String::valueOf(availableCredits), "1");
	sui->addTo("@player_structure:to_pay", "0", "0", "1");
	creature->getPlayerObject()->addSuiBox(sui);
	creature->sendMessage(sui->generateMessage());
}
void DroidMaintenanceSessionImplementation::addCreditsToCurrentStructure(int amount) {
	// WE know the current structure add it to our pay list.
	if (selectedStructure == NULL) {
		cancelSession();
		return;
	}
	this->maintenance.put(selectedStructure->getObjectID(),amount);
	if (selectedFees > 0){
		fees.add(selectedFees);
	}
}
void DroidMaintenanceSessionImplementation::performMaintenanceRun(){
    // launch the task and set droid cooldown.
	ManagedReference<CreatureObject*> creature = this->player.get();

	if (creature == nullptr) {
		return;
	}

	if (maintenance.size() == 0) {
		creature->sendSystemMessage("@pet/droid_modules:droid_maint_empty_maint_run");
		sendMaintanceRunBox();
		return;
	}

	Reference<DroidMaintenanceModuleDataComponent*> module = this->maintModule.get();

	if (module == nullptr) {
		cancelSession();
		return;
	}

	ManagedReference<DroidObject*> droid = module->getDroidObject();

	if (droid == nullptr) {
		return;
	}

	Locker locker(creature);
	Locker droidLock(droid, creature);

	Zone* zone = droid->getZone();

	if (zone == NULL)
		return;

	// pay all structures
	long totalCosts = 0;
	long totalFees = 0;
	for(int i=0;i<fees.size();i++)
		totalFees += fees.elementAt(i);
	for(int i =0; i< maintenance.size();i++)
		totalCosts += maintenance.elementAt(i).getValue();
	// pay fees
	if (availableCredits < totalCosts + totalFees) {
		if (availableCredits > totalCosts)
			creature->sendSystemMessage("@pet/droid_modules:droid_maint_cant_travel");
		else
			creature->sendSystemMessage("@pet/droid_modules:droid_maint_not_enough_cash");
		cancelSession();
		return;
	}
	// he had enough credits, so lets perform the run .

	long time = module->calculateRunTime(maintenance, zone->getZoneName(), droid);
	long powerCost = time/1000/60/15;
	// check for power now as it may hit zero while we are in the menu
	if (!droid->hasPower()) {
		creature->sendSystemMessage("@pet/droid_modules:not_enough_power"); // Your droid dosnt have enough power to do that.
		cancelSession();
		return;
	}
	// we might get killed off due to no power, do we let it run anyways and jsut leave droid as drained for later.
	// that seems ok he wont be able to touch the droid for a long time anyways so lets roleplay out it just runs out in low power situation.
	// we had enough to run.
	if (creature->getCashCredits() >= totalFees) {
		creature->subtractCashCredits(totalFees);
	} else {
		int payedSoFar = creature->getCashCredits();
		creature->subtractCashCredits(payedSoFar);
		creature->subtractBankCredits(totalFees - payedSoFar);
	}
	// now the structures.
	module->payStructures(creature,maintenance);
	// calculate time
	// we got milliseconds convert to minutes
	long minutes = time/1000; // seconds
	const static String abbrvs[3] = { "seconds", "minutes, ", "hours" };
	const static int intervals[3] = { 1, 60, 3600 };
	int values[3] = { 0, 0, 0 };
	StringBuffer str;
	str << "Maintenance run started. Completion ETA: ";
	for (int i = 2; i > -1; --i) {
		values[i] = floor((float) minutes / intervals[i]);
		minutes -= values[i] * intervals[i];
		if (values[i] > 0) {
			if (str.length() > 0){
				str << " ";
			}
			str << values[i] << " " << abbrvs[i];
		}
	}

	creature->sendSystemMessage(str.toString());

	// store the pet off and set the call cooldown.
	droid->getCooldownTimerMap()->updateToCurrentAndAddMili("call_cooldown",time);
	Reference<StorePetTask*> task = new StorePetTask(this->player.get(), droid);
	droid->usePower(DroidObject::MAX_POWER); // According to what i read, doing the run drains all power from teh droid.
	task->execute();
}
int DroidMaintenanceSessionImplementation::cancelSession() {
	auto strongPlayeRef = player.get();

	if (strongPlayeRef != nullptr)
		strongPlayeRef->dropActiveSession(SessionFacadeType::DROIDMAINTENANCERUN);

	selectedStructure = NULL;
	structures.removeAll();
	maintenance.removeAll();
	return 0;
}
