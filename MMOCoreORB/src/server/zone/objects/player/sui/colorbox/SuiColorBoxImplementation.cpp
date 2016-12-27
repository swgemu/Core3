/*
 * SuiColorBoxImplementation.cpp
 *
 *  Created on: 10/06/2010
 *      Author: victor
 */

#include "server/zone/objects/player/sui/colorbox/SuiColorBox.h"

BaseMessage* SuiColorBoxImplementation::generateMessage() {
	SuiCreatePageMessage* message = new SuiCreatePageMessage(boxID, "Script.ColorPicker");

	// Headers.
	addHeader("ColorPicker", "SelectedIndex");
	addHeader("bg.caption.lblTitle", "Text");

	StringBuffer id;
	id << usingObject.get()->getObjectID();

	//Set Body Options:
	addSetting("3", "bg.caption.lblTitle", "Text", "@base_player:swg");
	addSetting("3", "ColorPicker", "TargetRangeMax", "500");
	addSetting("3", "ColorPicker", "TargetNetworkId", id.toString().toCharArray());
	addSetting("3", "ColorPicker", "TargetVariable", variable.toCharArray());

	setHandlerText("handleColorizeFrame");

	//Generate Packet:
	generateHeader(message);
	generateBody(message);
	generateFooter(message);
	hasGenerated = true;

	return message;
}

