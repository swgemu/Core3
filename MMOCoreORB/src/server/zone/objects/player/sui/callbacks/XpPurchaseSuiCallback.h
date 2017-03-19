#ifndef XPPURCHASESUICALLBACK_H
#define XPPURCHASESUICALLBACK_H

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "templates/tangible/XpPurchaseTemplate.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/managers/crafting/schematicmap/SchematicMap.h"

class XpPurchaseSuiCallback : public SuiCallback {
public:
	XpPurchaseSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}


	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isMessageBox() || player == NULL || cancelPressed)
			return;

		if(player->isDead() || player->isIncapacitated())
			return;

		Reference<PlayerObject*> ghost = player->getSlottedObject("ghost").castTo<PlayerObject*>();

		if (ghost == NULL)
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject().get();

		if(obj == NULL)
			return;

		XpPurchaseTemplate* templateData = cast<XpPurchaseTemplate*>(obj->getObjectTemplate());

		if (templateData == NULL) {
			player->error("No XpPurchaseTemplate for: " + String::valueOf(obj->getServerObjectCRC()));
			return;
		}

		StringIdManager* stringIdManager = StringIdManager::instance();

		String skillNeeded = templateData->getRequiredSkill();

		if((!skillNeeded.isEmpty() && !player->hasSkill(skillNeeded))) {
			UnicodeString skill = stringIdManager->getStringId("@skl_n:" + skillNeeded);
			StringIdChatParameter stringID("item/xp_purchase", "msg_no_min_skill"); // You must have %TO skill in order to understand this.
			stringID.setTO(skill);
			player->sendSystemMessage(stringID);
			return;
		}

		String grantType = templateData->getGrantType();
		String grantName = templateData->getGrantName();

		if (grantType == "ability" && ghost->hasAbility(grantName)) {
			player->sendSystemMessage("@item/xp_purchase:msg_already_have_command");
			return;
		} else if (grantType == "schematic") {
			DraftSchematic* schematic = SchematicMap::instance()->get(grantName.hashCode());

			if (ghost->hasSchematic(schematic)) {
				player->sendSystemMessage("@item/xp_purchase:msg_already_have_schematic");
				return;
			}
		}

		String xpType = templateData->getXpType();
		int xpAmount = templateData->getXpAmount();

		int playerXp = ghost->getExperience(xpType);

		if (playerXp == 0) {
			UnicodeString type = stringIdManager->getStringId("@exp_n:" + xpType);
			StringIdChatParameter stringID("item/xp_purchase", "msg_no_xp"); // You cannot learn from this item. You do not have any %TO experience.
			stringID.setTO(type);
			player->sendSystemMessage(stringID);
			return;
		} else if (playerXp < xpAmount) {
			UnicodeString type = stringIdManager->getStringId("@exp_n:" + xpType);
			StringIdChatParameter stringID("item/xp_purchase", "msg_not_enough_xp"); // You do not have enough experience to learn from this item. You need at least %DI %TO experience.
			stringID.setTO(type);
			stringID.setDI(xpAmount);
			player->sendSystemMessage(stringID);
			return;
		}

		if (grantType == "ability") {
			SkillManager* skillManager = SkillManager::instance();
			Ability* grantAbility = skillManager->getAbility(grantName);

			if (grantAbility == NULL) {
				player->error("Unable to learn ability: " + grantName);
				return;
			}

			ghost->addAbility(grantAbility, true);
			ghost->addExperience(xpType, -xpAmount, true);
			player->sendSystemMessage("@item/xp_purchase:msg_learned_command");

			if (!templateData->isNoRemove()) {
				obj->destroyObjectFromWorld(true);
				obj->destroyObjectFromDatabase();
			}
		} else if (grantType == "schematic") {
			ManagedReference<DraftSchematic* > schematic = SchematicMap::instance()->get(grantName.hashCode());

			if (schematic == NULL) {
				player->error("Unable to learn schematic: " + grantName);
				return;
			}

			if(ghost->addRewardedSchematic(schematic, SchematicList::QUEST, -1, true)) {
				ghost->addExperience(xpType, -xpAmount, true);
				player->sendSystemMessage("@item/xp_purchase:msg_learned_schematic");

				if (!templateData->isNoRemove()) {
					obj->destroyObjectFromWorld(true);
					obj->destroyObjectFromDatabase();
				}
			}
		}
	}
};

#endif /* XPPURCHASESUICALLBACK_H */
