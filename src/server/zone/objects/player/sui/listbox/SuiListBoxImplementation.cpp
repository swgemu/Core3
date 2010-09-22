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
	//SuiCreatePageMessage* message = new SuiCreatePageMessage();
	//return message;

	if(otherButton) {
		addHeader("this", "otherPressed");
	}

	//Declare Headers:
	addHeader("List.lstList", "SelectedRow");
	addHeader("bg.caption.lblTitle", "Text");

	/// This crashes the client, but is what makes the third button
	/// Report info
	if(otherButton) {
		addHeader("this", "otherPressed");
	}

	//Set Body Options:
	addSetting("3", "bg.caption.lblTitle", "Text", promptTitle);
	addSetting("3", "Prompt.lblPrompt", "Text", promptText);

	if(otherButton) {
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
	}

	if(cancelButton) {
		addSetting("3", "btnCancel", "Text", "@cancel");
	} else {
		addSetting("3", "btnCancel", "visible", "false");
	}

	if(okButton) {
		addSetting("3", "btnOk", "Text", "@ok");
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

	if(otherButton && otherButtonText.indexOf('@') == 0) {
		addSetting("3", "btnOther", "visible", "true");
		addSetting("3", "btnOther", "Text", otherButtonText);
	}

	if(cancelButton && cancelButtonText.indexOf('@') == 0) {
		addSetting("3", "btnCancel", "Text", cancelButtonText);
	}

	if(okButton && okButtonText.indexOf('@') == 0) {
		addSetting("3", "btnOk", "Text", okButtonText);
	}

	generateHeader(message);
	generateBody(message);
	generateFooter(message);
	hasGenerated = true;

	return message;
}


