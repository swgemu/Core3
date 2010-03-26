
#ifndef GETTICKETSRESPONSEMESSAGE_H_
#define GETTICKETSRESPONSEMESSAGE_H_

class GetTicketsResponseMessage : public BaseMessage {
	int ticketCount;
public:
   GetTicketsResponseMessage() : BaseMessage() {
	   ticketCount = 0;
		insertShort(0x03);
		insertInt(0xBB567F98);  // CRC

		insertInt(0); //?
		insertInt(0); //?

		insertInt(0); //Ticket Count



   }

   void addTicket(const String& name, const UnicodeString& body, uint32 ticketid, uint64 timeStamp, bool read, bool open) {
			    insertInt(0); //??
	   			insertInt(0); //??
	   			insertAscii(name); //name
	   			insertUnicode(body); //text
	   			insertAscii(""); //??
	   			insertInt(ticketid); //ticket id
	   			insertLong(timeStamp); //time
	   			if (read == true)
	   				insertByte(0); //read  0 read  1 unread
	   			else
	   				insertByte(1);

	   			if (open == true)
	   				insertByte(0); //status 0 open 1 closed
	   			else
	   				insertByte(1);

	   			updateCount();
   }

   void updateCount() {
  	   insertInt(15, ticketCount++);
     }
};

#endif /*GETTICKETSRESPONSEMESSAGE_H__*/

