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
#include "server/zone/managers/player/BadgeList.h"

class PlayerInfoCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		ManagedReference<CreatureObject*> targetObject;

		if (!arguments.isEmpty()) {
			ManagedReference<PlayerManager*> playerManager = creature->getZoneServer()->getPlayerManager();

			targetObject = playerManager->getPlayer(arguments.toString());
		} else {
			targetObject = creature->getZoneServer()->getObject(creature->getTargetID()).castTo<CreatureObject*>();
		}

		if (targetObject == nullptr || !targetObject->isPlayerCreature()) {
			targetObject = creature;
		}

		Locker locker(targetObject, creature);

		PlayerObject* ghost = targetObject->getPlayerObject();

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, 0);

		box->setPromptTitle("Player Info");

		Locker smodLocker(targetObject->getSkillModMutex());

		const SkillModList* skillModList = targetObject->getSkillModList();

		StringBuffer promptText;
		promptText << "Name: " << targetObject->getCustomObjectName().toString()  << endl;
		promptText << "ObjectID: " << targetObject->getObjectID() << endl;

		if (ghost != nullptr) {
			promptText << "Online Status: ";

			if(ghost->isOnline())
				promptText << "ONLINE" << endl;
			else {
				promptText << "OFFLINE. Last On: " << ghost->getLastLogout()->getFormattedTime() << endl;
			}

			if (ghost->isOnline()) {
				auto zone = targetObject->getZone();

				promptText << "Current Location: " << targetObject->getWorldPosition().toString()
					<< " zone: " << (zone != nullptr ? zone->getZoneName() : "<nullZone>")
					<< endl;
			} else {
				auto loginPos = targetObject->getWorldPosition();

				Reference<SceneObject*> playerParent = creature->getZoneServer()->getObject(ghost->getSavedParentID(), true);

				if (playerParent == nullptr)
					playerParent = targetObject->getParent().get();

				if (playerParent != nullptr && playerParent->isCellObject()) {
					Reference<SceneObject*> root = playerParent->getRootParent();

					if (root != nullptr && root->isBuildingObject()) {
						float length = Math::sqrt(targetObject->getPositionX() * targetObject->getPositionX() + targetObject->getPositionY() * targetObject->getPositionY());
						float angle = root->getDirection()->getRadians() + atan2(targetObject->getPositionX(), targetObject->getPositionY());
						float posX = root->getPositionX() + (sin(angle) * length);
						float posY = root->getPositionY() + (cos(angle) * length);
						float posZ = root->getPositionZ() + targetObject->getPositionZ();

						loginPos = Vector3(posX, posY, posZ);
					}
				}

				promptText << "Login Location: " << loginPos.toString() << " zone: " << ghost->getSavedTerrainName() << endl;
			}
		}

		promptText << endl << "SkillMods:" << endl;
		promptText << skillModList->getPrintableSkillModList() << endl;

		smodLocker.release();

		promptText << "Skills:" << endl;
		const SkillList* list = targetObject->getSkillList();

		int totalSkillPointsWasted = 0;

		for (int i = 0; i < list->size(); ++i) {
			Skill* skill = list->get(i);
			promptText << skill->getSkillName() << " point cost:" << skill->getSkillPointsRequired() << endl;

			totalSkillPointsWasted += skill->getSkillPointsRequired();
		}

		promptText << endl << "Level: " << targetObject->getLevel() << endl;

		if (ghost != nullptr) {
			promptText << "totalSkillPointsWasted = " << totalSkillPointsWasted << " skillPoints var:" << ghost->getSkillPoints() << endl;

			promptText << endl << "Ability list:" << endl;

			const AbilityList* abilityList = ghost->getAbilityList();

			for (int i = 0; i < abilityList->size(); ++i) {
				const Ability* skill = abilityList->get(i);
				promptText << skill->getAbilityName() << endl;
			}

			if (creature->getPlayerObject()->getAdminLevel() >= 15) {
				const Vector<byte>* holoProfessions = ghost->getHologrindProfessions();

				promptText << endl;
				promptText << "Hologrind professions:\n";

				const BadgeList* badgeList = BadgeList::instance();
				if (badgeList != nullptr) {
					for (int i = 0; i < holoProfessions->size(); ++i) {
						byte prof = holoProfessions->get(i);
						const Badge* badge = badgeList->get(prof);
						if (prof) {
							String stringKey = badge->getKey();
							promptText << "@skl_n:" + stringKey << " badgeid: " << String::valueOf(prof)<<  endl;
						} else {
							promptText << "unknown profession " << String::valueOf(prof) << endl;
						}
					}
				}

				promptText << endl << "Visibility = " << ghost->getVisibility() << endl;

				MissionManager* missionManager = creature->getZoneServer()->getMissionManager();
				Vector<uint64> hunterList =  missionManager->getHuntersHuntingTarget(targetObject->getObjectID());

				for (int i = 0; i < hunterList.size(); i++) {
					promptText << "Hunter #" << i << ": " << hunterList.get(i) << endl;
				}

				promptText << endl;
			}
		} else {
			promptText << "ERROR: PlayerObject nullptr" << endl;
		}

		ManagedReference<SceneObject*> inventory = targetObject->getSlottedObject("inventory");
		ManagedReference<SceneObject*> bank = targetObject->getSlottedObject("bank");
		ManagedReference<SceneObject*> datapad = targetObject->getSlottedObject("datapad");

		promptText << "Inventory: " << (inventory == nullptr ? String("nullptr") : String::valueOf(inventory->getObjectID()));
		promptText << endl;

		promptText << "Bank: " << (bank == nullptr ? String("nullptr") : String::valueOf(bank->getObjectID()));
		promptText << endl;

		promptText << "Datapad: " << (datapad == nullptr ? String("nullptr") : String::valueOf(datapad->getObjectID()));
		promptText << endl;


		box->setPromptText(promptText.toString());

		creature->sendMessage(box->generateMessage());

		return 0;
	}
};


#endif /* PLAYERINFOCOMMAND_H_ */
