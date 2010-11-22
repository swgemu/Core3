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
   CreateTicketResponseMessage(int returnCode) : BaseMessage() {
		insertShort(0x09);
		insertInt(0x550A407A);  // CRC

		insertInt(int returnCode);
};

#endif /* CREATETICKETRESPONSEMESSAGE_H_ */
