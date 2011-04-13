/*
 * DebugTransformMessage.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef DEBUGTRANSFORMMESSAGE_H_
#define DEBUGTRANSFORMMESSAGE_H_

class DebugTransformMessage : public BaseMessage {
public:
	DebugTransformMessage() : BaseMessage() {
		insertShort(0x09);
		insertInt(0xD0CDAA62);  // CRC

		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertLong(0);



   }

};
#endif /* DEBUGTRANSFORMMESSAGE_H_ */
