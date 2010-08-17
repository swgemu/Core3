/*
 * SuiCharacterBuilderBoxImplementation.cpp
 *
 *  Created on: Jun 6, 2010
 *      Author: crush
 */


#include "SuiCharacterBuilderBox.h"
#include "server/zone/packets/ui/SuiCreatePageMessage.h"
#include "server/zone/objects/player/sui/listbox/SuiListBoxMenuItem.h"

BaseMessage* SuiCharacterBuilderBoxImplementation::generateMessage() {
	SuiCreatePageMessage* message = new SuiCreatePageMessage(boxID, "Script.listBox");

	//Declare Headers:
	addHeader("List.lstList", "SelectedRow");
	addHeader("bg.caption.lblTitle", "Text");

	//Set Body Options:
	addSetting("3", "bg.caption.lblTitle", "Text", promptTitle);
	addSetting("3", "Prompt.lblPrompt", "Text", promptText);

	if (currentNode->hasParentNode())
		addSetting("3", "btnCancel", "Text", "@back");
	else
		addSetting("3", "btnCancel", "Text", "@cancel");

	addSetting("3", "btnOk", "Text", "@ok");

	//Data Container Option
	addSetting("1", "List.dataList", "", "");

	//Fill the above Data Container
	for (int i = 0; i < currentNode->getChildNodeSize(); ++i) {
		CharacterBuilderMenuNode* node = currentNode->getChildNodeAt(i);

		if (node == NULL)
			continue;

		addSetting("4", "List.dataList", "Name", String::valueOf(i));
		addSetting("3", "List.dataList." + String::valueOf(i), "Text", node->getDisplayName());
	}

	setHandlerText("msgSelected");
	generateHeader(message);
	generateBody(message);
	generateFooter(message);

	hasGenerated = true;

	return message;
}

CharacterBuilderMenuNode* SuiCharacterBuilderBoxImplementation::getCurrentNode() {
	return currentNode;
}

void SuiCharacterBuilderBoxImplementation::setCurrentNode(CharacterBuilderMenuNode* node) {
	currentNode = node;
}
