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
#endif /* NEWTICKETACTIVITYRESPONSEMESSAGE_H_ */
