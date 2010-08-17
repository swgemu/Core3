/*
 * SuiTransferBoxImplementation.cpp
 *
 *  Created on: 09/06/2010
 *      Author: victor
 */

#include "SuiTransferBox.h"

BaseMessage* SuiTransferBoxImplementation::generateMessage() {
	SuiCreatePageMessage* message = new SuiCreatePageMessage(boxID, "Script.transfer");

	//Declare Headers:
	addHeader("transaction.txtInputFrom", "Text");
	addHeader("transaction.txtInputTo", "Text");

	//Set Body Options:
	addSetting("3", "bg.caption.lblTitle", "Text", promptTitle);
	addSetting("3", "Prompt.lblPrompt", "Text", promptText);

	addSetting("3", "transaction.lblFrom", "Text", lblFrom);
	addSetting("3", "transaction.lblTo", "Text", lblTo);

	addSetting("3", "transaction.lblStartingFrom", "Text", lblStartingFrom);
	addSetting("3", "transaction.lblStartingTo", "Text", lblStartingTo);

	addSetting("3", "transaction.txtInputFrom", "Text", lblInputFrom);
	addSetting("3", "transaction.txtInputTo", "Text", lblInputTo);

	addSetting("3", "transaction", "ConversionRatioFrom", convertRatioFrom);
	addSetting("3", "transaction", "ConversionRatioTo", convertRatioTo);

	setHandlerText("msgPayMaintenance");

	//Generate Packet:
	generateHeader(message);
	generateBody(message);
	generateFooter(message);
	hasGenerated = true;

	return message;
}

void SuiTransferBoxImplementation::addFrom(const String& from,
		const String& startingFrom, const String& inputFrom, const String& rFrom) {

	lblFrom = from;
	lblStartingFrom = startingFrom;
	lblInputFrom = inputFrom;
	convertRatioFrom = rFrom;

}

void SuiTransferBoxImplementation::addTo(const String& to,
		const String& startingTo, const String& inputTo, const String& rTo) {

	lblTo = to;
	lblStartingTo = startingTo;
	lblInputTo = inputTo;
	convertRatioTo = rTo;
}
