/*
 * RecruitSkillTrainer.h
 *
 *  Created on: Apr. 26 2012
 *      Author: TragD
 */

#ifndef RECRUITSKILLTRAINERCALLBACK_H_
#define RECRUITSKILLTRAINERCALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/creature/CreatureManager.h"

class RecruitSkillTrainerSuiCallback : public SuiCallback {
public:
	RecruitSkillTrainerSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed)
			return;

		if (args->size() < 1)
			return;

		if (player->getParent() != NULL)
			return;

		ManagedReference<CityRegion*> city = player->getCityRegion().get();
		CityManager* cityManager = player->getZoneServer()->getCityManager();
		if (city == NULL || cityManager == NULL)
			return;

		if (!city->isMayor(player->getObjectID()))
			return;

		if (!cityManager->canSupportMoreTrainers(city)) {
					player->sendSystemMessage("@city/city:no_more_trainers"); // Your city can't support any more trainers at its current rank!
					return;
		}

		Zone* zone = player->getZone();

		PlayerObject* ghost = player->getPlayerObject();
		if (ghost == NULL)
			return;

		if (!ghost->hasAbility("recruitskilltrainer"))
			return;

		int option = Integer::valueOf(args->get(0).toString());

		String trainerTemplatePath = "";

		switch (option) {

		case 0: trainerTemplatePath = "trainer_architect";
				break;

		case 1: trainerTemplatePath = "trainer_armorsmith";
				break;

		case 2: trainerTemplatePath = "trainer_artisan";
				break;

		case 3: trainerTemplatePath = "trainer_bioengineer";
				break;

		case 4: trainerTemplatePath = "trainer_bountyhunter";
				break;

		case 5: trainerTemplatePath = "trainer_brawler";
				break;

		case 6: trainerTemplatePath = "trainer_carbine";
				break;

		case 7: trainerTemplatePath = "trainer_chef";
				break;

		case 8: trainerTemplatePath = "trainer_combatmedic";
				break;

		case 9: trainerTemplatePath = "trainer_commando";
				break;

		case 10: trainerTemplatePath = "trainer_creaturehandler";
				break;

		case 11: trainerTemplatePath = "trainer_dancer";
				break;

		case 12: trainerTemplatePath = "trainer_doctor";
				break;

		case 13: trainerTemplatePath = "trainer_droidengineer";
				break;

		case 14: trainerTemplatePath = "trainer_entertainer";
				break;

		case 15: trainerTemplatePath = "trainer_1hsword";
				break;

		case 16: trainerTemplatePath = "trainer_imagedesigner";
				break;

		case 17: trainerTemplatePath = "trainer_marksman";
				break;

		case 18: trainerTemplatePath = "trainer_medic";
				break;

		case 19: trainerTemplatePath = "trainer_merchant";
				break;

		case 20: trainerTemplatePath = "trainer_musician";
				break;

		case 21: trainerTemplatePath = "trainer_pistol";
				break;

		case 22: trainerTemplatePath = "trainer_polearm";
				break;

		case 23: trainerTemplatePath = "trainer_politician";
				break;

		case 24: trainerTemplatePath = "trainer_ranger";
				break;

		case 25: trainerTemplatePath = "trainer_rifleman";
				break;

		case 26: trainerTemplatePath = "trainer_scout";
				break;

		case 27: trainerTemplatePath = "trainer_smuggler";
				break;

		case 28: trainerTemplatePath = "trainer_squadleader";
				break;

		case 29: trainerTemplatePath = "trainer_2hsword";
				break;

		case 30: trainerTemplatePath = "trainer_tailor";
				break;

		case 31: trainerTemplatePath = "trainer_unarmed";
				break;

		case 32: trainerTemplatePath = "trainer_weaponsmith";

		}

		if (trainerTemplatePath != "") {
			Locker clocker(city, player);

			if(city->getCityTreasury() < 1000) {
				StringIdChatParameter msg;
				msg.setStringId("@city/city:action_no_money");
				msg.setDI(1000);
				player->sendSystemMessage(msg); //"The city treasury must have %DI credits in order to perform that action.");
				return;

			}

			CreatureObject* trainer = zone->getCreatureManager()->spawnCreature(trainerTemplatePath.hashCode(),0,player->getWorldPositionX(),player->getWorldPositionZ(),player->getWorldPositionY(),0,true);

			if (trainer == NULL) {
				player->sendSystemMessage("@city/city:st_fail"); // Failed to create the skill trainer for some reason. Try again.
				return;
			}

			trainer->rotate(player->getDirectionAngle());
			city->subtractFromCityTreasury(1000);
			city->addSkillTrainer(trainer);

			if (!city->isRegistered()) {
				zone->unregisterObjectWithPlanetaryMap(trainer);
			}
		}
	}
};

#endif /* RECRUITSKILLTRAINERCALLBACK_H_ */
