/*
 * SuiInputBoxImplementation.cpp
 *
 *  Created on: 10/06/2010
 *      Author: victor
 */

#include "SuiInputBox.h"

BaseMessage* SuiInputBoxImplementation::generateMessage() {
	SuiCreatePageMessage* message = new SuiCreatePageMessage(boxID, "Script.inputBox");

	//Declare Headers:
	if (isFilterBox()) {
		addHeader("Prompt.lblPrompt", "Text");
		addHeader("bg.caption.lblTitle", "Text");
		addHeader("txtInput", "MaxLength");
		addHeader("txtInput", "LocalText");
	} else {
		addHeader("txtInput", "LocalText");
		addHeader("cmbInput", "SelectedText");
	}

	//Declare Body Settings:
	addSetting("3", "Prompt.lblPrompt", "Text", promptText);
	addSetting("3", "bg.caption.lblTitle", "Text", promptTitle);

	if (cancelButton) {
		addSetting("3", "btnCancel", "Text", "@cancel");
	} else {
		addSetting("3", "btnCancel", "Enabled", "False");
		addSetting("3", "btnCancel", "Visible", "False");
	}

	addSetting("3", "btnOk", "Text", "@ok");

	addSetting("3", "txtInput", "Enabled", "true");
	addSetting("3", "txtInput", "Visible", "true");

	addSetting("3", "cmbInput", "Enabled", "false");
	addSetting("3", "cmbInput", "Visible", "false");

	addSetting("3", "txtInput", "MaxLength", String::valueOf(maxInputSize));

	if (isFilterBox()) {
		if (defaultInput != "") {
			addSetting("3", "txtInput", "Text", defaultInput);
		} else {
			addSetting("3", "txtInput", "Text", "");
		}
	} else {
		addSetting("3", "cmbInput", "MaxLength", String::valueOf(maxInputSize));
	}

	//Generate Packet:
	if (isFilterBox()) {
		setHandlerText("handleFilterInput");
		generateHeader(message);
	} else {
		setHandlerText("handleAutoLevelSelect");
		generateHeader(message);
	}

	generateBody(message);
	generateFooter(message);
	hasGenerated = true;

	return message;
}

