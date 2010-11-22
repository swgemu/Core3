/*
 * VerifyPlayerNameResponseMessage.h
 *
 *  Created on: Nov 25, 2008
 *      Author: swgemu
 */

#ifndef VERIFYPLAYERNAMERESPONSEMESSAGE_H_
#define VERIFYPLAYERNAMERESPONSEMESSAGE_H_

class VerifyPlayerNameResponseMessage : public BaseMessage {
public:
   VerifyPlayerNameResponseMessage(bool success) : BaseMessage() {
		insertShort(0x09);
		insertInt(0xF4C498FD);  //VerifyPlayerNameResponseMessage
		insertByte((byte) success); //Success or fail
		insertInt(1);
   }

};
#endif /* VERIFYPLAYERNAMERESPONSEMESSAGE_H_ */
