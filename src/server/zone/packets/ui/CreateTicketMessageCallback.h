/*
 * CreateTicketMessageCallback.h
 *
 *  Created on: Nov 22, 2010
 *      Author: crush
 */

#ifndef CREATETICKETMESSAGECALLBACK_H_
#define CREATETICKETMESSAGECALLBACK_H_


#include "../MessageCallback.h"
#include "server/zone/packets/ui/CreateTicketResponseMessage.h"

class CreateTicketMessageCallback : public MessageCallback {
	String playerName;
	uint32 categoryId;
	uint32 subCategoryId;

	UnicodeString ticketBody;
public:
	CreateTicketMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {
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
