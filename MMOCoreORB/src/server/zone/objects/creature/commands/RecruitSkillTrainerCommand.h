/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RECRUITSKILLTRAINERCOMMAND_H_
#define RECRUITSKILLTRAINERCOMMAND_H_

#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/creature/commands/sui/RecruitSkillTrainerSuiCallback.h"

class RecruitSkillTrainerCommand : public QueueCommand {
public:

	RecruitSkillTrainerCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		PlayerObject* ghost = creature->getPlayerObject();
		if (ghost == NULL)
			return GENERALERROR;

		if (!ghost->hasAbility("recruitskilltrainer"))
			return GENERALERROR;

		ManagedReference<CityRegion*> city = creature->getCityRegion().get();
		if (city == NULL)
			return GENERALERROR;

		if (!city->isMayor(creature->getObjectID()))
			return GENERALERROR;

		ManagedReference<SuiListBox*> suiTrainerType = new SuiListBox(creature, SuiWindowType::RECRUIT_SKILL_TRAINER, 0);
		suiTrainerType->setCallback(new RecruitSkillTrainerSuiCallback(server->getZoneServer()));

		suiTrainerType->setPromptTitle("@city/city:trainer_n"); // Recruit Skill Trainer
		suiTrainerType->setPromptText("@city/city:trainer_d");

		suiTrainerType->addMenuItem("@city/city:st_architect", 0);
		suiTrainerType->addMenuItem("@city/city:st_armorsmith", 1);
		suiTrainerType->addMenuItem("@city/city:st_artisan", 2);
		suiTrainerType->addMenuItem("@city/city:st_bioengineer", 3);
		suiTrainerType->addMenuItem("@city/city:st_bountyhunter", 4);
		suiTrainerType->addMenuItem("@city/city:st_brawler", 5);
		suiTrainerType->addMenuItem("@city/city:st_carbine", 6);
		suiTrainerType->addMenuItem("@city/city:st_chef", 7);
		suiTrainerType->addMenuItem("@city/city:st_combatmedic", 8);
		suiTrainerType->addMenuItem("@city/city:st_commando", 9);
		suiTrainerType->addMenuItem("@city/city:st_creaturehandler", 10);
		suiTrainerType->addMenuItem("@city/city:st_dancer", 11);
		suiTrainerType->addMenuItem("@city/city:st_doctor", 12);
		suiTrainerType->addMenuItem("@city/city:st_droidengineer", 13);
		suiTrainerType->addMenuItem("@city/city:st_entertainer", 14);
		suiTrainerType->addMenuItem("@city/city:st_1hsword", 15);
		suiTrainerType->addMenuItem("@city/city:st_imagedesigner", 16);
		suiTrainerType->addMenuItem("@city/city:st_marksman", 17);
		suiTrainerType->addMenuItem("@city/city:st_medic", 18);
		suiTrainerType->addMenuItem("@city/city:st_merchant", 19);
		suiTrainerType->addMenuItem("@city/city:st_musician", 20);
		suiTrainerType->addMenuItem("@city/city:st_pistol", 21);
		suiTrainerType->addMenuItem("@city/city:st_polearm", 22);
		suiTrainerType->addMenuItem("@city/city:st_politician", 23);
		suiTrainerType->addMenuItem("@city/city:st_ranger", 24);
		suiTrainerType->addMenuItem("@city/city:st_rifleman", 25);
		suiTrainerType->addMenuItem("@city/city:st_scout", 26);
		suiTrainerType->addMenuItem("@city/city:st_smuggler", 27);
		suiTrainerType->addMenuItem("@city/city:st_squadleader", 28);
		suiTrainerType->addMenuItem("@city/city:st_2hsword", 29);
		suiTrainerType->addMenuItem("@city/city:st_tailor", 30);
		suiTrainerType->addMenuItem("@city/city:st_unarmed", 31);
		suiTrainerType->addMenuItem("@city/city:st_weaponsmith", 32);

		ghost->addSuiBox(suiTrainerType);
		creature->sendMessage(suiTrainerType->generateMessage());

		return SUCCESS;
	}

};

#endif //RECRUITSKILLTRAINERCOMMAND_H_
