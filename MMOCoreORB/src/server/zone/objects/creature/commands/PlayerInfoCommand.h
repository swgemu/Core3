/*
 * PlayerInfoCommand.h
 *
 *  Created on: 31/03/2012
 *      Author: victor
 */

#ifndef PLAYERINFOCOMMAND_H_
#define PLAYERINFOCOMMAND_H_

#include "engine/engine.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/creature/CreatureObject.h"

class PlayerInfoCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		if (!creature->getPlayerObject()->isPrivileged())
			return 1;

		CreatureObject* targetObject = cast<CreatureObject*>(creature->getZoneServer()->getObject(creature->getTargetID()));

		if (targetObject == NULL || !targetObject->isPlayerCreature())
			targetObject = creature;

		Locker locker(targetObject, creature);

		PlayerObject* ghost = targetObject->getPlayerObject();

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, 0);

		box->setPromptTitle("Player Info"); //Register City
		//box->setPromptText("@city/city:register_d");

		SkillModList* skillModList = targetObject->getSkillModList();

		StringBuffer promptText;
		promptText << "SkillMods:" << endl;
		promptText << skillModList->getPrintableSkillModList() << endl;

		promptText << "Skills:" << endl;
		SkillList* list = targetObject->getSkillList();

		int totalSkillPointsWasted = 0;

		for (int i = 0; i < list->size(); ++i) {
			Skill* skill = list->get(i);
			promptText << skill->getSkillName() << " point cost:" << skill->getSkillPointsRequired() << endl;

			totalSkillPointsWasted += skill->getSkillPointsRequired();
		}

		promptText << "Level: " << targetObject->getLevel() << endl;

		promptText << "totalSkillPointsWasted = " << totalSkillPointsWasted << " skillPoints var:" << ghost->getSkillPoints() << endl;

		promptText << "Ability list:" << endl;

		AbilityList* abilityList = ghost->getAbilityList();

		for (int i = 0; i < abilityList->size(); ++i) {
			Ability* skill = abilityList->get(i);
			promptText << skill->getAbilityName() << endl;
		}

		if (creature->getPlayerObject()->getAdminLevel() >= 15) {
			Vector<byte>* holoProfessions = ghost->getHologrindProfessions();

			promptText << endl;
			promptText << "Hologrind professions:\n";

			for (int i = 0; i < holoProfessions->size(); ++i) {
				byte prof = holoProfessions->get(i);

				int badgeIdx = 42 + prof;

				String stringKey = creature->getZoneServer()->getPlayerManager()->getBadgeKey(badgeIdx);

				promptText << "@skl_n:" + stringKey << endl;
			}
		}



		box->setPromptText(promptText.toString());

		creature->sendMessage(box->generateMessage());

		return 0;
	}
};


#endif /* PLAYERINFOCOMMAND_H_ */
