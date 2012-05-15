/*
 * CreateMissileMessage.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef CREATEMISSILEMESSAGE_H_
#define CREATEMISSILEMESSAGE_H_

class CreateMissileMessage : public BaseMessage {
public:
	CreateMissileMessage() : BaseMessage() {
		insertShort(0x14);
		insertInt(0x721CF08B);  // CRC

		insertInt(0);
		insertLong(0);
		insertLong(0);
		insertInt(0);
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

#endif /* CREATEMISSILEMESSAGE_H_ */
