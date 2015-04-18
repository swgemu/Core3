/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef APPENDCOMMENTSRESPONSEMESSAGE_H_
#define APPENDCOMMENTSRESPONSEMESSAGE_H_

class AppendCommentsResponseMessage : public BaseMessage {
public:
   AppendCommentsResponseMessage(uint32 ticketid, bool success) : BaseMessage() {
		insertShort(0x03);
		insertInt(0xA04A3ECA);  // CRC

		if (success == true)
			insertInt(0);
		else
			insertInt(1);

		insertInt(ticketid); //ticketid.


   }

};

#endif /*APPENDCOMMENTSRESPONSEMESSAGE_H_*/

