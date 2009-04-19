/*
 * ConnectionServerMessage.h
 *
 *  Created on: Nov 25, 2008
 *      Author: swgemu
 */
#ifndef CONNECTIONSERVERTESTMESSAGE_H_
#define CONNECTIONSERVERTESTMESSAGE_H_

class ConnectionServerTestMessage : public BaseMessage {
public:
   ConnectionServerTestMessage() : BaseMessage() {
		    insertShort(0x02);
	   		insertInt(0x0E20D7E9);

	   		insertAscii("ConnectionServer:1348");


   }

};

#endif /*CONNECTIONSERVERTESTMESSAGE_H__*/



