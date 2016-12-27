/*
 * CreateNebulaLightningMessage.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef CREATENEBULALIGHTNINGMESSAGE_H_
#define CREATENEBULALIGHTNINGMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class CreateNebulaLightningMessage : public BaseMessage {
public:
	CreateNebulaLightningMessage() : BaseMessage() {
		insertShort(0x11);
		insertInt(0x65F27987);  // CRC

		insertShort(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
   }

};

#endif /* CREATENEBULALIGHTNINGMESSAGE_H_ */
