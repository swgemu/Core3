#include "CharacterBuilderTerminal.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/sui/characterbuilderbox/SuiCharacterBuilderBox.h"

#include "server/zone/templates/tangible/CharacterBuilderTerminalTemplate.h"
#include "CharacterBuilderMenuNode.h"

void CharacterBuilderTerminalImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	CharacterBuilderTerminalTemplate* terminalData = dynamic_cast<CharacterBuilderTerminalTemplate*>(templateData);

	if (terminalData == NULL)
		return;

	rootNode = terminalData->getItemList();

	//info("loaded " + String::valueOf(itemList.size()));
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
	if (rootNode == NULL) {
		player->sendSystemMessage("There was an error initializing the menu for this character builder terminal. Sorry for the inconvenience.");
		return;
	}

	SuiCharacterBuilderBox* sui = new SuiCharacterBuilderBox(player, rootNode);
	sui->setUsingObjectID(getObjectID());

	player->sendMessage(sui->generateMessage());
	player->addSuiBox(sui);
}

