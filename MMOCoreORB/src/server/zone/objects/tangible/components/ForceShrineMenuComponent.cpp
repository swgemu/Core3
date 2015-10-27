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
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/player/sui/callbacks/JediTrialsQueryCallback.h"
#include "server/zone/objects/player/sui/callbacks/JediTrialsRestartCallback.h"
#include "server/zone/objects/player/sui/callbacks/JediTrialsAbortCallback.h"

#include "server/zone/ZoneServer.h"

void ForceShrineMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player){

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	if (player->hasSkill("force_title_jedi_novice")) {
		menuResponse->addRadialMenuItem(213, 3, "@jedi_trials:meditate"); // Meditate

		if (player->getScreenPlayState("trials:padawan:currentTrial") != 0) {
			menuResponse->addRadialMenuItem(214, 3, "@jedi_trials:button_restart"); // Restart Current Trial
			menuResponse->addRadialMenuItem(215, 3, "@jedi_trials:button_abort_padawan"); // Quit Padawan Trials
		}
	}


}

int ForceShrineMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID) {
	if (selectedID == 213) {

		if (!creature->hasSkill("force_title_jedi_novice"))
			return 0;

		if (creature->getPosture() != CreaturePosture::CROUCHED){
			creature->sendSystemMessage("@jedi_trials:show_respect"); // Must show respect
			return 0;
		} else {
			int rand = System::random(14) + 1;
			StringBuffer sysmsg;
			sysmsg << "@jedi_trials:force_shrine_wisdom_" << rand;

			creature->sendSystemMessage(sysmsg.toString());
		}

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == NULL)
			return 0;

		ZoneServer* zserv = creature->getZoneServer();

		if (zserv == NULL)
			return 0;

		if (!creature->hasSkill("force_title_jedi_rank_02") && (creature->getScreenPlayState("VillageJediProgression") == 32)) {
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

			// Find a trainer.
			findTrainerObject(creature, ghost.get());

			ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

			//Check if inventory is full.
			if (inventory->isContainerFullRecursive()) {
				creature->sendSystemMessage("@jedi_spam:inventory_full_jedi_robe"); //	You have too many items in your inventory. In order to get your Padawan Robe you must clear out at least one free slot.
				return 0;
			}

			String PadawanRobe = "object/tangible/wearables/robe/robe_jedi_padawan.iff";
			ManagedReference<SceneObject*> padawanRobe = zserv->createObject(PadawanRobe.hashCode(), 1);
			if (inventory->transferObject(padawanRobe, -1)) {
				inventory->broadcastObject(padawanRobe, true);
			} else {
				padawanRobe->destroyObjectFromDatabase(true);
			}

		} else if (creature->getScreenPlayState("VillageJediProgression") == 16 && creature->getScreenPlayState("trials:padawan:currentTrial") == 0) {

			ZoneServer* zserv = creature->getZoneServer();
			ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, SuiWindowType::NONE);
			box->setPromptTitle("@jedi_trials:force_shrine_title"); // Meditating at a Force Shrine...
			box->setPromptText("@jedi_trials:padawan_trials_start_query"); // You are eligible to undertake the Jedi Padawan trials. Would you like to start them?
			box->setCallback(new JediTrialsQuerySuiCallback(zserv));

			ghost->addSuiBox(box);
			creature->sendMessage(box->generateMessage());


		} else if (creature->hasSkill("force_title_jedi_rank_02")) {

			ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

			//Check if inventory is full.
			if (inventory->isContainerFullRecursive()) {
				creature->sendSystemMessage("@jedi_spam:inventory_full_jedi_robe"); //	You have too many items in your inventory. In order to get your Padawan Robe you must clear out at least one free slot.
				return 0;
			}

			String PadawanRobe = "object/tangible/wearables/robe/robe_jedi_padawan.iff";
			ManagedReference<SceneObject*> padawanRobe = zserv->createObject(PadawanRobe.hashCode(), 1);
			if (inventory->transferObject(padawanRobe, -1)) {
				inventory->broadcastObject(padawanRobe, true);
			} else {
				padawanRobe->destroyObjectFromDatabase(true);
			}

		}

		return 0;

	} else if (selectedID == 214) {

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == NULL)
			return 0;

		ZoneServer* zserv = creature->getZoneServer();
		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, SuiWindowType::NONE);
		box->setPromptTitle("@jedi_trials:force_shrine_title"); // Meditating at a Force Shrine...
		box->setPromptText("@jedi_trials:padawan_trials_abort_confirmation"); // Quitting the Jedi Padawan trials will remove all progress you've made up to this point in the trials, though you will remain eligilbie to attempt them again in the future should you wish to do so. Are you certain you wish to quit the Jedi Padawan trials?
		box->setCallback(new JediTrialsAbortSuiCallback(zserv));

		ghost->addSuiBox(box);
		creature->sendMessage(box->generateMessage());
	} else if (selectedID == 215) {

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == NULL)
			return 0;

		ZoneServer* zserv = creature->getZoneServer();
		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, SuiWindowType::NONE);
		box->setPromptTitle("@jedi_trials:force_shrine_title"); // Meditating at a Force Shrine...
		box->setPromptText("@jedi_trials:padawan_trials_restart_confirmation"); //Restarting your current Jedi Padawan trial task will erase all of your progress on that task to this point. Are you certain you wish to restart your current task?
		box->setCallback(new JediTrialsRestartSuiCallback(zserv));

		ghost->addSuiBox(box);
	}

	return 0;
}

void ForceShrineMenuComponent::findTrainerObject(CreatureObject* player, PlayerObject* ghost) {

	// Trainer number. Pick a random trainer, there are at least 600 in the galaxy.
	ZoneServer* zserv = player->getZoneServer();
	Vector<String> trainerTypes;

	// Map categories defined here.
	trainerTypes.add("trainer_brawler");
	trainerTypes.add("trainer_artisan");
	trainerTypes.add("trainer_scout");
	trainerTypes.add("trainer_marksman");
	trainerTypes.add("trainer_entertainer");
	trainerTypes.add("trainer_medic");

	bool found = false;
	Vector3 coords;
	String zoneName = "";

	// This specifies the number of attempts at a retry. The first is min, second int is max amount of attemps.
	int counter = 0;
	int retriesCounter = 40;

	while (!found && counter < retriesCounter) {
		// Increment counter to prevent infinite loop.
		++counter;

		Zone* zone = zserv->getZone(System::random(zserv->getZoneCount() - 1));

		if (zone == NULL || zone->getZoneName() == "tutorial") {
			continue;
		}


		SortedVector<ManagedReference<SceneObject*> > trainers = zone->getPlanetaryObjectList(trainerTypes.get(System::random(trainerTypes.size() - 1)));

		int size = trainers.size();

		if (size <= 0) {
			continue;
		}

		ManagedReference<SceneObject*> trainer = trainers.get(System::random(size - 1));

		if (trainer == NULL) {
			continue;
		}

		ManagedReference<CreatureObject*> trainerCreo = trainer.castTo<CreatureObject*>();

		if (trainerCreo == NULL) {
			continue;
		}

		if (!trainerCreo->isTrainerCreature()) {
			continue;
		}

		ManagedReference<CityRegion*> city = trainerCreo->getCityRegion();

		// Make sure it's not a player-city trainer.
		if (city != NULL && !city->isClientRegion()){
			continue;
		}

		zoneName = trainerCreo.get()->getZone()->getZoneName();
		coords = trainerCreo.get()->getWorldPosition();
		found = true;

	}

	ghost->setTrainerCoordinates(coords);
	ghost->setTrainerZoneName(zoneName); // For the Waypoint.
}
