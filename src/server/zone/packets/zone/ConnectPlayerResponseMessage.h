/*
 * ConnectPlayerResponseMessage.h
 *
 *  Created on: Nov 25, 2008
 *      Author: swgemu
 */

#ifndef CONNECTPLAYERRESPONSEMESSAGE_H_
#define CONNECTPLAYERRESPONSEMESSAGE_H_

class ConnectPlayerResponseMessage : public BaseMessage {
public:
   ConnectPlayerResponseMessage() : BaseMessage() {
		    insertShort(0x02);
	   		insertInt(0x6137556F);

	   		insertInt(0);


   }

};
#endif /* CONNECTPLAYERRESPONSEMESSAGE_H_ */
