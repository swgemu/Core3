/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "CoaEncodedDiskMenuComponent.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

void CoaEncodedDiskMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	TangibleObject* disk = cast<TangibleObject*>(sceneObject);
	if (disk == NULL) {
		return;
	}

	String faction = getFaction(disk);
	if (faction.isEmpty()) {
		return;
	}

	String file = "@theme_park/alderaan/act2/shared_" + faction + "_missions";

	menuResponse->addRadialMenuItem(20,3,file + ":use"); // Read

	if (faction == "rebel" && !isDecoded(disk)) {
		menuResponse->addRadialMenuItem(68,3,file + ":decode"); // Decode
	}
}

int CoaEncodedDiskMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
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

	String faction = getFaction(disk);
	if (faction.isEmpty()) {
		return 0;
	}

	bool decoded = isDecoded(disk);

	if (selectedID == 20) {
		String file = "@theme_park/alderaan/act2/" + faction + "_missions";
		String title, body;

		if (faction == "imperial") {
			title = file + ":disk_title";
			body = file + ":disk_text";
		} else if (faction == "rebel" && decoded) {
			title = file + ":disk_decoded_title";
			body = file + ":disk_decoded_text";
		} else {
			title = file + ":disk_encoded_title";
			body = file + ":disk_encoded_text";
		}

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(player, 0);
		box->setPromptTitle(title);
		box->setPromptText(body);
		box->setUsingObject(disk);
		box->setOkButton(true, "@theme_park/alderaan/act2/shared_" + faction + "_missions:close"); // Close

		ghost->addSuiBox(box);
		player->sendMessage(box->generateMessage());
		return 0;

	} else if (selectedID == 68) {
		if (faction != "rebel") {
			return 0;
		}

		String file = "@theme_park/alderaan/act2/shared_" + faction + "_missions";

		//TODO: check for decoder and decode if present

		player->sendSystemMessage(file + ":decode_failed"); // You do not have the required decoder to decode this message.
		return 0;
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}

String CoaEncodedDiskMenuComponent::getFaction(TangibleObject* disk) {
	String name = disk->getObjectNameStringIdFile();
	String faction;

	if (name.contains("imperial")) {
		faction = "imperial";
	} else if (name.contains("rebel")) {
		faction = "rebel";
	}

	return faction;
}

bool CoaEncodedDiskMenuComponent::isDecoded(TangibleObject* disk) {
	String name = disk->getObjectNameStringIdName();

	if (name.contains("decoded")) {
		return true;
	}

	return false;
}
