/*
 * NewTicketActivityResponseMessage.h
 *
 *  Created on: Nov 25, 2008
 *      Author: swgemu
 */

#ifndef NEWTICKETACTIVITYRESPONSEMESSAGE_H_
#define NEWTICKETACTIVITYRESPONSEMESSAGE_H_

class NewTicketActivityResponseMessage : public BaseMessage {
public:
   NewTicketActivityResponseMessage(byte flag, uint32 ticketid) : BaseMessage() {
		insertShort(0x03);
		insertInt(0x6EA42D80);  // CRC


		insertByte(flag); //??
		insertInt(ticketid); //Probably the ticket id.


   }

};

class NewTicketActivityMessageCalback : public MessageCallback {
	int ticketID;
public:
	NewTicketActivityMessageCalback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
		ticketID = message->parseInt();
	}

	void run() {
		NewTicketActivityResponseMessage* ntar = new NewTicketActivityResponseMessage(0, ticketID);
		client->sendMessage(ntar);
	}
};

#endif /* NEWTICKETACTIVITYRESPONSEMESSAGE_H_ */
