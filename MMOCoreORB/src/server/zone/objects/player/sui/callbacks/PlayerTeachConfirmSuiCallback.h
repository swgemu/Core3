/*
 * PlayerTeachConfirmSuiCallback.h
 *
 *  Created on: Mar 13, 2012
 *      Author: katherine
 */

#ifndef PLAYERTEACHCONFIRMSUICALLBACK_H_
#define PLAYERTEACHCONFIRMSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sessions/PlayerTeachSession.h"

class PlayerTeachConfirmSuiCallback : public SuiCallback {
	String skillname;

public:
	PlayerTeachConfirmSuiCallback(ZoneServer* serv, const String& name) : SuiCallback(serv) {
		skillname = name;
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!sui->isListBox() || cancelPressed)
			return;

		SuiListBox* listBox = cast<SuiListBox*>( sui);

		if(!creature->isPlayerCreature())
			return;

		if(!cancelPressed) {

			// Let's teach them.

			Skill* skill = SkillManager::instance()->getSkill(skillname);

				bool canLearnSkill = false;
				bool playerLacksSkillPoints = false;

				//Verify that player can train skill.
				if (SkillManager::instance()->canLearnSkill(skill->getSkillName(), creature, false)) {
					canLearnSkill = true;
				} else {
					//Check if the player lacks skill points.
					playerLacksSkillPoints = SkillManager::instance()->fullfillsSkillPrerequisitesAndXp(skill->getSkillName(), creature);
				}

				if (canLearnSkill) {

					//Award skill.
					SkillManager::instance()->awardSkill(skill->getSkillName(), creature, true, false, false);

					//Send message to client
					StringIdChatParameter systemMessageSkillLearned("@skill_teacher:prose_skill_learned");
					systemMessageSkillLearned.setTO("@skl_n:" + skill->getSkillName());
					creature->sendSystemMessage(systemMessageSkillLearned);


			// By now they should have learned it. Send a confirmation to the teacher.

			ManagedReference<CreatureObject*> player = cast<CreatureObject*>(sui->getUsingObject());

			StringIdChatParameter params("teaching", "teacher_skill_learned"); // %TT learns %TO from you.
			params.setTT(creature->getDisplayedName());
			params.setTO("@skl_n:" + skillname);
			player->sendSystemMessage(params);

			// Remove the session.
				creature->dropActiveSession(SessionFacadeType::PLAYERTEACH);

			} else {
				ManagedReference<CreatureObject*> player = cast<CreatureObject*>(sui->getUsingObject());
				creature->sendSystemMessage("@teaching:teaching_failed");
				player->sendSystemMessage("@teaching:teaching_failed");
				creature->dropActiveSession(SessionFacadeType::PLAYERTEACH);

			}
			} else {

			ManagedReference<CreatureObject*> player = cast<CreatureObject*>(sui->getUsingObject());

			StringIdChatParameter params("teaching", "offer_refused"); // %TT has refused your offer to teach.
			params.setTT(player->getDisplayedName());
			creature->sendSystemMessage(params);

			creature->dropActiveSession(SessionFacadeType::PLAYERTEACH);
		}
	}
};




#endif /* PLAYERTEACHCONFIRMSUICALLBACK_H_ */
