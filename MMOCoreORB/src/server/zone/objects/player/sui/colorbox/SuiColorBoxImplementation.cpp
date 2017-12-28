/*
 * SuiColorBoxImplementation.cpp
 *
 *  Created on: 10/06/2010
 *      Author: victor
 */

#include <algorithm>

#include "engine/core/ManagedReference.h"
#include "engine/core/ManagedWeakReference.h"
#include "server/zone/objects/player/sui/colorbox/SuiColorBox.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/ui/SuiCreatePageMessage.h"
#include "system/lang/String.h"
#include "system/lang/StringBuffer.h"

namespace engine {
namespace service {
namespace proto {
class BaseMessage;
}  // namespace proto
}  // namespace service
}  // namespace engine

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

