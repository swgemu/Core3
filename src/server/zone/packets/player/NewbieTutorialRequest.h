/*
 * NewbieTutorialRequest.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef NEWBIETUTORIALREQUEST_H_
#define NEWBIETUTORIALREQUEST_H_

#include "../MessageCallback.h"
/* Valid action strings found:
 * openCharacterSheet
 * closeCharacterSheet
 * openInventory
 * closeInventory
 * openStatMigration
 * closeStatMigration
 * openHolocron
 * closeHolocron
 * zoomCamera
 * overlayMap
 * changeLookAtTarget
 * changeMouseMode
 * equipToolbar
 */
class NewbieTutorialRequest : public BaseMessage {
public:
   /**
    * Sets a trigger on certain actions.
    *
    * The client can have multiple triggers set at once.
    *
    * Once a trigger is activated, a NewbieTutorialRequest
    * packet is sent echoing the request and the trigger is reset.
    *
    * NOTE: there is a bug in the client which causes the
    *       closeInventory trigger to never reset
    *
    * See list above for valid action strings
    *
    * @param action action to be monitored
    */
   NewbieTutorialRequest(const String& action) : BaseMessage() {
		insertShort(0x02);
		insertInt(0x90DD61AF);  // CRC

		insertAscii(action); //try openContainer openStatMigration etc.
   }

};

/**
 * Sends clientReady on zone.
 * Echos string sent by NewbieTutorialRequest, when action is triggered.
 */
class NewbieTutorialResponseCallback : public MessageCallback {
	String response;
public:
	NewbieTutorialResponseCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
		message->parseAscii(response);
	}

	void run() {
	}

};

#endif /* NEWBIETUTORIALREQUEST_H_ */
