/*
 * ChatServerStatus.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef CHATSERVERSTATUS_H_
#define CHATSERVERSTATUS_H_

class ChatServerStatus : public BaseMessage {
public:
   ChatServerStatus(byte flag) : BaseMessage() {
		insertShort(0x02);
		insertInt(0x7102B15F);  // CRC

		insertByte(flag); //status. -0 offline  1 online



   }

};
#endif /* CHATSERVERSTATUS_H_ */
