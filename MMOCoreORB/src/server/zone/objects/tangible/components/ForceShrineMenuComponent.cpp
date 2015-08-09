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

	if (player->hasSkill("force_title_jedi_novice"))
		menuResponse->addRadialMenuItem(213, 3, "@jedi_trials:meditate"); // Meditate

}

int ForceShrineMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID) {
	if (selectedID != 213)
		return 0;

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

	if (!creature->hasSkill("force_title_jedi_rank_02")) {
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

		ZoneServer* zoneServer = ghost->getZoneServer();
		int randomZone = System::random(zoneServer->getZoneCount() - 1);

		ManagedReference<Zone*> zone = zoneServer->getZone(randomZone);
		Vector3 randomTrainer = zone->getCreatureManager()->getRandomJediTrainer();

		if ((randomTrainer.getX() == 0) && (randomTrainer.getY() == 0)) { // No trainers on the zone.
			ManagedReference<Zone*> zone = zoneServer->getZone(0);
			Vector3 randomTrainer = zone->getCreatureManager()->getRandomJediTrainer();
		}

		Vector3 trainerPositionFinal(randomTrainer.getX(), randomTrainer.getY(), 0);

		String zoneName = zone->getZoneName();

		ghost->setTrainerCoordinates(trainerPositionFinal);
		ghost->setTrainerZoneName(zoneName); // For the Waypoint.


		ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

		//Check if inventory is full.
		if (inventory->isContainerFullRecursive()) {
			creature->sendSystemMessage("@jedi_spam:inventory_full_jedi_robe"); //	You have too many items in your inventory. In order to get your Padawan Robe you must clear out at least one free slot.
			return 0;
		}

		ZoneServer* zserv = creature->getZoneServer();

		String PadawanRobe = "object/tangible/wearables/robe/robe_jedi_padawan.iff";
		ManagedReference<SceneObject*> padawanRobe = zserv->createObject(PadawanRobe.hashCode(), 1);
		if (inventory->transferObject(padawanRobe, -1)) {
			inventory->broadcastObject(padawanRobe, true);
		} else {
			padawanRobe->destroyObjectFromDatabase(true);
		}

	} else {

		ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

		//Check if inventory is full.
		if (inventory->isContainerFullRecursive()) {
			creature->sendSystemMessage("@jedi_spam:inventory_full_jedi_robe"); //	You have too many items in your inventory. In order to get your Padawan Robe you must clear out at least one free slot.
			return 0;
		}

		ZoneServer* zserv = creature->getZoneServer();

		String PadawanRobe = "object/tangible/wearables/robe/robe_jedi_padawan.iff";
		ManagedReference<SceneObject*> padawanRobe = zserv->createObject(PadawanRobe.hashCode(), 1);
		if (inventory->transferObject(padawanRobe, -1)) {
			inventory->broadcastObject(padawanRobe, true);
		} else {
			padawanRobe->destroyObjectFromDatabase(true);
		}

	}

	return 0;


}

