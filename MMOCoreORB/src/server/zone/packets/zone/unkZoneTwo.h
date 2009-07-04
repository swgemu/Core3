/*
 * unkZoneTwo.h
 *
 *  Created on: Nov 25, 2008
 *      Author: swgemu
 */

#ifndef UNKZONETWO_H_
#define UNKZONETWO_H_

class unkZoneTwo : public BaseMessage {
public:
	unkZoneTwo() : BaseMessage() {
		insertShort(0x03);
		insertInt(0xE97AB594);
		insertLong(0);
		insertInt(0);
	}

};
#endif /* UNKZONETWO_H_ */
