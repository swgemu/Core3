#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "XpPurchaseMenuComponent.h"
#include "server/zone/objects/draftschematic/DraftSchematic.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/callbacks/XpPurchaseSuiCallback.h"

#include "templates/tangible/XpPurchaseTemplate.h"
#include "server/zone/managers/crafting/schematicmap/SchematicMap.h"

void XpPurchaseMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {

	if (!sceneObject->isTangibleObject())
		return;

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	XpPurchaseTemplate* templateData = cast<XpPurchaseTemplate*>(sceneObject->getObjectTemplate());

	if (templateData == NULL) {
		error("No XpPurchaseTemplate for: " + String::valueOf(sceneObject->getServerObjectCRC()));
		return;
	}

	menuResponse->addRadialMenuItem(50, 3, "@item/xp_purchase:menu_learn"); //Learn
}

int XpPurchaseMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (!sceneObject->isTangibleObject())
		return 0;

	if (!player->isPlayerCreature())
		return 0;

	if(selectedID == 50) {
		if (!sceneObject->isASubChildOf(player)) {
			player->sendSystemMessage("@loot_schematic:must_be_holding"); // You must be holding that in order to use it.
			return 0;
		}

		Reference<PlayerObject*> ghost = player->getSlottedObject("ghost").castTo<PlayerObject*>();

		if (ghost == NULL)
			return 0;

		XpPurchaseTemplate* templateData = cast<XpPurchaseTemplate*>(sceneObject->getObjectTemplate());

		if (templateData == NULL) {
			error("No XpPurchaseTemplate for: " + String::valueOf(sceneObject->getServerObjectCRC()));
			return 0;
		}

		StringIdManager* stringIdManager = StringIdManager::instance();

		String skillNeeded = templateData->getRequiredSkill();

		if((!skillNeeded.isEmpty() && !player->hasSkill(skillNeeded))) {
			UnicodeString skill = stringIdManager->getStringId("@skl_n:" + skillNeeded);
			StringIdChatParameter stringID("item/xp_purchase", "msg_no_min_skill"); // You must have %TO skill in order to understand this.
			stringID.setTO(skill);
			player->sendSystemMessage(stringID);
			return 0;
		}

		String grantType = templateData->getGrantType();
		String grantName = templateData->getGrantName();

		if (grantType == "ability" && ghost->hasAbility(grantName)) {
			player->sendSystemMessage("@item/xp_purchase:msg_already_have_command");
			return 0;
		} else if (grantType == "schematic") {
			DraftSchematic* schematic = SchematicMap::instance()->get(grantName.hashCode());

			if (ghost->hasSchematic(schematic)) {
				player->sendSystemMessage("@item/xp_purchase:msg_already_have_schematic");
				return 0;
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
			return 0;
		} else if (playerXp < xpAmount) {
			UnicodeString type = stringIdManager->getStringId("@exp_n:" + xpType);
			StringIdChatParameter stringID("item/xp_purchase", "msg_not_enough_xp"); // You do not have enough experience to learn from this item. You need at least %DI %TO experience.
			stringID.setTO(type);
			stringID.setDI(xpAmount);
			player->sendSystemMessage(stringID);
			return 0;
		}

		ManagedReference<SuiMessageBox*> suiMessageBox = new SuiMessageBox(player, SuiWindowType::TUNE_CRYSTAL);

		suiMessageBox->setPromptTitle("@item/xp_purchase:sui_title");
		suiMessageBox->setPromptText("@item/xp_purchase:sui_prompt1 " + String::valueOf(xpAmount) + " @item/xp_purchase:sui_prompt2");
		suiMessageBox->setCancelButton(true, "Cancel");
		suiMessageBox->setUsingObject(sceneObject);
		suiMessageBox->setCallback(new XpPurchaseSuiCallback(player->getZoneServer()));

		ghost->addSuiBox(suiMessageBox);
		player->sendMessage(suiMessageBox->generateMessage());

		return 0;
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
