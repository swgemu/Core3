/*
 * ForceShrinenMenuComponent.cpp
 *
 *  Created on: 01/23/2012
 *      Author: Valkyra
 */

#include "ForceShrineMenuComponent.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/packets/player/PlayMusicMessage.h"
#include "server/zone/managers/creature/CreatureManager.h"

#include "server/zone/ZoneServer.h"

void ForceShrineMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player){

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	menuResponse->addRadialMenuItem(213, 3, "@jedi_trials:meditate"); // Meditate
}

int ForceShrineMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID) {
	if (selectedID != 213)
		return 0;

	if (creature->getPosture() != CreaturePosture::CROUCHED){
		creature->sendSystemMessage("@jedi_trials:show_respect"); // Must show respect
		return 0;
	}

	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return 0;

	if (ghost->getAdminLevel() < 15)
		return 0;

	if (creature->hasSkill("force_title_jedi_novice") && !creature->hasSkill("force_title_jedi_rank_02")){
		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, SuiWindowType::NONE);
		box->setPromptTitle("@jedi_trials:padawan_trials_title"); // Jedi Trials
		box->setPromptText("@jedi_trials:padawan_trials_completed");

		ghost->addSuiBox(box);
		creature->sendMessage(box->generateMessage());

		SkillManager::instance()->awardSkill("force_title_jedi_rank_02", creature, true, true, true);

		creature->playEffect("clienteffect/entertainer_dazzle_level_3.cef", ""); // Not sure if it's the right one for this.

		PlayMusicMessage* pmm = new PlayMusicMessage("sound/intro.snd");
		creature->sendMessage(pmm);

		ghost->setJediState(2);

		// Trainer number. Pick a random trainer, there are at least 600 in the galaxy.
		CreatureManager* creatureManager = creature->getZone()->getCreatureManager();
		Vector<float>* trainersX = creatureManager->getTrainerObjectsX();
		Vector<float>* trainersY = creatureManager->getTrainerObjectsY();
		Vector<String>* trainerZone = creatureManager->getTrainerZone();
		uint32 trainerNumber = System::random(trainersX->size() - 1);

		int posX = trainersX->get(trainerNumber);
		int posY = trainersY->get(trainerNumber);
		String planetName = trainerZone->get(trainerNumber);

		ghost->setTrainerCoordinates(posX, posY);
		ghost->setTrainerZone(planetName);


		ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

		//Check if inventory is full.
		if (inventory->hasFullContainerObjects()) {
			creature->sendSystemMessage("@jedi_spam:inventory_full_jedi_robe"); //	You have too many items in your inventory. In order to get your Padawan Robe you must clear out at least one free slot.
			return 0;
		}

		ZoneServer* zserv = creature->getZoneServer();

		String PadawanRobe = "object/tangible/wearables/robe/robe_jedi_padawan.iff";
		ManagedReference<SceneObject*> padawanRobe = zserv->createObject(PadawanRobe.hashCode(), 1);
		padawanRobe->sendTo(creature, true);
		inventory->transferObject(padawanRobe, -1);
	}

	else if (!creature->hasSkill("force_title_jedi_novice")){

		int rand = System::random(14) + 1;

		StringBuffer sysmsg;

		sysmsg << "@jedi_trials:force_shrine_wisdom_" << rand;

		creature->sendSystemMessage(sysmsg.toString());

	}

	else if (creature->hasSkill("force_title_jedi_rank_02")){

		ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

		//Check if inventory is full.
		if (inventory->hasFullContainerObjects()) {
			creature->sendSystemMessage("@jedi_spam:inventory_full_jedi_robe"); //	You have too many items in your inventory. In order to get your Padawan Robe you must clear out at least one free slot.
			return 0;
		}

		ZoneServer* zserv = creature->getZoneServer();

		String PadawanRobe = "object/tangible/wearables/robe/robe_jedi_padawan.iff";
		ManagedReference<SceneObject*> padawanRobe = zserv->createObject(PadawanRobe.hashCode(), 1);
		padawanRobe->sendTo(creature, true);
		inventory->transferObject(padawanRobe, -1);

	}

	return 0;


}

