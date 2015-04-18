/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CANCELTICKETRESPONSEMESSAGE_H_
#define CANCELTICKETRESPONSEMESSAGE_H_

class CancelTicketResponseMessage : public BaseMessage {
public:
   CancelTicketResponseMessage(uint32 ticketid, bool success) : BaseMessage() {
		insertShort(0x03);
		insertInt(0xD6FBF318);  // CRC

		if (success == true)
			insertInt(0);
		else
			insertInt(1);

		insertInt(ticketid); //ticketid.



   }

};

#endif /*CANCELTICKETRESPONSEMESSAGE_H_*/

