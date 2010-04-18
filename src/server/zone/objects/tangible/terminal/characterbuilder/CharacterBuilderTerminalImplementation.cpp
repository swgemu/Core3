#include "CharacterBuilderTerminal.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"

void CharacterBuilderTerminalImplementation::loadTemplateData(LuaObject* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	//Maybe just have one large Items field instead of fields for each type of item?
	//Maybe make them multi dimensional?
	LuaObject deedsList = templateData->getObjectField("deedsList");

	//Ensure the list has an even number of elements
	if (deedsList.getTableSize() % 2 == 0) {
		for (int i = 1; i <= deedsList.getTableSize(); i+=2) {
			String itemName = deedsList.getStringAt(i);
			uint32 itemCRC = deedsList.getStringAt(i+1).hashCode();
			itemList.put(itemCRC, itemName);
		}
	} else {
		info("Elements in deedsList must be of an even order.", true);
	}

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

