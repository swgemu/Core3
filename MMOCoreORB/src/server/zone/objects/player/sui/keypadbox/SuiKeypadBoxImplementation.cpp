/*
 * SuiKeypadBoxImplementation.cpp
 *
 *  Created on: 09/06/2010
 *  Updated on: 09/03/2014
 *      Author: crush
 */

#include "server/zone/objects/player/sui/keypadbox/SuiKeypadBox.h"
#include "server/zone/objects/scene/SceneObject.h"

BaseMessage* SuiKeypadBoxImplementation::generateMessage() {
	//Yes, I hardcoded this for now. Get off me.
	BaseMessage* message = new BaseMessage();
	message->insertShort(0x02);
	message->insertInt(0xD44B7259); //SuiCreatePageMessage
	message->insertInt(boxID); //Page Id
	message->insertAscii("Script.keyPad"); //Page name
	message->insertInt(0x02); //how many commands are being sent

	message->setCompression(true);

	message->insertByte(0x05); //SubscribeToEvent SuiCommand
	message->insertInt(0x00); //The number of wide parameters (unicode)
	message->insertInt(0x07); //The number of narrow parameters (ascii)
	message->insertShort(0x00); //parent (parent is an empty string because we are targeting the root UIWidget)
	message->insertShort(0x01); //eventType (notice the next byte is actually part of this string but this is more efficient than writing out a string here.
	message->insertByte(0x09); //NotifyAccept event type
	message->insertAscii("onKeypadPressed"); //This doesn't get sent back to the server, so I assume it is some kind of client side hook. Can be arbitrary or blank.

	//subscribeToPropertyForEvent - these are the properties we want the value for.
	message->insertAscii("result.numberBox"); //This is the value of the code entered. It will be your first unicode string returned.
	message->insertAscii("LocalText");
	message->insertAscii("buttonEnter");
	message->insertAscii("ButtonPressed"); //The value of the ButtonPressed property on the enter button holds the actual value of the pressed button.
	//ButtonPressed will either be "slice", "keycard", or "enter"


	//This subscribes to the NotifyClosed event
	message->insertByte(0x05); //see above
	message->insertInt(0x00);
	message->insertInt(0x03);
	message->insertShort(0x00); //string 1
	message->insertShort(0x01); //string 2 + byte below
	message->insertByte(0x0A); //NotifyCancel
	message->insertAscii("onKeypadPressed"); //string 3
	//We don't need to subscribe to any properties. We just want to be notified that the keypad closed so we can kill the session.
	//message->insertAscii("result.numberBox");
	//message->insertAscii("LocalText");

	message->insertLong(usingObject.get()->getObjectID());
	message->insertFloat(forceCloseDistance);
	message->insertLong(0);

	hasGenerated = true;

	return message;
}
