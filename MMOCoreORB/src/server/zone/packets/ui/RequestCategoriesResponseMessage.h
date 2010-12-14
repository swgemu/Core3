/*
 * RequestCategoriesResponseMessage.h
 *
 *  Created on: Nov 25, 2008
 *      Author: swgemu
 */

#ifndef REQUESTCATEGORIESRESPONSEMESSAGE_H_
#define REQUESTCATEGORIESRESPONSEMESSAGE_H_

//#include "server/zone/managers/holocron/BugCategory.h"
#include "server/zone/managers/holocron/HolocronManager.h"
#include "server/zone/packets/MessageCallback.h"

class RequestCategoriesResponseMessage : public BaseMessage {
public:
   RequestCategoriesResponseMessage(SortedVector<BugCategory>* categories) : BaseMessage() {
		insertShort(0x03);
		insertInt(0x61148FD4);  // CRC

		insertInt(0); //??
		insertInt(categories->size());

		for (int i = 0; i < categories->size(); ++i) {
			BugCategory* category = &categories->get(i);

			if (category == NULL)
				continue;

			category->insertToMessage(this);
		}

		setCompression(true);
   }
};

class RequestCategoriesMessageCallback : public MessageCallback {
	String language;

public:
	RequestCategoriesMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
		message->parseAscii(language);
	}

	void run() {
		HolocronManager* holocronManager = server->getHolocronManager();
		holocronManager->sendRequestCategoriesResponseTo(client);
	}
};

#endif /* REQUESTCATEGORIESRESPONSEMESSAGE_H_ */
