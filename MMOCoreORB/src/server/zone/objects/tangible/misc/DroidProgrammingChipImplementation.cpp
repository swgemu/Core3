#include "server/zone/objects/tangible/misc/DroidProgrammingChip.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/objects/tangible/components/TangibleObjectMenuComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/callbacks/DroidProgrammingChipSuiCallback.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"

void DroidProgrammingChipImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player) {
	alm->insertAttribute("volume", volume);

	if (!craftersName.isEmpty()) {
		alm->insertAttribute("crafter", craftersName);
	}

	if (!objectSerial.isEmpty()) {
		alm->insertAttribute("serial_number", objectSerial);
	}

	if (datapadSize > 0) {
		alm->insertAttribute("droid_command_program_size", datapadSize);
	}

	if (!itemIdentifier.isEmpty()) {
		alm->insertAttribute("droid_command_name", itemIdentifier);
	}
}

void DroidProgrammingChipImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (objectMenuComponent == nullptr) {
		error("no object menu component set for " + templateObject->getTemplateFileName());

		return;
	}

	if (player == nullptr) {
		return;
	}

	//if chip is unprogrammed, offer programming option
	if (itemIdentifier.isEmpty()) {
		menuResponse->addRadialMenuItem(230, 3, "@space/space_interaction:memory_chip_program"); //"Program Droid Memory Chip"
	}

	//if chip is programmed, offer inspection option
	if (!itemIdentifier.isEmpty()) {
		menuResponse->addRadialMenuItem(232, 3, "@space/space_interaction:memory_chip_analyze"); //"Analyze"
	}
}

int DroidProgrammingChipImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (!this->isASubChildOf(player->asSceneObject())) {
		return 0;
	}

	ZoneServer* server = player->getZoneServer();

	if (server == nullptr) {
		return 0;
	}

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == nullptr) {
		return 0;
	}

	if (selectedID == 230) { //SUI for burning a command to chip
		//double-check that the chip hasn't already been burned before continuing
		if (getDatapadSize() != 0) {
			return 0;
		}

		//generate the SUI
		ManagedReference<SuiListBox*> sui = new SuiListBox(player, SuiWindowType::DROID_CHIP_PROGRAMMING);

		sui->setCallback(new DroidProgrammingChipSuiCallback(server));
		sui->setPromptTitle("@sui:swg"); //Star Wars Galaxies
		sui->setPromptText("@space/droid_commands:droid_program_prompt"); //"Please select the command you wish to burn into this memory chip."
		sui->setUsingObject(this->asSceneObject());
		sui->setOkButton(true, "@ok");

		SkillManager* skillManager = server->getSkillManager();

		if (skillManager == nullptr) {
			return 0;
		}

		Vector<String> playerDroidCommands;

		skillManager->getPlayerDroidCommands(ghost, playerDroidCommands);

		for (int i = 0; i < playerDroidCommands.size(); ++i) {
			sui->addMenuItem("@space/droid_commands:" + playerDroidCommands.get(i)); //command name
		}

		//Send to player.
		ghost->addSuiBox(sui);
		player->sendMessage(sui->generateMessage());

		return 0;
	}

	if (selectedID == 232) { //analysis box SUI
		ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(player, SuiWindowType::NONE);
		suiBox->setPromptTitle("@sui:swg"); //Star Wars Galaxies
		suiBox->setPromptText("@space/droid_commands:" + getItemIdentifier() + "_description");

		player->sendMessage(suiBox->generateMessage());

		return 0;
	}

	return 0;
}

void DroidProgrammingChipImplementation::programChip(String& commandName, int programSize) {
	if (commandName.isEmpty() || programSize == 0)
		return;

	setItemIdentifier(commandName);
	setDatapadSize(programSize);
	setCustomObjectName("", true);
	setObjectName("@space/droid_commands:" + commandName + "_chipname", true);
}
