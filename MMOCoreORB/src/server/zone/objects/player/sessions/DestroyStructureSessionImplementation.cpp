/*
 * DestroyStructureSessionImplementation.cpp
 *
 *  Created on: Jun 22, 2011
 *      Author: crush
 */

#include "DestroyStructureSession.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/DestroyStructureRequestSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/DestroyStructureCodeSuiCallback.h"
#include "server/zone/objects/structure/StructureObject.h"

int DestroyStructureSessionImplementation::initializeSession() {
	//TODO: Temporary until CreatureObject* dependency removed.
	if (!creatureObject->isPlayerCreature())
		return cancelSession();

	creatureObject->addActiveSession(SessionFacadeType::DESTROYSTRUCTURE, _this);

	Locker _lock(creatureObject, structureObject);

	CreatureObject* player = (CreatureObject*) creatureObject.get();

	String no = "\\#FF6347 @player_structure:can_redeed_no_suffix \\#.";
	String yes = "\\#32CD32 @player_structure:can_redeed_yes_suffix \\#.";

	String redeed = (structureObject->isRedeedable()) ? yes : no;

	StringBuffer maint;
	maint << "@player_structure:redeed_maintenance \\#" << ((structureObject->isRedeedable()) ? "32CD32 " : "FF6347 ") << structureObject->getSurplusMaintenance() << "/" << structureObject->getRedeedCost() << "\\#.";

	StringBuffer entry;
	entry << "@player_structure:confirm_destruction_d1 ";
	entry << "@player_structure:confirm_destruction_d2 \n\n";
	entry << "@player_structure:confirm_destruction_d3a ";
	entry << "\\#32CD32 @player_structure:confirm_destruction_d3b \\#. ";
	entry << "@player_structure:confirm_destruction_d4 \n";
	entry << "@player_structure:redeed_confirmation " << redeed;

	StringBuffer cond;
	cond << "@player_structure:redeed_condition \\#32CD32 " << (structureObject->getMaxCondition() - structureObject->getConditionDamage()) << "/" << structureObject->getMaxCondition() << "\\#.";

	ManagedReference<SuiListBox*> sui = new SuiListBox(player);
	sui->setCallback(new DestroyStructureRequestSuiCallback(creatureObject->getZoneServer()));
	sui->setCancelButton(true, "@no");
	sui->setOkButton(true, "@yes");
	sui->setUsingObject(structureObject);
	sui->setPromptTitle(structureObject->getObjectName()->getDisplayedName());
	sui->setPromptText(entry.toString());

	sui->addMenuItem("@player_structure:can_redeed_alert " + redeed);
	sui->addMenuItem(cond.toString());
	sui->addMenuItem(maint.toString());

	player->getPlayerObject()->addSuiBox(sui);
	player->sendMessage(sui->generateMessage());

	return 0;
}

int DestroyStructureSessionImplementation::sendDestroyCode() {
	//TODO: Temporary until CreatureObject* dependency removed.
	if (!creatureObject->isPlayerCreature())
		return cancelSession();

	Locker _lock(creatureObject, structureObject);

	CreatureObject* player = (CreatureObject*) creatureObject.get();

	destroyCode = System::random(899999) + 100000;

	String no = "\\#FF6347 @player_structure:will_not_redeed_confirm \\#.";
	String yes = "\\#32CD32 @player_structure:will_redeed_confirm \\#.";

	String redeed = (structureObject->isRedeedable()) ? yes : no;

	StringBuffer entry;
	entry << "@player_structure:your_structure_prefix ";
	entry << redeed << " @player_structure:will_redeed_suffix \n\n";
	entry << "Code: " << destroyCode;

	ManagedReference<SuiInputBox*> sui = new SuiInputBox(player);
	sui->setCallback(new DestroyStructureCodeSuiCallback(player->getZoneServer()));
	sui->setUsingObject(structureObject);
	sui->setPromptTitle("@player_structure:confirm_destruction_t"); //Confirm Structure Deletion
	sui->setPromptText(entry.toString());
	sui->setCancelButton(true, "@cancel");
	sui->setMaxInputSize(6);

	player->getPlayerObject()->addSuiBox(sui);
	player->sendMessage(sui->generateMessage());

	return 0;
}

int DestroyStructureSessionImplementation::destroyStructure() {
	creatureObject->sendSystemMessage("@player_structure:processing_destruction"); //Processing confirmed structure destruction...

	if (structureObject == NULL || structureObject->getZone() == NULL)
		return cancelSession();

	StructureManager* structureManager = structureObject->getZone()->getStructureManager();
	structureManager->redeedStructure(creatureObject);
}
