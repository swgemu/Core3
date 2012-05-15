/*
 * IsFlattenedTheaterMessage.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef ISFLATTENEDTHEATERMESSAGE_H_
#define ISFLATTENEDTHEATERMESSAGE_H_

class IsFlattenedTheaterMessage : public BaseMessage {
public:
	IsFlattenedTheaterMessage() : BaseMessage() {
		insertShort(0x03);
		insertInt(0x4EB0B06A);  // CRC

		insertLong(0); //Object id of the flattened theater?
		insertByte(0); //is it flattened? is it not?


   }

};
#endif /* ISFLATTENEDTHEATERMESSAGE_H_ */
