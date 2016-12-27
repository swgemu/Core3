/*
 * DogfightTauntPlayerMessage.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef DOGFIGHTTAUNTPLAYERMESSAGE_H_
#define DOGFIGHTTAUNTPLAYERMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class DogfightTauntPlayerMessage : public BaseMessage {
public:
	DogfightTauntPlayerMessage() : BaseMessage() {
		insertShort(0x09);
		insertInt(0xCA2A548B);  // CRC

		insertLong(0);
		insertInt(0);


   }

};
#endif /* DOGFIGHTTAUNTPLAYERMESSAGE_H_ */
