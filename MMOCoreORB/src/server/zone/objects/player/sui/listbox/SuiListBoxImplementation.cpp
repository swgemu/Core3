/*
 * SuiListBoxImplementation.cpp
 *
 *  Created on: 10/04/2010
 *      Author: victor
 */

#include "SuiListBox.h"

#include "server/zone/packets/ui/SuiCreatePageMessage.h"
#include "SuiListBoxMenuItem.h"

BaseMessage* SuiListBoxImplementation::generateMessage() {
	SuiCreatePageMessage* message = new SuiCreatePageMessage(boxID, "Script.listBox");

	//Declare Headers:
	addHeader("List.lstList", "SelectedRow");
	addHeader("bg.caption.lblTitle", "Text");

	/// This crashes the client, but is what makes the third button
	/// Report info
	//if(otherButton)
	//	addHeader("this", "otherPressed");

	//Set Body Options:
	addSetting("3", "bg.caption.lblTitle", "Text", promptTitle);
	addSetting("3", "Prompt.lblPrompt", "Text", promptText);

	if(cancelButton)
		addSetting("3", "btnCancel", "Text", cancelButtonText);

	if(okButton)
		addSetting("3", "btnOk", "Text", okButtonText);

	if(otherButton) {
		addSetting("3", "btnOther", "visible", "true");
		addSetting("3", "btnOther", "Enabled", "true");
		addSetting("3", "btnOther", "Text", otherButtonText);
	}

	//Data Container Option
	addSetting("1", "List.dataList", "", "");

	//Fill the above Data Container
	String tempVal = "";
	for (int i = 0; i < getMenuSize(); i++) {
		char tempStr[30];
		sprintf(tempStr, "%d", i);

		addSetting("4", "List.dataList", "Name", tempStr);

		sprintf(tempStr, "List.dataList.%d", i);

		tempVal = menuItems.get(i)->getOptionName();

		addSetting("3", tempStr, "Text", tempVal);
	}

	generateHeader(message);
	generateBody(message);
	generateFooter(message, 2);
	hasGenerated = true;

	return message;
}


