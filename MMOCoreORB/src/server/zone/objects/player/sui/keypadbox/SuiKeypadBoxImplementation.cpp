/*
 * SuiKeypadBoxImplementation.cpp
 *
 *  Created on: 09/06/2010
 *      Author: xyborn
 */

#include "SuiKeypadBox.h"

BaseMessage* SuiKeypadBoxImplementation::generateMessage() {
	SuiCreatePageMessage* message = new SuiCreatePageMessage(boxID, "Script.keyPad");

	//Generate Packet:
	generateHeader(message);
	generateBody(message);
	generateFooter(message);
	hasGenerated = true;

	return message;
}
