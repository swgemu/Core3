#include "CharacterBuilderTerminal.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"

#include "server/zone/templates/tangible/CharacterBuilderTerminalTemplate.h"

void CharacterBuilderTerminalImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	CharacterBuilderTerminalTemplate* terminalData = dynamic_cast<CharacterBuilderTerminalTemplate*>(templateData);

	if (terminalData == NULL)
		return;

	itemList = terminalData->getItemList();

	info("loaded " + String::valueOf(itemList.size()));
}

void CharacterBuilderTerminalImplementation::initializeTransientMembers() {
	TerminalImplementation::initializeTransientMembers();

	setLoggingName("CharacterBuilderTerminal");
}

int CharacterBuilderTerminalImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	//System::out << "entering start terminal radial call" << endl;

	if (selectedID != 20) // not use object
		return 1;

	sendInitialChoices(player);

	return 0;
}

void CharacterBuilderTerminalImplementation::sendInitialChoices(PlayerCreature* player) {
	SuiListBox* listBox = new SuiListBox(player, SuiWindowType::CHARACTERBUILDERITEMSELECT);
	listBox->setPromptTitle("Character Builder");
	listBox->setPromptText("Provided below are items which the developers deem necessary for testing. Please select the items you require:");
	listBox->setUsingObjectID(getObjectID());

	for (int i = 0; i < itemList.size(); ++i) {
		VectorMapEntry<uint32, String> entry = itemList.elementAt(i);
		listBox->addMenuItem(entry.getValue(), entry.getKey());
	}

	player->sendMessage(listBox->generateMessage());
	player->addSuiBox(listBox);
}

