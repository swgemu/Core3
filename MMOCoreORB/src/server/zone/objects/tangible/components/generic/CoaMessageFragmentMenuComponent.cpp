
#include "CoaMessageFragmentMenuComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/callbacks/CoaMessageFragmentSuiCallback.h"

void CoaMessageFragmentMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	menuResponse->addRadialMenuItem(20,3,"@sui:read_option"); // Read

}

int CoaMessageFragmentMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (!player->isPlayerCreature()) {
		return 0;
	}

	if (!sceneObject->isASubChildOf(player)) {
		player->sendSystemMessage("@encoded_disk/message_fragment:sys_not_in_inv"); // The disk can't be used unless it is in your inventory!
		return 0;
	}

	TangibleObject* fragment = cast<TangibleObject*>(sceneObject);
	if (fragment == NULL) {
		return 0;
	}

	PlayerObject* ghost = player->getPlayerObject();
	if (ghost == NULL) {
		return 0;
	}

	if (selectedID == 20) {
		String title = fragment->getCustomObjectName().toString();
		StringBuffer body;
		body << "@encoded_disk/message_fragment:text_event";

		if (title.contains("Imperial")) {
			body << "imp1";
		} else if (title.contains("Rebel")) {
			body << "reb1";
		} else {
			return 0;
		}

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(player, SuiWindowType::COA_MESSAGE_FRAGMENT);
		box->setCallback(new CoaMessageFragmentSuiCallback(player->getZoneServer()));
		box->setPromptTitle(title);
		box->setPromptText(body.toString());
		box->setUsingObject(fragment);
		box->setCancelButton(true, "@close");
		box->setOkButton(true, "@encoded_disk/message_fragment:combine");

		ghost->addSuiBox(box);
		player->sendMessage(box->generateMessage());
		return 0;
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
