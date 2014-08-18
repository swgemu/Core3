
#include "CoaMessageMenuComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/callbacks/CoaMessageFragmentSuiCallback.h"
#include "server/zone/objects/tangible/components/generic/CoaMessageDataComponent.h"

void CoaMessageMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	menuResponse->addRadialMenuItem(20,3,"@sui:read_option"); // Read

}

int CoaMessageMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (!player->isPlayerCreature()) {
		return 0;
	}

	if (!sceneObject->isASubChildOf(player)) {
		player->sendSystemMessage("@encoded_disk/message_fragment:sys_not_in_inv"); // The disk can't be used unless it is in your inventory!
		return 0;
	}

	TangibleObject* disk = cast<TangibleObject*>(sceneObject);
	if (disk == NULL) {
		return 0;
	}

	PlayerObject* ghost = player->getPlayerObject();
	if (ghost == NULL) {
		return 0;
	}

	if (selectedID == 20) {
		CoaMessageDataComponent* data = cast<CoaMessageDataComponent*>(disk->getDataObjectComponent()->get());

		if (data == NULL) {
			return 0;
		}

		String title = disk->getObjectName()->getFullPath();
		StringBuffer body;
		body << "@encoded_disk/message_fragment:complete_event";

		if (data->getFaction().toLowerCase() == "imperial") {
			body << "imp1\n\n" << "@encoded_disk/message_fragment:frag_eventimp1_" << String::valueOf(data->getNumber());
		} else if (data->getFaction().toLowerCase() == "rebel") {
			body << "reb1\n\n" << "@encoded_disk/message_fragment:frag_eventreb1_" << String::valueOf(data->getNumber());
		} else {
			return 0;
		}

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(player, SuiWindowType::COA_MESSAGE);
		box->setPromptTitle(title);
		box->setPromptText(body.toString());
		box->setUsingObject(disk);
		box->setOkButton(true, "@close");

		ghost->addSuiBox(box);
		player->sendMessage(box->generateMessage());
		return 0;
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
