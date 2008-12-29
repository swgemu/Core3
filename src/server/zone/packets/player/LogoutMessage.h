/*
 * LogoutMessage.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef LOGOUTMESSAGE_H_
#define LOGOUTMESSAGE_H_

class LogoutMessage : public BaseMessage {
public:
   LogoutMessage() : BaseMessage() {
		insertShort(0x01);
		insertInt(0x42FD19DD);  // CRC

		//Logs out the player.
   }

};
#endif /* LOGOUTMESSAGE_H_ */
