/*
 * CreateTicketResponseMessage.h
 *
 *  Created on: Nov 22, 2008
 *      Author: swgemu
 */

#ifndef CREATETICKETRESPONSEMESSAGE_H_
#define CREATETICKETRESPONSEMESSAGE_H_


class CreateTicketResponseMessage : public BaseMessage {
public:
   CreateTicketResponseMessage(bool success) : BaseMessage() {
		insertShort(0x09);
		insertInt(0x550A407A);  // CRC

		//The structure is right, I just don't know if its ticketid or success flag.
		if (success == true)
			insertInt(0);
		else
			insertInt(1);
	   }

};

#endif /* CREATETICKETRESPONSEMESSAGE_H_ */
