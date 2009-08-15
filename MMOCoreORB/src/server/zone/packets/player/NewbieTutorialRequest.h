/*
 * NewbieTutorialRequest.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef NEWBIETUTORIALREQUEST_H_
#define NEWBIETUTORIALREQUEST_H_

#include "../MessageCallback.h"

class NewbieTutorialRequest : public BaseMessage {
public:
   NewbieTutorialRequest(const String& test) : BaseMessage() {
		insertShort(0x02);
		insertInt(0x90DD61AF);  // CRC

		insertAscii(test); //try openContainer openStatMigration etc.
   }

};

class NewbieTutorialResponseCallback : public MessageCallback {
	String response;
public:
	NewbieTutorialResponseCallback(ZoneClientSession* client, ZoneProcessServerImplementation* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
		message->parseAscii(response);
	}

	void run() {

	}

};

#endif /* NEWBIETUTORIALREQUEST_H_ */
