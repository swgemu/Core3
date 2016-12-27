/*
 * ConGenericMessage.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef CONGENERICMESSAGE_H_
#define CONGENERICMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class ConGenericMessage : public BaseMessage {
public:
   ConGenericMessage(const String& msg) : BaseMessage() {
		insertShort(0x03);
		insertInt(0x08C5FC76);  // CRC

		insertAscii(msg); //Message to show in spatial chat box
		insertInt(0); //??

		setCompression(true);
   }

};
#endif /* CONGENERICMESSAGE_H_ */
