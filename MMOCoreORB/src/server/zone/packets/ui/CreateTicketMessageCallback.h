/*
 * CreateTicketMessageCallback.h
 *
 *  Created on: Nov 22, 2010
 *      Author: crush
 */

#ifndef CREATETICKETMESSAGECALLBACK_H_
#define CREATETICKETMESSAGECALLBACK_H_

#include "server/zone/packets/MessageCallback.h"
#include "server/zone/managers/holocron/HolocronManager.h"

class CreateTicketMessageCallback : public MessageCallback {
	String playerName;
	uint32 categoryId;
	uint32 subCategoryId;

	UnicodeString ticketBody;
public:
	CreateTicketMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server), categoryId(0), subCategoryId(0) {
	}

	void parse(Message* message) {
		message->parseAscii(playerName);
		categoryId = message->parseInt();
		subCategoryId = message->parseInt();

		message->parseUnicode(ticketBody);
	}

	void run() {
		HolocronManager* holocronManager = server->getHolocronManager();
		holocronManager->submitTicket(client, ticketBody);
	}
};

#endif /* CREATETICKETMESSAGECALLBACK_H_ */
