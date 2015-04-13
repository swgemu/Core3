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
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/mission/MissionManager.h"

class PlayerInfoCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		if (!creature->getPlayerObject()->isPrivileged())
			return 1;

		ManagedReference<CreatureObject*> targetObject;

		if (!arguments.isEmpty()) {
			ManagedReference<PlayerManager*> playerManager = creature->getZoneServer()->getPlayerManager();

			targetObject = playerManager->getPlayer(arguments.toString());
		} else {
			targetObject = creature->getZoneServer()->getObject(creature->getTargetID()).castTo<CreatureObject*>();
		}

		if (targetObject == NULL || !targetObject->isPlayerCreature()) {
			targetObject = creature;
		}

		Locker locker(targetObject, creature);

		PlayerObject* ghost = targetObject->getPlayerObject();

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, 0);

		box->setPromptTitle("Player Info"); //Register City
		//box->setPromptText("@city/city:register_d");

		SkillModList* skillModList = targetObject->getSkillModList();

		StringBuffer promptText;
		promptText << "ObjectID: " << targetObject->getObjectID() << endl;
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

				String stringKey = creature->getZoneServer()->getPlayerManager()->getBadgeKey(prof);

				promptText << "@skl_n:" + stringKey << endl;
			}

			promptText << endl << "Visibility = " << ghost->getVisibility() << endl;

			MissionManager* missionManager = creature->getZoneServer()->getMissionManager();
			Vector<uint64>* hunterList =  missionManager->getHuntersHuntingTarget(targetObject->getObjectID());

			if (hunterList != NULL) {
				for (int i = 0; i < hunterList->size(); i++) {
					promptText << "Hunter #" << i << ": " << hunterList->get(i) << endl;
				}
			}

			promptText << endl;
		}

		ManagedReference<SceneObject*> inventory = targetObject->getSlottedObject("inventory");
		ManagedReference<SceneObject*> bank = targetObject->getSlottedObject("bank");
		ManagedReference<SceneObject*> datapad = targetObject->getSlottedObject("datapad");

		promptText << "Inventory: " << (inventory == NULL ? String("NULL") : String::valueOf(inventory->getObjectID()));
		promptText << endl;

		promptText << "Bank: " << (bank == NULL ? String("NULL") : String::valueOf(bank->getObjectID()));
		promptText << endl;

		promptText << "Datapad: " << (datapad == NULL ? String("NULL") : String::valueOf(datapad->getObjectID()));
		promptText << endl;


		box->setPromptText(promptText.toString());

		creature->sendMessage(box->generateMessage());

		return 0;
	}
};


#endif /* PLAYERINFOCOMMAND_H_ */
