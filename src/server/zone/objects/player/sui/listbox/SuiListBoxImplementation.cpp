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
	//addHeader("Prompt.lblPrompt", "Text"); //note: the list ui script doesnt need this...not sure why

	//Set Body Options:
	addSetting("3", "bg.caption.lblTitle", "Text", promptTitle);
	addSetting("3", "Prompt.lblPrompt", "Text", promptText);

	switch(type) {
	case HANDLESTATUSUI:
		if (!backButton)
			addSetting("3", "btnCancel", "Text", cancelButtonText);
		else
			addSetting("3", "btnCancel", "Text", backButtonText);
		addSetting("3", "btnOk", "Text", "@refresh");
		break;
	case HANDLEDESTROYUI:
		addSetting("3", "btnCancel", "Text", "@no");
		addSetting("3", "btnOk", "Text", "@yes");
		break;
	default:
		if (cancelButton)
			addSetting("3", "btnCancel", "Text", cancelButtonText);
		else if (backButton)
			addSetting("3", "btnCancel", "Text", backButtonText);
		else {
			addSetting("3", "btnCancel", "Enabled", "False");
			addSetting("3", "btnCancel", "Visible", "False");
		}

		if(okButton)
			addSetting("3", "btnOk", "Text", okButtonText);
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

	//Generate Packet:
	switch(type) {
	case HANDLESTATUSUI:
		generateHeader(message, "handleStatusUi");
		break;
	case HANDLEDESTROYUI:
		generateHeader(message, "handleDestroyUi");
		break;
	default:
		generateHeader(message, "msgSelected");
	}
	generateBody(message);
	generateFooter(message);
	hasGenerated = true;

	return message;
}


