/*
 * SuiKeypadBoxImplementation.cpp
 *
 *  Created on: 09/06/2010
 *      Author: xyborn
 */

#include "SuiKeypadBox.h"
#include "server/zone/objects/scene/SceneObject.h"

BaseMessage* SuiKeypadBoxImplementation::generateMessage() {
	//Yes, I hardcoded this for now. Get off me.
	BaseMessage* message = new BaseMessage();
	message->insertShort(0x02);
	message->insertInt(0xD44B7259); //SuiCreatePageMessage
	message->insertInt(boxID); //Box ID
	message->insertAscii("Script.keyPad");
	message->insertInt(0x02);

	message->setCompression(true);

	message->insertByte(0x05);
	message->insertInt(0x00);
	message->insertInt(0x05);
	message->insertShort(0x00);
	message->insertShort(0x01);
	message->insertByte(0x09);
	message->insertAscii("onKeypadPressed");
	message->insertAscii("result.numberBox");
	message->insertAscii("LocalText");

	message->insertByte(0x05);
	message->insertInt(0x00);
	message->insertInt(0x05);
	message->insertShort(0x00);
	message->insertShort(0x01);
	message->insertByte(0x0A);
	message->insertAscii("onKeypadPressed");
	message->insertAscii("result.numberBox");
	message->insertAscii("LocalText");

	message->insertLong(usingObject.get()->getObjectID());
	message->insertFloat(forceCloseDistance);
	message->insertLong(0);

	hasGenerated = true;

	return message;
}
