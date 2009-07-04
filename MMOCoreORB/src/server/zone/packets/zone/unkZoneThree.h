/*
 * unkZoneThree.h
 *
 *  Created on: Nov 25, 2008
 *      Author: swgemu
 */

#ifndef UNKZONETHREE_H_
#define UNKZONETHREE_H_

class unkZoneThree : public BaseMessage {
public:
	unkZoneThree() : BaseMessage() {
		insertShort(0x03);
		insertInt(0xF8C275B0);
		insertLong(0);
		insertInt(0);

	}

};
#endif /* UNKZONETHREE_H_ */
