/*
 * CreateProjecticeMessage.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef CREATEPROJECTICEMESSAGE_H_
#define CREATEPROJECTICEMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class CreateProjectileMessage : public BaseMessage {
public:
	CreateProjectileMessage() : BaseMessage() {
		insertShort(0x12);
		insertInt(0xB88AF9A5);  // CRC

		insertShort(0);
		insertByte(0);
		insertByte(0);
		insertByte(0);
		insertShort(0);
		insertShort(0);
		insertShort(0);
		insertShort(0);
		insertShort(0);
		insertShort(0);
		insertInt(0);
   }

};

#endif /* CREATEPROJECTICEMESSAGE_H_ */
