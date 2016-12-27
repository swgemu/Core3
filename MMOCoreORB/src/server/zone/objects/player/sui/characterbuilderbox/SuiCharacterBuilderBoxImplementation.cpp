/*
 * SuiCharacterBuilderBoxImplementation.cpp
 *
 *  Created on: Jun 6, 2010
 *      Author: crush
 */

#include "server/zone/objects/player/sui/characterbuilderbox/SuiCharacterBuilderBox.h"
#include "server/zone/packets/ui/SuiCreatePageMessage.h"

BaseMessage* SuiCharacterBuilderBoxImplementation::generateMessage() {

	SuiCreatePageMessage* message = new SuiCreatePageMessage(boxID, "Script.listBox");

	addHeader("this", "otherPressed");

	//Declare Headers:
	addHeader("List.lstList", "SelectedRow");
	addHeader("bg.caption.lblTitle", "Text");

	addHeader("this", "otherPressed");

	//Set Body Options:
	addSetting("3", "bg.caption.lblTitle", "Text", promptTitle);
	addSetting("3", "Prompt.lblPrompt", "Text", promptText);

	addSetting("3", "btnOther", "visible", "true");
	addSetting("3", "btnOther", "visible", "@refresh");

    addSetting("3","btnOther","Location","102,262");
    addSetting("3","btnOther","Size","81,19");
    addSetting("3","btnOther","ScrollExtent","81,19");

    addSetting("3","btnOk","Location","188,262");
    addSetting("3","btnOk","Size","81,19");
    addSetting("3","btnOk","ScrollExtent","81,19");

    addSetting("3","btnCancel","Size","81,19");
    addSetting("3","btnCancel","ScrollExtent","81,19");

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

	addSetting("3", "btnOther", "visible", "true");
	addSetting("3", "btnOther", "Text", otherButtonText);

	addSetting("3", "btnCancel", "Text", cancelButtonText);

	addSetting("3", "btnOk", "Text", okButtonText);

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
