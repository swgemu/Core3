/*
 * TeachPlayerListBoxImplementation.cpp
 *
 *  Created on: 6/21/2010
 *      Author: thoop
 */

#include "TeachPlayerListBox.h"
#include "server/zone/objects/creature/professions/SkillBox.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/Races.h"
#include "server/zone/objects/group/GroupObject.h"

void TeachPlayerListBoxImplementation::init() {
	setPromptTitle("@sui:teach");
	setPromptText("What would you like to teach?");
	//setOkButton(true, "");
	//setCancelButton(true, "");
}


bool TeachPlayerListBoxImplementation::generateSkillList(PlayerCreature* teacher, PlayerCreature* student) {
	//pre: both players are locked
	//post: both players are locked

	init();

	setStudent(student);

	teachingSkillOptions.removeAll();

	//The boxes that will be sent to the SUI
	Vector<SkillBox*> trainableBoxes;

	SkillBoxList* skillBoxList = teacher->getSkillBoxList();

	/*
	 * If the player has no skills at all
	 */
	if (skillBoxList->size() <= 0) {

		teacher->sendSystemMessage("teaching","no_skills");
		return false;

	}

	/*
	 * Loop through each skill that the player has and filter out accordingly
	 */
	for(int i = 0; i < skillBoxList->size(); i++) {

		SkillBox* sBox = skillBoxList->get(i);

		/*
		 * Players cannot teach novice skill boxes
		 */
		if (sBox->isNoviceBox())
			continue;

		/*
		 * Players cannot teach jedi skills
		 */
		if (sBox->getSkillXpType() == "jedi_general" ||
			sBox->getSkillXpType() == "space_combat_general" ||
			sBox->getSkillXpType() == "fs_crafting" ||
			sBox->getSkillXpType() == "fs_combat" ||
			sBox->getSkillXpType() == "fs_reflex" ||
			sBox->getSkillXpType() == "fs_senses" ||
			sBox->getSkillXpType() == "force_rank_xp") {

			continue;
		}

		/*
		 * Cannot teach someone a skill box that they already have
		 */
		if (student->hasSkillBox(sBox->getName()))
			continue;

		if (student->getSlottedObject("ghost") == NULL)
			continue;

		/*
		 * Cannot teach them a skill that they dont have enough xp for
		 */
		if (sBox->getSkillXpCost() > ((PlayerObject*)student->getSlottedObject("ghost"))->getExperience(sBox->getSkillXpType()))
			continue;

		/*
		 * Cannot teach someone a skill if they dont have the required skills
		 */
		bool hasReqs = true;

		for (int j = 0; j < sBox->getRequiredSkillsSize(); j++) {

				if (!student->hasSkillBox(sBox->getRequiredSkill(j)->getName()))
						hasReqs = false;

		}


		/*
		 * Cannot teach someone a skill that is God only or that is Hidden
		 */
		if (hasReqs && !sBox->getSkillGodOnly() && !sBox->getSkillIsHidden()) {

			/*
			 * Lastly, we cannot teach someone the base language skill. Ex. "social_language_basic"
			 * Only the speak and comprehend skills can be taught.
			 */
			if(sBox->getName().indexOf("social_language") >= 0) {

				if(sBox->getName().indexOf("speak") == -1 && sBox->getName().indexOf("comprehend") == -1)
					continue;

				/*
				 * Also, there are race restrictions on some languages
				 */
				if(sBox->getRequiredSpeciesSize() > 0) {
					String race;
					bool correctRace = false;

					for(int i = 0; i < sBox->getRequiredSpeciesSize(); i++) {

						sBox->getRequiredSpecies(race, i);

						if(race.compareTo(Races::getRace(student->getRaceID())) == 0) {
							correctRace = true;
						}
					}

					if(!correctRace)
						continue;
				}
			}

			trainableBoxes.add(sBox);

		}

	}

	//we want to make sure we're still in the group with them
	if ( trainableBoxes.size() > 0 ) {

		if ( (teacher->getGroup() == NULL) || (!teacher->getGroup()->hasMember(student)) ) {

			StringIdChatParameter message("teaching","not_in_same_group");
			message.setTT(player->getObjectID());
			teacher->sendSystemMessage(message);

			return false;

		}

		for (int i = 0; i < trainableBoxes.size(); i++) {

			StringBuffer skillboxname;
			skillboxname << "@skl_n:" << trainableBoxes.get(i)->getName();
			addMenuItem(skillboxname.toString());
			teachingSkillOptions.add(trainableBoxes.get(i));
		}

		teacher->addSuiBox(_this);
		teacher->sendMessage(generateMessage());

	} else {

		StringIdChatParameter message("teaching","no_skills_for_student");
		message.setTT(player->getFirstName());
		teacher->sendSystemMessage(message);

		return false;

	}

	return true;


}


